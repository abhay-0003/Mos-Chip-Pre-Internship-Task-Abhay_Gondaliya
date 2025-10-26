#include <stdio.h>
#define MAXLINE 1000

int getline_custom(char s[], int lim);
void remove_trailing(char s[]);

int main(void) {
	char line[MAXLINE];
	char cleaned[MAXLINE * 100] = "";  // store all cleaned lines together
	int len;

	while ((len = getline_custom(line, MAXLINE)) > 0) {
		remove_trailing(line);
		if (line[0] != '\0') {   // skip empty lines
			strcat(cleaned, line);
			strcat(cleaned, "\n");
		}
	}

	printf("%s", cleaned);  // print only after Ctrl+D
	return 0;
}

/* getline_custom: read a line into s, return length */
int getline_custom(char s[], int lim) {
	int c, i = 0;
	while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* remove_trailing: remove trailing blanks, tabs, and newline */
void remove_trailing(char s[])
{
	int i = strlen(s) - 1;
	while (i >= 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i--;
	s[i + 1] = '\0';
}
