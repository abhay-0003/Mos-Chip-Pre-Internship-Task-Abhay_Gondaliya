#include <stdio.h>
#include <ctype.h>

void expand(char s1[], char s2[]) {
	int i, j;
	char c;

	i = j = 0;
	while ((c = s1[i++]) != '\0') {
		if (s1[i] == '-' && s1[i+1] != '\0') {
		// Check for valid range (e.g., a-z, 0-9)
			char start = c;
			char end = s1[i+1];
			if ((isdigit(start) && isdigit(end) && start <= end) || (islower(start) && islower(end) && start <= end) || (isupper(start) && isupper(end) && start <= end)) {
                
			// Expand range
				for (char k = start; k <= end; k++)
					s2[j++] = k;

			i += 2; // skip '-' and end char
			continue;
			}
		}
		// Copy literal characters
		s2[j++] = c;
	}
	s2[j] = '\0';
}

int main() {
	char s1[][30] = {"a-z", "a-z0-9", "a-b-c", "-a-z", "a-z-", "A-D"};

	char s2[100];

	for (int i = 0; i < 6; i++) {
		expand(s1[i], s2);
		printf("%-8s -> %s\n", s1[i], s2);
	}

	return 0;
}

