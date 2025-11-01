//detab — Replace Tabs with Spaces

#include <stdio.h>
#include <stdlib.h>

#define MAXSTOPS 100
#define TABSIZE 8   /* default tab size */

/* store tab stops */
int tabstops[MAXSTOPS];
int nstops = 0;

/* check if column is a tab stop */
int is_tabstop(int col)
{
	int i;
	if (nstops == 0)     /* default every TABSIZE cols */
		return (col % TABSIZE == 0);
	for (i = 0; i < nstops; i++)
		if (col == tabstops[i])
			return 1;
	return 0;
}

/* main detab */
int main(int argc, char *argv[])
{
	int c, col = 1;

	/* load custom tab stops if given */
	while (--argc > 0)
		tabstops[nstops++] = atoi(*++argv);

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			do {
				putchar(' ');
				col++;
			} while (!is_tabstop(col));
		} 
		else if (c == '\n') {
			putchar(c);
			col = 1;
		}
		else {
			putchar(c);
			col++;
		}
	}
	return 0;
}

