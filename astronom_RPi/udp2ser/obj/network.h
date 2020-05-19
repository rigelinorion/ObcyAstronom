#ifndef NETWORK_H
#define NETWORK_H

#include "includes.inc"


#define	MAX_NETWORK_ADAPTORS						3
#define	MAX_ADAPTOR_NAME_LENGTH						20

char addr[INET_ADDRSTRLEN];
uint8_t found_network_adaptors_count;
char NetworkAdaptorName[MAX_NETWORK_ADAPTORS][MAX_ADAPTOR_NAME_LENGTH];
char NetworkAdaptorIpAddress[MAX_NETWORK_ADAPTORS][INET_ADDRSTRLEN];
char NetworkAdaptorSubnetMask[MAX_NETWORK_ADAPTORS][INET_ADDRSTRLEN];

void networkInit();
void network_read_network_adaptor_settings (void);
#endif 