#include <stdio.h>
   #define IN   1  /* inside a word */
   #define OUT  0  /* outside a word */
   /* count lines, words, and characters in input */
int main()
{
	int c, nl, nw, nc, state;
	state = OUT;
	nl = nw = nc = 0;
	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("line = %d\nword =  %d\ncharacter =  %d\n", nl, nw, nc);
	return 0;
}


/*--------------------------------------------------------------------
Test the program
----------------------------------------------------------------------
1. Normal sentence
	>Hello World
	>2 words, 1 line, characters count.
----------------------------------------------------------------------
2. Multiple spaces between words
	>Hello         World
----------------------------------------------------------------------
3. Tabs between words
	>Hello	World
----------------------------------------------------------------------
4. Empty input
	>Ctrl+d
----------------------------------------------------------------------
5. Only newline
	>\n\n\n
----------------------------------------------------------------------
Possible bugs to uncover:

Incorrect use of tab check (c = '\t' should be c == '\t')

Words after last line without newline.

Handling of multiple spaces or tabs.

Non-ASCII or punctuation characters.

Off-by-one errors in counting characters.

So, the most likely bug-revealing inputs are:

Many spaces/tabs.

Only delimiters.

No newline at end.

Very long words.

Mixed whitespace types.*/
