#include "myreminder.h"

// Output the time of day, followed by the current Alarm's reminder
// Then set an alarm for the next reminder
void writeAlarm(int sig)
{
	writeTimeOfDay();
	write(2, currentAlarm->reminder, strlen(currentAlarm->reminder));
	write(2, "\r\n", 2);
	currentAlarm = currentAlarm->next;
	setAlarm();
	
}
