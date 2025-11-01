#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (c == EOF)
		return;  // ignore pushing EOF

	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

/* test main */
int main(void)
{
	int c;

	printf("Enter a character: ");
	c = getch();
	printf("\nYou entered: %c\n", c);

	ungetch(EOF);   // should do nothing
	ungetch(c);     // push back the character
	printf("getch after ungetch: %c\n", getch());

	return 0;
}

