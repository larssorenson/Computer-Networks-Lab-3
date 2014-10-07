#include "mobilereminder.h"

void setClientAlarm()
{
	if(!registered)
	{
		alarm(5);
		alarmSet = 1;
	}
	
}
