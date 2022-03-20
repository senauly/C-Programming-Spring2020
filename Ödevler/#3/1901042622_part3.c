#include<stdio.h>

int andop (int a, int b);
int check_binary(int a);
int check_lenght(int a);

int main()
{

	int num1,num2;

	printf("First integer:\n");  //get the numbers.//
	scanf("%d",&num1);
	printf("Second integer:\n");
	scanf("%d",&num2);

	while(check_binary(num1) == 1 || check_binary(num2) == 1 || (check_lenght(num1) != check_lenght(num2)))  //untill we get everything as wanted.//
	{
		if(check_binary(num1) == 1 || check_binary(num2) == 1)   //if numbers have numbers other than 0 and 1.//
		{
			printf("Integers should be binary, please enter 2 new integers.\n");  //get the new integers.//
			printf("First integer:\n");
			scanf("%d",&num1);
			printf("Second integer:\n");
			scanf("%d",&num2);
		}

		if (check_lenght(num1) != check_lenght(num2))  //if numbers lenght's are not equal to each other.//
		{	
			printf("Integers should have the same lenght, please enter 2 new integers.\n");   //get new integers.//
			printf("First integer:\n");
			scanf("%d",&num1);
			printf("Second integer:\n");
			scanf("%d",&num2);
		}
	}
	
	printf("%d AND %d = %d \n",num1,num2,andop(num1,num2));   //display the result.//
	

return (0);
}

int check_binary(int a)
{
	int temp=0;
	int count=0;
	int flag=0;

	while(a!=0)
	{
		temp = a%10;    //get the last digit.//
		a = a/10;       //decrease the digit number.//
		if (temp !=0 && temp !=1)   //if they are not binary numbers.//
		{
			count++;   	//increase the count.//
		}
	}

	if (count >= 1)   //if there's other numbers than 0 and 1.//
	{	
		flag = 1;     //return 1.//
	}
	
return(flag);

}

int check_lenght(int a)
{
	int count = 0;
	
	while(a!=0)
	{
		a = a/10;     //decrease the digit number.//
		count ++;     //count the steps = digits.//
	}

return(count);
}

int andop (int a, int b)
{
	int sum = 0, digit = 1;
	int temp1 = 0, temp2 = 0;
	int number = 0;
	int result = 0;  //output.//
	int count = 0;

	sum = a+b;        //in the sum '2' means 1 in and operation, because 1&1=1 and all the other ones are zero.So if we get 2 this means we get 1,
	temp1 = sum;     //if we get '1'and '0' this equals '0' in and operation.//

	do
	{
		number = temp1%10;   // to get the last digit of the number.//
		if (number == 2)     // then we should have the '1'.//
		{
			while(temp2 != count)   //to equal it to the digit's number.//
			{
				digit = digit*10;   //it multiple it by 10 to increase its digit untill count so it will get the exact digit.//
				temp2++;            //count was counting the digits.//
			}

			result = result + digit;
		}

		temp1 = temp1/10;         //to decrease the digits.//
		count ++;				 //count the number of digit.//
	
	} while(temp1 != 0); 

	return(result);
}