#include "ping.h"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		write(2, "You must supply a port!\r\n", 25);
		return -1;
	}
	
	int port = numberFromString(argv[1]);
	#ifdef Debug
		printInt(port);
	#endif
	
	
	
}
