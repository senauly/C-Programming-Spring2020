#include<stdio.h>

int sum (int n, int flag);
int mult (int n, int flag);

int main()
{

	int n;      //input - number to count.//
	int flag, op_flag;  //input - to choose operation.//
	int rsum, rmult;    //output - result of the funcs.//

	printf("Enter an integer:\n");      //get the number.//
	scanf("%d",&n);

	printf("Please enter '0' for sum, '1' for multiplication.\n");     //get the selection.//
	scanf("%d",&op_flag);

	printf("Please enter '0' to work on even numbers, '1' to work on odd numbers. \n");   //get the second selection to use on functions.//
	scanf("%d",&flag);

	if (flag !=0 && flag !=1)
	{
		printf("Invalid value for odd/even selection.\n");
		return 0;
	}

	switch(op_flag)
	{
		case 0:
		printf("%d\n",sum(n,flag));
		break;

		case 1:
		printf("%d\n",mult(n,flag));	
		break;

		default:
		printf("Unsupported operation.\n");
		break;
	}

return (0);
}

int sum (int n, int flag)
{
	int sum_even = 0;   //output - sum of even numbers.//
	int sum_odd = 0;   //output - sum of odd numbers.//
	int i;            //for loop.//
	int result = 0;   //output - result of the functions.//

	switch(flag)
	{
		case 0:
		i = 2;     //because even numbers start at 2.//
		do
		{
			sum_even = sum_even + i;     //compute sum.//    
			printf("%d + ",i);           //display i.//
			i = i + 2;                  //because even numbers increase two at a time.//

		} while(i<n && i!=(n-1));       
		
		sum_even = sum_even + i;         //add the last i to last sum.//
		printf("%d = ",i);              //display the last i//
		result = sum_even;
		break;
		
		case 1:
		i = 1;     //because odd numbers start at 1.//
		do
		{
			sum_odd = sum_odd + i;      
			printf("%d + ",i);
			i = i + 2;                  //because odd numbers increase two at a time.//

		}while(i<n && i!=(n-1));
		
		sum_odd = sum_odd + i;
		printf("%d = ",i);
		result = sum_odd;
		break;
	}

return (result);
}

int mult (int n, int flag)
{
	int mult_even = 1;      //output - multiplication of even numbers.//
	int mult_odd = 1;       //output - multiplication of odd numbers.//
	int i = 0;              //for loops.//
	int result = 0;         //output - result of the functions.// 

	switch(flag)            //same situation with the sum funciton but '*' instead of '+'.// 
	{
		case 0:
		i = 2;
		do
		{
			mult_even = mult_even * i;
			printf("%d * ",i);
			i = i + 2;

		}while(i<n && i!=(n-1));
		
		mult_even = mult_even * i;
		printf("%d = ",i);
		result = mult_even;
		break;

		case 1:
		i = 1;
		do
		{
			mult_odd = mult_odd * i;
			printf("%d * ",i);
			i = i + 2;

		}while(i<n && i!=(n-1));
		
		mult_odd = mult_odd * i;
		printf("%d = ",i);
		result = mult_odd;
		break;
	
	}
	
	return(result);
}