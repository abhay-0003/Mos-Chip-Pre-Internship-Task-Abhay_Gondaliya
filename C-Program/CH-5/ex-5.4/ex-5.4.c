#include <stdio.h>

/* strend: return 1 if t occurs at end of s, else 0 */
int strend(const char *s, const char *t)
{
	const char *bs = s;
	const char *bt = t;

	while (*s) s++;     /* move to end of s */
	while (*t) t++;     /* move to end of t */

	while (t > bt && s > bs && *--s == *--t)
		;
	return (t == bt && *s == *t);
}

/* Test */
int main(void)
{
	printf("%d\n", strend("hello world", "world")); // 1
	printf("%d\n", strend("hello world", "word"));  // 0
	return 0;
}

