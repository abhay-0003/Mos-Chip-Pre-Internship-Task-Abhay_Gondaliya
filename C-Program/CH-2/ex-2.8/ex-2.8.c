#include <stdio.h>

unsigned rightrot(unsigned x, int n) {
	int word_size = sizeof(x) * 8;
	n = n % word_size; // avoid over-rotation

	unsigned right = x & ~(~0 << n);          // rightmost n bits
	return (x >> n) | (right << (word_size - n));
}

int main() {
	unsigned x = 0b10010110; // 150
	unsigned result = rightrot(x, 3);
	printf("rightrot: %u (binary: %08b)\n", result, result);
	return 0;
}

