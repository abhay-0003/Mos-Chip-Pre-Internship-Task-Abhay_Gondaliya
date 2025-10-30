#include <stdio.h>
#include <time.h>

int binsearch_original(int x, int v[], int n) {
	int low, high, mid;
	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int binsearch_one_test(int x, int v[], int n) {
	int low, high, mid;
	low = 0;
	high = n - 1;

	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}	

	mid = (low + high) / 2;
	if (v[mid] == x)
		return mid;
	else
		return -1;
}

int main() {
	int n = 1000000;
	int arr[n];
	for (int i = 0; i < n; i++)
		arr[i] = i;

	int target = 999999;
	clock_t start, end;

	start = clock();
	for (int i = 0; i < 100000; i++)
		binsearch_original(target, arr, n);
	end = clock();
	printf("Original binary search: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	for (int i = 0; i < 100000; i++)
		binsearch_one_test(target, arr, n);
	end = clock();
	printf("Optimized one-test version: %.3f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	return 0;
}

