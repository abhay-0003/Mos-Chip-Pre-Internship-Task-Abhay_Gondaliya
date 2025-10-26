#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define FOLDLEN 20

int getline_custom(char s[], int lim);
void fold_line(char in[], char out[]);

int main(void)
{
	char line[MAXLINE];
	char result[MAXLINE * 1000] = "";
	char temp[MAXLINE];
	int len;

	while ((len = getline_custom(line, MAXLINE)) > 0) {
		fold_line(line, temp);
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

void fold_line(char in[], char out[])
{
	int i, j = 0, col = 0, last_space = -1;
	for (i = 0; in[i] != '\0'; i++) {
		out[j++] = in[i];
		col++;
		if (in[i] == ' ')
			last_space = j - 1;
		if (col >= FOLDLEN) {
			if (last_space != -1) {
				out[last_space] = '\n';
				col = j - last_space - 1;
				last_space = -1;
			} 
			else {
				out[j++] = '\n';
				col = 0;
			}
		}
	}
	out[j] = '\0';
}

