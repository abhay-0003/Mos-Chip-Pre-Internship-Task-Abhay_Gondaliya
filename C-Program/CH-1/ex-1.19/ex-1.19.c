#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getline_custom(char s[], int lim);
void reverse(char s[]);

int main(void)
{
	char line[MAXLINE];
	char output[MAXLINE * 1000] = "";   // store all reversed lines
	int len;

	// Read all lines until Ctrl+D
	while ((len = getline_custom(line, MAXLINE)) > 0) {
		if (line[0] != '\n' && line[0] != '\0') {
			reverse(line);
			strcat(output, line);
			strcat(output, "\n");
		}
	}

	// Print after EOF (Ctrl+D)
	printf("%s", output);
	return 0;
}

/* getline_custom: read a line into s, return length */
int getline_custom(char s[], int lim)
{
	int c, i = 0;
	while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
	int i, j;
	char temp;
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}

