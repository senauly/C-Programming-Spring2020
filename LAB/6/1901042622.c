#include<stdio.h>
#include<string.h>

#define DNA_SIZE 200

void encode_dna(char *str, int size, char *encoded);
int occur(char *str, int i);

void main(){
	char dna[DNA_SIZE];
	char encoded[DNA_SIZE*2];
	
	int size;
	
	printf("Enter the DNA sequence.\n");
	scanf("%s",dna);

	size = strlen(dna);
	encode_dna(dna,size,encoded);

	printf("%s\n",encoded);
}

void encode_dna(char *str, int size, char *encoded){
	int count = 1;
	int temp;
	char x;
	int a = 0;
	int i = 0;
	
	while(str[i] != '\0'){
		encoded[a] = str[i];
		temp = occur(str,i);
		
		i = i + temp;
		x = temp + '0';
		
		encoded[a+1] = x;
		a = a+2;
	}
}


int occurunce(char *str, int i){
	char x = str[i];
	int count = 1;

	for (int j = i+1; j < strlen(str); ++j){
		if(x == str[j]) count ++;
		else break;
	}

	return(count);
}