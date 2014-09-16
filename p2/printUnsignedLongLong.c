#include "mychecksum.h"

void printUnsignedLongLong(unsigned long long number)
{
	
	char output[20] = {0};
	int length = 0;
	while(number != 0)
	{
		output[length] = (char)((number - (((unsigned long long)(number/10))*10))+48);
		length++;
		number /= 10;
	}
	
	for(int x = length; x > -1; x--)
	{
		write(2, &output[x], 1);
	}
	
}
