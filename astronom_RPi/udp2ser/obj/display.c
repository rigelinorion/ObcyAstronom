#include "display.h"
#include "./oled/OLED_icons.h"
#include "camera.h"


extern struct tsettings fsettings;
extern int compas_started;
extern char* _raspicmd_preview_sizes[3];
extern char* _raspicmd_exposure[5];
extern char* _raspicmd_image_codec[4];
extern char* _raspicmd_video_codec[2];
extern char* _raspicmd_awb[4]; 
extern char* _raspicmd_metering[4]; 

void displayInit(){
	DEV_ModuleInit();
	OLED_SCAN_DIR OLED_ScanDir = SCAN_DIR_DFT;//SCAN_DIR_DFT = D2U_L2R
	OLED_Init(OLED_ScanDir );
	//printf( "mi: %D\n", menu_index );
}
void* displayThread(void* args)
{
    while(1)
    {
     key_event();  
    }
}

char * int2str(int value){
	char n[6];
	snprintf(n, sizeof(n), "%d", value);
	return n;
}
int xpos(char text[]){
	int l = 64 - ((strlen(text)*7)/2);
	return l;
}
void displayText_R2L(POINT Xstart, POINT Ystart, char pString[]){
	int l = 128 - (strlen(pString)*7) - Xstart;
	GUI_DisString_EN(l, Ystart, pString, &Font12, FONT_BACKGROUND, WHITE);
}
void displayText_CenterX(POINT Ystart, char pString[]){
	int l = 64 - ((strlen(pString)*7)/2);
	GUI_DisString_EN(l, Ystart, pString, &Font12, FONT_BACKGROUND, WHITE);
}

void displayText_Center(char pString[]){
	int l = 64 - ((strlen(pString)*7)/2);
	GUI_DisString_EN(l, 28, pString, &Font12, FONT_BACKGROUND, WHITE);
}

void displayEditTedt(char value[], char title[], const unsigned char icon[], char options[]){
	OLED_Clear(BLACK);
	GUI_DrawLine(1,16,128,16,WHITE, LINE_SOLID, DOT_FILL_AROUND);
	GUI_DisString_EN(0, 1, title, &Font12, FONT_BACKGROUND, WHITE);
	displayText_R2L(0,1,options); 
	displayText_CenterX(30, value);
	OLED_Display();
}

void displayEditNum(signed int value, char title[], const unsigned char icon[], char options[]){
	OLED_Clear(BLACK);
	GUI_DrawLine(1,16,128,16,WHITE, LINE_SOLID, DOT_FILL_AROUND);
	GUI_DisString_EN(0, 1, title, &Font12, FONT_BACKGROUND, WHITE);
	displayText_R2L(0,1,options);
	GUI_DisNum(xpos("000"), 30, value, &Font12, FONT_BACKGROUND, WHITE);
	OLED_Display();
}

void displayDraw2Options(char option1[], char option2[], int selected, char title[], char options[]){
	OLED_Clear(BLACK);
	GUI_DrawLine(1,16,128,16,WHITE, LINE_SOLID, DOT_FILL_AROUND);
	GUI_DisString_EN(0, 1, title, &Font12, FONT_BACKGROUND, WHITE);
	displayText_R2L(0,1,options);
	if(selected){
		GUI_DisString_EN(xpos(option1), 25, option1, &Font12, FONT_FOREGROUND, BLACK);
		GUI_DisString_EN(xpos(option2), 40, option2, &Font12, FONT_BACKGROUND, WHITE);
	} else {
		GUI_DisString_EN(xpos(option1), 25, option1, &Font12, FONT_BACKGROUND, WHITE);
		GUI_DisString_EN(xpos(option2), 40, option2, &Font12, FONT_FOREGROUND, BLACK);
	}
	OLED_Display();
}
void displayButton(char title[]){
	OLED_Clear(BLACK);
	GUI_DrawRectangle(4, 4, 124, 60, WHITE, DRAW_EMPTY, DOT_FILL_AROUND);
	GUI_DrawRectangle(6, 6, 122, 58, WHITE, DRAW_EMPTY, DOT_FILL_AROUND);
	GUI_DrawLine(128, 8, 128, 64, WHITE, LINE_SOLID, DOT_FILL_AROUND);
	GUI_DrawLine(128, 64, 8, 64, WHITE, LINE_SOLID, DOT_FILL_AROUND);
	displayText_Center(title);
	OLED_Display();
}
void displayMessage(char title[]){
	OLED_Clear(BLACK);
	GUI_DrawRectangle(1, 1, 128, 64, WHITE, DRAW_EMPTY, DOT_FILL_AROUND);
	displayText_Center(title);
	OLED_Display();
	DEV_Delay_ms(1000);
}

