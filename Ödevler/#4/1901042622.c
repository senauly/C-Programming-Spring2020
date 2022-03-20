#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

void decrypt_and_print (char* file_path);
char decrypt_numbers (int number);
void deep_decrypt_and_print (char* file_path);
void track_machine ();
void refresh_position (int *X, int *Y, double *D, double *R);
void encrypt_messages (char* file_path);
void menu();

int main()
{
	
	menu();
	
	return 0;
}

void decrypt_and_print (char* file_path)
{
	FILE *fp;
	char x;                       //the char which it read from the file.//
	int num;                      //result of conversion of char.//
	fp = fopen(file_path,"r");    //open the file.//

	while(!feof(fp))            
	{
		fscanf(fp,"%c",&x);     //read the char.//
		if (x == '\n')          
		{ 
			printf("\n");      //to add space after end of line.//
		}

		else
		{
			num = x - '0';   //convert the char to int.//
			printf("%c",decrypt_numbers(num));  //print the result.//
		}
	}

	printf("\n\n");          
	fclose(fp);             //close the file.//
}

char decrypt_numbers (int number)
{
	switch(number)     //to convert chars into integers.//
	{
		case 0:
		number = ' ';
		break;

		case 1:
		number = '-';
		break;

		case 2:
		number = '_';
		break;

		case 3:
		number = '|';
		break;

		case 4:
		number = '/';
		break;

		case 5:
		number = '\\';
		break;

		case 6:
		number = 'O';
		break;
	}

	return(number);
}

void deep_decrypt_and_print (char* file_path)
{
	FILE *fp;
	int n1,n2,n3,n4;           //results of conversion of chars.//
	int result;                //result of the formula.//
	char x1,x2,x3,new_value;   //chars which it read from the file.//
	
	fp = fopen(file_path,"r");
	
	fscanf(fp,"%c %c %c",&x1,&x2,&x3);   //read the chars.//
	n1 = x1 - '0';                       //convert the chars into integers.//
	n2 = x2 - '0';
	n3 = x3 - '0';
	
	while(!feof(fp))
	{
		result = (n1+n2+n3)%7;                   //apply the formula.//
		printf("%c",decrypt_numbers(result));    //print the char result with the help of the function.//
		
		fscanf(fp,"%c",&new_value);             //read a new value.//

		if (new_value == '\n')                 //if end of the line.//
		{
			printf("\n");                     //to add space.//
			fscanf(fp,"%c ",&new_value);      //read new values and convert them into integers.//
			n2 = new_value - '0';
			fscanf(fp,"%c ",&new_value);
			n3 = new_value - '0';
			fscanf(fp,"%c ",&new_value);
		}

		n4 = new_value - '0';           //convert the last value to integer.//
		n1 = n2;                        //now it don't need the first value to continue to loop.//
		n2 = n3;                        //so it assign first number to second, second to third, third to new value it has read.//
		n3 = n4;
		
	}

	printf("\n\n");
	fclose(fp);                       //close the file.//
}

void track_machine ()
{
	int curr_x = 0, curr_y = 0;                 //coordinates of the enemy.//
	double displacement = 0,distance = 8.49;    //initial displacement of enemy and enemy's distance to out camp.//
	char command;                               //refresh or end.//

	while(command != 'E')
	{
		if(command == 'R') refresh_position(&curr_x,&curr_y,&displacement,&distance);   //if 'R' is entered refresh the positions.//
		
		for(int i = 1; i <= 11; i++)         //columns of the battlefield.//
		{
			for (int j = 1; j < 11; j++)    //lines of the battlefield.//
			{
				if (i == 6 && j == 6) printf("O\t");                    //when it's (6,6) print our position.//
				else if (i == curr_x && j == curr_y) printf("E\t");    //when it's enemy's current position print it.//
				else printf(".\t");                                   //when it's not the both print a dot.//
			}

			printf(".\n");                                          
			
		}
		
		printf("Enemies x position: %d, y position: %d, displacement: %.2f, distance to our camp: %.2f\nCommand waiting..: ",curr_x,curr_y,displacement,distance);
		scanf(" %c",&command);    //get the command.//

		if(command != 'R' && command != 'E')     //when user enters non-valid command.//
		{
			printf("\nError, unsupported command. Please enter 'R' to refresh position, 'E' to shut down the machine.\nCommand waiting..: ");
			scanf(" %c",&command);              //get a valid command.//
		}
	} 

	printf("\n\n");
}

