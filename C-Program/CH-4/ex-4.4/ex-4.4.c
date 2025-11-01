#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
void print_top(void);
void duplicate(void);
void swap(void);
void clear(void);

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

/* print_top: print the top element of stack */
void print_top(void)
{
	if (sp > 0)
		printf("Top of stack: %.8g\n", val[sp - 1]);
	else
		printf("Stack empty\n");
}

/* duplicate: duplicate top element */
void duplicate(void)
{
	if (sp > 0 && sp < MAXVAL)
		val[sp] = val[sp - 1], sp++;
	else
	printf("error: can't duplicate\n");
}

/* swap: swap top two elements */
void swap(void)
{
	if (sp >= 2) {
		double temp = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = temp;
	} 
	else
		printf("error: not enough elements to swap\n");
}

/* clear: clear the stack */
void clear(void)
{
	sp = 0;
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
			s[++i] = next;
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
		case '?':  // print top
			print_top();
			break;
		case 'd':  // duplicate
			duplicate();
			break;
		case 's':  // swap
			swap();
			break;
		case 'c':  // clear
			clear();
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

