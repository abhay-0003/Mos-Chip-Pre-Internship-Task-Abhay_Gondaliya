#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define MAXLINE 1000
#define MAXNOISE 20

struct tnode {
    char *word;
    int lines[MAXLINE];
    int count;
    struct tnode *left;
    struct tnode *right;
};

int getword(char *, int, int *);
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int noiseword(char *);
struct tnode *talloc(void);
char *strdup_custom(const char *);

const char *noise[] = {
    "a", "an", "and", "are", "as", "at", "be", "by",
    "for", "from", "has", "he", "in", "is", "it",
    "its", "of", "on", "that", "the", "to", "was",
    "were", "will", "with", NULL
};

int main(void)
{
    struct tnode *root = NULL;
    char word[MAXWORD];
    int lineno = 1;

    while (getword(word, MAXWORD, &lineno) != EOF)
        if (isalpha(word[0]) && !noiseword(word))
            root = addtree(root, word, lineno);

    printf("\n=== Cross Reference (word : line numbers) ===\n\n");
    treeprint(root);
    return 0;
}

/* addtree: add a node or update line list */
struct tnode *addtree(struct tnode *p, char *w, int lineno)
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup_custom(w);
        p->count = 1;
        p->lines[0] = lineno;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        if (p->lines[p->count - 1] != lineno)  /* avoid duplicate line numbers */
            p->lines[p->count++] = lineno;
    } else if (cond < 0)
        p->left = addtree(p->left, w, lineno);
    else
        p->right = addtree(p->right, w, lineno);
    return p;
}

/* print tree in alphabetical order with line numbers */
void treeprint(struct tnode *p)
{
    int i;

    if (p != NULL) {
        treeprint(p->left);
        printf("%-15s : ", p->word);
        for (i = 0; i < p->count; i++)
            printf("%d ", p->lines[i]);
        printf("\n");
        treeprint(p->right);
    }
}

/* return 1 if word is a noise word */
int noiseword(char *w)
{
    for (int i = 0; noise[i] != NULL; i++)
        if (strcmp(w, noise[i]) == 0)
            return 1;
    return 0;
}

/* improved getword: skip comments, strings, and preprocessor lines */
int getword(char *word, int lim, int *lineno)
{
    int c, d;
    char *w = word;

    while (isspace(c = getchar()))
        if (c == '\n')
            (*lineno)++;

    if (c == EOF)
        return EOF;

    if (c == '/') {   /* handle comments */
        if ((d = getchar()) == '/') {
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            if (c == '\n')
                (*lineno)++;
            return getword(word, lim, lineno);
        } else if (d == '*') {
            while ((c = getchar()) != EOF)
                if (c == '*' && (d = getchar()) == '/')
                    break;
                else if (c == '\n')
                    (*lineno)++;
            return getword(word, lim, lineno);
        } else
            ungetc(d, stdin);
    }

    if (c == '"' || c == '\'') {  /* skip string or char constants */
        int quote = c;
        while ((c = getchar()) != EOF) {
            if (c == '\\')
                getchar();  /* skip escape */
            else if (c == quote)
                break;
            else if (c == '\n')
                (*lineno)++;
        }
        return getword(word, lim, lineno);
    }

    if (c == '#') {  /* preprocessor line */
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        (*lineno)++;
        return getword(word, lim, lineno);
    }

    if (!isalpha(c) && c != '_') {
        *w++ = c;
        *w = '\0';
        return c;
    }

    for (*w++ = c; --lim > 0; w++)
        if (!isalnum(*w = getchar()) && *w != '_') {
            if (*w == '\n')
                (*lineno)++;
            ungetc(*w, stdin);
            break;
        }

    *w = '\0';
    return word[0];
}

/* allocate node */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdup alternative */
char *strdup_custom(const char *s)
{
    char *p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

