#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int generate_number(int num,int upper,int lower);
void push(int *arr, int *top, int num);
int pop(int *arr,int *secarr,int *top,int *i);

void main(){
	srand(time(NULL));
	int *firstarr;
	int *secarr;
	int num,top = 0;
	int size = generate_number(size,50,10);
	int i = 0;
	int j = 0;
	
	firstarr =(int *) malloc(sizeof(int)*size);
	secarr = (int *) malloc(sizeof(int)*size);

	while(i < (size*size)){
		if((i+1) > size){
			firstarr = (int *) realloc(firstarr,sizeof(int)*(i+1));
		} 
		
		num = rand() %(100 - 0 + 1) + 0;
		push(firstarr,&top,num);
		
		i ++;
	}

    for(int i = 0; i < size*size; i++){
        printf("%d ",firstarr[i]);
    }
}

int generate_number(int num,int upper,int lower){
	num = rand() %(upper - lower + 1) + lower;

	return(num);
}

void push(int *arr, int *top, int num){
    arr[(*top)++] = num;
}

int pop(int *arr,int *secarr,int *top,int *i){
    
	secarr[(*i)++] = arr[--(*top)]; 
    return arr[--(*top)];
}

