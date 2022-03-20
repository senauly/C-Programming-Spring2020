#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
//In the commands.txt it says there's 3 actions but it has 6. I've changed it with 6 and made my solutions according to 6 actions.//

struct point{
	char name[5];
	float start_loc;
	float finish_loc;
};

struct line{
	char name[5];
	struct point start;
	struct point finish;
};

struct polygon{
	char name[5];
	struct point P[20];

};

void read_file(char *file_path,struct point Points[100],struct line Lines[100],struct polygon Polygons[100]);
int count_char(char *str, char c);
void remove_char(char *str);
int search_point(struct point *Points,char *str);
int search_line(struct line *Lines, char *str);
int search_polygon(struct polygon *Polygons, char *str);
void distance_points(struct point *Points,int i,int j,float *distancep);
void distance_point_line(struct point *Points,struct line *Lines, int i, int j,float *distancel);
void find_angle(struct line *Lines,int i,int j,float *angle);
void length_line(struct line *Lines,int i,float *lenghtline);
void length_polygon(struct polygon *Polygons,int i,int num,float *lenghtpolygon);
void area_polygon(struct polygon *Polygons,int i,int n,float *area);

void main(){
	struct line Lines[100];       //structs.//
	struct point Points[100];
	struct polygon Polygons[100];
	
	FILE *fp, *output;           //files.//

	char temp[100],name[5],startpoint[5],finishpoint[5],*ptr,polygon[20][3];  //temp variables to hold data.//
	char act1[5],act2[5],action_name[10];
	int count = 0, a = 0, b = 0, c = 0, n = 0, num = 0,m = 0; 
	int Linenum[20];
	float startloc, finishloc,result;
	int startpointloc, endpointloc,i,j;
	
	int num_data,num_action;                                   //number of data and actions.//
	char file[30];

	float distancep = 0,distancel = 0,angle = 0,lenghtline = 0,lenghtpolygon = 0,area = 0;  //outputs.//

	fp = fopen("commands.txt","r");
	
	while(!feof(fp)){
		fscanf(fp,"%s",temp);                       //read a line.//
		
		if(strcmp(temp,"data") == 0){ 
			fscanf(fp,"%d",&num_data);             //number of 2D objects.//
		
			while(count < num_data){
				fgets(temp,100,fp);               //read the next line.//
				ptr = strchr(temp,'/');           //if line includes char '\',
				if(ptr != NULL) *ptr = '\0';      //remove the chars after that.//
				 
				//if line includes only 'P',than it's defining a point.//
				if(strchr(temp,'P') != NULL && strchr(temp,'L') == NULL && strchr(temp,'G') == NULL ){ 
					sscanf(temp,"%f %f %s",&startloc,&finishloc,name);   //get the data from the line it has readed.//
					strcpy(Points[a].name,name);                         //copy name to point struct.//
					Points[a].start_loc = startloc;                      //assign start location to point struct.//
					Points[a].finish_loc = finishloc;                    //assign finish location to point struct.//
					count ++;
					a ++;
				}
				//if line includes 'L', but not 'G'; than it's defining a line.//
				if(strchr(temp,'L') != NULL && strchr(temp,'G') == NULL ){
					sscanf(temp,"%s %s %s",startpoint,finishpoint,name);

					strcpy(Lines[b].name,name);
					i = search_point(Points,startpoint);     //search the name of the point in point struct, and take its location.//
					Lines[b].start = Points[i];              //then assign line struct to point struct in the location it found.//

					i = search_point(Points,finishpoint);
					Lines[b].finish = Points[i];
					count ++;
					b ++;
				}
				//if line includes only 'G',than it's defining a polygon.//
				if(strchr(temp,'G') != NULL ){
					m = 0;
					if (strchr(temp,'L') != NULL){     //if polygon is defined by lines.//
						j = count_char(temp,'L');      //count how many lines it has to find out edge number.//

						Linenum[c] = j;  //hold the number of edges in a array.//
						
						for (a = 0; a < j; ++a){
							sscanf(temp,"%s",polygon[a]);  //read untill space to temp str.//

							for (i = 0; i < 100; ++i){     //search that name in the line struct and take its location.//
								if(strcmp(Lines[i].name,polygon[a]) == 0) break;
							}

							if(search_point(Polygons[c].P,Lines[i].start.name) == -1){  //if Polygon[c] does not have the start point of that line,
								Polygons[c].P[m].start_loc = Lines[i].start.start_loc;      //assign it to Polygon struct.//
								Polygons[c].P[m].finish_loc =  Lines[i].start.finish_loc;
								strcpy(Polygons[c].P[m].name,Lines[i].start.name);
								m++;                	
							}

							if(search_point(Polygons[c].P,Lines[i].finish.name) == -1){

								Polygons[c].P[m].start_loc = Lines[i].finish.start_loc;
								Polygons[c].P[m].finish_loc =  Lines[i].finish.finish_loc;
								strcpy(Polygons[c].P[m].name,Lines[i].finish.name);
								m ++;
							}
							
							remove_char(temp);   //remove the first 'line' from string until it reaches end.//
						}

					}

					else if (strchr(temp,'P') != NULL && strchr(temp,'L') == NULL){
 						j = count_char(temp,'P') - 1;    //-1 because Polygon name has P in it.//
 						Linenum[c] = j;
 						for (int a = 0; a < j; ++a){
							sscanf(temp,"%s",polygon[a]);
							i = search_point(Points,polygon[a]);

							Polygons[c].P[a].start_loc = Points[i].start_loc;
							Polygons[c].P[a].finish_loc = Points[i].finish_loc;
							strcpy(Polygons[c].P[a].name,Points[i].name);

							remove_char(temp);
						}
					}
					
					sscanf(temp,"%s",name);    //assign the last string to name of struct.//
					strcpy(Polygons[c].name,name);
					c ++;
					count ++;
				}
			}
		}

		if(strcmp(temp,"actions") == 0){
			count = 0;
			fscanf(fp,"%s",file);
			output = fopen(file,"w");     //open the file to write output of actions.//
			fscanf(fp,"%d",&num_action);  //number of actions.//

			while(count < num_action){
				fscanf(fp,"%s ",action_name);  //get the name of the action of the line.//
				fgets(temp,100,fp);            //then take rest of the line.//
				ptr = strchr(temp,'/');        //again remove comment line if it has.//
				if(ptr != NULL) *ptr = '\0';

				if(strcmp(action_name,"Distance") == 0){
					sscanf(temp,"%s %s",act1,act2);    //take the 2D objects.//

					if(strchr(temp,'L') == NULL){      //if they're just points.//
						j =	search_point(Points,act1); //search point in the Point struct and take its location.//
						i = search_point(Points,act2);
						distance_points(Points,i,j,&distancep);  //find the distance between two points.//
						fprintf(output,"Distance(%s,%s) = %.1f\n",act1,act2,distancep);  //write it to the output file.//
						count ++;
					}

					if(strchr(temp,'L') != NULL){    //if one of them is a line.//
						sscanf(temp,"%s %s",act1,act2);

						if(strchr(act1,'L') == NULL) j = search_point(Points,act1);
						if(strchr(act1,'L') != NULL) i = search_line(Lines,act1);
						if(strchr(act2,'L') == NULL) j = search_point(Points,act2);
						if(strchr(act2,'L') != NULL) i = search_line(Lines,act2);

						distance_point_line(Points,Lines,i,j,&distancel);
						fprintf(output,"Distance(%s,%s) = %.1f\n",act1,act2,distancel);
						count ++;
					}
				}

				if(strcmp(action_name,"Angle") == 0){
					sscanf(temp,"%s %s",act1,act2);
					j = search_line(Lines,act1);   //search point in the Line struct and take its location.//
					i = search_line(Lines,act2);

					find_angle(Lines,i,j,&angle);
					fprintf(output,"Angle(%s,%s) = %.1f\n",act1,act2,angle);
					count ++;
				}

				if(strcmp(action_name,"Length") == 0){
					sscanf(temp,"%s",act1);

					if(strchr(act1,'G') == NULL){   //length of lines.//
						i = search_line(Lines,act1);
						length_line(Lines,i,&lenghtline);
						fprintf(output,"Length(%s) = %.1f\n",act1,lenghtline);
						count ++;
					}

					if(strchr(act1,'G') != NULL){   //length of polygons.//
						i = search_polygon(Polygons,act1);
						num = Linenum[i];    //number of edges.//
						length_polygon(Polygons,i,num,&lenghtpolygon);
						fprintf(output,"Length(%s) = %.1f\n",act1,lenghtpolygon);
						count ++;
					}
				}

				if(strcmp(action_name,"Area") == 0){
					sscanf(temp,"%s",act1);
					i = search_polygon(Polygons,act1);
					num = Linenum[i];
					area_polygon(Polygons,i,num,&area);
					fprintf(output,"Area(%s) = %.1f\n",act1,area);
					count ++;

				}
			}
		}
	}
	
	printf("Outputs have been saved.\n");
	fclose(output);
	fclose(fp);
}

