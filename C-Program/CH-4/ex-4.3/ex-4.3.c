#include <stdio.h>
#include <stdlib.h>   // for atof()
#include <ctype.h>    // for isdigit()
#include <math.h>     // for fmod()

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;
	while ((s[0] = c = getchar()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if (!isdigit(c) && c != '.' && c != '-')
		return c;  // not a number

	i = 0;
	if (c == '-') {
		int next = getchar();
		if (isdigit(next) || next == '.') {
			s[++i] = next; // negative number
			c = next;
		} 
		else {
			ungetc(next, stdin);
			return '-';
		}
	}

	if (isdigit(c))
		while (isdigit(s[++i] = c = getchar()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getchar()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetc(c, stdin);
	return NUMBER;
}

/* main: reverse Polish calculator */
int main(void)
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
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
		case '%':
			op2 = pop();
			if (op2 != 0.0)
				push(fmod(pop(), op2));
			else
				printf("error: zero divisor for modulo\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

