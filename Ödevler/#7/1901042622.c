#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LINE 2000
#define G_LINE 12
#define P_LINE 10

void lists(char names[LINE][100], char genres[G_LINE][20], char platforms[P_LINE][20],float data[LINE][7]);
void print_string(char str[][20],int n);
int check_duplication(char temp[20], char str[20][20], int n);
void check_string(char temp[20], char str[20][20]);
float find_string(char temp[20], char str[20][20], int n);

int main(){
	int operation;
	char names[LINE][100];
	char genres[G_LINE][20];
	char platforms[P_LINE][20];
	float data[LINE][7];
	char name[100];
	int temp, count, result = -1;
	int selectedyear, untilorsince,i,a,b,c,column;
	float total_score = 0;
	int genre[G_LINE];
	int platform[P_LINE];

	lists(names,genres,platforms,data);  //take the data's from file.//

	while(operation != 8){
		printf("\n0: List of Genres\n1: List of the Platforms\n2: List of the Games Through the Years\n3: All Informations of a Single Game\n4: Average of the User Scores\n5: Georographical Information of a Single Game\n6: Frequence of the Genres\n7: Frequence of the Platforms\n8: Exit\n\n");
		printf("Please select an operation: ");
		scanf("%d",&operation);     //take the operation.//
		
		switch(operation){
			case 0:
			print_string(genres,G_LINE);     //display genres.//
			break;

			case 1:
			print_string(platforms,P_LINE);   //display platforms.//
			break;

			case 2:
			selectedyear = 3000;  //to enter the loop, when it's selected again otherwise it stayed at the last value it has and don't enter loop.//
			while(((selectedyear > 2005 || selectedyear <= 1985) && untilorsince == 0) || ((selectedyear >= 2005 || selectedyear < 1985) && untilorsince == 1)){
				printf("\nEnter a year: ");
				scanf("%d",&selectedyear);
				printf("Until(0) or Since(1) %d: ",selectedyear);
				scanf("%d",&untilorsince);
				if((selectedyear > 2005 || selectedyear <= 1985) && untilorsince == 0) printf("TRY AGAIN.\n");
				if((selectedyear >= 2005 || selectedyear < 1985) && untilorsince == 1) printf("TRY AGAIN.\n");

				if (untilorsince == 0){
					count = 0;  //count the lines.//
					for (i = 0; i < LINE; ++i){
						temp = (int)data[i][2]; //year is in float format in the array so assign it to an int value.//
						if(temp < selectedyear) count ++; //until it's selecetedyear count.//
					}
				}

				if (untilorsince == 1){
					count = 0;
					for (i = 0; i < LINE; ++i){
						temp = (int)data[i][2];
						if(temp > selectedyear) count ++; //since selected year, count.//
					}
				}
			}
			
			if (untilorsince == 0){
				for (int j = 0; j < count; ++j){
					printf("%s\n",names[j]);   //print until count.//
				}
			}

			if (untilorsince == 1){
				for (int j = LINE-count; j < LINE ; j++){ 
					printf("%s\n",names[j]);  //print until last line but start from LINE-count, because it needs games after selectedyear.//
				}
			}
			
			break;

			case 3:
			result = -1; //if there's no game in the that name result is -1.//
			while(result == -1){  //take a new name each time if there's no game in that name.//
				printf("\nPlease enter the name of the game.\n");
				scanf("%s",name);

				for (column = 0; column < LINE; ++column){
					if(strcmp(names[column], name) == 0){  //check if name exist.//
						result = column; //result is the location of the name in the names str.//
						break;  //for the games which released on different platforms, it breaks the loop to pick the first one.//
					}
				}

				if(result == -1) printf("TRY AGAIN.\n");
			}

			a = (int)data[result][0];  //location of genres/platforms is in float format so store them in int to use as array element.//
			b = (int)data[result][1];
			c = (int)data[result][2];  //year is in float format so store it in int format to use.//

			printf("\nName: %s\nGenre: %s\nPlatform: %s\nYear: %d\nSales in NA: %.2f\nSales in EU: %.2f\n",name,genres[a],platforms[b],c,data[result][3],data[result][4]);
			if(data[result][5] != 0.0) printf("Total Sales: %.2f\nUser Score: %.2f\n",data[result][5],data[result][6]);
			else if(data[result][5] == 0.0) printf("Total Sales: Not Available\nUser Score: %.2f\n",data[result][6]);
			break;  //strtod returns 0 if "not_available" so if total sales is 0 print not available instead of 0.//
			
			case 4:
			total_score = 0;
			for (int i = 0; i < LINE; ++i){
				total_score = total_score + data[i][6];  //sum the scores.//
			}

			printf("\nAverage: %f\n",(total_score/LINE)); //display the average.//
			break;

			case 5:
			result = -1; //if there's no game in the that name result is -1.//
			while(result == -1){  //take a new name each time if there's no game in that name.//
				printf("Plese enter the name of the game: ");
				scanf("%s",name);

				for (column = 0; column < LINE; ++column){
					if(strcmp(names[column], name) == 0){  //check if name exist.//
						result = column;  //result is the location of the name in the names str.//
						break;  //for the games which released on different platforms, it breaks the loop to pick the first one.//
					}
				}

				if(result == -1) printf("TRY AGAIN.\n");
			}
			
			if(data[result][4] > data[result][3]) printf("\n%s was more popular in Europe.\n",name);  //control which one is greater and print.//
			else if(data[result][4] < data[result][3]) printf("\n%s was more popular in North America.\n",name);
			else if(data[result][4] = data[result][3]) printf("\n%s was equally popular in both.\n",name);
			break;

			case 6:
			for (int i = 0; i < LINE; ++i){         //count the genres in other array elements.//
				if(data[i][0] == 0.0) genre[0] ++;
				if(data[i][0] == 1.0) genre[1] ++;
				if(data[i][0] == 2.0) genre[2] ++;
				if(data[i][0] == 3.0) genre[3] ++;
				if(data[i][0] == 4.0) genre[4] ++;
				if(data[i][0] == 5.0) genre[5] ++;
				if(data[i][0] == 6.0) genre[6] ++;
				if(data[i][0] == 7.0) genre[7] ++;
				if(data[i][0] == 8.0) genre[8] ++;
				if(data[i][0] == 9.0) genre[9] ++;
				if(data[i][0] == 10.0) genre[10] ++;
				if(data[i][0] == 11.0) genre[11] ++;
			}

			for (int i = 0; i < G_LINE; ++i){
				printf("%-15s%-10d\n",genres[i],genre[i]); //print the frequency.//
			}

			break;

			case 7:
			for (int i = 0; i < LINE; ++i){        //count the platforms in other array elements.//
				if(data[i][1] == 0.0) platform[0] ++;
				if(data[i][1] == 1.0) platform[1] ++;
				if(data[i][1] == 2.0) platform[2] ++;
				if(data[i][1] == 3.0) platform[3] ++;
				if(data[i][1] == 4.0) platform[4] ++;
				if(data[i][1] == 5.0) platform[5] ++;
				if(data[i][1] == 6.0) platform[6] ++;
				if(data[i][1] == 7.0) platform[7] ++;
				if(data[i][1] == 8.0) platform[8] ++;
				if(data[i][1] == 9.0) platform[9] ++;
			}

			for (int i = 0; i < P_LINE; ++i){
				printf("%-5s%-10d\n",platforms[i],platform[i]); //print the frequency.//
			}

			break;

			case 8:
			printf("\nGOODBYE!\n");
			break;

			default:
			printf("\nTRY AGAIN.\n");
			break;
		}
	}
}
	
