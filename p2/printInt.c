#include "mychecksum.h"

void printInt(int number)
{
	char buffer[2];
	buffer[0] = 0;
	buffer[1] = 0;
	while(number != 0)
	{
		buffer[0] = (char)((number - (((int)(number/10))*10))+48);
		write(2, buffer, 1);
		number /= 10;
	}
}
