#include <stdio.h>

/* print Celsius-Fahrenheit table in reverse order */

int main()
{
	float fahr, celsius;

	printf("Celsius   Fahrenheit\n"); // heading
	printf("---------------------\n");

	for (celsius = 300; celsius >= 0; celsius = celsius - 20) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%6.0f %12.1f\n", celsius, fahr);
		printf("---------------------\n");
	}
	return 0;
}

