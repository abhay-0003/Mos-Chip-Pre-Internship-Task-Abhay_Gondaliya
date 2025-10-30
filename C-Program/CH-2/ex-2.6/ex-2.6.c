#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y) {
	return (x & ~(~(~0 << n) << (p + 1 - n))) | ((y & ~(~0 << n)) << (p + 1 - n));
}

int main() {
	unsigned x = 0b10101010; // 170
	unsigned y = 0b00000111; // 7
	unsigned result = setbits(x, 5, 3, y);
	printf("setbits: %u (binary: %08b)\n", result, result);
	return 0;
}

