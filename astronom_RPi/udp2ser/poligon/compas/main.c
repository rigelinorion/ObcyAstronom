#include "includes.inc"
#include "ICM20948.h"

#define M_PI 3.14159265358979323846
#define PI 3.14159265358979323846
#define settings_file "./settings.dat"

#define SERVER "127.0.0.1"
#define MAXLINE 512	//Max length of buffer
#define PORT 11110	//The port on which to send data


int minX = 0;
int maxX = 0;
int minY = 0;
int maxY = 0;
int offX = 0;
int offY = 0;
int oldX = 0;
int oldY = 0;

int sockfd; 
struct sockaddr_in servaddr, cliaddr;

struct tsettings {
	
	uint8_t camera_autorun;
	uint8_t camera_display_on;
	uint8_t camera_shooter_count;
	uint8_t camera_shooter_interval;
	
	signed int compas_mdec_cor_deg; //5;
	int compas_mdec_cor_min; //44;
	signed int compas_azimuth_cor; //0;
	
	uint8_t network_type; //NETWORK_TYPE_LOCAL;
	uint8_t server_type; //SERVER_TYPE_INDY;
};

struct tsettings fsettings;

IMU_EN_SENSOR_TYPE enMotionSensorType;
IMU_ST_ANGLES_DATA stAngles;
IMU_ST_SENSOR_DATA stGyroRawData;
IMU_ST_SENSOR_DATA stAccelRawData;
IMU_ST_SENSOR_DATA stMagnRawData;

struct sockaddr_in si_other;
int s, i, slen=sizeof(si_other);
char buf[MAXLINE];
char message[MAXLINE];

int eqcounter = 0;

void die(char *s)
{
	perror(s);
	exit(1);
}
void udpInit(){
	if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		die("socket");
	}
	memset((char *) &si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);

	if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}
}

void settingsRead(){
	FILE *infile; 
    // open file for writing 
	printf("opening settings file now !\n");
    infile = fopen (settings_file, "r"); 
    if (infile == NULL) 
    { 
        fprintf(stderr, "\nError opend file\n"); 
    } 

    fread(&fsettings, sizeof(struct tsettings), 1, infile);
	printf("contents readeen successfully !\n"); 
    // close file 
    fclose (infile); 
}

void compas_calibrate(){
    //
    while(1){
        imuDataGet( &stAngles, &stGyroRawData, &stAccelRawData, &stMagnRawData);
        if (stMagnRawData.s16X < minX) minX = stMagnRawData.s16X;
  		if (stMagnRawData.s16X > maxX) maxX = stMagnRawData.s16X;
  		if (stMagnRawData.s16Y < minY) minY = stMagnRawData.s16Y;
  		if (stMagnRawData.s16Y > maxY) maxY = stMagnRawData.s16Y;
		
		offX = (maxX + minX)/2;
 		offY = (maxY + minY)/2;
        
        delay(100);
		printf("counter: %d  offX: %d  oldX: %d  offY: %d  oldY: %d \r\n", eqcounter, offX, oldX, offY, oldY);
		if((oldX == offX)&&(oldY==offY))eqcounter++;
		oldX = offX;
		oldY = offY;
		if(eqcounter==200){
			printf("Calibration complette --- offX: %d  offY: %d \r\n",offX, offY);
			break;
		}
    }
}


int compas_getazimuth(){
    int ax, ay = 0;
    imuDataGet( &stAngles, &stGyroRawData, &stAccelRawData, &stMagnRawData);
    ax = stMagnRawData.s16X - offX;
    ay = stMagnRawData.s16Y - offY;
    float heading = atan2(ay, ax);
    float declinationAngle = (fsettings.compas_mdec_cor_deg + (fsettings.compas_mdec_cor_min / 60.0)) / (180 / M_PI);
    heading += declinationAngle;

    if (heading < 0) heading += 2 * PI;
    if (heading > 2 * PI) heading -= 2 * PI;

    float headingDegrees = heading * 180/M_PI;

    return (int)headingDegrees;

}

int main(int argc, char* argv[])
{
	settingsRead();
	int eqcounter = 0;
	imuInit(&enMotionSensorType);
	if(IMU_EN_SENSOR_TYPE_ICM20948 == enMotionSensorType) printf("Motion sersor is ICM-20948\n" ); else printf("Motion sersor NULL\n");
	compas_calibrate();
	int az = compas_getazimuth();
	printf("Azimuth: %d\r\n",az);
	udpInit();

	while(1)
    {
		char outbuffer[2];
     	char buffer[MAXLINE];
     	int len, n;
	 	len = sizeof(si_other); //len is value/resuslt

     	n = recvfrom(s, (char *)buffer, MAXLINE , MSG_DONTWAIT, ( struct sockaddr *) &si_other, &len);
		if(n>0){
			if((buffer[0]=='$')&&(buffer[2]=='$')){
				if(buffer[1]=='X'){
					return 0;
				} 	
			}

		} 
		
		int az = compas_getazimuth();
		outbuffer[0] = '$';
		if(az>255){
			outbuffer[1] = 255;
			outbuffer[2] = az-255;
		} else {
			outbuffer[1] = az;
			outbuffer[2] = 0;
		}
		outbuffer[3] = '$';
		sendto(s, (char *)outbuffer, 4,  MSG_DONTWAIT, (const struct sockaddr *) &si_other, len);
		usleep(1000*100);		
	}  
	return 0;
}
