#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define TABSTOP 8

int getline_custom(char s[], int lim);
void entab(char in[], char out[]);

int main(void)
{
	char line[MAXLINE];
	char result[MAXLINE * 1000] = "";
	char temp[MAXLINE];
	int len;

	while ((len = getline_custom(line, MAXLINE)) > 0) {
		entab(line, temp);
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

void entab(char in[], char out[])
{
	int i, j, pos, space_count = 0;
	for (i = 0, j = 0, pos = 0; in[i] != '\0'; i++, pos++) {
		if (in[i] == ' ') {
			space_count++;
			if (pos % TABSTOP == TABSTOP - 1) {
				out[j++] = '\t';
				space_count = 0;
			} 
		}
		else {
			while (space_count > 0) {
				out[j++] = ' ';
				space_count--;
			}
			out[j++] = in[i];
		}
	}
	out[j] = '\0';
}

