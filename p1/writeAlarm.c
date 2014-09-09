#include "myreminder.h"

void writeAlarm(int sig)
{
	writeTimeOfDay();
	write(2, currentAlarm->reminder, strlen(currentAlarm->reminder));
	write(2, "\r\n", 2);
	currentAlarm = currentAlarm->next;
	setAlarm();
	
}
