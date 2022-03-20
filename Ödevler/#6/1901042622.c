#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>


void choose_line(int array1[],int array2[],int n);
void choose_words(char *file_path, int lines[10], char words[10][15]);
int  check_array(int lines[10], int number);
void shuffle(int array[], int n);
void set_array(int array[], int n);
void swap (int *a, int *b);
void print_2D(char str[20][20],int column, int row);
void make_grid(char grid[20][20]);
void place_words(int n, char words[10][15],char grid[20][20],int order);
void shufflestr(char array[], int n);
int choose_order();
void add_chars(char grid[20][20], char str[26]);
int search_word(char word[15],int x,int y,char grid[20][20]);
void print_wordlist(char words[10][15]);
void print_numbers();

int main(){
	char str[26] = "abcdefghijklmnopqrstuvwxyz";
	int lines[10];
	char words[10][15];
	int numbers[100];
	char grid[20][20];
	char *text = "words.txt";
	int order,xaxis,yaxis,i = 0;
	int count = 0;
	char ycharaxis;
	char word[15];
	char string[20];
	char exit[5] = "EXIT";
	int grid_size = 20;
	int selectedword = 10;
	int wordnum = 100;

	srand(time(NULL));
	
	set_array(numbers,wordnum);           //set an array to choose random line numbers. [1-100] because we have 100 different words.//
	shuffle(numbers,wordnum);              //shuffle the numbers randomly.//
	choose_line(numbers,lines,selectedword); //choose 10 from randomly shuffled numbers and assign them to line array.//
	choose_words(text,lines,words);   //choose 10 random words according to the line they held.//
	print_wordlist(words);            //display the word list.//
	make_grid(grid);                  //fill the grid with *.//
	print_numbers();                  //print row numbers.//
	
	for (int n = 0; n < selectedword; ++n){          //place 10 selected words.//
    	order = choose_order();           //randomly choose their order.//
    	place_words(n,words,grid,order);  //place the words on the grid.//
    }

    add_chars(grid,str);                  //randomly add chars in place of "*".//
	print_2D(grid,grid_size,grid_size);   //print the puzzle.//
	printf("\nIf you want to exit the game enter 'EXIT'.\n"); 
	printf("Entry example --> B16 smile\n");
	
	while(count != selectedword){                   //untill all 10 words found.//
		
		printf("\nPlease enter the coordinate and the word: ");   //get the infos.//
		fgets(string,15,stdin);                                   //to a string.//
		
		if (strncmp(string,exit,4) == 0){   //exit the program if user types 'EXIT'.//
			printf("\nGoodbye!\n");
			break;
		}

		else{
			sscanf(string,"%c%d %s",&ycharaxis,&xaxis,word);   //get the position and word from the string.//
			yaxis = ycharaxis - 17 - '0';                      //[ex: A = 0] convert char into integer.//
			i = 0;
		
			while (i < selectedword){                                        //check the words list.//
				if (strcmp(words[i],word) == 0){                  //if entered word is in the list
					if(search_word(word,xaxis,yaxis,grid) == 1){  //search word at all the orders and if func returns 1 it mean there's.//
						for (int j = 0; j < strlen(words[i]); ++j){
						words[i][j] -= 32;                       //make the word uppercase.//
						}
					}
					
					count ++;            //count when it found a word.//
				}
				
				print_wordlist(words);   //display the puzzle and wordlist everytime.//
				print_numbers();
				add_chars(grid,str);
				print_2D(grid,grid_size,grid_size);
				i ++;
			}
		}
	}

	if(count == selectedword) printf("\nCongrats! You completed the word puzzle!\n");
	
	return(0);
}

void shuffle(int array[], int n){      //Fisher–Yates shuffle algorithm with int arrays..//
	int i,j;

	for (i = n-1; i > 0; i--){        //start from the last element of the array to first.
		j = rand()%(i +1);            //choose a random value in i numbers.//
		swap(&array[i], &array[j]);   //and swap the j.th element of the array and i.th element of the array.// 
	}                                 //so the function shuffles elements randomly.//
}

void shufflestr(char array[], int n){       //Fisher–Yates shuffle algorithm with string.//
	int i,j;
	char temp;

	for (i = n-1; i > 0; i--){      
		j = rand()%(i +1);          
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;							   
	}                                 
}

void swap (int *a, int *b){ 
    int temp;                    //swap one integer to another.//
    temp = *a;                   //using temp value to not lose the value of them.//
    *a = *b; 
    *b = temp; 
} 

void set_array(int array[], int n){
	int j = 1;
	for (int i = 0; i < n; ++i){
		array[i] = j;          //fill the array with sequential numbers starting with j to n.//
		j++;
	}
}

void print_2D(char str[20][20],int c, int r){
	char x = 'A';       
	printf("\n");

	for (int i = 0; i < c; i++){            //print the grid.//
       	printf("%3c%3c",x,str[i][0]);       //print the column chars.//
       	x++;

       	for (int j = 1; j < r; j++) {
        	printf("%3c",str[i][j]);
        }
       
    	printf("\n");
    }
}

