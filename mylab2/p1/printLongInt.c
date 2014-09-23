#include "mobilereminder.h"

void printLongInt(long int number, char* buffer)
{
	#ifdef Debug
		printf("Printing Long: %ld\r\n", number);
	#endif
	char output[11] = {0};
	int length = 0;
	while(number != 0)
	{
		output[length] = (char)((number - (((int)(number/10))*10))+48);
		
		#ifdef Debug
			printf("%s", &output[length]);
		#endif
		length++;
		number /= 10;
	}
	#ifdef Debug
		printf("\r\n");
	#endif
	int x;
	for(x = length; x > -1; x--)
	{
		strncat(buffer, &output[x], 1);
		#ifdef Debug
			printf("Buffer So Far: %s\r\n", buffer);
			printf("Character Added: %c\r\n", output[x]);
		#endif
	}
	
	strcat(buffer, "\0");
	
	#ifdef Debug
		printf("\r\n");
	#endif
}
