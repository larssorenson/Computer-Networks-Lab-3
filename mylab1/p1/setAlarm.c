#include "myreminder.h"

void setAlarm()
{
	// If we have an alarm available that can be set
	if(currentAlarm)
	{
		// If we are out of time for the reminder, output it immediately!
		if(currentAlarm->time - currentAlarm->prev->time <= 0)
			writeAlarm(0);
		else
			// Otherwise, schedule it for the future
			alarm(currentAlarm->time - currentAlarm->prev->time);
	}
}
