#include <stdio.h>

void itoa(int n, char s[]);
void itoa_rec(int n, char s[], int *i);

void itoa(int n, char s[]) {
	int i = 0;
	if (n < 0) {
		s[i++] = '-';
		n = -n;
	}
	itoa_rec(n, s, &i);
	s[i] = '\0';
}

void itoa_rec(int n, char s[], int *i) {
	if (n / 10)
		itoa_rec(n / 10, s, i);
	s[(*i)++] = n % 10 + '0';
}

int main() {
	char s[100];
	itoa(-12345, s);
	printf("%s\n", s);
	return 0;
}