int count_char(char *str, char c){
	int count = 0;                               //counting char to calculate number of edges.//
	for (int i = 0; i < strlen(str); ++i){
		if (str[i] == c) count ++;              //when it finds the char,increases the count.//
	}

	return(count);
}

void remove_char(char *str){                   
	int i;
	for (i = 0; i < strlen(str); ++i){         //when it finds white space, break the loop and take the location of white space.//       

		if (str[i] == ' ') break;
	}

	for (int j = 0; j < strlen(str); j++){    //assign value after white space to first element of the string, and goes on.//
		str[j] = str[i+1+j];                  //so it has removed chars before white space.//
	}
}

int search_point(struct point *Points,char *str){
	int result = -1;
	for (int i = 0; i < 100; ++i){                        //search the name of a Point in Points structure, and return its location.//
		if(strcmp(Points[i].name,str) == 0) result = i;
	}

	return(result);
}

int search_line(struct line *Lines, char *str){          //search the name of a Line in Lines structure, and return its location.//     
	int i;
	for (i = 0; i < 100; ++i){
		if(strcmp(Lines[i].name,str) == 0) break;
	}

	return(i);
}

int search_polygon(struct polygon *Polygons, char *str){     //search the name of a Polygon in Polygons structure, and return its location.//
	int result = -1;
	for (int i = 0; i < 100; ++i){
		if(strcmp(Polygons[i].name,str) == 0) result = i;
	}

	return(result);
}

