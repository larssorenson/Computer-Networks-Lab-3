#include "myreminder.h"

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
		int digit = (time-((int)(time/10)*10));
		switch(digit)
		{
			case 0:
				strcat(result, "0");
				break;
			case 1:
				strcat(result, "1");
				break;
			case 2:
				strcat(result, "2");
				break;
			case 3:
				strcat(result, "3");
				break;
			case 4:
				strcat(result, "4");
				break;
			case 5:
				strcat(result, "5");
				break;
			case 6:
				strcat(result, "6");
				break;
			case 7:
				strcat(result, "7");
				break;
			case 8:
				strcat(result, "8");
				break;
			case 9:
				strcat(result, "9");
				break;
		}
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
