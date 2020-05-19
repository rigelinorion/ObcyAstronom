#include "joystick.h"
#include "udpserver.h"
#include "camera.h"
#include "settings.h"

uint8_t speed = 9;
uint8_t JConnected = 0;
extern _Bool recording_now;

int joy_fd, *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
char *button=NULL, name_of_joystick[80];
struct js_event js;

extern int DEBUG;
extern int serial_port;
extern serial_busy;
int last_command = KEY_NONE;

extern fsetting;
extern int thread_camera;
extern pthread_t id_camera;

char speeds1[10][16] 	= {":I1900F00\r", ":I1C80700\r", ":I1F90000\r", ":I17D0000\r", ":I13E0000\r",":I11F0000\r",":I1100000\r", ":I19F0000\r", ":I16A0000\r", ":I1500000\r"};
char speeds2[10][16] 	= {":I2900F00\r", ":I2C80700\r", ":I2F90000\r", ":I27D0000\r", ":I23E0000\r",":I21F0000\r",":I2100000\r", ":I29F0000\r", ":I26A0000\r", ":I2500000\r"};
char dirs_left[10][16] 	= {":G110\r", ":G110\r", ":G110\r", ":G110\r", ":G110\r", ":G110\r", ":G110\r", ":G130\r", ":G130\r", ":G130\r"};
char dirs_right[10][16] = {":G111\r", ":G111\r", ":G111\r", ":G111\r", ":G111\r", ":G111\r", ":G111\r", ":G131\r", ":G131\r", ":G131\r"};
char dirs_up[10][16] 	= {":G210\r", ":G210\r", ":G210\r", ":G210\r", ":G210\r", ":G210\r", ":G210\r", ":G230\r", ":G230\r", ":G230\r"};
char dirs_down[10][16] 	= {":G211\r", ":G211\r", ":G211\r", ":G211\r", ":G211\r", ":G211\r", ":G211\r", ":G231\r", ":G231\r", ":G231\r"};

//initialize string
char init_string[24][16] = {":e1\r",":q1010000\r",":\r",":e1\r",":e2\r",":q1010000\r",":W1050000\r",":W2050000\r",":P12\r",":P22\r",":a1\r",
								":a2\r",":b1\r",":g1\r",":g2\r",":j1\r",":j2\r",":F1\r",":F2\r",":f1\r",":f2\r","AT+CWMODE_CUR?\r\r","AT+CWMODE_CUR?\r\r","AT+CWMODE_CUR?\r\r"};
//goto park position string
char goto_parkPosition_string[8][16] = {":K1\r", ":K2\r", ":G201\r",":M2AC0D00\r",":J2\r",":G101\r",":M1AC0D00\r",":J1\r"};
	
char bulbShutter_on[2][16] = {":011\r", ":021\r"};
char bulbShutter_off[2][16] = {":010\r", ":020\r"};

void joystick_init(){
    if( ( joy_fd = open( JOY_DEV , O_RDONLY)) == -1 )
	{
		if(DEBUG)printf( "Couldn't open joystick\n" );
	} else {

		ioctl( joy_fd, JSIOCGAXES, &num_of_axis );
		ioctl( joy_fd, JSIOCGBUTTONS, &num_of_buttons );
		ioctl( joy_fd, JSIOCGNAME(80), &name_of_joystick );

		axis = (int *) calloc( num_of_axis, sizeof( int ) );
		button = (char *) calloc( num_of_buttons, sizeof( char ) );

		fcntl( joy_fd, F_SETFL, O_NONBLOCK );	/* use non-blocking mode */

        for(uint8_t i = 0; i<23; i++) joystick_sendCommand(init_string[i]); 
	    //init speed
	    joystick_sendCommand(speeds1[speed]);joystick_sendCommand(speeds2[speed]);
	}
}
void joystick_destroy(){
    close( joy_fd );
}

int joystick_getJStateEx(int *faxis, char *fbuttons){
		int retkey = KEY_NONE;
		//ax_right
		if(faxis[0]==32767)retkey = retkey+KEY_AX_RIGHT;
		//lax_left	
		if(faxis[0]==-32767)retkey = retkey+KEY_AX_LEFT;
		//lax_up	
		if(faxis[1]==-32767)retkey = retkey+KEY_AX_UP;
		//lax_down	
		if(faxis[1]==32767)retkey = retkey+KEY_AX_DOWN;
		
		if(faxis[2]==32767)retkey = retkey+KEY_AX_RIGHT;
		//lax_left	
		if(faxis[2]==-32767)retkey = retkey+KEY_AX_LEFT;
		//lax_up	
		if(faxis[3]==-32767)retkey = retkey+KEY_AX_UP;
		//lax_down	
		if(faxis[3]==32767)retkey = retkey+KEY_AX_DOWN;

		for(int i = 0; i < 12; i++){
			if(fbuttons[i]==1)retkey=i+1;
		}

		return retkey;
}

