#ifndef camera_H
#define camera_H

#include "includes.inc"
#include "settings.h"

#define BASE_WIDTH     320
#define BASE_HEIGHT    240
#define PROGRAM_PATH  "/home/pi/astronom/"

void camera_init();
void camera_createPreview();
void camera_destroyPreview();
void camera_restartPreview();
void camera_raspistill_takepicture();
void camera_startRecord();
void* camera_recordVideo(void* args);
void* camera_previewThread(void* args);

#endif