#ifndef udpserver2_H
#define udpserver2_H

#include "includes.inc"

#define PORT2	 	11110 
#define MAXLINE 	255

void udpserver2Send(char udpstring[]);
void* udpserver2Thread(void* args);

#endif