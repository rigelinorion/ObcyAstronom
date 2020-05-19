#ifndef udpserver_H
#define udpserver_H

#include "includes.inc"

#define PORT	 	11880 
#define MAXLINE 	1024 
#define timeOut 	20
#define bufferSize 	1024

void* udpserverThread(void* args);

#endif