void displayCompasValue(int az){
	GUI_DisString_EN(20, 30, "az: ", &Font16, FONT_BACKGROUND, WHITE);
	GUI_DisNum(60, 30, az, &Font16, FONT_BACKGROUND, WHITE);
	OLED_Display();
}

void displayClear(){
	OLED_Clear(BLACK);
	OLED_Display();
}

void displayAlignZeroPosTelescope(){
	OLED_Clear(BLACK);
	GUI_DrawRectangle(1,1,128,64,WHITE, DRAW_EMPTY, DOT_FILL_RIGHTUP);
	GUI_DisString_EN(5, 10, "now align zero", &Font12, FONT_BACKGROUND, WHITE); 
	GUI_DisString_EN(5, 20, "telescope position", &Font12, FONT_BACKGROUND, WHITE); 	
	OLED_Display();
	DEV_Delay_ms(1000);
}
void displayMenu(int index){
	//char buf[255];
	//sprintf(buf, "menindex: %i", index);
	//puts(buf);
	if((fsettings.server_type!=SERVER_TYPE_UDP2SER)&&(index>7)) return;
	switch(index){
		case MENU_BLACK:
			OLED_Clear(BLACK);
		break;
		case MENU_INFO:
			OLED_Clear(BLACK);
			GUI_DrawRectangle(1,1,128,64,WHITE, DRAW_EMPTY, DOT_FILL_RIGHTUP);
			if(fsettings.server_type==SERVER_TYPE_INDY) 
				GUI_DisString_EN(6, 10, "server type: INDI", &Font12, FONT_BACKGROUND, WHITE); 
			else 
				GUI_DisString_EN(8, 10, "server type: U2S", &Font12, FONT_BACKGROUND, WHITE);
			if(fsettings.network_type==NETWORK_TYPE_LOCAL) 
				GUI_DisString_EN(10, 27, "wifi mode: LOCAL", &Font12, FONT_BACKGROUND, WHITE); 
			else 
				GUI_DisString_EN(19, 27, "wifi mode: AP", &Font12, FONT_BACKGROUND, WHITE);
			
			GUI_DisString_EN(20, 44, &NetworkAdaptorIpAddress[0][0], &Font12, FONT_BACKGROUND, WHITE);
			OLED_Display();
		break;
		case MENU_PARK_TELESCOPE:
			displayButton("Park telescope");
		break;
		case MENU_POWERDOWN:
			displayButton("Shutdown");
		break;
		case MENU_RESET:
			displayButton("Reboot");
		break;
		case MENU_SAVESETTINGS:
			displayButton("Save settings");
		break;
		case MENU_NETWORK:
			displayDraw2Options( "Local network", "Acces point",fsettings.network_type, "WiFi mode", "< >");
		break;
		case MENU_SERVER:
			displayDraw2Options("INDI server", "Udp2Ser server", fsettings.server_type, "Server type", "< >");
		break;

		case MENU_CAMERA_ENABLED:
			displayDraw2Options("enabled", "disabled", fsettings.camera_autorun, "Camera autorun", "< >");
		break;
		case MENU_CAMERA_SHOOT_COUNT:
			displayEditNum(fsettings.camera_shooter_count, "Shoot count", NULL, "< >");
		break;
		case MENU_CAMERA_SHOOT_DELAY:
			displayEditNum(fsettings.camera_shooter_delay, "Shoot delay", NULL, "< >");
		break;
		case MENU_CAMERA_SHOOT_INTERVAL:
			displayEditNum(fsettings.camera_shooter_interval, "Shoot interval", NULL, "< >");
		break;
		case MENU_CAMERA_BRIGTHNESS:
			displayEditNum(fsettings.camera_brigthness, "Brigthness", NULL, "< >");
		break;
		case MENU_CAMERA_CONTRAST:
			displayEditNum(fsettings.camera_contrast, "Contrast", NULL, "< >");
		break;
		case MENU_CAMERA_AWB:
			displayEditTedt(_raspicmd_awb[fsettings.camera_awb], "AWB", NULL, "< >");
		break;
		case MENU_CAMERA_EXPOSURE:
			displayEditTedt(_raspicmd_exposure[fsettings.camera_exposure], "Exposure", NULL, "< >");
		break;
		case MENU_CAMERA_ISO:
			displayEditNum(fsettings.camera_ISO, "ISO", NULL, "< >");
		break;
		case MENU_CAMERA_STAB:
			displayDraw2Options( "OFF", "ON",fsettings.camera_stab, "Stabilization", "< >");
		break;
		case MENU_CAMERA_METERING:
			displayEditTedt(_raspicmd_metering[fsettings.camera_metering], "Metering", NULL, "< >");
		break;
		case MENU_CAMERA_SS:
			displayEditNum(fsettings.camera_ss, "Snapshot speed", NULL, "< >");
		break;
		case MENU_CAMERA_VF:
			displayDraw2Options( "OFF", "ON",fsettings.camera_vf, "Vertical flip", "< >");
		break;
		case MENU_CAMERA_HF:
			displayDraw2Options( "OFF", "ON",fsettings.camera_hf, "Horizontal flip", "< >");
		break;
		case MENU_CAMERA_ROT:
			displayEditNum(fsettings.camera_rot, "Rotation", NULL, "< >");
		break;

		case MENU_CAMERA_IMAGE_SIZE:
			displayEditNum(fsettings.camera_image_size, "Image size", NULL, "< >");
		break;
		case MENU_CAMERA_IMAGE_CODEC:
			displayEditTedt(_raspicmd_image_codec[fsettings.camera_image_codec], "Image codec", NULL, "< >");
		break;
		case MENU_CAMERA_IMAGE_QUALITY:
			displayEditNum(fsettings.camera_image_quality, "Image quality", NULL, "< >");
		break;


		case MENU_CAMERA_VIDEO_SIZE:
			displayEditNum(fsettings.camera_video_size, "Video size", NULL, "< >");
		break;
		case MENU_CAMERA_VIDEO_CODEC:
			displayEditTedt(_raspicmd_video_codec[fsettings.camera_video_codec], "Video codec", NULL, "< >");
		break;
		case MENU_CAMERA_VIDEO_QUALITY:
			displayEditNum(fsettings.camera_video_quality, "Video bitrate", NULL, "< >");
		break;
		case MENU_CAMERA_VIDEO_RECTIME:
			displayDraw2Options( "Count is min", "Endless", fsettings.camera_video_rectime, "Video record time", "< >");
		break;
		case MENU_CAMERA_VIDEO_FPS:
			displayEditNum(fsettings.camera_video_fps, "Video fps", NULL, "< >");
		break;


		case MENU_CAMERA_PREVIEW_SIZE:
			displayEditTedt(_raspicmd_preview_sizes[fsettings.camera_preview_size], "Preview size", NULL, "< >");
		break;
		case MENU_CAMERA_PREVIEW_ON:
			displayDraw2Options( "STREAM", "HDMI",fsettings.camera_preview_on, "View on...", "< >");
		break;


		case MENU_COMPAS_MDEC_COR_DEG:
			displayEditNum(fsettings.compas_mdec_cor_deg, "Cmp MDec deg", NULL, "< >");
		break;
		case MENU_COMPAS_MDEC_COR_MIN:
			displayEditNum(fsettings.compas_mdec_cor_mins, "Cmp MDec min", NULL, "< >");
		break;
		case MENU_COMPAS_AZIMUTH_COR:
			displayEditNum(fsettings.compas_azimuth_cor, "Azimuth cor", NULL, "< >");
		break;
		case MENU_COMPAS_CALIBRATE:
			if(!compas_started) displayButton("Compas calibrate"); else displayMessage("Calibrating...");
		break;
		case MENU_COMPAS_SHOW_AZ:
			if(!compas_started) displayButton("Run align");
		break;
	}
}