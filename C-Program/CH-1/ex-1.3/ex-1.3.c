#include <stdio.h>

/* print Fahrenheit-Celsius table with heading */

int main()
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;      /* lower limit of temperature scale */
	upper = 300;    /* upper limit */
	step = 20;      /* step size */

	fahr = lower;

	printf("Fahrenheit   Celsius\n");  // heading
	printf("---------------------\n");

	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr - 32.0);
		printf("%6.0f %12.1f\n", fahr, celsius);
		printf("---------------------\n");
		fahr = fahr + step;
	}
	return 0;
}

