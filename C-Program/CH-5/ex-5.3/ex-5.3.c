#include <stdio.h>

/* strcat_p: concatenate string t to end of s; s must be big enough */
void strcat_p(char *s, const char *t)
{
	while (*s)          /* move to end of s */
		s++;
	while ((*s++ = *t++))  /* copy t including '\0' */
		;
}

/* Test */
int main(void)
{
	char s[100] = "Hello, ";
	char t[] = "World!";
	strcat_p(s, t);
	printf("Result: %s\n", s);
	return 0;
}

