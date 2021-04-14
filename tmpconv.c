#include <stdio.h>

#define MIN_TEMP 0
#define MAX_TEMP 50000

double CelsiusToFarenheit(double arg)
{
    double res = 0.0;
    res = arg * 9.0;
    res = res / 5.0;
    res = res + 32.0;
    return res;
}

int main ( int argc, char **argv )
{
    int lowLim = -1;
    int highLim = -1;
    int step = -1;
    int diff = 0;

    while( lowLim < (int) MIN_TEMP ) {
	printf("Please give in a lower limit, limit >= %d: ", (int) MIN_TEMP);
	scanf("%d", &lowLim);
    }

    while( ( highLim <= lowLim ) || ( highLim > (int) MAX_TEMP ) ) {
	printf("Please give in a higher limit, %d > limit <= %d: ", lowLim, (int) MAX_TEMP);
	scanf("%d", &highLim);
    }

    diff = highLim - lowLim;
    while( ( step <= 0 ) || ( step > diff ) ) {
	printf("Please give in a step, 0 < step <= %d: ", diff);
	scanf("%d", &step);
    }

    printf("\nCelsius\t\tFarenheit");
    printf("\n-------\t\t---------\n");
    double i;
    for(i = lowLim; i < highLim; i+=step)
    {
	printf("%6f\t%6f\n", i, CelsiusToFarenheit(i));
    }
    printf("\n");
    return 0;
}
