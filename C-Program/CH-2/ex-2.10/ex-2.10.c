#include <stdio.h>

int lower(int c) {
	return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}

int main() {
	char test1 = 'G';
	char test2 = 'x';
	printf("%c -> %c\n", test1, lower(test1));
	printf("%c -> %c\n", test2, lower(test2));
	return 0;
}

