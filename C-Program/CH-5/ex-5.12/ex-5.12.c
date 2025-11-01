#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTOPS 100
#define TABSIZE 8  /* default tab width */

/* global tab configuration */
int tabstops[MAXSTOPS];
int nstops = 0;
int start = 1;   /* starting column (m) */
int step = TABSIZE; /* tab interval (n) */

/* check if current column is a tab stop */
int is_tabstop(int col)
{
	if (nstops == 0)  /* generate stops if none explicitly given */
		return (col >= start && ((col - start) % step == 0));
	for (int i = 0; i < nstops; i++)
		if (col == tabstops[i])
			return 1;
	return 0;
}

/* parse command line: supports -m +n and explicit stops */
void settabstops(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-')        /* -m form */
			start = atoi(argv[i] + 1);
		else if (argv[i][0] == '+')   /* +n form */
			step = atoi(argv[i] + 1);
		else                          /* explicit stops */
			tabstops[nstops++] = atoi(argv[i]);
	}
}

/* DETAB: replace tabs with spaces */
void detab(void)
{
	int c, col = 1;
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
}

/* ENTAB: replace spaces with tabs */
void entab(void)
{
	int c, col = 1, nspace = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			nspace++;
			if (is_tabstop(col)) {
				putchar('\t');
				nspace = 0;
			}
			col++;
		}
		else {
			while (nspace-- > 0)
				putchar(' ');
			nspace = 0;
			putchar(c);
			if (c == '\n')
				col = 1;
			else
				col++;
		}
	}
}

/* main: decides whether to run as entab or detab */
int main(int argc, char *argv[])
{
	int entab_mode = 0;
	char *prog = argv[0];

	if (strstr(prog, "entab"))
		entab_mode = 1;
	else if (strstr(prog, "detab"))
		entab_mode = 0;

	settabstops(argc, argv);

	if (entab_mode)
		entab();
	else
		detab();

	return 0;
}

