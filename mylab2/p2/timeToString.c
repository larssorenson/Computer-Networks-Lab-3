#include "mobilereminder.h"


// This will take in an integer and go digit by digit through it
// and construct a string that will represent the time.
// Unfortunately, the way it is written the number will be reversed
// so we have to reverse it before we return it
char* timeToString(int time)
{
	char* result = malloc(sizeof(char)*11);
	if(!result)
	{
		return NULL;
	}
	
	memset(result, 0, 11);
	int length = 0;
	while(time > 0)
	{
		result[length] = (char)((time - (((int)(time/10))*10))+48);
		time /= 10;
		length++;
	}
	
	char* rev_result = malloc(sizeof(char)*(length+1));
	if(!rev_result)
		return NULL;
		
	memset(rev_result, 0, length+1);
	
	int y;
	for(y = 0; y < length; y++)
	{
		rev_result[y] = result[(length-1)-y];
	}
	
	return rev_result;
}