void print_wordlist(char words[10][15]){
	
	printf("\n\n***WORD LIST***\n\n");                 //print the word list.//
	for (int i = 0; i < 10; ++i){
    	for(int j = 0; j < strlen(words[i]); ++j){
        	printf("%c",words[i][j]);
    	}
    	printf("\n");
	}
}

void choose_line(int array1[],int array2[],int n){
	for (int i = 0; i < n; i++){
		array2[i] = array1[i];      //copy the n element of an array to another array.//  
	}
}

void choose_words(char *file_path, int lines[10], char words[10][15]){
	FILE *fp;
	char unwanted[15];  //to get unwanted words.//
	int line = 1;  //to count the lines of the file.//
	char temp[15];
	int i = 0,n;
	
	fp = fopen(file_path,"r");  //open the file.//

	while(!feof(fp)){           //read untill it's end of the file.//
		if(check_array(lines,line) == 1){   //if function returns 1 this means line value that it count is in the our randomly choosen line array.//
			fscanf(fp,"%s",temp);	       //read the word into temp string.//
			strcpy(words[i],temp);         //copy the temp string into 2D string.//
			n = strlen(temp);              //find the lenght of the string aka lenght of the word.//
			words[i][n] = '\0';            //to add \0 to end of the string.//
			line ++;                       //increment line.//   
			i ++;                          //increment the string column.//
		}

		words[i][n] = '\0';

		if(check_array(lines,line) == 0){   //if function returns 0 this means line value that it count is not in the our randomly choosen line array.//	
			fscanf(fp,"%s",unwanted);      //read the next word.//
			line ++;                      //increment line.//
		} 
	}
	
	fclose(fp);
}

int check_array(int lines[10], int number){
	int count = 0;      //to count if the number is in the array.//
	
	for (int i = 0; i < 10; i++){
		if (number == lines[i]){    //if number is in the array.//
			count ++;              //increment count.//
		}
	}

	return(count);
}

void make_grid(char grid[20][20]){
	for (int i = 0; i < 20; ++i){         //fill the grid with "*" in first place.//
		for (int j = 0; j < 20; ++j){	
			grid[i][j] = '*';       
		}
	}
}

void print_numbers(){

	char space = ' '; 
	printf("\n%3c",space);
	
	for (int i = 0; i < 20; i++){         //print the row numbers.//
        printf("%3d",i);
    }

}

