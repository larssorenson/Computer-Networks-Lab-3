#include "ping.h"

void printInt(int number)
{
	char output[12] = {0};
	int length = 0;
	while(number != 0)
	{
		output[length] = (char)((number - (((int)(number/10))*10))+48);
		length++;
		number /= 10;
	}
	
	int x;
	for(x = length; x > -1; x--)
	{
		write(2, &output[x], 1);
	}
	
}