void joystick_sendCommand(char cmd[16]){
		serial_busy=1;
		char cmd_stop[] = ":K1:\r:K2:\r";
		for(int i = 0; i<8;i++){
			serialPutchar(serial_port, cmd_stop[i]);
		} 
		
		for(int i = 0; i<16;i++){
			if(cmd[i]!=0){
				serialPutchar(serial_port, cmd[i]);
			}
		}
		usleep(timeOut*1000);
		serial_busy=0;
	}

void joystick_slew(int key){
	char cmd_start1[16]=":J1\r";
	char cmd_start2[16]=":J2\r";

	//int s = 0;
	switch(key){
		case KEY_AX_RIGHT:
			//sendCommand(cmd_axis1);
			joystick_sendCommand(dirs_left[speed]);	
			joystick_sendCommand(speeds1[speed]);	
			joystick_sendCommand(cmd_start1);	
		break;
		case KEY_AX_LEFT:
			//sendCommand(cmd_axis1);
			joystick_sendCommand(dirs_right[speed]);	
			joystick_sendCommand(speeds1[speed]);		
			joystick_sendCommand(cmd_start1);
		break;
		case KEY_AX_DOWN:
			//sendCommand(cmd_axis2);
			joystick_sendCommand(dirs_up[speed]);	
			joystick_sendCommand(speeds2[speed]);		
			joystick_sendCommand(cmd_start2);
		break;
		case KEY_AX_UP:
			//sendCommand(cmd_axis2);
			joystick_sendCommand(dirs_down[speed]);	
			joystick_sendCommand(speeds2[speed]);		
			joystick_sendCommand(cmd_start2);
			break;
		}
}
void joystick_stop(){
	if((last_command==KEY_BTN_6)||(last_command==KEY_BTN_8)){
		pwmWrite(18,0);
	}
	//stops focuser
	if((last_command==KEY_AX_LEFT)||(last_command==KEY_AX_RIGHT)){
		char cmd_stop1[] = ":K1\r";
		joystick_sendCommand(cmd_stop1);
	} 
    //stops alt axis
	if((last_command==KEY_AX_UP)||(last_command==KEY_AX_DOWN)){
		char cmd_stop2[] = ":K2\r";
		joystick_sendCommand(cmd_stop2);	
	}
	//
	if((last_command==KEY_BTN_5)||(last_command==KEY_BTN_7)){

	}
}
void joystick_keyEvent(){
    uint8_t key = KEY_NONE;
		
		if(joy_fd>-1){
			read(joy_fd, &js, sizeof(struct js_event));
		
			/* see what to do with the event */
			switch (js.type & ~JS_EVENT_INIT)
			{
				case JS_EVENT_AXIS:
					axis   [ js.number ] = js.value;
					break;
				case JS_EVENT_BUTTON:
					button [ js.number ] = js.value;
					break;
			}

			key = joystick_getJStateEx((int *)axis, (char *)button);
		
			if(key!=last_command){
				joystick_stop();
				if(DEBUG)printf("key: %i \n", key);
				if((key!=KEY_NONE)&&(key>KEY_BTN_12))joystick_slew(key);
				switch (key) {
					//increase speed
					case KEY_BTN_1:
						if(speed<9)speed++;
						//joystick_sendCommand(speeds1[speed]);
						//joystick_sendCommand(speeds2[speed]);
						break;
				 	//decrease speed
				 	case KEY_BTN_3:
						if(speed>0)speed--;
						//joystick_sendCommand(speeds1[speed]);
						//joystick_sendCommand(speeds2[speed]);
				 		break;
				 	//set slowest speed
				 	case KEY_BTN_2:
						speed=0;
						//joystick_sendCommand(speeds1[speed]);
						//joystick_sendCommand(speeds2[speed]);
				 		break;
				 	//set fastest speed
				 	case KEY_BTN_4:
						speed=9;
						//joystick_sendCommand(speeds1[speed]);
						//joystick_sendCommand(speeds2[speed]);
						break;
					// (left arm up)
					case KEY_BTN_5:

						break;
					//focuser++ (right arm up)
					case KEY_BTN_6:
						pwmWrite(18,134);
						break;
					// (left arm down)
					case KEY_BTN_7:

						break;
					//focuser-- (right arm down)
					case KEY_BTN_8:
						pwmWrite(18,144);
						break;
				 	// (select button)
				 	case KEY_BTN_9:
						
						break;
					// goto park position Alt 0*0'0'' Deg 0*0'0'' (start button)
					case KEY_BTN_10:
						//for(int i = 0; i<8; i++) joystick_sendCommand(goto_parkPosition_string[i]);
						break;
					//(left arm fire button)
					case KEY_BTN_11:
						camera_raspistill_takepicture();
						break;
					//(right arm fire button)
					case KEY_BTN_12:
						if(recording_now) camera_destroyPreview(); else camera_startRecord();
					break;
				}
				last_command=key;
			}
		}
}