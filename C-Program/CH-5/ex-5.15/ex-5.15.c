#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000     /* max #lines to be sorted */
char *lineptr[MAXLINES];  /* pointers to text lines */

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort_custom(void *v[], int left, int right,
                  int (*comp)(void *, void *), int reverse);
int numcmp(char *, char *);
int strcmp_fold(char *s1, char *s2, int fold);

/* main: sort input lines */
int main(int argc, char *argv[])
{
    int nlines;            /* number of input lines read */
    int numeric = 0;       /* 1 if numeric sort */
    int reverse = 0;       /* 1 if reverse sort */
    int fold = 0;          /* 1 if fold upper/lower case together */

    /* process command line options */
    while (--argc > 0 && (*++argv)[0] == '-') {
        char *opt = *argv + 1;
        while (*opt) {
            switch (*opt) {
            case 'n':
                numeric = 1;
                break;
            case 'r':
                reverse = 1;
                break;
            case 'f':
                fold = 1;
                break;
            default:
                printf("Invalid option: -%c\n", *opt);
                return 1;
            }
            opt++;
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (numeric)
            qsort_custom((void **)lineptr, 0, nlines - 1,
                         (int (*)(void *, void *))numcmp, reverse);
        else
            qsort_custom((void **)lineptr, 0, nlines - 1,
                         (int (*)(void *, void *)) (fold ?
                            (int (*)(void *, void *))strcmp_fold :
                            (int (*)(void *, void *))strcmp),
                         reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: input too big to sort\n");
        return 1;
    }
}

/* qsort_custom: sort v[left]...v[right] into increasing or decreasing order */
void qsort_custom(void *v[], int left, int right,
                  int (*comp)(void *, void *), int reverse)
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right)
        return;

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; i++) {
        int cmp = (*comp)(v[i], v[left]);
        if ((reverse == 0 && cmp < 0) || (reverse == 1 && cmp > 0))
            swap(v, ++last, i);
    }

    swap(v, left, last);
    qsort_custom(v, left, last - 1, comp, reverse);
    qsort_custom(v, last + 1, right, comp, reverse);
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
    void *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1 = atof(s1);
    double v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* strcmp_fold: compare s1 and s2, optionally ignoring case */
int strcmp_fold(char *s1, char *s2, int fold)
{
    for (; *s1 && *s2; s1++, s2++) {
        char c1 = fold ? tolower((unsigned char)*s1) : *s1;
        char c2 = fold ? tolower((unsigned char)*s2) : *s2;
        if (c1 != c2)
            return c1 - c2;
    }
    return *s1 - *s2;
}

/* getline_custom: read line into s, return length */
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

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[1000];
    nlines = 0;

    while ((len = getline_custom(line, 1000)) > 0)
        if (nlines >= maxlines || (p = malloc(len + 1)) == NULL)
            return -1;
        else {
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    for (int i = 0; i < nlines; i++)
        printf("%s", lineptr[i]);
}

