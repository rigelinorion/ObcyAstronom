#ifndef compas_H
#define compas_H

#include "./sense/ICM20948.h"

#define M_PI 3.14159265358979323846
#define PI   3.14159265358979323846

void compas_init();
void* compas_calibration_thread(void* args);
void compas_calibrate();
int compas_getazimuth();

#endif