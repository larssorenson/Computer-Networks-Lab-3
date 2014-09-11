#include "myreminder.h"

#ifndef Testing
int main(int argc, char** argv)
{
	// Need the file to read from
	if(argc < 2)
	{
		write(2, "You must supply a file name to read from!\r\n", 43);
		return 1;
	}
	
	// Set the alarm handler for SIGALRM
	int resp = setAlarmHandler();
	if(resp)
	{
		write(2, "Error! Could not set Signal Alarm Handler!\r\n", 44);
		return 1;
	}
	
	// Parse the file passed in
	if(parse(argv[1]))
	{
		// If we've successfully parsed
		// We'll time stamp the start for comparison
		writeTimeOfDay();
		write(2, "Reminders set!\r\n", 16);
		
		// Set the first alarm
		alarm(currentAlarm->time);
		
		// Busy wait until all alarms have been processed.
		// currentAlarm is a global linked list of alarms
		// and will move forward until currentAlarm is NULL
		// so this will wait until we've hit the tail
		while(currentAlarm){}	
	}
	
	return 0;
}
#endif
