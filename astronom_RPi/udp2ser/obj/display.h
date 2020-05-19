#ifndef DISPLAY_H
#define DISPLAY_H

#include "includes.inc"

#include "settings.h"
#include "network.h"

#include "./oled/OLED_Driver.h"
#include "./oled/OLED_GUI.h"
#include "./oled/DEV_Config.h"



#define MSG_REBOOT      "now reboting..."
#define MSG_POWERDOWN	"now powerdown..."

#define MENU_COUNT				    37

#define MENU_BLACK				    0
#define MENU_INFO				    MENU_BLACK+1
#define MENU_PARK_TELESCOPE         MENU_INFO+1
#define MENU_POWERDOWN			    MENU_PARK_TELESCOPE+1
#define MENU_RESET				    MENU_POWERDOWN+1
#define MENU_SAVESETTINGS           MENU_RESET+1
#define MENU_NETWORK			    MENU_SAVESETTINGS+1
#define MENU_SERVER				    MENU_NETWORK+1

#define MENU_CAMERA_ENABLED		    MENU_SERVER+1
#define MENU_CAMERA_SHOOT_COUNT	    MENU_CAMERA_ENABLED+1
#define MENU_CAMERA_SHOOT_DELAY     MENU_CAMERA_SHOOT_COUNT+1
#define MENU_CAMERA_SHOOT_INTERVAL  MENU_CAMERA_SHOOT_DELAY+1
#define MENU_CAMERA_BRIGTHNESS      MENU_CAMERA_SHOOT_INTERVAL+1
#define MENU_CAMERA_CONTRAST        MENU_CAMERA_BRIGTHNESS+1
#define MENU_CAMERA_AWB             MENU_CAMERA_CONTRAST+1
#define MENU_CAMERA_EXPOSURE        MENU_CAMERA_AWB+1
#define MENU_CAMERA_ISO             MENU_CAMERA_EXPOSURE+1
#define MENU_CAMERA_STAB            MENU_CAMERA_ISO+1
#define MENU_CAMERA_METERING        MENU_CAMERA_STAB+1
#define MENU_CAMERA_SS              MENU_CAMERA_METERING+1
#define MENU_CAMERA_VF              MENU_CAMERA_SS+1
#define MENU_CAMERA_HF              MENU_CAMERA_VF+1
#define MENU_CAMERA_ROT             MENU_CAMERA_HF+1

#define MENU_CAMERA_IMAGE_SIZE      MENU_CAMERA_ROT+1
#define MENU_CAMERA_IMAGE_CODEC     MENU_CAMERA_IMAGE_SIZE+1
#define MENU_CAMERA_IMAGE_QUALITY   MENU_CAMERA_IMAGE_CODEC+1
#define MENU_CAMERA_VIDEO_SIZE      MENU_CAMERA_IMAGE_QUALITY+1
#define MENU_CAMERA_VIDEO_CODEC     MENU_CAMERA_VIDEO_SIZE+1
#define MENU_CAMERA_VIDEO_QUALITY   MENU_CAMERA_VIDEO_CODEC+1
#define MENU_CAMERA_VIDEO_RECTIME   MENU_CAMERA_VIDEO_QUALITY+1
#define MENU_CAMERA_VIDEO_FPS       MENU_CAMERA_VIDEO_RECTIME+1

#define MENU_CAMERA_PREVIEW_SIZE    MENU_CAMERA_VIDEO_FPS+1
#define MENU_CAMERA_PREVIEW_ON		MENU_CAMERA_PREVIEW_SIZE+1

#define MENU_COMPAS_MDEC_COR_DEG    MENU_CAMERA_PREVIEW_ON+1
#define MENU_COMPAS_MDEC_COR_MIN	MENU_COMPAS_MDEC_COR_DEG+1
#define MENU_COMPAS_AZIMUTH_COR	    MENU_COMPAS_MDEC_COR_MIN+1
#define MENU_COMPAS_CALIBRATE       MENU_COMPAS_AZIMUTH_COR+1
#define MENU_COMPAS_SHOW_AZ         MENU_COMPAS_CALIBRATE+1


#define IDLE_TIME 300



void displayInit();
void* displayThread(void* args);
int xpos(char text[]);
void displayText_R2L(POINT Xstart, POINT Ystart, char pString[]);
void displayText_CenterX(POINT Ystart, char pString[]);
void displayText_Center(char pString[]);
void displayEditText(char value[], char title[], const unsigned char icon[], char options[]);
void displayEditNum(signed int value, char title[], const unsigned char icon[], char options[]);
void displayDraw2Options(char option1[], char option2[], int selected, char title[], char options[]);
void displayButton(char title[]);
void displayMessage(char title[]);
void displayCompasValue(int az);
void displayClear();
void displayAlignZeroPosTelescope();
void displayMenu(int index);

#endif 