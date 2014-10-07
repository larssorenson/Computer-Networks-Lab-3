#include "vpntunnel.h"

// Modular function to check argc count
// Will return non-zero on error
// 0 on success
int checkArgc(int argc, int count, char* message)
{
	if (argc < count)
	{
		printf("%s\r\n", message);
		return 1;
	}
	
	return 0;
}
