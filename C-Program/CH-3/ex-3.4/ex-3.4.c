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

void itoa(int n, char s[]) {
	int i = 0;
	unsigned int num;  // use unsigned to handle INT_MIN safely
	int sign = n;

	if (n < 0)
		num = -n;  // converts properly even for INT_MIN due to unsigned range
	else
		num = n;

	do {
		s[i++] = num % 10 + '0';
	} while ((num /= 10) > 0);

	if (sign < 0)
		s[i++] = '-';

	s[i] = '\0';
	reverse(s);
}

int main() {
	int n = -2147483648;  // INT_MIN
	char s[50];
	itoa(n, s);
	printf("itoa(%d) = %s\n", n, s);
	return 0;
}

