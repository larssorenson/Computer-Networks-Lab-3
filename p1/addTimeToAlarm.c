#include "myreminder.h"

int addTimeToAlarm(char time)
{
	switch(time)
	{
		case '9':
			currentAlarm->time *= 10;
			currentAlarm->time += 9;
		break;
		case '8':
			currentAlarm->time *= 10;
			currentAlarm->time += 8;
		break;
		case '7':
			currentAlarm->time *= 10;
			currentAlarm->time += 7;
		break;
		case '6':
			currentAlarm->time *= 10;
			currentAlarm->time += 6;
		break;
		case '5':
			currentAlarm->time *= 10;
			currentAlarm->time += 5;
		break;
		case '4':
			currentAlarm->time *= 10;
			currentAlarm->time += 4;
		break;
		case '3':
			currentAlarm->time *= 10;
			currentAlarm->time += 3;
		break;
		case '2':
			currentAlarm->time *= 10;
			currentAlarm->time += 2;
		break;
		case '1':
			currentAlarm->time *= 10;
			currentAlarm->time += 1;
		break;
		case '0':
			currentAlarm->time *= 10;
		break;
		default:
			return -1;
		break;
	}
	
	return 0;
}
