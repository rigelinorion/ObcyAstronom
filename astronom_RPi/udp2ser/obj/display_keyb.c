#include "includes.inc"
#include "display_keyb.h"
#include "settings.h"
#include "udpserver2.h"
#include "common.h"
#include "compas.h"
#include "joystick.h"
#include "camera.h"
#include "display.h"
#include "utils.h"

int idle_counter = 0;
int idle_subcounter = 0;
int menu_index = MENU_INFO;
extern int compas_started;
extern char goto_parkPosition_string[8][16];
extern struct tsettings fsettings;

extern char* _raspicmd_preview_sizes[3];
extern char* _raspicmd_exposure[5];
extern char* _raspicmd_image_codec[4];
extern char* _raspicmd_video_codec[2];
extern char* _raspicmd_awb[4]; 
extern struct tsettings fsettings;

void key_event(void)
{
		
        if((idle_counter < 65000)&&(!compas_started))idle_counter++;
        if(idle_counter==65000){
        	idle_counter=0;
        	idle_subcounter++;
        	if(idle_subcounter==IDLE_TIME){
        		displayClear();
        		idle_subcounter=0;
        	}
        }
		if(KEY1_RD == 0){
			menu_index = MENU_INFO;
			displayMenu(menu_index);
		}
		if(KEY2_RD == 0){
			menu_index = MENU_CAMERA_SHOOT_COUNT;
			displayMenu(menu_index);
		}
		if(KEY3_RD == 0){
			menu_index = MENU_COMPAS_MDEC_COR_DEG;
			displayMenu(menu_index);
		}
        if(KEY_UP_RD == 0) {
            while(KEY_UP_RD == 0)DEV_Delay_ms(10);
            if(menu_index>MENU_INFO)menu_index--;
            displayMenu(menu_index);
            idle_subcounter=0;
        }
        if(KEY_DOWN_RD == 0) {
            while(KEY_DOWN_RD == 0)DEV_Delay_ms(10);
            if(menu_index<MENU_COUNT)menu_index++;
            displayMenu(menu_index);
            idle_subcounter=0;
        }
        if(KEY_LEFT_RD == 0) {
            while(KEY_LEFT_RD == 0)DEV_Delay_ms(10);
            switch(menu_index){
				case MENU_SERVER:
            		fsettings.server_type = 0;
            	break;
            	case MENU_NETWORK:
            		fsettings.network_type = 0;
            	break;
				case MENU_CAMERA_ENABLED:
					fsettings.camera_autorun = 0;
				break;
				case MENU_CAMERA_SHOOT_COUNT:
					if(fsettings.camera_shooter_count > 2) fsettings.camera_shooter_count--;
				break;
				case MENU_CAMERA_SHOOT_DELAY:
					if(fsettings.camera_shooter_delay > 0) fsettings.camera_shooter_delay--;
				break;
				case MENU_CAMERA_SHOOT_INTERVAL:
					if(fsettings.camera_shooter_interval > 0) fsettings.camera_shooter_interval--;
				break;
				case MENU_CAMERA_BRIGTHNESS:
					if(fsettings.camera_brigthness > 10) fsettings.camera_brigthness-=10;
				break;
				case MENU_CAMERA_CONTRAST:
					if(fsettings.camera_contrast > 10) fsettings.camera_contrast-=10;
				break;
				case MENU_CAMERA_AWB:
					if(fsettings.camera_awb > 0) fsettings.camera_awb--;
				break;
				case MENU_CAMERA_EXPOSURE:
					if(fsettings.camera_exposure > 0) fsettings.camera_exposure--;
				break;
				case MENU_CAMERA_ISO:
					if(fsettings.camera_ISO > 100) fsettings.camera_ISO-=100;
				break;
				case MENU_CAMERA_STAB:
					fsettings.camera_stab = 0;
				break;
				case MENU_CAMERA_METERING:
					if(fsettings.camera_metering > 0) fsettings.camera_metering--;
				break;
				case MENU_CAMERA_SS:
					if(fsettings.camera_ss >= 250) fsettings.camera_ss-=250;
				break;
				case MENU_CAMERA_VF:
					fsettings.camera_vf = 0;
				break;
				case MENU_CAMERA_HF:
					fsettings.camera_hf = 0;
				break;
				case MENU_CAMERA_ROT:
					if(fsettings.camera_rot >= 90) fsettings.camera_ss-=90;
				break;

				case MENU_CAMERA_IMAGE_SIZE:
					if(fsettings.camera_image_size > 2) fsettings.camera_image_size--;
				break;
				case MENU_CAMERA_IMAGE_CODEC:
					if(fsettings.camera_image_codec > 0) fsettings.camera_image_codec--;
				break;
				case MENU_CAMERA_IMAGE_QUALITY:
					if(fsettings.camera_image_quality > 10) fsettings.camera_image_quality-=10;
				break;
				case MENU_CAMERA_VIDEO_SIZE:
					if(fsettings.camera_video_size > 2) fsettings.camera_video_size--;
				break;
				case MENU_CAMERA_VIDEO_CODEC:
					if(fsettings.camera_video_codec > 0) fsettings.camera_video_codec--;
				break;
				case MENU_CAMERA_VIDEO_QUALITY:
					if(fsettings.camera_video_quality > 1) fsettings.camera_video_quality--;
				break;
				case MENU_CAMERA_VIDEO_RECTIME:
					fsettings.camera_video_rectime = 0;
				break;
				case MENU_CAMERA_VIDEO_FPS:
					if(fsettings.camera_video_fps > 2) fsettings.camera_video_fps--;
				break;

				case MENU_CAMERA_PREVIEW_SIZE:
					if(fsettings.camera_preview_size > 0) fsettings.camera_preview_size--;
				break;
				case MENU_CAMERA_PREVIEW_ON:
					fsettings.camera_preview_on = 0;
				break;

				case MENU_COMPAS_MDEC_COR_DEG:
					if(fsettings.compas_mdec_cor_deg > 0)fsettings.compas_mdec_cor_deg--;
				break;
				case MENU_COMPAS_MDEC_COR_MIN:
					if(fsettings.compas_mdec_cor_mins > 0) fsettings.compas_mdec_cor_mins--;
				break;
				case MENU_COMPAS_AZIMUTH_COR:
					fsettings.compas_azimuth_cor--;
				break;
            }
			displayMenu(menu_index);
            idle_subcounter=0;
        }
        if(KEY_RIGHT_RD == 0) {
            while(KEY_LEFT_RD == 0)DEV_Delay_ms(10);
            switch(menu_index){
            	case MENU_SERVER:
            		fsettings.server_type = 1;
            	break;
            	case MENU_NETWORK:
            		fsettings.network_type = 1;
            	break;
				case MENU_CAMERA_ENABLED:
					fsettings.camera_autorun = 1;
				break;
				case MENU_CAMERA_SHOOT_COUNT:
					if(fsettings.camera_shooter_count < 1000) fsettings.camera_shooter_count++;
				break;
				case MENU_CAMERA_SHOOT_DELAY:
					if(fsettings.camera_shooter_delay < 100) fsettings.camera_shooter_delay++;
				break;
				case MENU_CAMERA_SHOOT_INTERVAL:
					if(fsettings.camera_shooter_interval < 65000) fsettings.camera_shooter_interval++;
				break;
				case MENU_CAMERA_BRIGTHNESS:
					if(fsettings.camera_brigthness < 100) fsettings.camera_brigthness+=10;
				break;
				case MENU_CAMERA_CONTRAST:
					if(fsettings.camera_contrast < 200) fsettings.camera_contrast+=10;
				break;
				case MENU_CAMERA_AWB:
					if(fsettings.camera_awb < 3) fsettings.camera_awb++;
				break;
				case MENU_CAMERA_EXPOSURE:
					if(fsettings.camera_exposure < 4) fsettings.camera_exposure++;
				break;
				case MENU_CAMERA_ISO:
					if(fsettings.camera_ISO < 800) fsettings.camera_ISO+=100;
				break;
				case MENU_CAMERA_STAB:
					fsettings.camera_stab = 1;
				break;
				case MENU_CAMERA_METERING:
					if(fsettings.camera_metering < 3) fsettings.camera_metering++;
				break;
				case MENU_CAMERA_SS:
					if(fsettings.camera_ss < 6000) fsettings.camera_ss+=250;
				break;
				case MENU_CAMERA_VF:
					fsettings.camera_vf = 1;
				break;
				case MENU_CAMERA_HF:
					fsettings.camera_hf = 1;
				break;
				case MENU_CAMERA_ROT:
					if(fsettings.camera_rot < 270) fsettings.camera_rot+=90;
				break;
				
				case MENU_CAMERA_IMAGE_SIZE:
					if(fsettings.camera_image_size < 9) fsettings.camera_image_size++;
				break;
				case MENU_CAMERA_IMAGE_CODEC:
					if(fsettings.camera_image_codec < 3) fsettings.camera_image_codec++;
				break;
				case MENU_CAMERA_IMAGE_QUALITY:
					if(fsettings.camera_image_quality < 100) fsettings.camera_image_quality+=10;
				break;
				case MENU_CAMERA_VIDEO_SIZE:
					if(fsettings.camera_video_size < 5) fsettings.camera_video_size++;
				break;
				case MENU_CAMERA_VIDEO_CODEC:
					if(fsettings.camera_video_codec < 1) fsettings.camera_video_codec++;
				break;
				case MENU_CAMERA_VIDEO_QUALITY:
					if(fsettings.camera_video_quality < 10) fsettings.camera_video_quality++;
				break;
				case MENU_CAMERA_VIDEO_RECTIME:
					fsettings.camera_video_rectime = 1;
				break;
				case MENU_CAMERA_VIDEO_FPS:
					if(fsettings.camera_video_quality < 30) fsettings.camera_video_quality++;
				break;
				
				case MENU_CAMERA_PREVIEW_SIZE:
					if(fsettings.camera_preview_size < 2) fsettings.camera_preview_size++;
				break;
				case MENU_CAMERA_PREVIEW_ON:
					fsettings.camera_preview_on = 1;
				break;


				case MENU_COMPAS_MDEC_COR_DEG:
					fsettings.compas_mdec_cor_deg++;
				break;
				case MENU_COMPAS_MDEC_COR_MIN:
					fsettings.compas_mdec_cor_mins++;
				break;
				case MENU_COMPAS_AZIMUTH_COR:
					fsettings.compas_azimuth_cor++;
				break;
            }
            displayMenu(menu_index);
            idle_subcounter=0;
        }
        if(KEY_PRESS_RD == 0) {
            while(KEY_PRESS_RD == 0)DEV_Delay_ms(10);

            	if((menu_index >= MENU_CAMERA_SHOOT_COUNT) && (menu_index <= MENU_COMPAS_AZIMUTH_COR)){
					settingsWrite();
					if((menu_index>=MENU_CAMERA_BRIGTHNESS) && (menu_index<=MENU_CAMERA_ROT))camera_restartPreview();
					if(menu_index == MENU_CAMERA_PREVIEW_SIZE)camera_restartPreview();
				}
			
				switch(menu_index){
					case MENU_SERVER:
            			displayMessage("Switching server type");
            			if(fsettings.server_type) _system_sh("astronommode.sh"); else _system_sh("indimode.sh");
            		break;
            	case MENU_NETWORK:
            			displayMessage("Switching network type");
            			_system_sh("switchNetworkMode.sh");
            	break;
					case MENU_PARK_TELESCOPE:
						displayMessage("Parking...");
						for(int i = 0; i<8; i++) joystick_sendCommand(goto_parkPosition_string[i]);
						displayMessage("Done");
						usleep(10000);
					break;
					case MENU_RESET:
						displayMessage(MSG_REBOOT);
						settingsWrite();
						system("sudo reboot");
					break;
					case MENU_POWERDOWN:
						displayMessage(MSG_POWERDOWN);
						settingsWrite();
						system("sudo shutdown now");
					break;
					case MENU_SAVESETTINGS:
						displayMessage("saving settings now...");
						settingsWrite();
					break;
					case MENU_BLACK:
						displayMenu(menu_index);
					break;
					case MENU_COMPAS_CALIBRATE:
						if(!compas_started){
							compas_started = 1;
							displayMessage("Calibrating...");
							compas_calibrate();
						} else {
							displayMessage("Done");
							usleep(10000);
							compas_started = 0;
						}
					break;
					case MENU_COMPAS_SHOW_AZ:
						if(!compas_started){
							compas_started = 1;
							displayMessage("Run align...");
							while(1){
								OLED_Clear(BLACK);
								displayCompasValue(compas_getazimuth());
								usleep(500000);
								if(KEY_PRESS_RD==0){
									compas_started = 0;
									break;
								}
							}
						}
					break;
				}

            	displayMenu(menu_index);
            	idle_subcounter=0;
        }
}