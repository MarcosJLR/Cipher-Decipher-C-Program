#include "date.h"

long dateToInt(int *day, int *month, int *year){
	long date;
	date=(*day)+100*(*month)+1000*(*year);
}
void intToDate(long date, int *day, int *month, int *year){
	*day=date%100;
	date=date/100;
	*month=date%100;
	date=date/100;
	*year=date;
}