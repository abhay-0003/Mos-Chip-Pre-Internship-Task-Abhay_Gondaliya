#include <stdio.h>
#include <string.h>

void reverse(char s[]) {
	int i, j;
	char c;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itob(int n, char s[], int b) {
	int i = 0, sign;
	unsigned int num;

	if ((sign = n) < 0)
		num = -n;
	else
		num = n;

	do {
		int rem = num % b;
		s[i++] = (rem < 10) ? rem + '0' : rem - 10 + 'A';
	} while ((num /= b) > 0);

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

int main() {
	char s[50];
	itob(255, s, 16);
	printf("Hex (255): %s\n", s);

	itob(255, s, 2);
	printf("Binary (255): %s\n", s);

	itob(-255, s, 8);
	printf("Octal (-255): %s\n", s);
}

