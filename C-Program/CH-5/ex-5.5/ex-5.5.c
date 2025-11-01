#include <stdio.h>

/* strncpy_p: copy at most n chars of t to s */
char *strncpy_p(char *s, const char *t, int n)
{
	char *p = s;
	while (n-- > 0 && (*s++ = *t++))
		;
	while (n-- > 0)
		*s++ = '\0';
	return p;
}

/* strncat_p: concatenate at most n chars of t to s */
char *strncat_p(char *s, const char *t, int n)
{
	char *p = s;
	while (*s) s++;      /* move to end of s */
	while (n-- > 0 && (*s++ = *t++))
		;
	*s = '\0';           /* ensure null termination */
	return p;
}

/* strncmp_p: compare at most n chars of s and t */
int strncmp_p(const char *s, const char *t, int n)
{
	for (; n > 0; s++, t++, n--) {
		if (*s != *t || *s == '\0' || *t == '\0')
			return *s - *t;
	}
	return 0;
}

/* Test */
int main(void)
{
	char a[50] = "Hello";
	char b[50] = "World";
	char c[50];

	strncpy_p(c, b, 3);
	c[3] = '\0';
	printf("strncpy_p: %s\n", c); // Wor

	strncat_p(a, b, 3);
	printf("strncat_p: %s\n", a); // HelloWor

	printf("strncmp_p(\"abc\",\"abd\",2): %d\n", strncmp_p("abc","abd",2)); // 0
	printf("strncmp_p(\"abc\",\"abd\",3): %d\n", strncmp_p("abc","abd",3)); // <0
	return 0;
}

