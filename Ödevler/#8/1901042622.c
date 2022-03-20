#include<stdio.h>
#include<string.h>

#define SIZE 500

void generate_hofstadters_sequence (int *arr, int n);
int find_max (int arr[], int index, int max_value);
char* remove_duplicates (char* str);
void menu();
void menu_part1(int arr[SIZE]);

int main(){
	
	menu();
	return 0;
}

void generate_hofstadters_sequence (int *arr, int n){
	printf("How many items of Hofstdadters Q-sequence do you want?\n");
	scanf("%d",&n);

	arr[0] = 1;   //Q-sequence's first and second element is 0.//
	arr[1] = 1;
	
	for (int i = 2; i < n; ++i){
		arr[i] = arr[i - arr[i - 1]] + arr[i - arr[i - 2]];   //apply the formula.//
	}

	for (int i = n; i < SIZE; ++i){     //the array elements that out of the range is zero.//
		arr[i] = 0;
	}
}

int find_max (int arr[], int index, int max_value){
	if (index == 1) return arr[0];
	
	max_value = find_max(arr,index-1,max_value); //assign max value to next value.//
	if (arr[index-1] > max_value){       //check which one is bigger.//
		max_value = arr[index-1];        //biggest one is the new max now.//
	}

	return(max_value);
}

char* remove_duplicates (char* str){
	if (str[0] == '\0') return(str);            //if string is empty there's nothing to change.//
	if (str[0] == str[1]){
		for (int i = 0; i < strlen(str); ++i){  //shift the chars one left.//
			str[i] = str[i+1]; 
		}

		remove_duplicates(str);   //check the new string's conditions to see if there's still str[0] == str[1].//
	}

	return (remove_duplicates(str+1));  //if side by side chars not same, then return the next char address.//
}
	
void menu(){
	int option;
	int Q[SIZE];
	char str[SIZE];
	
	while(option != 4){
		printf("\nWelcome to Homework 8, please choose one of the parts to continue:\n_____________________\n\n");
		printf("1) Execute Part 1\n2) Execute Part 2\n3) Execute Part 3\n4) Exit\n");
		scanf("%d",&option);

		switch(option){
		case 1:
		menu_part1(Q);
		break;

		case 2:
		break;

		case 3:
		printf("Please enter the string.\n");
		scanf(" %[^\n]",str);     //get the string untill \n.//
		remove_duplicates(str);   //remove duplicates.//
		printf("%s\n",str);      //display the new string.//
		break;

		case 4:
		printf("Goodbye!\n");
		break;

		default:
		printf("Invalid choice.\n");
		break;
		}
	}
}

void menu_part1(int arr[SIZE]){
	int choice;
	int n;
	int max_value = 0, index = SIZE;
	double *mean = 0;
	
	while(choice != 5){
		printf("\nPlease make your choice:\n_____________________\n");
		printf("1) Fill Array\n2) Find Biggest Number\n3) Calculate Sum\n4) Calculate Standart Deviation\n5) Exit\n");
		scanf("%d",&choice);

		switch(choice){
		case 1:
		generate_hofstadters_sequence(arr,n);
		break;

		case 2:
		max_value = find_max(arr,index,max_value);
		printf("Maximum value is: %d\n",max_value);   //display the max value.//
		break;

		case 3:
		break;

		case 4:
		break;

		case 5:
		break;

		default:
		printf("Invalid choice.\n");
		break;
		}
	}
}

