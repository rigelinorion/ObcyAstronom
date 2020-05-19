#include "compas.h"
#include "includes.inc"
#include "./sense/ICM20948.h"
#include "settings.h"
#include "display.h"


int minX = 0;
int maxX = 0;
int minY = 0;
int maxY = 0;
int offX = 0;
int offY = 0;
int oldX = 0;
int oldY = 0;

int udpsend = 0;


extern struct tsettings fsettings;
int compas_started = 0;


IMU_EN_SENSOR_TYPE enMotionSensorType;
IMU_ST_ANGLES_DATA stAngles;
IMU_ST_SENSOR_DATA stGyroRawData;
IMU_ST_SENSOR_DATA stAccelRawData;
IMU_ST_SENSOR_DATA stMagnRawData;

int eqcounter = 0;

compas_init(){
	
	
    imuInit(&enMotionSensorType);
	if(IMU_EN_SENSOR_TYPE_ICM20948 == enMotionSensorType)
	{
		printf("Motion sersor is ICM-20948\n" );
	}
	else
	{
		printf("Motion sersor NULL\n");
	}
	
}
void compas_calibrate(){
    minX = 0;
    maxX = 0;
    minY = 0;
    maxY = 0;
    offX = 0;
    offY = 0;
    oldX = 0;
    oldY = 0;
    eqcounter = 0;
    int loopexit = 0;
    //
    while(!loopexit){
        imuDataGet( &stAngles, &stGyroRawData, &stAccelRawData, &stMagnRawData);
        if (stMagnRawData.s16X < minX) minX = stMagnRawData.s16X;
  		if (stMagnRawData.s16X > maxX) maxX = stMagnRawData.s16X;
  		if (stMagnRawData.s16Y < minY) minY = stMagnRawData.s16Y;
  		if (stMagnRawData.s16Y > maxY) maxY = stMagnRawData.s16Y;
		
		offX = (maxX + minX)/2;
 		offY = (maxY + minY)/2;
        
        delay(100);
		//printf("counter: %d  offX: %d  oldX: %d  offY: %d  oldY: %d \r\n", eqcounter, offX, oldX, offY, oldY);
		if((oldX == offX)&&(oldY==offY))eqcounter++;
		oldX = offX;
		oldY = offY;
        char buff[255];
        sprintf(buff,"| %d %d %d %d %d", offX, offY, stMagnRawData.s16X, stMagnRawData.s16Y, stMagnRawData.s16Y, eqcounter);
        udpserver2Send(buff);
		if(eqcounter==200){
            sprintf(buff,"| %d %d", offX, offY);
            udpserver2Send(buff);
            printf("Calibration complette --- offX: %d  offY: %d \r\n",offX, offY);
			compas_started = 0;
            displayMessage("Done");
            loopexit = 1;
            udpsend = 0;
		}
    }
}


int compas_getazimuth(){
    int ax, ay = 0;
    imuDataGet( &stAngles, &stGyroRawData, &stAccelRawData, &stMagnRawData);
    ax = stMagnRawData.s16X - offX;
    ay = stMagnRawData.s16Y - offY;
    float heading = atan2(ay, ax);
    float declinationAngle = (fsettings.compas_mdec_cor_deg + (fsettings.compas_mdec_cor_mins / 60.0)) / (180 / M_PI);
    heading += declinationAngle;

    if (heading < 0) heading += 2 * PI;
    if (heading > 2 * PI) heading -= 2 * PI;

    float headingDegrees = heading * 180/M_PI;
    int az = (int) headingDegrees;
    int cor = fsettings.compas_azimuth_cor;
    int x = az+cor;

       if(x<0)headingDegrees = 359 - abs(x);
       if(x=0)headingDegrees = 0;
       if(x>0)headingDegrees = headingDegrees+x;

    return (int)headingDegrees;

}
int compas_getlevel(){
    imuDataGet( &stAngles, &stGyroRawData, &stAccelRawData, &stMagnRawData);
    return (int)stMagnRawData.s16Z;
}