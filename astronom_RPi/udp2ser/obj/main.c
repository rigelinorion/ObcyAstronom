// UDP to serial communicaton bridge for raspbrerry pi
//rigelinorion 02.2020
#include "includes.inc"
#include "display.h"
#include "display_keyb.h"
#include "settings.h"
#include "network.h"
#include "udpserver.h"
#include "joystick.h"
#include "camera.h"
#include "udpserver2.h"
#include "compas.h"

extern int serial_port;
extern int volatile serial_busy;
extern int thread_camera; 
extern pthread_t id_camera;
extern struct tsettings fsettings;

/////uint8_t raspividsvr_enabled = 1;
//uint8_t udpb_enabled = 1;
//int udp2ser_proc = 0;
//int udp2ser_proc2 = 0;
//int raspividsvr_proc = 0;

int indi_status = 768;
pthread_t id_display, id_udp2ser,  id_udp2ser2,id_camera;
char program_path[255];

int DEBUG = 1;

int isINDY(){
	int ret = system("systemctl is-active indi");
	printf("isindi: %i", ret); 
	fflush( stdout );
	if(ret==0)fsettings.server_type = SERVER_TYPE_INDY; else fsettings.server_type = SERVER_TYPE_UDP2SER; 
} 

int main( int argc, char *argv[], char *envp[] ) {
	char b[255];
	sprintf(b, "%s", argv[0]);
	strncpy(program_path, b, strlen(b)-12);
	puts(program_path);

	int last_command = 0;

	if(argc>1)DEBUG=1;
	
	wiringPiSetup();
  	wiringPiSetupGpio();
	
	//init focus servo	
  	pinMode (18, PWM_OUTPUT) ;
   	pwmSetMode (PWM_MODE_MS);
   	pwmSetRange (2000);
   	pwmSetClock (195);
	settingsRead();

	displayInit();
	networkInit();
	compas_init();
	isINDY();
	displayMenu(MENU_INFO);
	int thread_display=pthread_create(&id_display,NULL,&displayThread,NULL);
	
	if(fsettings.server_type == SERVER_TYPE_UDP2SER){
		int thread_udpserver=pthread_create(&id_udp2ser,NULL,&udpserverThread,NULL);
		camera_init();
	}

	int thread_udpserver2=pthread_create(&id_udp2ser2,NULL,&udpserver2Thread,NULL);
	joystick_init();

	for(;;){
		joystick_keyEvent();
	}
	settingsWrite();
	joystick_destroy();
	DEV_ModuleExit();
	return 0; 
} 
