#include <stdio.h>

void escape(char s[], const char t[]);
void unescape(char s[], const char t[]);

int main() {
	char text[] = "Hello\tAbhi\nWelcome\\Back!";
	char escaped[100], unescaped[100];

	escape(escaped, text);
	printf("Original:  %s\n", text);
	printf("Escaped:   %s\n", escaped);

	unescape(unescaped, escaped);
	printf("Unescaped: %s\n", unescaped);

	return 0;
}

void escape(char s[], const char t[]) {
	int i, j;
	for (i = j = 0; t[i] != '\0'; i++) {
		switch (t[i]) {
		case '\n':
			s[j++] = '\\';
			s[j++] = 'n';
			break;
		case '\t':
			s[j++] = '\\';
			s[j++] = 't';
			break;
		case '\\':
			s[j++] = '\\';
			s[j++] = '\\';
			break;
		default:
			s[j++] = t[i];
			break;
		}
	}
	s[j] = '\0';
}

void unescape(char s[], const char t[]) {
	int i, j;
	for (i = j = 0; t[i] != '\0'; i++) {
		if (t[i] == '\\') {
			switch (t[++i]) {
			case 'n':
				s[j++] = '\n';
				break;
			case 't':
				s[j++] = '\t';
				break;
			case '\\':
				s[j++] = '\\';
				break;
			default:
				s[j++] = '\\';
				s[j++] = t[i];
				break;
			}
		} 
		else {
			s[j++] = t[i];
		}
	}
	s[j] = '\0';
}

