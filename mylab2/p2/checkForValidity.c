#include "mobilereminder.h"

int checkForValidity(char* in)
{
	if(in)
	{
		char* p = in;
		while(*p != '\0')
		{
			if((*p >= 48 && *p <= 57) || (*p >= 65 && *p <= 90) || (*p >= 97 && *p <= 122) || *p == (int)'\t')
			{
				p++;
			}
			
			else
			{
				return 0;
			}
			
		}
		
		return 1;
	}
	
	return 0;
	
}
