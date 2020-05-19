#include "udpserver2.h"
#include "display.h"
#include "settings.h"
#include "camera.h"
#include "compas.h"
#include "utils.h"

extern int DEBUG;
extern int udpsend;

int sockfd2; 
extern _Bool recording_now;
extern struct tsettings fsettings;
struct sockaddr_in servaddr2, cliaddr2;

void udpserver2Init(){
	
}

void udpserver2Send(char* udpstring){
	int len;
	len = sizeof(cliaddr2);
	sendto(sockfd2, (char *)udpstring, strlen(udpstring),  MSG_DONTWAIT, (const struct sockaddr2 *) &cliaddr2, len);
}
void* udpserver2Thread(void* args)
{
	// Creating socket file descriptor 
	if ( (sockfd2 = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket 2 creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr2, 0, sizeof(servaddr2)); 
	memset(&cliaddr2, 0, sizeof(cliaddr2)); 
	
	// Filling server information 
	servaddr2.sin_family = AF_INET; // IPv4 
	servaddr2.sin_addr.s_addr = INADDR_ANY; 
	servaddr2.sin_port = htons(PORT2); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd2, (const struct sockaddr *)&servaddr2, sizeof(servaddr2)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	while(1)
    {
     char dat;
     char buffer[MAXLINE];
	 char outbuffer[MAXLINE];
     int len, n;
	 len = sizeof(cliaddr2); //len is value/resuslt
	 for(int i = 0; i<10;i++)buffer[i]=0;	
     n = recvfrom(sockfd2, (char *)buffer, MAXLINE , 0, ( struct sockaddr2 *) &cliaddr2, &len);
		if(n>0){
			if(buffer[0]=='m'){ // record
			char msg[255];
			sscanf(buffer, "m %s", msg);
			displayMessage(msg);
			}
			if(buffer[0]==':'){ // record
				if(recording_now) camera_destroyPreview(); else camera_startRecord();
			}
			if(buffer[0]=='.'){ // still
				camera_raspistill_takepicture();
			}
			if(buffer[0]=='<'){ // Compas
				int az = compas_getazimuth();
				int level = compas_getlevel();
				sprintf(outbuffer, "< %i %i", az, level);
				udpserver2Send(outbuffer);
			}
			if(buffer[0]=='|'){ // calibrate
				udpsend = 1;
				compas_calibrate();
			}
			if(buffer[0]==';'){ // noop
				outbuffer[0]=';'; 
				udpserver2Send(outbuffer);
			}
			if(buffer[0]=='?'){ // check connection
				outbuffer[0]='*'; 
				printf("request for ? %s\n",outbuffer);
				udpserver2Send(outbuffer);

			}
			if(buffer[0]=='^'){ //shutdown
				system("sudo shutdown now");
			}
			if(buffer[0]=='!'){ //reboot
				system("sudo reboot");
			}
			if(buffer[0]=='@'){ //update display
				camera_restartPreview();
			}
			if(buffer[0]=='&'){ // # switch server type, ## switch network type
				if(buffer[1]=='&'){
					fsettings.server_type = !fsettings.server_type;
					_system_sh("switchToINDIMode.sh");
				} else {
					fsettings.network_type = !fsettings.network_type;
					_system_sh("switchNetworkMode.sh");
				}
			}

			if((buffer[0]=='#')){	 // recived #-get $-settings
				int param;
				char outbuffer[255];
				//printf("request setting %s\n",buffer); 
				sscanf(buffer, "# %d", &param);
				switch (param){
					case MENU_NETWORK					:sprintf(outbuffer, "# %d %d", MENU_NETWORK, fsettings.server_type); break;
					case MENU_SERVER					:sprintf(outbuffer, "# %d %d", MENU_SERVER, fsettings.network_type);	break;
					case MENU_CAMERA_ENABLED			:sprintf(outbuffer, "# %d %d", MENU_CAMERA_ENABLED, fsettings.camera_autorun); break;
					case MENU_CAMERA_SHOOT_COUNT		:sprintf(outbuffer, "# %d %d", MENU_CAMERA_SHOOT_COUNT, fsettings.camera_shooter_count); break;
					case MENU_CAMERA_SHOOT_DELAY		:sprintf(outbuffer, "# %d %d", MENU_CAMERA_SHOOT_DELAY, fsettings.camera_shooter_delay); break;
					case MENU_CAMERA_SHOOT_INTERVAL		:sprintf(outbuffer, "# %d %d", MENU_CAMERA_SHOOT_INTERVAL, fsettings.camera_shooter_interval); break; 
					case MENU_CAMERA_BRIGTHNESS			:sprintf(outbuffer, "# %d %d", MENU_CAMERA_BRIGTHNESS, fsettings.camera_brigthness); break;      
					case MENU_CAMERA_CONTRAST			:sprintf(outbuffer, "# %d %d", MENU_CAMERA_CONTRAST, fsettings.camera_contrast); break;		        
					case MENU_CAMERA_AWB             	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_AWB, fsettings.camera_awb); break;
					case MENU_CAMERA_EXPOSURE        	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_EXPOSURE, fsettings.camera_exposure); break;
					case MENU_CAMERA_ISO             	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_ISO, fsettings.camera_ISO); break;
					case MENU_CAMERA_STAB            	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_STAB, fsettings.camera_stab); break;
					case MENU_CAMERA_METERING        	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_METERING, fsettings.camera_metering); break;
					case MENU_CAMERA_SS        			:sprintf(outbuffer, "# %d %d", MENU_CAMERA_SS, fsettings.camera_ss); break;
					case MENU_CAMERA_VF        			:sprintf(outbuffer, "# %d %d", MENU_CAMERA_VF, fsettings.camera_vf); break;
					case MENU_CAMERA_HF        			:sprintf(outbuffer, "# %d %d", MENU_CAMERA_HF, fsettings.camera_hf); break;
					case MENU_CAMERA_ROT       			:sprintf(outbuffer, "# %d %d", MENU_CAMERA_ROT, fsettings.camera_rot); break;

					case MENU_CAMERA_IMAGE_SIZE      	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_IMAGE_SIZE, fsettings.camera_image_size); break;
					case MENU_CAMERA_IMAGE_CODEC     	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_IMAGE_CODEC, fsettings.camera_image_codec); break;
					case MENU_CAMERA_IMAGE_QUALITY   	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_IMAGE_QUALITY, fsettings.camera_image_quality); break;		
					case MENU_CAMERA_VIDEO_SIZE      	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_VIDEO_SIZE, fsettings.camera_video_size); break;
					case MENU_CAMERA_VIDEO_CODEC     	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_VIDEO_CODEC, fsettings.camera_video_codec); break;
					case MENU_CAMERA_VIDEO_QUALITY   	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_VIDEO_QUALITY, fsettings.camera_video_quality); break;
					case MENU_CAMERA_VIDEO_RECTIME   	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_VIDEO_RECTIME, fsettings.camera_video_rectime); break;
					case MENU_CAMERA_VIDEO_FPS       	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_VIDEO_FPS, fsettings.camera_video_fps); break;

					case MENU_CAMERA_PREVIEW_SIZE    	:sprintf(outbuffer, "# %d %d", MENU_CAMERA_PREVIEW_SIZE, fsettings.camera_preview_size); break;
					case MENU_CAMERA_PREVIEW_ON			:sprintf(outbuffer, "# %d %d", MENU_CAMERA_PREVIEW_ON, fsettings.camera_preview_on); break;

					case MENU_COMPAS_MDEC_COR_DEG		:sprintf(outbuffer, "# %d %d", MENU_COMPAS_MDEC_COR_DEG, fsettings.compas_mdec_cor_deg); break;
					case MENU_COMPAS_MDEC_COR_MIN		:sprintf(outbuffer, "# %d %d", MENU_COMPAS_MDEC_COR_MIN, fsettings.compas_mdec_cor_mins); break;
					case MENU_COMPAS_AZIMUTH_COR		:sprintf(outbuffer, "# %d %d", MENU_COMPAS_AZIMUTH_COR, fsettings.compas_azimuth_cor); break;
				}
				//printf("sending %s\n", outbuffer);
				udpserver2Send(outbuffer);
			}
			if((buffer[0]=='$')){		//recived $-set $-settings
				int param, value, save = 0;
				sscanf(buffer, "$ %i %i %i", &param, &value, &save);
				//printf("request for save setting %s\n",buffer);
				switch (param){
					case MENU_CAMERA_ENABLED			:fsettings.camera_autorun=value;	 		break;
					case MENU_CAMERA_SHOOT_COUNT		:fsettings.camera_shooter_count=value;		break;
					case MENU_CAMERA_SHOOT_DELAY		:fsettings.camera_shooter_delay=value;		break;
					case MENU_CAMERA_SHOOT_INTERVAL		:fsettings.camera_shooter_interval=value;	break; 
					case MENU_CAMERA_BRIGTHNESS			:fsettings.camera_brigthness=value;			break;      
					case MENU_CAMERA_CONTRAST			:fsettings.camera_contrast=value;			break;		        
					case MENU_CAMERA_AWB             	:fsettings.camera_awb=value;				break;
					case MENU_CAMERA_EXPOSURE        	:fsettings.camera_exposure=value;			break;
					case MENU_CAMERA_ISO             	:fsettings.camera_ISO=value;				break;
					case MENU_CAMERA_STAB            	:fsettings.camera_stab=value;				break;
					case MENU_CAMERA_METERING        	:fsettings.camera_metering=value;			break;
					case MENU_CAMERA_SS        			:fsettings.camera_ss=value;					break;
					case MENU_CAMERA_VF        			:fsettings.camera_vf=value;					break;
					case MENU_CAMERA_HF        			:fsettings.camera_hf=value;					break;
					case MENU_CAMERA_ROT       			:fsettings.camera_rot=value;				break;

					case MENU_CAMERA_IMAGE_SIZE      	:fsettings.camera_image_size=value;			break;
					case MENU_CAMERA_IMAGE_CODEC     	:fsettings.camera_image_codec=value;		break;
					case MENU_CAMERA_IMAGE_QUALITY   	:fsettings.camera_image_quality=value;		break;		
					case MENU_CAMERA_VIDEO_SIZE      	:fsettings.camera_video_size=value;			break;
					case MENU_CAMERA_VIDEO_CODEC     	:fsettings.camera_video_codec=value;		break;
					case MENU_CAMERA_VIDEO_QUALITY   	:fsettings.camera_video_quality=value;		break;
					case MENU_CAMERA_VIDEO_RECTIME   	:fsettings.camera_video_rectime=value;		break;
					case MENU_CAMERA_VIDEO_FPS       	:fsettings.camera_video_fps=value;			break;

					case MENU_CAMERA_PREVIEW_SIZE    	:fsettings.camera_preview_size=value;		break;
					case MENU_CAMERA_PREVIEW_ON			:fsettings.camera_preview_on=value;			break;

					case MENU_COMPAS_MDEC_COR_DEG		:fsettings.compas_mdec_cor_deg=value;		break;
					case MENU_COMPAS_MDEC_COR_MIN		:fsettings.compas_mdec_cor_mins=value;		break;
					case MENU_COMPAS_AZIMUTH_COR		:fsettings.compas_azimuth_cor=value;		break;
				}
				if(save)settingsWrite();
				displayMenu(param);
			}  
	
		}  
	}
}