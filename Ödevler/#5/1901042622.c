#include<stdio.h>

void menu();
void read_news(char buffer[500], char file_path[11], int is_Only_Title);
void append_file(char* file_path, char c);
void read_magic_numbers(char buffer_magic[10], char buffer_news[500]);
double f_func(int x);
double g_func(double f(int x), int a);
double find_secret_number(char buffer_magic[10]);
int check_if_readed(char* file_path, char c);
void ask_option(char cont);

int main()
{
	menu();
	return(0);
}

void menu()
{
	FILE *fp;      //for part b.//
	char choice;   //input - choice of the action.//
	int ch_news;   //input - choice of the news text.//
	int is_Only_Title = 0, answer;  //inputs.//
	int a = 0;     //for g_func.//
	char c, cont;  //for functions//continue input.//
	char x;        //readed char from file.//
	
	char text_1[11] = "news/1.txt";     //file paths.//
	char text_2[11] = "news/2.txt";
	char text_3[11] = "news/3.txt";
	char text_4[11] = "news/4.txt";
	char *readed_news = "readed_news_id.txt";
	char buffer[500];             //string to put news in it.//
	char buffer_magic[10];        //string to put magic numbers in it.//


	printf("\n\n*************** DAILY PRESS ***************\n\n");
	printf("Title of 1. news:");
	read_news(buffer,text_1,0);       //read only the titles from the file.//
	printf("Title of 2. news:");
	read_news(buffer,text_2,0);
	printf("Title of 3. news:");
	read_news(buffer,text_3,0);
	printf("Title of 4. news:");
	read_news(buffer,text_4,0);
	printf("\nWhat do you want to do?\na. Read a new\nb. List the readed news\nc. Get decrypted information from the news\n\n");
	scanf(" %c",&choice);   //get the choice.//

	switch(choice)
	{
		case 'a':
		printf("\nWhich news text you want to read?\n");
		scanf("%d",&ch_news);   //get the news choice.//

		is_Only_Title = 1;          //in this part it'll need the whole of the news.//
		if(ch_news == 1) c = '1';   //to append the file and to check if it is readed before.//
		if(ch_news == 2) c = '2';
		if(ch_news == 3) c = '3';
		if(ch_news == 4) c = '4';

		if (check_if_readed(readed_news,c) == 1) 
		{
			printf("This new is readed. Do you want to read again? Yes(1)/No(0): ");
			scanf("%d",&answer);

			while(answer != 0 && answer != 1)
			{
				printf("ERROR! You made a nonvalid choice. Please choose again: ");
				scanf("%d",&answer);                       //get a valid answer.//
			}
		}

		if(check_if_readed(readed_news,c) == 0 || answer == 1)
		{
			if(ch_news == 1) read_news(buffer,text_1,is_Only_Title);    //read news according to choice.//
			if(ch_news == 2) read_news(buffer,text_2,is_Only_Title);
			if(ch_news == 3) read_news(buffer,text_3,is_Only_Title);
			if(ch_news == 4) read_news(buffer,text_4,is_Only_Title);
				
			append_file(readed_news,c);    //append file after reading the news.//
		}
		
		ask_option(cont);                //to not write the same thing again for all the parts I've made a function to ask if they want to continue.//
		break;

		case 'b':

		fp = fopen("readed_news_id.txt","r");      //open the file.//
		fscanf(fp," %c",&x);                       //read a char.//
		printf("Readed news are listed below:\n");

		while(!feof(fp))
		{
			if(x == '\0') printf("There is no readed news.\n");   //if there's no char to read.//
			else printf("%c. new is readed.\n",x);                //if there's display it.//
			fscanf(fp," %c",&x);                                  //read the next char again and then loop untill it's EOF.//
		}
		
		ask_option(cont);
		break;

		case 'c':

		printf("\nWhich news would you like to decrypt? ");
		scanf("%d",&ch_news);
                                              //display the secret message according to choice.//
		if(ch_news == 1) 	
		{ 
			read_news(buffer,text_1,1);                  //read the selected news.//
			read_magic_numbers(buffer_magic,buffer);     //find magic numbers in it.//
			printf("\nNumber of tests performed: %.2f\n",find_secret_number(buffer_magic));   //display the message.//
		}
	

		if(ch_news == 2) 	
		{
			read_news(buffer,text_2,1);
			read_magic_numbers(buffer_magic,buffer);
			printf("\nNumber of sick people: %.2f\n",find_secret_number(buffer_magic));
		}
		
		if(ch_news == 3) 	
		{	
			read_news(buffer,text_3,1);
			read_magic_numbers(buffer_magic,buffer);
			printf("\nNumber of deaths: %.2f\n",find_secret_number(buffer_magic));
		}

		if(ch_news == 4) 	
		{	
			read_news(buffer,text_4,1);
			read_magic_numbers(buffer_magic,buffer);
			printf("\nExpected number of sick people: %.2f\n",find_secret_number(buffer_magic));
		}

		ask_option(cont);
		break;

		default:
		printf("ERROR! You made a nonvalid choice. Please choose again:\n\n");    //if user enter out of the range.//
		menu();
	}

}