void place_words(int n, char words[10][15],char grid[20][20], int order){
	char column[20] = "ABCDEFGHIJKLMNOPQRST";
	int row[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int r,c;
	int size,grid_size;

	shufflestr(column,20);      //randomly shuffle the column string.//
	shuffle(row,20);            //randomly shuffle the row array.//
	
	size = strlen(words[n]);
	grid_size = 20;
	r = row[n];                
	c = column[n] - 17 - '0';  //convert the char into integer.//

	switch(order){
		case 1:    //to the east.//
		
		for(int i = 0; i < size; ++i){    //check for the size of the word//
			while(grid[c][r+i] != '*' || (grid_size - r < size)){  //if there's a another word there or the word can get fit.
				shufflestr(column,20);                             //re-shuffle the arrays.//
				shuffle(row,20);
				r = row[n];                                        //assign the row and column to their new value.//
				c = column[n] - 17 - '0';                          //repeat it untill all conditions are true.//
			}
		}

		r = row[n];
		c = column[n] - 17 - '0';
		for (int j = 0; j < size; ++j){                         //for the size of the word
			grid[c][r+j] = words[n][j];                         //place the word into grid.//
		}
		
		break;

		case 2:  //to the south.//
		
		for(int i = 0; i < size; ++i){
			while(grid_size - c < size || grid[c+i][r] != '*'){
				shufflestr(column,20);
				shuffle(row,20);
				r = row[n];
				c = column[n] - 17 - '0';
			}
		}

		r = row[n];
		c = column[n] - 17 - '0';
		for (int j = 0; j < size; ++j){
			grid[c+j][r] = words[n][j];
		}

		break;

		case 3:  //to the west.//
	
		for(int i = 0; i < size; ++i){
			while(r+1 < size || grid[c][r-i] != '*'){
				shufflestr(column,20);
				shuffle(row,20);
				r = row[n];
				c = column[n] - 17 - '0';
			}
		}

		r = row[n];
		c = column[n] - 17 - '0';
		for (int j = 0; j < size; ++j){
			grid[c][r-j] = words[n][j];
		}

		break;
	
		case 4: //to the north.//
	
		for(int i = 0; i < size; ++i){
			while(c+1 < size || grid[c-i][r] != '*'){
				shufflestr(column,20);
				shuffle(row,20);
				r = row[n];
				c = column[n] - 17 - '0';
			}
		}

		r = row[n];
		c = column[n] - 17 - '0';
		for (int j = 0; j < size; ++j){
			grid[c-j][r] = words[n][j];
		}
		
		break;

	  	case 5: //to the north east.//
	
		for(int i = 0; i < size; ++i){
			while((grid_size - r < size) || (c + 1 < size) || (grid[c-i][r+i] != '*')){
				shufflestr(column,20);
				shuffle(row,20);
				r = row[n];
				c = column[n] - 17 - '0';
			}
		}

		r = row[n];
		c = column[n] - 17 - '0';
		for (int j = 0; j < size; ++j){
			grid[c-j][r+j] = words[n][j];
		}
		
		break;

		case 6: //to the south east.//
	
		for(int i = 0; i < size; ++i){	
			if((grid_size - r < size) || (grid_size -c < size) || (grid[c+i][r+i] != '*')){
				shufflestr(column,20);
				shuffle(row,20);
				r = row[n];
				c = column[n] - 17 - '0';
			}
		}

		r = row[n];
		c = column[n] - 17 - '0';
		for (int j = 0; j < size; ++j){
			grid[c+j][r+j] = words[n][j];
		}
	
		break;

		case 7: //to the north west.//
	
		for(int i = 0; i < size; ++i){
			while((r +1 < size) || (c + 1 < size) || (grid[c-i][r-i] != '*')){
				shufflestr(column,20);
				shuffle(row,20);
				r = row[n];
				c = column[n] - 17 - '0';
			}
		}

		r = row[n];
		c = column[n] - 17 - '0';
		for (int j = 0; j < size; ++j){
			grid[c-j][r-j] = words[n][j];
		}

		break;
	
		case 8: //to the south west.//
	
		for(int i = 0; i < size; ++i){
			while((r + 1 < size) || (grid_size - c < size) || (grid[c+i][r-i] != '*')){
				shufflestr(column,20);
				shuffle(row,20);
				r = row[n];
				c = column[n] - 17 - '0';
			}
		}

		r = row[n];
		c = column[n] - 17 - '0';
		for (int j = 0; j < size; ++j){	
			grid[c+j][r-j] = words[n][j];
		}
		
		break;
	}

}

int choose_order(){
	int order;
	order = rand()%8 +1;   //choose a number in the range[1-8].//

	return(order);
}

void add_chars(char grid[20][20], char str[26]){
	char x;
	
	for (int i = 0; i < 20; ++i){               //after 10 words is placed, place random chars.//
		shufflestr(str,26);                     //shuffle all chars.//
		
		for (int j = 0; j < 20; ++j){ 
			x = str[j];           
			
			if(grid[i][j] == '*'){           //place them on "*"s.//
				grid[i][j] = x;
			}
		}
	}
}

int search_word(char word[15],int x,int y,char grid[20][20]){
	int flag = 0;             //make flag 1, when successfully a word found and made uppercase.//
	int size = strlen(word);
	int result = 1;          //make result 0 if the word isn't there.//
		
	for (int i = 0; i < size; i++){    // control order 1.//
		if (grid[y][x+i] != word[i]) result = 0;
	}
	
	if (result == 1){                      //if the word is there.
		for (int i = 0; i < size; ++i){
			grid[y][x+i] -= 32;           //make it uppercase.//
		}

		flag = 1;                       //make flag 1 after succes.//
	}

	result = 1;
	for (int i = 0; i < size; i++){   // control order 2.//
		if (grid[y+i][x] != word[i]) result = 0;
	}

	if (result == 1){
		for (int i = 0; i < size; ++i){
			grid[y+i][x] -= 32;
		}

		flag = 1;
	}

	result = 1;
	for (int i = 0; i < size; i++){    // control order 3.//
		if (grid[y][x-i] != word[i]) result = 0;
	}

	if (result == 1){
		for (int i = 0; i < size; ++i){
			grid[y][x-i] -= 32;
		}

		flag = 1;
	}

	result = 1;
	for (int i = 0; i < size; i++){    // control order 4.//
		if (grid[y-i][x] != word[i]) result = 0;
	}

	if (result == 1){
		for (int i = 0; i < size; ++i){
			grid[y-i][x] -= 32;
		}

		flag = 1;
	}

	result = 1;
	for (int i = 0; i < size; i++){   // control order 5.//
		if (grid[y-i][x+i] != word[i]) result = 0;
	}

	if (result == 1){
		for (int i = 0; i < size; ++i){
			grid[y-i][x+i] -= 32;
		}

		flag = 1;
	}

	result = 1;
	for (int i = 0; i < size; i++){   // control order 6.//
		if (grid[y+i][x+i] != word[i]) result = 0;
	}

	if (result == 1){
		for (int i = 0; i < size; ++i){
			grid[y+i][x+i] -= 32;
		}

		flag = 1;
	}

	result = 1;
	for (int i = 0; i < size; i++){   // control order 7.//
		if (grid[y-i][x-i] != word[i]) result = 0;
	}

	if (result == 1){
		for (int i = 0; i < size; ++i){
			grid[y-i][x-i] -= 32;
		}

		flag = 1;
	}

	result = 1;
	for (int i = 0; i < size; i++){   // control order 8.//
		if (grid[y+i][x-i] != word[i]) result = 0;
	}

	if (result == 1){
		for (int i = 0; i < size; ++i){
			grid[y+i][x-i] -= 32;
		}

		flag = 1;
	}

	return(flag);
}