#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Hospital
{
	char *name;
	char citiesServed[3];
};

struct card {
	const char *face;
	const char *suit;
};

void menu();

int numPathshome(int street,int avenue);

int control_cities(char _cities[6]);

void delete_cities(char _cities[6],char c,int counter);

void fill_struct(char  (*_locations)[3],struct Hospital *results,char _cities[6],int counter);

int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4]);

void number_array(int number[52]);

void Part3(struct card deck[52]);

int main()
{
	menu();

	return 0;


}


void menu()
{
	srand(time(NULL));	

	char _cities[6]= {'A','B','C','D','E','F' };
	char _locations[4][3] = { {'A','C','D'}, {'B','F'}, {'C','E','F'} ,{'A','B','C'}};
	int _numHospitals;
	struct Hospital results[4];
	struct card deck[52];
	int numb[52];
	int i;
	int number,select,street,avenue;


	for (int i = 0; i < 52; ++i)
	{
		numb[i] = -1;
	}

	_locations[4][0] = '\0';

	printf("\n\nChoice Part\n");
	scanf("%d",&select);

	printf("\n\n");
	switch(select)
	{

		case 1:
			printf("Enter the stree number: ");
			scanf("%d",&street);
			printf("Enter the avenue number: ");
			scanf("%d",&avenue);
			printf("Number of optimal paths to take back home: %d\n",numPathshome(street,avenue));
			menu();
		break;
		case 2:
			printf("Enter the maximum number of hospitals that can be constructed: ");
			scanf("%d",&number);

			while(number <0 || number >4)
			{
				printf("This hospitals number is not valid. Enter Valid Number (0-4)\n");
				scanf("%d",&number);
			}
			
			if (canOfferCovidCoverage(_cities,_locations,number,results))
			{
				for (int i = 0; i < number; ++i)
				{
					printf("Hospital-%d\n",i);
					printf("Hospital locations: %s\n",results[i].citiesServed);
				}
			}
			else
				printf("No,some cities are not covered.\n");
			menu();
		break;
		case 3:
			number_array(numb);
			Part3(deck);
			for (i = 0; i < 51; ++i)
			{
				printf("%s ",deck[numb[i]].face);
				printf("of");
				printf(" %s\n",deck[numb[i]].suit);
			}
			menu();
		break;
		case 4:
		break;
		default:
			menu();
		break;
	}	

}


int numPathshome(int street,int avenue)
{
	if (street == 0 || avenue == 0)
	{
		return 1;
	}
	return numPathshome(street-1,avenue) + numPathshome(street,avenue-1);
}

void delete_struct(struct Hospital *results)
{
	results->citiesServed[0] = '\0';
}



int control_cities(char _cities[6])
{
	if (*_cities != '\0' && *_cities != '.')
	{
		return 0;
	}
	else if (*_cities == '\0')
	{
		return 1;
	}
	else
		return control_cities(_cities+1);
}

void delete_cities(char _cities[6],char c,int counter)
{
	if (_cities[counter] != '\0')
	{
		if (c != _cities[counter])
		{
			delete_cities(_cities,c,counter+1);
		}
		else{
			_cities[counter] = '.';
		}
	}
}

void fill_struct(char  (*_locations)[3],struct Hospital *results,char _cities[6],int counter)
{
	if ( (*_locations)[counter] != '\0' && counter < 3)
	{
		results->citiesServed[counter] = (*_locations)[counter];

		delete_cities(_cities,(*_locations)[counter],0);
		fill_struct(_locations,results,_cities,counter+1);
	}
	else
		results->citiesServed[counter] = '\0';
}

/*

1. Since the city series will change in the future, its copy is saved first.
2. The city sequence is checked [ control_cities(_cities) ]. If all the elements in the array are dots, the function returns 1.
3. Function Checks Are 3 hospital checks completed? (_ NumHospitals) && control_number is 1 or 0
4. All hospital locations are visited one by one.
	A-If it is wrong, the new position is changed. Struct is reset, and since temp cities hold the original series, 
	it becomes the original one again.Cities recorded in Structa become dots in the city series.
	B-If the location is right or wrong, structa cities are saved. Because if the struct is wrong in condition A, it will be reset.
*/

int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4])
{
	int control_number;
	char temp_city[6];
 	//1.
	strcpy(temp_city,_cities);
	//2.
	control_number = control_cities(_cities);
	//3.
	if (control_number == 1 && _numHospitals == 0)
	{
		return 1;
	}
	else if (_numHospitals == 0 && control_number == 0)
	{
		return 0;
	}
	else 
		control_number = 0;

	//4.
	if ( *(_locations)[0] != '\0' )
	{
		//B
		fill_struct(_locations,results,_cities,0);
		control_number = canOfferCovidCoverage(_cities,_locations+1,_numHospitals-1,results+1);
	}
	if ( *(_locations+1)[0] != '\0' && control_number == 0)
	{
		//A
		strcpy(_cities,temp_city);
		delete_struct(results);
		//B
		fill_struct(_locations+1,results,_cities,0);
		control_number = canOfferCovidCoverage(_cities,_locations+1,_numHospitals-1,results+1);
	}
	if ( *(_locations+2)[0] != '\0' && control_number == 0)
	{
		//A
		strcpy(_cities,temp_city);
		delete_struct(results);
		//B
		fill_struct(_locations+2,results,_cities,0);
		control_number = canOfferCovidCoverage(_cities,_locations+2,_numHospitals-1,results+1);
	}
	if ( *(_locations+3)[0] != '\0' && control_number == 0)
	{
		//A
		strcpy(_cities,temp_city);
		delete_struct(results);
		//B
		fill_struct(_locations+3,results,_cities,0);
		control_number = canOfferCovidCoverage(_cities,_locations+3,_numHospitals-1,results+1);
	}


	return control_number;

}

