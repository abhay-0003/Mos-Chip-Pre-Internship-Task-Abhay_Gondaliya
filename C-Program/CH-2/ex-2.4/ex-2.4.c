#include <stdio.h>

void squeeze(char s1[], char s2[]) {
	int i, j, k;
	int remove;

	for (i = j = 0; s1[i] != '\0'; i++) {
		remove = 0;  // flag to check if s1[i] should be removed
		for (k = 0; s2[k] != '\0'; k++) {
			if (s1[i] == s2[k]) {
				remove = 1;
				break;
			}
		}
		if (!remove)
			s1[j++] = s1[i];
	}
	s1[j] = '\0';
}

int main() {
	char s1[] = "hello world";
	char s2[] = "aeiou";

	squeeze(s1, s2);
	printf("Result after squeeze: %s\n", s1);

	return 0;
}

