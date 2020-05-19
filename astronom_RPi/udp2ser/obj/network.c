#include "network.h"
#include "settings.h"
extern struct tsettings fsettings;

void networkInit(){
	network_read_network_adaptor_settings();
	if (strcmp((const char*)&NetworkAdaptorIpAddress[0][0], "192.168.4.1")== 0)fsettings.network_type = NETWORK_TYPE_AP; else fsettings.network_type = NETWORK_TYPE_LOCAL;
}
void network_read_network_adaptor_settings (void)
{
	struct ifaddrs * ifAddrStruct = NULL;
	struct ifaddrs * ifa = NULL;
	void * tmpAddrPtr = NULL;
	found_network_adaptors_count = 0;
	getifaddrs(&ifAddrStruct);

	for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
	{
		if (ifa->ifa_addr->sa_family == AF_INET)
		{
			//GET IP ADDRESS
			tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
			char IpAddressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, IpAddressBuffer, INET_ADDRSTRLEN);
			//GET SUBNET MASK
			tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_netmask)->sin_addr;
			char SnAddressBuffer[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, tmpAddrPtr, SnAddressBuffer, INET_ADDRSTRLEN);

			if (strncmp((const char*)&IpAddressBuffer[0], "127.0.0.1", 10) != 0)
			{
				if (found_network_adaptors_count < MAX_NETWORK_ADAPTORS)
				{
					strncpy(&NetworkAdaptorName[found_network_adaptors_count][0], ifa->ifa_name, MAX_ADAPTOR_NAME_LENGTH);
					strncpy(&NetworkAdaptorIpAddress[found_network_adaptors_count][0], IpAddressBuffer, INET_ADDRSTRLEN);
					strncpy(&NetworkAdaptorSubnetMask[found_network_adaptors_count][0], SnAddressBuffer, INET_ADDRSTRLEN);
					found_network_adaptors_count++;
				}
			}

		}
		else if (ifa->ifa_addr->sa_family == AF_INET6)
		{
			tmpAddrPtr = &((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
			char addressBuffer[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
		}

	} //for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
	if (ifAddrStruct != NULL)
		freeifaddrs(ifAddrStruct);
	return;
}