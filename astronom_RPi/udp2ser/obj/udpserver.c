#include "udpserver.h"
#include "includes.inc"

extern int DEBUG;
char serialBuffer[bufferSize];
uint8_t serialIndex = 0;
uint8_t ignore = 1; 

int serial_port;
int sockfd; 
struct sockaddr_in servaddr, cliaddr;
int volatile serial_busy = 0; 

/* udp2ser ported from esp32, ESP32 ADAPTER SOURCE: https://github.com/vlaate/SkyWatcherWiFi */

void* udpserverThread(void* args)
{
	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	
	// Filling server information 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	
	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
  	
  	if ((serial_port = serialOpen ("/dev/serial0", 9600)) < 0){
    	fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
  	}

	while(1)
    {
     char dat;
     char buffer[MAXLINE];
     int len, n;
	 len = sizeof(cliaddr); //len is value/resuslt

     n = recvfrom(sockfd, (char *)buffer, MAXLINE , MSG_DONTWAIT, ( struct sockaddr *) &cliaddr, &len);
		if(n>0){
			
			if((buffer[0]=='$')&&(buffer[2]=='$')){			//zdalne sterowanie ostroscia
					if(buffer[1]=='S') pwmWrite(18,0);
					if(buffer[1]=='L') pwmWrite(18,134);
					if(buffer[1]=='R') pwmWrite(18,144);
					if(DEBUG)printf("%c", buffer[1]);		
			} else {
				while(serial_busy)usleep(timeOut*100);
					for(int i = 0; i<n;i++){
						serialPutchar(serial_port, buffer[i]);
						if(DEBUG)printf("%c", buffer[i]);	
					}
			}
			if(DEBUG)printf("\n", ' ');
			ignore = 1;
		} 
		
		// 
		if(serialDataAvail (serial_port)){
			serial_busy = 1;
			dat = serialGetchar (serial_port);
			while(serialDataAvail (serial_port)){ 
				dat = serialGetchar (serial_port);
				if((dat==61) || (dat==33)){
					ignore = 0;
				}
				if(!ignore){
					serialBuffer[serialIndex] = dat; 
          			if (serialIndex < bufferSize - 1){
            			serialIndex++;
          			}
				}
				usleep(timeOut*100);
			}
			serial_busy = 0;
			sendto(sockfd, (char *)serialBuffer, serialIndex,  MSG_DONTWAIT, (const struct sockaddr *) &cliaddr, len);
			serialIndex = 0;
		}
	}  
}