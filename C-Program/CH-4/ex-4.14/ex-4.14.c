#include <stdio.h>

#define swap(t, x, y) { \
    t temp;             \
    temp = x;           \
    x = y;              \
    y = temp;           \
}

int main() {
	int a = 10, b = 20;
	double p = 3.14, q = 2.71;
	char c1 = 'A', c2 = 'B';

	printf("Before swap:\n");
	printf("a = %d, b = %d\n", a, b);
	printf("p = %.2f, q = %.2f\n", p, q);
	printf("c1 = %c, c2 = %c\n", c1, c2);

	swap(int, a, b);
	swap(double, p, q);
	swap(char, c1, c2);

	printf("\nAfter swap:\n");
	printf("a = %d, b = %d\n", a, b);
	printf("p = %.2f, q = %.2f\n", p, q);
	printf("c1 = %c, c2 = %c\n", c1, c2);

	return 0;
}

