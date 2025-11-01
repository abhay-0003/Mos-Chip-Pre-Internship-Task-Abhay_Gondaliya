#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <ctype.h>    /* for isdigit() */

#define MAXVAL 100    /* maximum depth of val stack */

int sp = 0;           /* next free stack position */
double val[MAXVAL];   /* value stack */

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

/* expr: evaluate reverse Polish expression from command line */
int main(int argc, char *argv[])
{
	double op2;

	if (argc < 2) {
		printf("Usage: expr <expression in RPN>\n");
		printf("Example: expr 2 3 4 + *\n");
		return 1;
	}

	while (--argc > 0) {
		char *arg = *++argv;

		if (isdigit(*arg) || (*arg == '-' && isdigit(*(arg + 1)))) {
			push(atof(arg));   /* number */
		} 
		else if (arg[1] == '\0') {   /* single char operator */
			switch (*arg) {
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
                			push((int)pop() % (int)op2);
                		else
                    			printf("error: zero divisor for modulo\n");
                		break;
            		default:
                		printf("error: unknown command %s\n", arg);
                		break;
			}
		} 
		else {
            		printf("error: invalid argument %s\n", arg);
		}
	}

    	if (sp == 1)
        	printf("%.8g\n", pop());
    	else
        	printf("error: invalid expression (stack has %d items)\n", sp);

    	return 0;
}

