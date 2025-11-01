#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;       /* next free position in buf */

int getch(void)      /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;

	while (isspace(c = getch()))    /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);                 /* not a number */
		return 0;
	}

	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		int next = getch();
		if (!isdigit(next)) {       /* sign not followed by digit */
			if (next != EOF)
				ungetch(next);
			ungetch(c);
			return 0;
		}
		c = next;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;

	if (c != EOF)
		ungetch(c);
	return c;
}

int main(void)
{
	int n, array[10], i = 0;

	printf("Enter integers (non-number to stop):\n");
	while (getint(&n) != 0 && i < 10)
		array[i++] = n;

	printf("You entered: ");
	for (int j = 0; j < i; j++)
		printf("%d ", array[j]);
	printf("\n");
	return 0;
}

