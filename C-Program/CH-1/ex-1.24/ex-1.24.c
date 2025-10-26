#include <stdio.h>

int main(void)
{
	int c, paren = 0, brace = 0, bracket = 0;

	while ((c = getchar()) != EOF) {
		if (c == '(') paren++;
		else if (c == ')') paren--;
		else if (c == '{') brace++;
		else if (c == '}') brace--;
		else if (c == '[') bracket++;
		else if (c == ']') bracket--;
	}

	if (paren == 0 && brace == 0 && bracket == 0)
		printf("Syntax OK\n");
	else {
		printf("Syntax Error:\n");
		if (paren != 0) printf("Unmatched parentheses\n");
		if (brace != 0) printf("Unmatched braces\n");
		if (bracket != 0) printf("Unmatched brackets\n");
	}

	return 0;
}

