#ifndef SETTINGS_H
#define SETTINGS_H

#include "includes.inc"

#define settings_file "settings.dat"

#define NETWORK_TYPE_AP   		0
#define NETWORK_TYPE_LOCAL 		1
#define SERVER_TYPE_UDP2SER 	0
#define SERVER_TYPE_INDY 		1
#define CAMERA_ON_HDMI  		0
#define CAMERA_ON_STREAM  		1

struct tsettings {
	int camera_autorun;					//1
	int camera_shooter_count;
	int camera_shooter_interval;
	int camera_shooter_delay;
	int camera_brigthness;
	int camera_contrast;
	int camera_awb;
	int camera_exposure;
	int camera_ISO;
	int camera_stab;
	int camera_metering;
	int camera_ss;						//12
	int camera_vf;
	int camera_hf;
	int camera_rot;

	int camera_image_size; //1..9
	int camera_image_codec;
	int camera_image_quality;
	int camera_video_size;
	int camera_video_codec;
	int camera_video_quality;
	int camera_video_rectime;
	int camera_video_fps;				//20
	

	int camera_preview_size;
	int camera_preview_on;	

	int compas_mdec_cor_deg; //5;
	int compas_mdec_cor_mins; //44;
	int compas_azimuth_cor; //0;

	int network_type; //NETWORK_TYPE_LOCAL;
	int server_type; //SERVER_TYPE_INDY;
};

void settingsRead();
void settingsWriteDefault();
void settingsWrite();
#endif 