void distance_points(struct point *Points,int i,int j,float *distancep){   
	float x1,x2,y1,y2;               //assign coordinates values.//
	x1 = Points[i].start_loc;
	x2 = Points[j].start_loc;
	y1 = Points[i].finish_loc;
	y2 = Points[j].finish_loc;

	*distancep = sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));   //apply the formula.//
}

void distance_point_line(struct point *Points,struct line *Lines, int i, int j,float *distancel){
	float x1,x2,y1,y2,x0,y0;

	x1 = Lines[i].start.start_loc;       //assign coordinates values.//
	y1 = Lines[i].start.finish_loc;
	x2 = Lines[i].finish.start_loc;
	y2 = Lines[i].finish.finish_loc;
	x0 = Points[j].start_loc;
	y0 = Points[j].finish_loc;

	*distancel = (abs((y2-y1)*x0 - (x2-x1)*y0 + x2*y1 - y2*x1))/(sqrt(((y2-y1)*(y2-y1)) + ((x2-x1)*(x2-x1))));  //apply the formula.//
}

void find_angle(struct line *Lines,int i,int j,float *angle){
	float m1,m2;
	float x;    
	//assign slopes of the lines according to formula.//
	m1 = ((Lines[i].finish.finish_loc) - (Lines[i].start.finish_loc))/((Lines[i].finish.start_loc) - (Lines[i].start.start_loc));
	m2 = ((Lines[j].finish.finish_loc) - (Lines[j].start.finish_loc))/((Lines[j].finish.start_loc) - (Lines[j].start.start_loc));

	x = abs((m2-m1)/(1 + (m1*m2)));   //apply angle formula.//
	*angle = abs(atan(x) * (180/PI));
}

void length_line(struct line *Lines,int i,float *lenghtline){
	float x,y;

	*lenghtline = 0.0;   //initialize it.//

	x = abs(Lines[i].start.start_loc - Lines[i].finish.start_loc);    //assign coordinate values.//
	y = abs(Lines[i].start.finish_loc - Lines[i].finish.finish_loc);

	*lenghtline = sqrt((x*x)+(y*y));   //apply formula.//
}

void length_polygon(struct polygon *Polygons,int i,int num,float *lenghtpolygon){
	float result = 0;
	*lenghtpolygon = 0.0;    //initialize it.//  
	
	for (int a = 0; a < num; ++a){
		distance_points(Polygons[i].P,a,a+1,&result);      //to find the circumferene of any polygon we should simply sum up sides of it.//
		*lenghtpolygon += result;                          //to find out lenght of sides I've used distance of points and sum them up.//
	}
}


void area_polygon(struct polygon *Polygons,int i,int num,float *area){
	int n,j;
	float X[20],Y[20];   //to hold X and Y coordinates.//
	
	j = num - 1;
	*area = 0.0;    //initialize area.//

	for (int a = 0; a < num; ++a){
		X[a] = Polygons[i].P[a].start_loc;
		Y[a] = Polygons[i].P[a].finish_loc;
	}
	//According to Shoelace Formula.//
	for (int a = 0; a < num; ++a){
		*area += ((X[j] + X[a]) * (Y[j] - Y[a]));   //apply formula.//
		j = a;
	}

	*area = (abs(*area/2));
}


