#include <stdio.h>
#include <string.h>

#define MAXLINES 5000   /* max number of lines to be sorted */
#define MAXLEN 1000     /* max length of any input line */
#define ALLOCSIZE 10000 /* total storage space for all lines */

char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int maxlines, char *storage, int maxstorage);
void writelines(char *lineptr[], int nlines);
int getline_custom(char *, int);
void qsort_custom(char *lineptr[], int left, int right);

int main(void)
{
	int nlines;  /* number of input lines read */
	char allocbuf[ALLOCSIZE];  /* storage for all lines */

	if ((nlines = readlines(lineptr, MAXLINES, allocbuf, ALLOCSIZE)) >= 0) {
		qsort_custom(lineptr, 0, nlines - 1);
		writelines(lineptr, nlines);
		return 0;
	} 
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

/* readlines: read input lines, store them in the given storage array */
int readlines(char *lineptr[], int maxlines, char *storage, int maxstorage)
{
	int len, nlines;
	char line[MAXLEN];
	char *p = storage;           /* pointer to next free position in storage */
	char *storage_end = storage + maxstorage; /* end of storage buffer */

	nlines = 0;
	while ((len = getline_custom(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || p + len > storage_end)
			return -1;  /* not enough room */
		else {
			line[len - 1] = '\0';  /* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;  /* advance pointer */
		}
	}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	for (int i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}

/* getline_custom: read a line into s, return length */
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

/* qsort_custom: sort v[left]...v[right] into increasing order */
void qsort_custom(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);
	if (left >= right)
		return;

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort_custom(v, left, last - 1);
	qsort_custom(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
	char *temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

