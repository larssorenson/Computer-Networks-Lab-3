#include "mobilereminder.h"

void rewindAlarms(int number)
{
	while(currentAlarm->reminderNumber > number && currentAlarm->prev != NULL)
		currentAlarm = currentAlarm->prev;
}