void lists(char names[LINE][100], char genres[G_LINE][20], char platforms[20][20],float data[LINE][7]){
	FILE *fp;
	char str[200];
	char temp2[100];
	char temp3[100];
	char global[20];
	char *temp;
	int i = 0, x = 0, c = 0;

	fp = fopen("Video_Games.txt","r");  //open the file.//
	
	fgets(str,100,fp);   //read the first line of the file.//
	
	
	for (c = 0; c < LINE; c++){  //read until the end of the file.//
		fscanf(fp,"%s",str);  //take each line in a string.//
		sscanf(str," %[^,] %*c %[^,] %*c %[^,] %*c %f %*c %f %*c %f %*c %[^,] %*c %f %*c",names[c],temp2,temp3,&data[c][2],&data[c][3],&data[c][4],global,&data[c][6]);
		//to read until ',' and assign them.//
		
		if(check_duplication(temp2,genres,G_LINE) != 1){  //if the temp value is not in the genres string.//
			strcpy(genres[i],temp2);   //copy the temp value to real string.//
			i ++; //increase genres element.//
		}
 
		if(check_duplication(temp3,platforms,P_LINE) != 1){  //if the temp value is not in the platform string.//
			strcpy(platforms[x],temp3);  //copy the temp value to real string.//
			x ++;  //increase platforms element.//
		}

		data[c][0] = find_string(temp2,genres,G_LINE);  //find the location of the genre in the genres string and take that location in float.//
		data[c][1] = find_string(temp3,platforms,P_LINE);  //find the location of the platform in the platforms string and take that location in float.//
		data[c][5] = strtod(global, &temp); //if there's only string value it returns 0, otherwise take the float value.//
		
	}

	fclose(fp);  //close the file.//
}
	


void print_string(char str[][20],int n){
	printf("\n");
	for (int i = 0; i < n; ++i){  //print string n lines.//
		printf("%s\n",str[i]);
	}
}

int check_duplication(char temp[20], char str[20][20], int n){
	for (int i = 0; i < n; ++i){
		if(strcmp(str[i], temp) == 0){  //if the temp value has already in the string.//
			return(1);   //return 1.//
		}
	}
}

float find_string(char temp[20], char str[20][20], int n){
	for (int i = 0; i < n; ++i){  //check n lines.//
		if(strcmp(str[i], temp) == 0) return(i/1.0); //when it find temp value in string returns i(location).//
	}                                                //I divided it with 1.0 to make it float.//
}