void number_array(int number[52])
{
	int temp;
	int i,j;

	for (i = 0; i < 52;)
	{
		temp = rand()%52;
		for (j = 0; j < 52; ++j)
		{
			if (temp == number[j])
			{
				break;
			}
			if (number[j] == -1)
			{			
				number[i] = temp;
				++i;
				break;
			}
		}

	}
}

void Part3(struct card deck[52])
{

	deck[0].face = "King";
	deck[0].suit = "Clubs";

	deck[1].face = "Deuce";
	deck[1].suit = "Spades";
	
	deck[2].face = "Four";
	deck[2].suit = "Clubs";

	deck[3].face = "Eight";
	deck[3].suit = "Diamonds";

	deck[4].face = "Six";
	deck[4].suit = "Clubs";

	deck[5].face = "Ace";
	deck[5].suit = "Clubs";

	deck[6].face = "King";
	deck[6].suit = "Diamonds";

	deck[7].face = "Seven";
	deck[7].suit = "Hearts";

	deck[8].face = "Five";
	deck[8].suit = "Spades";

	deck[9].face = "Ace";
	deck[9].suit = "Hearts";

	deck[10].face = "Deuce";
	deck[10].suit = "Clubs";

	deck[11].face = "Four";
	deck[11].suit = "Diamonds";

	deck[12].face = "Deuce";
	deck[12].suit = "Hearts";

	deck[13].face = "Seven";
	deck[13].suit = "Spades";

	deck[14].face = "Eight";
	deck[14].suit = "Hearts";

	deck[15].face = "Seven";
	deck[15].suit = "Clubs";

	deck[16].face = "Nine";
	deck[16].suit = "Spades";

	deck[17].face = "Six";
	deck[17].suit = "Hearts";

	deck[18].face = "Nine";
	deck[18].suit = "Clubs";

	deck[19].face = "Queen";
	deck[19].suit = "Hearts";

	deck[20].face = "Seven";
	deck[20].suit = "Diamonds";

	deck[21].face = "Nine";
	deck[21].suit = "Diamonds";

	deck[22].face = "Ten";
	deck[22].suit = "Diamonds";

	deck[23].face = "Ten";
	deck[23].suit = "Spades";

	deck[24].face = "Queen";
	deck[24].suit = "Spades";

	deck[25].face = "Five";
	deck[25].suit = "Clubs";

	deck[26].face = "Five";
	deck[26].suit = "Diamonds";

	deck[27].face = "Ace";
	deck[27].suit = "Spades";

	deck[28].face = "Ten";
	deck[28].suit = "Clubs";

	deck[29].face = "Queen";
	deck[29].suit = "Diamonds";

	deck[30].face = "Ten";
	deck[30].suit = "Hearts";

	deck[31].face = "Four";
	deck[31].suit = "Hearts";

	deck[32].face = "Five";
	deck[32].suit = "Hearts";

	deck[33].face = "Eight";
	deck[33].suit = "Clubs";

	deck[34].face = "King";
	deck[34].suit = "Spades";

	deck[35].face = "Jack";
	deck[35].suit = "Hearts";

	deck[36].face = "Jack";
	deck[36].suit = "Clubs";

	deck[37].face = "Queen";
	deck[37].suit = "Clubs";

	deck[38].face = "Three";
	deck[38].suit = "Diamonds";

	deck[39].face = "King";
	deck[39].suit = "Hearts";

	deck[40].face = "Eight";
	deck[40].suit = "Spades";

	deck[41].face = "Nine";
	deck[41].suit = "Hearts";

	deck[42].face = "Jack";
	deck[42].suit = "Diamonds";

	deck[43].face = "Jack";
	deck[43].suit = "Spades";

	deck[44].face = "Four";
	deck[44].suit = "Spades";

	deck[45].face = "Three";
	deck[45].suit = "Clubs";

	deck[46].face = "Three";
	deck[46].suit = "Hearts";

	deck[47].face = "Six";
	deck[47].suit = "Spades";

	deck[48].face = "Ace";
	deck[48].suit = "Diamonds";

	deck[49].face = "Six";
	deck[49].suit = "Diamonds";

	deck[50].face = "Deuce";
	deck[50].suit = "Diamonds";

	deck[51].face = "Three";
	deck[51].suit = "Spades";

}