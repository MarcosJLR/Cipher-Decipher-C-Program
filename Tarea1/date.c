#include "date.h"

// Recibe una fecha dada en dia, mes y ano y la devuelve como un unico entero
long dateToInt(long day, long month, long year){
	return day + 100*month + 10000*year;
}
/* Recibe un entero donde las primeras dos cifras son el dia, las segundas dos el 
   mes y el resto el ano y los asigna a tres enteros que represetan cada uno de estos.
*/
void intToDate(long date, int *day, int *month, int *year){
	*day = date%100;
	date /= 100;
	*month = date%100;
	date /= 100;
	*year = date;
}