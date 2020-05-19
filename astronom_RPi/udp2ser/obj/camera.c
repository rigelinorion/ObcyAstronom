#include "includes.inc"
#include "camera.h"
#include "settings.h"
#include "display.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

char* _raspicmd_preview_sizes[3]  = {"0,0,480,320", "0,0,640,480",  "0,0,800,600"};
char* _raspicmd_exposure[5]       = {"auto", "night", "verylong", "spotlight", "antishake"};
char* _raspicmd_image_codec[4]    = {"bmp", "jpg", "png", "gif"};
char* _raspicmd_video_codec[2]    = {"H264", "MJPEG"};
char* _raspicmd_awb[4]            = {"auto", "sun", "cloud", "shade"};
char* _raspicmd_metering[4]		  = {"average", "spot", "backlit", "matrix"};

extern char program_path[255];
extern struct tsettings fsettings;

pthread_t id_camera, id_record = NULL;
int thread_camera = 0;
int thread_record = 0;

_Bool recording_now = FALSE;

void camera_init(){
	camera_restartPreview();
}

void camera_raspistill_takepicture(){
	char pref[] = "%04d";
	int tl = fsettings.camera_shooter_interval * 1000;
	int t = tl * fsettings.camera_shooter_count-1;

	char picture_folder[255];
	char picture_filename[255];
	char cmdline[255];

	time_t tt = time(NULL);
  	struct tm tm = *localtime(&tt);
	int y = tm.tm_year + 1900;
	int m = tm.tm_mon + 1;
	int d = tm.tm_mday;
	int h = tm.tm_hour;
	int mn = tm.tm_min;
	int s = tm.tm_sec;

	sprintf(picture_folder, "%spictures/astro_%i_%i_%i", program_path, y, m, d);
	if(opendir(picture_folder)==NULL){
		mkdir(picture_folder);
		char b[255];
		sprintf(b, "sudo chmod 777 %s", picture_folder);
		system(b);
	}
	sprintf(picture_filename, "%s/astro_%i_%i_%i_%s.%s", picture_folder,h,mn,s, pref, _raspicmd_image_codec[fsettings.camera_image_codec]);
	puts(picture_filename);
	if(fsettings.camera_shooter_count==1)sprintf(cmdline, "raspistill -t 1"); else sprintf(cmdline, "raspistill -t %i -tl %i", t, tl);
	if(fsettings.camera_ss>0)sprintf(cmdline, "%s -ss %i", cmdline, fsettings.camera_ss*1000);
	if(fsettings.camera_vf)sprintf(cmdline, "%s -vf", cmdline);
	if(fsettings.camera_hf)sprintf(cmdline, "%s -hf", cmdline);
	if(fsettings.camera_rot>0)sprintf(cmdline, "%s -rot %i", cmdline, fsettings.camera_rot);
	sprintf(cmdline, "%s -br %i -co %i -awb %s -ex %s -ISO %i -w %i -h %i -e %s -q %i -mm %s -o %s",
					cmdline,
					fsettings.camera_brigthness,
					fsettings.camera_contrast,
					_raspicmd_awb[fsettings.camera_awb],
					_raspicmd_exposure[fsettings.camera_exposure],
					fsettings.camera_ISO,
					fsettings.camera_image_size*BASE_WIDTH,
					fsettings.camera_image_size*BASE_HEIGHT,
					_raspicmd_image_codec[fsettings.camera_image_codec],
					fsettings.camera_image_quality,
					_raspicmd_metering[fsettings.camera_metering],
					picture_filename
					);
	puts(cmdline);

	camera_destroyPreview();
	system(cmdline);
	camera_createPreview();
}
void camera_startRecord(){
	thread_record=pthread_create(&id_record,NULL,&camera_recordVideo,NULL);
}
void* camera_recordVideo(void* args){
	char pref[] = "%04d";

	char picture_folder[255];
	char picture_filename[255];
	char cmdline[255];

	time_t tt = time(NULL);
  	struct tm tm = *localtime(&tt);
	int y = tm.tm_year + 1900;
	int m = tm.tm_mon + 1;
	int d = tm.tm_mday;
	int h = tm.tm_hour;
	int mn = tm.tm_min;
	int s = tm.tm_sec;

	sprintf(picture_folder, "%spictures/astro_%i_%i_%i", program_path, y, m, d);
	if(opendir(picture_folder)==NULL){
		mkdir(picture_folder);
		char b[255];
		sprintf(b, "sudo chmod 777 %s", picture_folder);
		system(b);
	}
	sprintf(picture_filename, "%s/astro_%i_%i_%i.avi", picture_folder,h,mn,s);
	puts(picture_filename);

	if(!fsettings.camera_video_rectime)sprintf(cmdline, "raspivid -k"); else sprintf(cmdline, "raspivid -t %d", fsettings.camera_shooter_count*60000);
	if(fsettings.camera_stab)sprintf(cmdline, "%s -vs", cmdline);
	if(fsettings.camera_ss>0)sprintf(cmdline, "%s -ss %i", cmdline, fsettings.camera_ss*1000);
	if(fsettings.camera_vf)sprintf(cmdline, "%s -vf", cmdline);
	if(fsettings.camera_hf)sprintf(cmdline, "%s -hf", cmdline);
	if(fsettings.camera_rot>0)sprintf(cmdline, "%s -rot %i", cmdline, fsettings.camera_rot);
	sprintf(cmdline, "%s -g 10 -i 'record' -p %s -b %i -co %i -awb %s -ex %s -mm %s -ISO %d -w %d -h %d -cd %s -b %d -fps %i -o %s",
					cmdline,
					_raspicmd_preview_sizes[fsettings.camera_preview_size],
					fsettings.camera_brigthness,
					fsettings.camera_contrast,
					_raspicmd_awb[fsettings.camera_awb],
					_raspicmd_exposure[fsettings.camera_exposure],
					_raspicmd_metering[fsettings.camera_metering],
					fsettings.camera_ISO,
					fsettings.camera_video_size*BASE_WIDTH,
					fsettings.camera_video_size*BASE_HEIGHT,
					_raspicmd_video_codec[fsettings.camera_video_codec],
					fsettings.camera_video_quality*1000000,
					fsettings.camera_video_fps,
					picture_filename
					);
	puts(cmdline);
	camera_destroyPreview();
	sleep(2);
	recording_now = TRUE;
	puts("recording...");
	system(cmdline);
	puts("...end record");
	camera_restartPreview();
}
void camera_createPreview(){
	if(fsettings.camera_autorun){
		thread_camera=pthread_create(&id_camera,NULL,&camera_previewThread,NULL);
	}
}
void camera_destroyPreview(){
	system("sudo killall raspistill");
	system("sudo killall raspivid");
	system("sudo killall python3");
	recording_now = FALSE;
}
void camera_restartPreview(){
	camera_destroyPreview();
	camera_createPreview();
}
void* camera_previewThread(void* args)
{
		if( access( "/dev/video0", F_OK ) != -1 ){
			if(fsettings.camera_preview_on==CAMERA_ON_HDMI){
				char cmdline[255];
				sprintf(cmdline, "raspistill");
				if(fsettings.camera_vf)sprintf(cmdline, "%s -vf", cmdline);
				if(fsettings.camera_hf)sprintf(cmdline, "%s -hf", cmdline);
				if(fsettings.camera_rot>0)sprintf(cmdline, "%s -rot %i", cmdline, fsettings.camera_rot);
				sprintf(cmdline, "%s -t 0 -p %s -awb %s -ex %s -br %i -co %i -ISO %i", 
					cmdline,
					_raspicmd_preview_sizes[fsettings.camera_preview_size],
					_raspicmd_awb[fsettings.camera_awb],
					_raspicmd_exposure[fsettings.camera_exposure],
					fsettings.camera_brigthness,
					fsettings.camera_contrast-100,
					fsettings.camera_ISO
					);
				system(cmdline);
			} else {
                printf("display camera view by video server");
				_system_sh("run_video_stream.sh");
				//system("raspivid -o - -t 0 -hf -w 800 -h 400 -fps 24 |cvlc -vvv stream:///dev/stdin --sout '#standard{access=http,mux=ts,dst=:8554}' :demux=h264");
				//system("raspivid -o - -t 0 -n | cvlc -vvv stream:///dev/stdin --sout '#rtp{sdp=rtsp://:3333/}' :demux=MJPG");
				//system("raspivid -l -o #rtp://0.0.0.0:3333");
			}
		} else {
            printf("no camera fount");
        }
}