void refresh_position (int *X, int *Y, double *D, double *R)
{
	int prev_x = 0,last_x ,prev_y = 0,last_y;    //initial values.//
	prev_x = *X;                                 //to not lose the previous values.//
	prev_y = *Y;
	
	//[rand() % (upper - lower + 1)) + lower] to generate numbers in our range. upper = 11 and lower = 0//

	do
	{	
		srand(time(0));
		last_x = (rand() %11 + 1);     //generate random x and y.//
		last_y = (rand() %11 + 1);

		*X = last_x;
		*Y = last_y;

	} while(*X == 6 && *Y == 6);


	*R = sqrt(((6-last_x)*(6-last_x)) + ((6-last_y)*(6-last_y)));      //compute the distance to our camp.//
	*D = sqrt(((last_x-prev_x)*(last_x-prev_x)) + ((last_y-prev_y)*(last_y-prev_y)));   //compute the displacement of the enemy.//

} 

void encrypt_messages (char* file_path)
{
	FILE *decrypted;
	FILE *encrypted;
	char x;                     			//char which it read from the file.//
	int n1 = 0,n2 = 0,n3 = 0,result = 0;    		//conversion of integer.//
	
	decrypted = fopen(file_path,"r");            //read-only the decrypted_4.img.//
	encrypted = fopen("encrypted_p4.img", "w");  //create a new file to write encrypt results.//

	    

	while(!feof(decrypted))
	{
		fscanf(decrypted, "%c", &x);                  //read the char.//
		
		while (x == '\n' && !feof(decrypted))        //to prevent the infinite loop, because end of the file is \n as well.//
		{
	       	fprintf(encrypted,"%c",x);   
			fscanf(decrypted,"%c",&x);            //read the new char.//
			n1 = 0;                             //there are no longer available three number so assume missing numbers are 0.//
			n2 = 0;
		}

		
		switch(x)                            //convert char into integer.//
		{
			case ' ':
			n3 = 0;
			break;

			case '-':
			n3 = 1;
			break;
			
			case '_':
			n3 = 2;
			break;

			case '|':
			n3 = 3;
			break;

			case '/':
			n3 = 4;
			break;

			case '\\':
			n3 = 5;
			break;

			case 'O':
			n3 = 6;
			break;
		}
		
		result = (n1+n2+n3)%7;          //apply the formula.//
		fprintf(encrypted, "%d",result);  //print the result in the new file.//

		n1 = n2;                       //to continue to loop.//
		n2 = n3;
	}

	printf("Message is encrypted.\n\n");
	fclose(decrypted);
	fclose(encrypted);	


}

void menu()
{
	int ch = 0;                                	   //menu choice.//
	char *encrypted_p1 = "encrypted_p1.img";      //file_paths.//
	char *encrypted_p2 = "encrypted_p2.img";
	char *decrypted_p4 = "decrypted_p4.img";
	
	while(ch != 5)
	{
		printf("\n1) Decrypt and print encrypted_p1.img\n2) Decrypt and print encrypted_p2.img\n3) Switch on the tracking machine\n4) Encrypt the message\n5) Switch off\n");
		printf("\nPlease make your choice:\n");
		scanf("%d",&ch);

		if(ch == 1) decrypt_and_print(encrypted_p1);
		if(ch == 2) deep_decrypt_and_print (encrypted_p2);
		if(ch == 3) track_machine();
		if(ch == 4) encrypt_messages(decrypted_p4);
		if(ch != 1 && ch != 2 && ch != 3 && ch != 4 && ch != 5) printf("\nInvalid number. Choose in the range below.\n");
	}
}
	
	


