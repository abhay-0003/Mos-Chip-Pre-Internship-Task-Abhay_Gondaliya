#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define NAME 'n'
#define VARIABLE 'v'

int getop(char []);
void push(double);
double pop(void);
void mathfnc(char []);
void clear(void);

/* Stack */
#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full\n");
}

double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* Variables */
double vars[26];  // A-Z variables
double last_print = 0.0;

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getchar()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	if (islower(c)) {
		i = 0;
		while (islower(s[i++] = c))
			c = getchar();
		s[i - 1] = '\0';
		if (c != EOF)
			ungetc(c, stdin);
		return NAME;
	}

	if (isupper(c))
		return VARIABLE;

	if (!isdigit(c) && c != '.' && c != '-')
 		return c;
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

/* mathfnc: handle math functions */
void mathfnc(char s[])
{
	double op2;

	if (strcmp(s, "sin") == 0)
		push(sin(pop()));
	else if (strcmp(s, "exp") == 0)
		push(exp(pop()));
	else if (strcmp(s, "pow") == 0) {
		op2 = pop();
		push(pow(pop(), op2));
	} 
	else
		printf("error: %s not supported\n", s);
}

/* main: calculator with variables */
int main(void)
{
	int type, var = 0;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case NAME:
			mathfnc(s);
			break;
		case VARIABLE:
			var = s[0];
			push(vars[var - 'A']);
			break;
		case '=':
			pop();
			if (var >= 'A' && var <= 'Z')
				vars[var - 'A'] = pop();
			else
				printf("error: no variable name\n");
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
			last_print = pop();
			printf("\t%.8g\n", last_print);
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}

