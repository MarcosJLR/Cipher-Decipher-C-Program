#include "date.h"

long dateToInt(long day, long month, long year){
	return day + 100*month + 10000*year;
}
void intToDate(long date, int *day, int *month, int *year){
	*day = date%100;
	date /= 100;
	*month = date%100;
	date /= 100;
	*year = date;
}