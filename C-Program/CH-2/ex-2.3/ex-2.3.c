#include <stdio.h>

int htoi(char s[]) {
	int i = 0, n = 0;
	int c;

	// Skip optional "0x" or "0X"
	if (s[0] == '0') {
		if (s[1] == 'x' || s[1] == 'X')
			i = 2;
	}

	for (; s[i] != '\0'; ++i) {
		c = s[i];
		int value;

		if (c >= '0' && c <= '9')
			value = c - '0';
		else if (c >= 'a' && c <= 'f')
			value = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			value = c - 'A' + 10;
		else
			break;   // stop if invalid hex digit

		n = 16 * n + value;
	}

	return n;
}

int main() {
	char hex1[] = "0x1A3F";
	char hex2[] = "7f";
	char hex3[] = "0XFF";

	printf("%s = %d\n", hex1, htoi(hex1));
	printf("%s = %d\n", hex2, htoi(hex2));
	printf("%s = %d\n", hex3, htoi(hex3));

	return 0;
}

