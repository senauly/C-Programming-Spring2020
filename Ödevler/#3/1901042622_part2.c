#include <stdio.h>
#include <math.h>

int isprime (int a);

int main()
{

	int num;  //input - checks the every integer from 2 to the num.//
	int result; //output - result of the func.//

	printf("Please enter an integer:\n");   //get the number.//
	scanf("%d",&num);

	for (int i = 2; i < num; i++)
	{
		result = isprime(i);

		if (result == 1)       //flag = 1//
		
			printf("%d is a prime number.\n",i);
		 
		else                  //flag = least divisor of the integer.//
		
			printf("%d is not a prime number, it is dividible by %d.\n",i,result);
	}

return (0);

}

int isprime (int a)
{
	int result = 0;  //output - result of the function.//
	int flag = 0;    
	int count = 0;  //counts the divisors.//
	int sqr;        //square root of the number.//

	sqr = sqrt(a);

	for (int i = 1; i <= sqr && count < 2; i++)     //when it finds 2 divisor it leaves the loop. (one of the divisor is '1')//
	{
		if (a%i == 0)        //if the number can divide with another number, increment count.//
		{	
			count ++;
		}

		if (count == 2)     //if count is at least 2, this means the number cannot be a prime number.//
		{
			flag = i;       //then return the least divisor.//
		}

		else if (count == 1) //if count is 1, this means only divisor of the number is '1', so it is a prime number.//
		{
			flag = 1;       //then return 1 for primes.//
		}
	}

return (flag);
}

