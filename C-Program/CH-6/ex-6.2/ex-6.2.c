#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define DEFAULT_PREFIX 6

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *, int);
int compare_prefix(const char *, const char *, int);
struct tnode *talloc(void);
char *strdup_custom(const char *);

int main(int argc, char *argv[])
{
    struct tnode *root = NULL;
    char word[MAXWORD];
    int prefixlen = (argc == 2) ? atoi(argv[1]) : DEFAULT_PREFIX;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) || word[0] == '_')
            root = addtree(root, word);

    printf("\nGrouped variable names (prefix length = %d):\n\n", prefixlen);
    treeprint(root, prefixlen);
    return 0;
}

/* addtree: add a node, or increment count */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup_custom(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

/* print groups of variable names that share same prefix */
void treeprint(struct tnode *p, int prefix)
{
    static struct tnode *prev = NULL;

    if (p != NULL) {
        treeprint(p->left, prefix);

        if (prev && compare_prefix(prev->word, p->word, prefix) == 0)
            printf("   %s\n   %s\n\n", prev->word, p->word);

        prev = p;
        treeprint(p->right, prefix);
    }
}

/* compare first n chars of two strings */
int compare_prefix(const char *s1, const char *s2, int n)
{
    for (; n > 0; s1++, s2++, n--)
        if (*s1 != *s2)
            return *s1 - *s2;
    return 0;
}

/* allocate tree node */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* duplicate string */
char *strdup_custom(const char *s)
{
    char *p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

/* improved getword (from Ex 6-1) */
int getword(char *word, int lim)
{
    int c, d;
    char *w = word;

    while (isspace(c = getchar()))
        ;

    if (c == EOF)
        return EOF;

    if (c == '/') {   /* handle comments */
        if ((d = getchar()) == '/') {
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            return getword(word, lim);
        } else if (d == '*') {
            while ((c = getchar()) != EOF)
                if (c == '*' && (d = getchar()) == '/')
                    break;
            return getword(word, lim);
        } else
            ungetc(d, stdin);
    }

    if (c == '"' || c == '\'') {  /* skip string or char constants */
        int quote = c;
        while ((c = getchar()) != EOF) {
            if (c == '\\') getchar();
            else if (c == quote) break;
        }
        return getword(word, lim);
    }

    if (c == '#') {  /* preprocessor line */
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        return getword(word, lim);
    }

    if (!isalpha(c) && c != '_') {
        *w++ = c;
        *w = '\0';
        return c;
    }

    for (*w++ = c; --lim > 0; w++)
        if (!isalnum(*w = getchar()) && *w != '_') {
            ungetc(*w, stdin);
            break;
        }

    *w = '\0';
    return word[0];
}

