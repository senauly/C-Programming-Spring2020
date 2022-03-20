#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

struct node {
	int num;
	struct node *next;
};

struct difference{
	int n1;
	int n2;
};

int *read_array(char *filename,int *arr);
struct node *read_linkedlist(char *filename,struct node *head);
float *stats_array(int *arr,float *stats);
float *stats_linkedlist(struct node *head,float *stats);
int size_array(int *arr);
int size_ll(struct node *head);
struct difference *FindDifferent(int *arr,struct node *ll);

void main(){
	char *file = "list.txt";
	int *numbers;
	float *stats_arr,*stats_ll;
	struct node *head = NULL;
	clock_t t;
	double time_arr = 0,time_ll = 0,time_sarr = 0, time_sll = 0;

	struct difference *num;
	struct node *ll;
	int *sequ;
	int i = 0;

	t = clock();                                      //time taken by read_array function.//
   	numbers = read_array(file,numbers);
   	t = clock() - t; 
	time_arr += ((double)t)/CLOCKS_PER_SEC;

	head = NULL;                                     //time taken by read_linkedlist function.//
	t = clock();                                     //calculated several times for better value.//
   	head = read_linkedlist(file,head);
   	t = clock() - t;
	time_ll += ((double)t)/CLOCKS_PER_SEC;

	head = NULL;
	t = clock();
   	head = read_linkedlist(file,head);
   	t = clock() - t;
	time_ll += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	numbers = read_array(file,numbers);
   	t = clock() - t; 
	time_arr += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	numbers = read_array(file,numbers);
   	t = clock() - t; 
	time_arr += ((double)t)/CLOCKS_PER_SEC;

	head = NULL;
	t = clock();
   	head = read_linkedlist(file,head);
   	t = clock() - t;
	time_ll += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	numbers = read_array(file,numbers);
   	t = clock() - t; 
	time_arr += ((double)t)/CLOCKS_PER_SEC;

	head = NULL;
	t = clock();
   	head = read_linkedlist(file,head);
   	t = clock() - t; 
	time_ll += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	stats_arr = stats_array(numbers,stats_arr);                  //time taken by stats_array function.//
   	t = clock() - t; 
	time_sarr += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	stats_ll = stats_linkedlist(head,stats_ll);                  //time taken by stats_linkedlist function.//
   	t = clock() - t; 
	time_sll += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	stats_arr = stats_array(numbers,stats_arr);
   	t = clock() - t; 
	time_sarr += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	stats_arr = stats_array(numbers,stats_arr);
   	t = clock() - t; 
	time_sarr += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	stats_ll = stats_linkedlist(head,stats_ll);
   	t = clock() - t; 
	time_sll += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	stats_arr = stats_array(numbers,stats_arr);
   	t = clock() - t; 
	time_sarr += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	stats_ll = stats_linkedlist(head,stats_ll);
   	t = clock() - t; 
	time_sll += ((double)t)/CLOCKS_PER_SEC;

	t = clock();
   	stats_ll = stats_linkedlist(head,stats_ll);
   	t = clock() - t; 
	time_sll += ((double)t)/CLOCKS_PER_SEC;

	printf("The time taken for read_array function: %f seconds.\n", time_arr/4);       //time.//
    printf("Total memory of array: %ld bytes.\n", sizeof(int)*size_array(numbers));   //size//


   	printf("\nThe time taken for stats_arr function: %f seconds.\n", time_sarr/4);    //stats.//
   	printf("Minimum value of the Array:%.2f\nMaximum value of the Array:%.2f\nMean value of the Array:%.2f\nStandart Deviation of the Array:%.2f\n\n",stats_arr[0],stats_arr[1],stats_arr[2],stats_arr[3]);
	printf("**********************************************************\n");

	printf("\nThe time taken for read_linkedlist function: %f seconds.\n", time_ll/4); 
	printf("Total memory of linked list: %ld bytes.\n", sizeof(struct node)*size_ll(head));

	printf("\nThe time taken for stats_linkedlist function: %f seconds.\n", time_sll/4);
   	printf("Minimum value of the Linked List:%.2f\nMaximum value of the Lİnked List:%.2f\nMean value of the Linked List:%.2f\nStandart Deviation of the Linked List:%.2f\n\n",stats_ll[0],stats_ll[1],stats_ll[2],stats_ll[3]);
	printf("**********************************************************\n");
	printf("\nread_array function is faster than read_linkledlist function but stats_linkedlist function is faster than stats_array function.\n\n");
	printf("**********************************************************\n");

	//PART 2//

	num = FindDifferent(sequ,ll);  //I have tried but couldn't make it work properly.//

	free(stats_arr);
	free(numbers);
}

