#include <stdio.h>

/* print Celsius-Fahrenheit table */

int main()
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;      /* lower limit of temperature scale */
	upper = 300;    /* upper limit */
	step = 20;      /* step size */

	celsius = lower;

	printf("Celsius   Fahrenheit\n"); // heading
	printf("---------------------\n");

	while (celsius <= upper) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%6.0f %12.1f\n", celsius, fahr);
		printf("---------------------\n");
		celsius = celsius + step;
	}
	return 0;
}

