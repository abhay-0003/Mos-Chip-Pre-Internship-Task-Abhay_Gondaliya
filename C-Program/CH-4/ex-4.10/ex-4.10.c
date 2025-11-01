#include <stdio.h>
#include <stdlib.h>   // for atof()
#include <ctype.h>    // for isdigit(), etc.
#include <string.h>

#define MAXLINE 1000
#define MAXOP   100
#define NUMBER  '0'

#define MAXVAL  100

int sp = 0;            // next free stack position
double val[MAXVAL];    // value stack

void push(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

int getline_custom(char s[], int lim) {
	int c, i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int getop(char s[], char line[], int *pos) {
	int i = 0, c;

	// Skip whitespace
	while ((s[0] = c = line[(*pos)++]) == ' ' || c == '\t')
		;

	s[1] = '\0';
	if (!isdigit(c) && c != '.' && c != '-')
		return c; // not a number

	// handle negative numbers
	if (c == '-') {
		if (isdigit(line[*pos]) || line[*pos] == '.')
			; // negative number
		else
			return '-';
	}

	if (isdigit(c) || c == '-') // collect integer part
		while (isdigit(s[++i] = c = line[(*pos)++]))
			;
	if (c == '.') // collect fraction part
		while (isdigit(s[++i] = c = line[(*pos)++]))
			;
	s[i] = '\0';
	(*pos)--; // put back one char
	return NUMBER;
}

int main() {
	char line[MAXLINE];
	char s[MAXOP];
	int type, len, pos;
	double op2;

	while ((len = getline_custom(line, MAXLINE)) > 0) {
		pos = 0;
		while ((type = getop(s, line, &pos)) != '\0') {
			switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				if (type != ' ' && type != '\t')
					printf("error: unknown command %s\n", s);
				break;
			}
		}
		printf("\t%.8g\n", pop());
	}
	return 0;
}

