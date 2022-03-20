#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

struct card {
	const char *face;
	const char *suit;
};

void menu();
int numPathsHome(int street, int avenue);
void fillDeck(struct card *deck);
void shuffleDeck(struct card *deck);
void printDeck(struct card *deck);

int main(){
	
	srand(time(NULL));
	menu();
	return(0);
}

void menu(){
	int option;
	int street = 0,avenue = 0;
	struct card deck[52];

	while(option != 4){
		printf("\n\nPLEASE CHOOSE AN OPTION:\n\n1) Stay Home Problem\n2) COVID-19 Health Coverage\n3) Shuffle Cards\n4) Exit\n\n");
		scanf("%d",&option);

		switch(option){
			case 1:
			while(street <= 0 || avenue <= 0){       //to prevent invalid entry.//
				printf("Enter the street number: ");
				scanf("%d",&street);
				printf("street: %d\n",street);
				printf("Enter the avenue number: ");
				scanf("%d",&avenue);
				printf("avenue: %d\n",avenue);
				if(street <= 0 || avenue <= 0) printf("Invalid entry.\n");
			}
			
			printf("Numbers of optimal paths to take back home: %d\n",numPathsHome(street,avenue));
			break;

			case 2:
			break;

			case 3:
			fillDeck(deck);
			shuffleDeck(deck);
			printDeck(deck);
			break;

			case 4:
			printf("Goodbye!\n");
			break;

			default:
			printf("Invalid option.\n");
			break;
		}
	}
}

int numPathsHome(int street, int avenue){
	if(street == 1 || avenue == 1) //this means there's only one way left.//
		return(1);
	else 
		return(numPathsHome(street-1,avenue) + numPathsHome(street,avenue -1)); //until there's one way left recall itself then sum for each x and y coordinat.//
}

void fillDeck(struct card *deck){
	for (int i = 0; i < 52; ++i){                              //fill faces, there's 4 card for all faces.//
		if (i >= 0 && i < 4) deck[i].face = "Ace";
		if (i >= 4 && i < 8) deck[i].face = "Deuce";
		if (i >= 8 && i < 12) deck[i].face = "Three";
		if (i >= 12 && i < 16) deck[i].face = "Four";
		if (i >= 16 && i < 20) deck[i].face = "Five";
		if (i >= 20 && i < 24) deck[i].face = "Six";
		if (i >= 24 && i < 28) deck[i].face = "Seven";
		if (i >= 28 && i < 32) deck[i].face = "Eight";
		if (i >= 32 && i < 36) deck[i].face = "King";
		if (i >= 36 && i < 40) deck[i].face = "Nine";
		if (i >= 40 && i < 44) deck[i].face = "Ten";
		if (i >= 44 && i < 48) deck[i].face = "Jack";
		if (i >= 48 && i < 52) deck[i].face = "Queen";
	}

	for (int i = 0; i < 52; ++i){                           //to combine one suits with all faces, fill at every 4 steps.//
		if (i%4 == 0) deck[i].suit = "Hearts";
		if (i%4 == 1) deck[i].suit = "Diamonds";
		if (i%4 == 2) deck[i].suit = "Clubs";
		if (i%4 == 3) deck[i].suit = "Spades";
	}
}

void shuffleDeck(struct card *deck){
	int i,j;
	struct card temp;                //Fisher–Yates shuffle algorithm//

	for (i = 52-1; i > 0; i--){      //start from the last element of the array to first.//
		j = rand()%(i +1);           //choose a random value in i numbers.//   
		temp = deck[i];              //and swap the j.th element of the array and i.th element of the array.// 
		deck[i] = deck[j];           //so the function shuffles elements randomly.//
		deck[j] = temp;							   
	}
}

void printDeck(struct card *deck){
	for (int i = 0; i < 52; ++i){   //print the struct.//
		printf("%s of %s\n",deck[i].face,deck[i].suit);
	}
}