int *read_array(char *filename,int *arr){
	FILE *fp;
	int i = 0;
	char temp;
	
	fp = fopen(filename,"r");
	arr = (int *)malloc(sizeof(int)*200);     //allocate memory for 200 ints.//

	while(!feof(fp)){
		
		fscanf(fp,"%d%c",&arr[i],&temp);     //take the number and ','.//
		i ++;

		if(i%200 == 0) arr = (int *)realloc(arr, sizeof(int)*(i+200));   //if 200 integers have taken then re-allocate the memory.//
	}
	
	arr[i-1] = (-1);    //end of the array.//
	
	fclose(fp);

	return(arr);
}

struct node *read_linkedlist(char *filename,struct node *head){
	FILE *fp;
	char a;
	int x;
	
	fp = fopen(filename,"r");

	while(!feof(fp)){
		struct node *new = (struct node *)malloc(sizeof(struct node));    //create a new node for a number.//
		fscanf(fp,"%d%c",&x,&a);             //take the number and ','.//

		new->num = x;       //data of the new node is the one it read from file.//
		new->next = head;   //add at the begining.//
		head = new;
	}

	return(head);
}

float *stats_array(int *arr,float *stats){
	float min, max, mean, std = 0.0, sum = 0.0;
	int i = 1;
	stats = malloc(sizeof(float)*4);    //allocate memory for stats array.//

	if (stats == NULL) return NULL;    

	min = arr[0];  
	max = arr[0];

	while(arr[i] != -1){
		if(min > arr[i]) min = arr[i];    //if there's a smaller value than arr[i], then it's min.//
		if(max < arr[i]) max = arr[i];    //if there's a bigger value than arr[i], then it's max.//

		i++;
	}

	for (int j = 0; j < i; ++j){     //sum the numbers.//
		sum += arr[j];
	}

	mean = sum/(i);    //calculate the mean.//

	for (int j = 0; j < i; ++j){
		std += (arr[j] - mean)*(arr[j] - mean);    //apply std formula.//
	}

	std = sqrt(std/(i));

	stats[0] = min;
	stats[1] = max;
	stats[2] = mean;
	stats[3] = std;

	return(stats);
}


float *stats_linkedlist(struct node *head,float *stats){
	struct node *temp = head;
	float min, max, mean, std = 0.0, sum = 0.0;
	int i = 0;
	stats = malloc(sizeof(float)*4);

	min = head->num;
	max = head->num;

	while(temp != NULL){

		sum += temp->num;
		
		if(min > temp->num) min = temp->num;    //if there's a smaller value than the we have, then it's min.//
		if(max < temp->num) max = temp->num;    //if there's a biggest value than the we have, then it's max.//

		temp = temp->next;                      //traverse the linked list.//
		i ++;
	}

	mean = sum/(i-1);
	temp = head; 

	while(temp != NULL){
		std += (temp->num - mean)*(temp->num - mean);
		temp = temp->next;
	}

	std = sqrt(std/(i-1));

	stats[0] = min;
	stats[1] = max;
	stats[2] = mean;
	stats[3] = std;

	return(stats);

}

int size_array(int *arr){
	int i = 0;
	while(arr[i] != -1){   //find the size of the array.//
		i ++;
	}

	return(i);
}

int size_ll(struct node *head){
	int i = 0;
	struct node *temp = head;

	while(temp != NULL){    //traverse the linked list and count each time to find the lenght of it.//
		temp = temp->next;
		i++;
	}
	
	return(i-1);
}

struct difference *FindDifferent(int *arr,struct node *ll){
	int i = 0;
	int x = 0;
	int a = 0;
	struct difference *num;

	arr = (int *)malloc(sizeof(int));

	printf("\nEnter numbers to fill array. Enter -1 to quit.\n");   //fill the array.//
	while(x != -1){
		scanf("%d",&x);
		i ++;
		
		arr = (int *)realloc(arr,sizeof(int)*i);    //allocate memory.//
		arr[i-1] = x;
	}

	printf("Enter numbers to fill linked list. You can enter %d number.\n",i-1);
	
	for (int j = 0; j < i-1; ++j){
		scanf("%d",&x);
		struct node *new = (struct node *)malloc(sizeof(struct node));

		if(j == 0){   //when list is empty.//
			new->num = x;
			new->next = NULL;
			ll = new;   //new entry is the head.//
		}

		if(j>0){
			struct node *temp = ll;
			while(temp->next != NULL) temp = temp->next;  //otherwise add to the end.//
			new->num = x;
			new->next = NULL;
			temp->next = new;
		}
	}

	struct node *tmp = ll;
	for (int j = 0; j < i-1; ++j){
		if(arr[j] != tmp->num){
			num = (struct difference *)malloc(sizeof(struct difference));
			num[a].n1 = arr[j];
			num[a].n2 = tmp->num;
			a++;
		}

		tmp = tmp->next;
	}

	num = (struct difference *)malloc(sizeof(struct difference));
	num[a+1].n1 = -1;
	
	return(num);
}