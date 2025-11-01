#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000   /* maximum number of input lines */
#define MAXLEN 1000     /* maximum length of any input line */
#define DEFAULT_N 10    /* default number of lines to print */

char *lineptr[MAXLINES];   /* pointers to text lines */

/* read a line into s, return length */
int getline_custom(char *s, int lim)
{
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* readlines: read input lines into *lineptr[] */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines = 0;
	char *p, line[MAXLEN];

	while ((len = getline_custom(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = malloc(len + 1)) == NULL)
			return -1;
		strcpy(p, line);
		lineptr[nlines++] = p;
	}
	return nlines;
}

/* freelines: free allocated lines */
void freelines(char *lineptr[], int nlines)
{
	for (int i = 0; i < nlines; i++)
		free(lineptr[i]);
}

/* main tail function */
int main(int argc, char *argv[])
{
	int n = DEFAULT_N;
	int nlines;

	/* check for optional argument */
	if (argc == 2 && argv[1][0] == '-') {
		n = atoi(argv[1] + 1);
		if (n <= 0)
			n = DEFAULT_N;
	}

	if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
		fprintf(stderr, "Error: input too big to process.\n");
		return 1;
	}

	/* if fewer than n lines, print all */
	if (n > nlines)
		n = nlines;

	/* print last n lines */
	for (int i = nlines - n; i < nlines; i++)
		printf("%s", lineptr[i]);

	freelines(lineptr, nlines);
	return 0;
}

