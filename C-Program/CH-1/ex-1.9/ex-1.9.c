#include <stdio.h>

int main() {
	int c;
	int last_was_blank = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (!last_was_blank) {
				putchar(c);
				last_was_blank = 1;
			}
		} 
		else {
			putchar(c);
			last_was_blank = 0;
		}
	}
	return 0;
}


