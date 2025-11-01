#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'

int getop(char s[]) {
	int i = 0;
	int c;
	static int lastc = 0;  // internal static variable instead of ungetch

	if (lastc != 0) {
		c = lastc;
		lastc = 0;
	} 
	else {
		c = getchar();
	}

	// Skip whitespace
	while (c == ' ' || c == '\t')
		c = getchar();

	s[0] = c;
	s[1] = '\0';

	if (!isdigit(c) && c != '.' && c != '-')
		return c;  // not a number

	// Handle negative numbers or minus operator
	if (c == '-') {
		int next = getchar();
		if (!isdigit(next) && next != '.') {
			lastc = next;
			return '-';
		}
		c = next;
		s[++i] = c;
	}

	if (isdigit(c)) {
		while (isdigit(s[++i] = c = getchar()))
			;
	}
	if (c == '.') {
		while (isdigit(s[++i] = c = getchar()))
			;
	}

	s[i] = '\0';
	if (c != EOF)
		lastc = c;

	return NUMBER;
}

