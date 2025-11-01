#include <stdio.h>

int buf = 0;     // single pushback character
int buf_full = 0;  // flag to indicate if buffer is full

int getch(void)
{
	if (buf_full) {
		buf_full = 0;      // clear flag
		return buf;        // return pushed-back char
	} 
	else
		return getchar();  // otherwise get fresh input
}

void ungetch(int c)
{
	if (buf_full)
		printf("ungetch: buffer already full\n");
	else {
		buf = c;
		buf_full = 1;      // mark buffer as full
	}
}

/* test main */
int main(void)
{
	int c;

	c = getchar();
	ungetch(c);
	printf("First getch: %c\n", getch());
	printf("Second getch (reads new input): %c\n", getch());

	return 0;
}

