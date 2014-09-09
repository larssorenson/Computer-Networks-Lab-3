#include "myreminder.h"

// This was to be used for timestamping reminders
// but things like leap years / leap seconds make it imprecise
// so it was easier to just print out the unix epoch
char* secondsToDate(int time)
{
	int year = 1970;
	int month = 1;
	int day = 1;
	int hour = 1;
	int minute = 0;
	int second = 0;
	while(time > 31449600)
	{
		year++;
		time -= 31449600;
	}
	
	while(time > 2419200)
	{
		month++;
		time -= 2419200;
	}
	
	while(time > 86400)
	{
		day++;
		time -= 86400;
	}
	
	while(time > 3600)
	{
		hour++;
		time -= 3600;
	}
	
	while(time > 60)
	{
		minute++;
		time -= 60;
	}
	
	while(time > 0)
	{
		second++;
		time -= 1;
	}
	
	int total = 4 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1;
	//          YR  /  DAY  /  MNTH _   HR  :  MN   :  S '\0'
	char* res = (char*)malloc(sizeof(char)*(total));
	memset(res, 0, total);
	
	strcat(res, timeToString(year));
	strcat(res, "/");
	if(day < 10)
		strcat(res, "0");
	strcat(res, timeToString(day));
	strcat(res, "/");
	if(month < 10)
		strcat(res, "0");
	strcat(res, timeToString(month));
	strcat(res, " ");
	if(hour < 10)
		strcat(res, "0");
	strcat(res, timeToString(hour));
	strcat(res, ":");
	if(minute < 10)
		strcat(res, "0");
	strcat(res, timeToString(minute));
	strcat(res, ":");
	if(second < 10)
		strcat(res, "0");
	strcat(res, timeToString(second));
	
	return res;
}
