#include <stdio.h>

int bitcount(unsigned x) {
	int count = 0;
	while (x != 0) {
		x &= (x - 1);   // delete rightmost 1-bit
		count++;
	} 
	return count;
}

int main() {
	unsigned x = 0b10101100; // 172 (4 bits set)
	printf("Bit count of %u = %d\n", x, bitcount(x));
	return 0;
}