void read_news(char buffer[500], char file_path[11], int is_Only_Title)
{
	FILE *fp;                     
	char x;                       //readed char from the file.//
	int i = 0;                    //to count.//

	fp = fopen(file_path, "r");   //open the file.//
	fscanf(fp,"%c",&x);           //read the first char.//

	if (is_Only_Title == 0)      // to read only the title.//
	{
		while(x != '\n')         //untill it gets to the end of the line.//
		{
			buffer[i] = x;       //i.factor of the string is the readed char.//
			fscanf(fp,"%c",&x);  //read the next char then loop.//
			i ++;                //to count the string factors.//
			
		}
	}

	else if(is_Only_Title == 1)	 //to read the whole news.//
	{
		while(!feof(fp))        //until it's end of the file.//
		{
			buffer[i] = x;
			fscanf(fp,"%c",&x);
			i ++;
		}
	}

	buffer[i] = '\0';        //to put an end to the string.//
	printf("%s\n",buffer);   //display the string that filled with the news.//
	fclose(fp);              //close the file.//
}

void append_file(char* file_path, char c)
{
	FILE *fp;            
	char x;                 //readed char from the file.//
	int count = 0;              

	fp = fopen(file_path, "a+");    //open to read&append.//

	while(!feof(fp))
	{
		fscanf(fp,"%c",&x);
		if (x == c) count ++;     //if the readed char in the file is the same as user wants to append +1 to count.//
	}

	if(count == 0)               //this means the char user wants to append is not in the file.//
	{
		fprintf(fp, "%c\n",c);   //so append that in the file.//
	}

	fclose(fp);                 //close the file.//
}


int check_if_readed(char* file_path, char c)
{
	FILE *fp;
	char x;
	int result = 0,count = 0;

	fp = fopen(file_path, "r");

	while(!feof(fp))
	{
		fscanf(fp,"%c",&x);
		if (x == c) count ++;
	}

	if (count == 1)      //this means the char user wants to append in the file so it has read before.//
	{
		result = 1;     //if it has read return 1 if not return 0.//
	}

	return(result);
}

void read_magic_numbers(char buffer_magic[10], char buffer_news[500])
{
	int j = 0;   //to count the buffer_magic's factors.//
	
	for (int i = 0; i < 500; ++i)   //to read buffer_news's factors.
	{
		if (buffer_news[i] == '#')  //numbers after # are magic numbers, it'll find #.//
		{
			buffer_magic[j] = buffer_news[i+1];   //then assign the number after that to magic string's i.factor.//
			j ++;                                 //+1 j and loop.//
		}
	}

	buffer_magic[j] = '\0';                     //to put an end to the string.//
}

double f_func(int x)
{
	double result = 0;
	result = (x*x*x) - (x*x) + 2;            //compute the function according to given.//

	return(result);
}

double g_func(double f(int x), int a)
{
	double result = 0;
	result = (f_func(a)*f_func(a));        //compute the function according to given.//
	
	return(result);
}

double find_secret_number(char buffer_magic[10])
{
	int i = 0;
	double result = 0;

	while(buffer_magic[i] != '\0')      //untill the end of the buffer magic string.//
	{
		buffer_magic[i] = buffer_magic[i] - '0';                  //convert char into integer to compute the functions.//
		result =  result + g_func(f_func,buffer_magic[i]);        //it should add up the result of the g_function for all the magic numbers.//
		i ++;                                                     //loop.//
	}

	return(result);
}

void ask_option(char cont)
{
	printf("Do you want to continue? Yes(y)/No(n): ");
	scanf(" %c",&cont);                                  //get the answer.//

	while (cont != 'y' && cont != 'n')                  //untill the user enters a valid char.//
	{
		printf("ERROR! You made a nonvalid choice. Please choose again: ");
		scanf(" %c",&cont);                       //get a valid answer.//
	}
		
	if (cont == 'y') menu();
	if (cont == 'n') printf("Goodbye!\n");
}