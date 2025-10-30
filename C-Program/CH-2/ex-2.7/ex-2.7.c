#include <stdio.h>

unsigned invert(unsigned x, int p, int n) {
	return x ^ (~(~0 << n) << (p + 1 - n));
}

int main() {
	unsigned x = 0b10101100; // 172
	unsigned result = invert(x, 4, 3);
	printf("invert: %u (binary: %08b)\n", result, result);
	return 0;
}

