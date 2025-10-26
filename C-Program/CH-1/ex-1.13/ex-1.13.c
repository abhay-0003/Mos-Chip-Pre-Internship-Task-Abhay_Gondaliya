#include<stdio.h>
/* count digits, white space, others */
int main(){
	int c, i, j, length = 0;
	int wordlength[50] = {0}; // store count of words of length
		
	while((c = getchar()) != EOF){
		if(c == ' ' || c == '\n' || c == '\t'){
			if(length > 0){
				wordlength[length]++;
				length = 0;
			}
		}
		else
			length++;
	}

//if input doesn't end with space or new line
	if(length > 0)
		wordlength[length]++;

//print histogram

//Horizontal Histogram

	printf("\nHorizontal Histogram of word length\n");
	for(i = 1; i < 50; i++){
		if(wordlength[i] > 0){
			printf("%2d: ", i);
			for(j = 0; j < wordlength[i]; j++)
				printf("*");
			printf("\n");
		}
	}

//vertical Histogram
	printf("\nVertical Histogram of word length\n");
	// find max frequency for vertical histogram
	int maxCount = 0;
	for (i = 1; i < 50; i++) {
		if (wordlength[i] > maxCount)
			maxCount = wordlength[i];
	}

// print histogram from maxCount down to 1
	for (int row = maxCount; row > 0; row--) {
		for (i = 1; i < 50; i++) {
			if (wordlength[i] >= row)
				printf(" * ");
			else
				printf("   ");
		}
		printf("\n");
	}

// print word lengths as labels
	for (i = 1; i < 50; i++) {
		if (wordlength[i] > 0)
			printf("%2d ", i);
		else
			printf("   ");
	}
	printf("\n");


	return 0;
}
