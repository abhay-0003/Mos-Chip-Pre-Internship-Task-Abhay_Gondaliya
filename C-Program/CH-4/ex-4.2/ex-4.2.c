#include <stdio.h>
#include <ctype.h>

/* atof: convert string s to double, handling scientific notation */
double atof_extended(char s[])
{
	double val, power;
	int i, sign, exp_sign, exp_val;

	// skip white space
	for (i = 0; isspace(s[i]); i++)
		;

	// handle optional sign
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;

	// integer part
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	// fractional part
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	val = sign * val / power;

	// scientific notation (e or E)
	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		exp_sign = (s[i] == '-') ? -1 : 1;
		if (s[i] == '+' || s[i] == '-')
			i++;

		for (exp_val = 0; isdigit(s[i]); i++)
			exp_val = 10 * exp_val + (s[i] - '0');

		// adjust by exponent
		double exp_factor = 1.0;
		while (exp_val-- > 0)
			exp_factor *= 10.0;

		if (exp_sign == 1)
			val *= exp_factor;
		else
			val /= exp_factor;
	}

	return val;
}

/* Test main */
int main(void)
{
	printf("%g\n", atof_extended("123.45e-6"));   // 0.00012345
	printf("%g\n", atof_extended("1.23E3"));      // 1230
	printf("%g\n", atof_extended("-4.56e2"));     // -456
	printf("%g\n", atof_extended("7.89E-2"));     // 0.0789
	return 0;
}

