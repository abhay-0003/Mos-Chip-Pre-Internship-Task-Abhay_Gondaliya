#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct listnode {
    char *word;
    int count;
};

/* function prototypes */
int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
void treetolist(struct tnode *, struct listnode *, int *);
void sortlist(struct listnode *, int);
struct tnode *talloc(void);
char *strdup_custom(const char *);

/* ---------- MAIN ---------- */
int main(void)
{
    struct tnode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = addtree(root, word);

    /* flatten tree to array for sorting */
    struct listnode list[1000];
    int n = 0;
    treetolist(root, list, &n);
    sortlist(list, n);

    printf("\n=== Word frequency list ===\n\n");
    for (int i = 0; i < n; i++)
        printf("%4d  %s\n", list[i].count, list[i].word);

    return 0;
}

/* ---------- TREE OPERATIONS ---------- */

/* addtree: add a node, or increment count of existing word */
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

/* traverse tree into list array */
void treetolist(struct tnode *p, struct listnode *list, int *n)
{
    if (p == NULL)
        return;
    treetolist(p->left, list, n);
    list[*n].word = p->word;
    list[*n].count = p->count;
    (*n)++;
    treetolist(p->right, list, n);
}

/* ---------- SORT AND PRINT ---------- */

/* simple bubble sort by frequency descending */
void sortlist(struct listnode *list, int n)
{
    int i, j;
    struct listnode temp;
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (list[i].count < list[j].count) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
}

/* ---------- GETWORD ---------- */

int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getchar()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getchar())) {
            ungetc(*w, stdin);
            break;
        }
    *w = '\0';
    return word[0];
}

/* ---------- MEMORY HELPERS ---------- */

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup_custom(const char *s)
{
    char *p = (char *) malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}

