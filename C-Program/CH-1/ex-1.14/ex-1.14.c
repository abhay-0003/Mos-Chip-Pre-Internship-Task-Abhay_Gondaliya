#include<stdio.h>
int main(){
	int c, i, j;
	int freq[26] = {0}; // a to z
	
	while((c = getchar()) != EOF){
		if(c >= 'a' && c <= 'z'){
			freq[c-'a']++;
		}
		else if(c >= 'A' && c <= 'Z'){
			freq[c-'A']++;
		}
	}

//print histogram
//Horizontal
	printf("\nHorizontal character frequency histogram\n");
	for(i = 0; i < 26; i++){
		if(freq[i] > 0){
			printf("%c: ", 'a' + i);
			for(j = 0; j < freq[i]; j++){
				printf("*");
			}
			printf("\n");
		}
	}

//Vertical
	printf("\nVertical character frequency histogram\n");
	int max = 0;
	
	//find max freq
	for(i = 0; i < 26; i++){
		if(freq[i] > max){
			max = freq[i];
		}
	}
	for (int level = max; level > 0; level--) {
		for (int i = 0; i < 26; i++) {
			if (freq[i] >= level)
				printf(" * ");
			else
				printf("   ");
		}
		printf("\n");
 	}

    // Print labels
	for (int i = 0; i < 26; i++) {
		if (freq[i] > 0)
			printf(" %c ", 'a' + i);
		else
			printf("   ");
	}
	printf("\n");
	return 0;
}
