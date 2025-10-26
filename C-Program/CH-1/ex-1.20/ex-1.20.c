#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8   // fixed tab width

int getline_custom(char s[], int lim);
void detab(char in[], char out[]);

int main(void)
{
	char line[MAXLINE];
	char result[MAXLINE * 1000] = "";
	char temp[MAXLINE];
	int len;

	while ((len = getline_custom(line, MAXLINE)) > 0) {
		detab(line, temp);
		strcat(result, temp);
		strcat(result, "\n");
	}

	printf("%s", result);
	return 0;
}

int getline_custom(char s[], int lim)
{
	int c, i = 0;
	while (i < lim - 1 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

void detab(char in[], char out[])
{
	int i, j, pos;
	for (i = 0, j = 0, pos = 0; in[i] != '\0'; i++) {
		if (in[i] == '\t') {
			int spaces = TABSTOP - (pos % TABSTOP);
			for (int k = 0; k < spaces; k++)
				out[j++] = ' ';
			pos += spaces;
		} 
		else {
			out[j++] = in[i];
			pos++;
		}
	}
	out[j] = '\0';
}

