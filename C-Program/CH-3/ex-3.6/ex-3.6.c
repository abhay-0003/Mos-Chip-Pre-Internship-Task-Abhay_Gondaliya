#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
	int i, j;
	char c;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
    }
}

void itoa_width(int n, char s[], int width) {
	int i = 0, sign;
	unsigned int num;

	if ((sign = n) < 0)
		num = -n;
	else
		num = n;

	do {
		s[i++] = num % 10 + '0';
	} while ((num /= 10) > 0);

	if (sign < 0)
 		s[i++] = '-';

	// Pad with spaces if needed
	while (i < width)
 		s[i++] = ' ';

 	s[i] = '\0';
	reverse(s);
}

int main() {
	char s[50];
	itoa_width(123, s, 6);
	printf("'%s'\n", s);   // prints: '   123'
	itoa_width(-42, s, 6);
	printf("'%s'\n", s);   // prints: '   -42'
	return 0;
}

