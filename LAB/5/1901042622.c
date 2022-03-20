#include<stdio.h>

int bintodec(int binary);
int countdigits(int number);
int powerfunction(int base,int power);

int main(){
	int binary = 0;
	int number;
	int base;
	int power;
	int result;

	while(binary >= 0){
		printf("Enter a binary number. Enter a negative number to quit.\n");
		scanf("%d",&binary);

		result = bintodec(binary);
		if(binary >= 0) printf("Decimal: %d\n",result);
	}

	return 0;
}

int bintodec(int binary){
	int digit = countdigits(binary);
	int digit_new;
	
	if(binary == 0) return 0;
	
	else{
		return(((binary%10)*powerfunction(2,(digit))) + bintodec(binary/10));
	}
}

int countdigits(int number){
	if(number == 0) return 0;

	else{
		return(1 + countdigits(number/10));
	}
}

int powerfunction(int base, int power){
	if(power == 0) return 1;

	else{
		return(base * (powerfunction(base,power-1)));
	}
}