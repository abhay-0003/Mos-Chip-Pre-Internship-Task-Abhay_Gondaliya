#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

/* buffer for ungetch */
char buf[BUFSIZE];
int bufp = 0;

/* getch: get a (possibly pushed-back) character */
int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getfloat: get next floating-point number from input into *pf */
int getfloat(float *pf)
{
	int c, sign;
	float power;

	while (isspace(c = getch()))   /* skip white space */
		;

	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
		ungetch(c);                /* not a number */
		return 0;
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-') {
		int next = getch();
		if (!isdigit(next) && next != '.') {
			if (next != EOF)
				ungetch(next);
			ungetch(c);
			return 0;
		}
		c = next;
	}
	/* integer part */
	for (*pf = 0.0; isdigit(c); c = getch())
		*pf = 10.0 * *pf + (c - '0');

	/* fractional part */
	if (c == '.')
		c = getch();

	for (power = 1.0; isdigit(c); c = getch()) {
		*pf = 10.0 * *pf + (c - '0');
		power *= 10.0;
	}

	*pf = sign * (*pf / power);

	if (c != EOF)
		ungetch(c);

	return c;
}

/* --- Test Program --- */
int main(void)
{
	float array[10];
	int n = 0;
	int status;

	printf("Enter floating-point numbers (non-number to stop):\n");

	while (n < 10 && (status = getfloat(&array[n])) != EOF && status != 0)
		n++;
	printf("\nYou entered:\n");
	for (int i = 0; i < n; i++)
		printf("%f\n", array[i]);

	return 0;
}

