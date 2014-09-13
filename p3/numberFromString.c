#include "ping.h"

int numberFromString(char* str)
{
	if(!str)
		return 0;
	
	int x = 0;
	int result = 0;
	while(str[x] != '\0' && x < 12)
	{
		#ifdef Debug
			printf("%02x %c %d ", str[x], str[x], str[x]);
			printf("\r\n");
		#endif
		if(str[x] < 58 && str[x] > 47)
		{
			result += ((int)(str[x]))-48;
			result *= 10;
		}
		
		x++;
		
	}
	
	result /= 10;
	
	return result;
}
