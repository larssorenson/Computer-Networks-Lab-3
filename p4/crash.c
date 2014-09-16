#include "ping.h"

// NO PACKET! AAAAAAAAH
void crash(int sig)
{
	write(2, "THERE'S NO RESPONSE!\r\n", 22);
	close(udpSocket);
	exit(-1);
}
