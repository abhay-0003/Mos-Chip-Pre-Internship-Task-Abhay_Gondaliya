#include <stdio.h>
#define MAXLINE 1000

/* Print lines longer than 80 characters. 
   This reads character-by-character and prints the whole line when it's confirmed to be longer than 80. */
int main(void) {
	int c;
	int count;               /* length counter for current line */
	char buf[MAXLINE];
	int i;
	int is_long;

	count = 0;
	is_long = 0;
	i = 0;

	while ((c = getchar()) != EOF) {
		++count;
		if (i < MAXLINE - 1) {
			buf[i++] = (char)c;
		}
		if (count > 80) {
		is_long = 1;
		}
		if (c == '\n') {
			buf[i] = '\0';
			if (is_long) {
                /* If the stored buffer contains the whole line, just print it.
                   If the line was longer than buffer, our buffer has the initial part;
                   however, because we consumed the entire line, printing buf prints
                   only stored part. For extremely long lines (longer than buffer),
                   you would need to handle streaming differently. This version prints
                   at least the stored start and indicates overflow. */
				printf("%s", buf);
				if (count >= MAXLINE)
					printf("(...line longer than %d chars, only initial part shown...)\n", MAXLINE-1);
			}
            /* reset for next line */
			count = 0;
			i = 0;
			is_long = 0;
		}
	}
	return 0;
}

