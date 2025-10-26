#include<stdio.h>
#define MAXLINE 1000

int get_line(char s[], int lim);
void copy(char to[], char from[]);

int main(){
	int len;               /*current line length*/
	int max;               /*maximum length seen so far*/
	char line[MAXLINE];    /*current input line*/
	char longest[MAXLINE]; /*longest line saved here*/

	max = 0;
	while((len = get_line(line, MAXLINE)) > 0){
		if(len > max){
			max = len;
			copy(longest, line);
		}
	}

	if(max > 0){
		printf("Longest length = %d\n", max);
		printf("Stored start of longest line (up to %d chars) : \n%s",MAXLINE-1, longest);
		if(max >= MAXLINE)
			printf("\n(NOTE: line was longer than buffer; only initial part shown.)\n");
	}
	return 0;
}

/*get_line: read a line into s, return actual length (may be > lim-1);
  store up to lin-1 char in s (and null-terminate). */

int get_line(char s[],int lim){
	int c, i, total;
	i =0;
	total = 0;
	while((c = getchar()) != EOF && c != '\n'){
		++total;
		if(i < lim-1){
			s[i++] = c;
		}
	}
	if(c == '\n'){
		++total;
		if(i < lim-1){
			s[i++] = c;
		}
	}
	s[i] = '\0';
	return 0;
}

void copy(char to[], char from[]){
	int i = 0;
	while((to[i] = from[i]) != '\0')
		++i;
}

