#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

int main() {
	printf("Using standard headers:\n");
	printf("---------------------------------------\n");
	printf("char:   %d to %d\n", CHAR_MIN, CHAR_MAX);
	printf("uchar:  0 to %u\n", UCHAR_MAX);
	printf("short:  %d to %d\n", SHRT_MIN, SHRT_MAX);
	printf("ushort: 0 to %u\n", USHRT_MAX);
	printf("int:    %d to %d\n", INT_MIN, INT_MAX);
	printf("uint:   0 to %u\n", UINT_MAX);
	printf("long:   %ld to %ld\n", LONG_MIN, LONG_MAX);
	printf("ulong:  0 to %lu\n", ULONG_MAX);

	printf("\nFloating-point types (from <float.h>):\n");
	printf("---------------------------------------\n");
	printf("float:       %e to %e\n", FLT_MIN, FLT_MAX);
	printf("double:      %e to %e\n", DBL_MIN, DBL_MAX);
	printf("long double: %Le to %Le\n", LDBL_MIN, LDBL_MAX);

	printf("\nBy direct computation:\n");
	printf("---------------------------------------\n");
	// compute ranges for integer types
	printf("char:   %d to %d\n", -(1 << (sizeof(char)*8 - 1)), (1 << (sizeof(char)*8 - 1)) - 1);
	printf("uchar:  0 to %u\n", (unsigned char)~0);
	printf("short:  %d to %d\n", -(1 << (sizeof(short)*8 - 1)), (1 << (sizeof(short)*8 - 1)) - 1);
	printf("ushort: 0 to %u\n", (unsigned short)~0);
	printf("int:    %d to %d\n", -(1 << (sizeof(int)*8 - 1)), (1 << (sizeof(int)*8 - 1)) - 1);
	printf("uint:   0 to %u\n", (unsigned int)~0);
	printf("long:   %ld to %ld\n", -(1L << (sizeof(long)*8 - 1)), (1L << (sizeof(long)*8 - 1)) - 1);
	printf("ulong:  0 to %lu\n", (unsigned long)~0L);

	return 0;
}

