#include "ping.h"

void printLong(long number)
{
	
	char output[20] = {0};
	int length = 0;
	while(number != 0)
	{
		output[length] = (char)((number - (((long)(number/10))*10))+48);
		length++;
		number /= 10;
	}
	
	for(int x = length; x > -1; x--)
	{
		write(2, &output[x], 1);
	}
	
}
