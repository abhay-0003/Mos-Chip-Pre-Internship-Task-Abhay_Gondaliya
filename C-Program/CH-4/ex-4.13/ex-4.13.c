#include <stdio.h>
#include <string.h>

void reverse(char s[]);
void reverse_rec(char s[], int i, int j);

void reverse(char s[]) {
	reverse_rec(s, 0, strlen(s) - 1);
}

void reverse_rec(char s[], int i, int j) {
	if (i >= j)
		return;
	char temp = s[i];
	s[i] = s[j];
	s[j] = temp;
	reverse_rec(s, i + 1, j - 1);
}

int main() {
	char s[] = "AbhiGPT";
	reverse(s);
	printf("%s\n", s);
	return 0;
}

