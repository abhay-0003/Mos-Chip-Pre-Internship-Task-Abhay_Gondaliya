#include <stdio.h>
#include <ctype.h>

#define MAXWORD 100

int getword(char *word, int lim);
int getch(void);
void ungetch(int);

int main(void)
{
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF)
        printf("%s\n", word);
    return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    /* skip whitespace */
    while (isspace(c = getch()))
        ;

    if (c != EOF)
        *w++ = c;

    /* Handle comments */
    if (c == '/') {
        int d = getch();
        if (d == '/') {             /* single-line comment */
            while ((c = getch()) != '\n' && c != EOF)
                ;
            return getword(word, lim);
        } else if (d == '*') {      /* multi-line comment */
            int prev = 0;
            while ((c = getch()) != EOF) {
                if (prev == '*' && c == '/')
                    break;
                prev = c;
            }
            return getword(word, lim);
        } else {
            ungetch(d);
        }
    }

    /* Handle string constants */
    if (c == '"' || c == '\'') {
        int quote = c;
        while ((c = getch()) != EOF) {
            if (c == '\\') getch();  /* skip escaped chars */
            else if (c == quote) break;
        }
        return getword(word, lim);
    }

    /* Handle preprocessor lines (e.g. #include) */
    if (c == '#') {
        while ((c = getch()) != '\n' && c != EOF)
            ;
        return getword(word, lim);
    }

    /* Handle identifiers (letters, underscores) */
    if (!isalpha(c) && c != '_') {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_') {
            ungetch(*w);
            break;
        }

    *w = '\0';
    return word[0];
}

/* Simple character pushback buffer */
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

