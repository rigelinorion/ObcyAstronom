#include "settings.h"

extern char program_path[255];
struct tsettings fsettings;

void settingsRead(){
	char filename[255];
    FILE *infile; 
    // open file for writing 
	printf("opening settings file now !\n");
    sprintf(filename, "%s%s", program_path, settings_file);
    infile = fopen (filename, "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opend file. Writeing default values to file\n"); 
        settingsWriteDefault();
		settingsWrite();
		infile = fopen (filename, "r");

    } 
    int n,s = 0;
    int r = fscanf(infile, "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i",
                    &fsettings.camera_autorun,
	                &fsettings.camera_shooter_count,
                    &fsettings.camera_shooter_interval,
                    &fsettings.camera_shooter_delay,
                    &fsettings.camera_brigthness,
                    &fsettings.camera_contrast,
                    &fsettings.camera_awb,
                    &fsettings.camera_exposure,
                    &fsettings.camera_ISO,
                    &fsettings.camera_stab,
                    &fsettings.camera_metering,
                    &fsettings.camera_ss,
                    &fsettings.camera_vf,
                    &fsettings.camera_hf,
                    &fsettings.camera_rot,
                    &fsettings.camera_image_size,
                    &fsettings.camera_image_codec,
                    &fsettings.camera_image_quality,
                    &fsettings.camera_video_size,
                    &fsettings.camera_video_codec,
                    &fsettings.camera_video_quality,
                    &fsettings.camera_video_rectime,
                    &fsettings.camera_video_fps,
                    &fsettings.camera_preview_size,
                    &fsettings.camera_preview_on,
                    &fsettings.compas_mdec_cor_deg,
                    &fsettings.compas_mdec_cor_mins,
                    &fsettings.compas_azimuth_cor,
                    &n,
                    &s
            );
	if(r>-1) printf("contents readeen successfully !\n"); else printf("error reading form file !\n");
    // close file 
    fclose (infile); 
}

void settingsWriteDefault(){
	fsettings.camera_autorun = 1;
	fsettings.camera_shooter_count = 1;
	fsettings.camera_shooter_interval = 0;
    fsettings.camera_shooter_delay = 0;
    fsettings.camera_brigthness = 50;
    fsettings.camera_contrast = 100;
    fsettings.camera_awb = 0;
    fsettings.camera_exposure = 0;
    fsettings.camera_ISO = 400;
    fsettings.camera_stab = 0;
    fsettings.camera_metering = 0;
    fsettings.camera_ss = 0;
    fsettings.camera_vf = 0;
    fsettings.camera_hf = 0;
    fsettings.camera_rot = 0;

    fsettings.camera_image_size = 8; //1..9
	fsettings.camera_image_codec = 0;
	fsettings.camera_image_quality = 100;
	fsettings.camera_video_size = 2; //max 5
	fsettings.camera_video_codec = 0;
	fsettings.camera_video_quality = 3;
    fsettings.camera_video_rectime = 0;
    fsettings.camera_video_fps = 15;

    fsettings.camera_preview_size = 0;
	fsettings.camera_preview_on = 0;	
    
	fsettings.compas_mdec_cor_deg = 5;
	fsettings.compas_mdec_cor_mins = 44;
	fsettings.compas_azimuth_cor = 0;
	fsettings.network_type = NETWORK_TYPE_LOCAL;
	fsettings.server_type = SERVER_TYPE_UDP2SER;
}

void settingsWrite(){
    char buffer[128];
    char filename[255];
	FILE *outfile; 

    sprintf(filename, "%s%s", program_path, settings_file);
    outfile = fopen (filename, "w");
    if (outfile == NULL) 
    { 
        printf(stderr, "\nError opend file\n"); 
        //exit (1); 
    } 
    
    // write struct to file 
    int r = fprintf(outfile, "%i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i %i",
                    fsettings.camera_autorun,
	                fsettings.camera_shooter_count,
                    fsettings.camera_shooter_interval,
                    fsettings.camera_shooter_delay,
                    fsettings.camera_brigthness,
                    fsettings.camera_contrast,
                    fsettings.camera_awb,
                    fsettings.camera_exposure,
                    fsettings.camera_ISO,
                    fsettings.camera_stab,
                    fsettings.camera_metering,
                    fsettings.camera_ss,
                    fsettings.camera_vf,
                    fsettings.camera_hf,
                    fsettings.camera_rot,
                    fsettings.camera_image_size,
                    fsettings.camera_image_codec,
                    fsettings.camera_image_quality,
                    fsettings.camera_video_size,
                    fsettings.camera_video_codec,
                    fsettings.camera_video_quality,
                    fsettings.camera_video_rectime,
                    fsettings.camera_video_fps,
                    fsettings.camera_preview_size,
                    fsettings.camera_preview_on,
                    fsettings.compas_mdec_cor_deg,
                    fsettings.compas_mdec_cor_mins,
                    fsettings.compas_azimuth_cor,
                    fsettings.network_type,
                    fsettings.server_type
    );
    if(r > -1)  
        printf("contents to file written successfully !\n"); 
    else 
        printf("error writing file !\n"); 
  
    // close file 
    fclose (outfile); 

}
