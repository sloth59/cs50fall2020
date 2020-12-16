// Ask the user how much change is owed and then print the minimum number of coins with which that change can be made.Assume that the only coins available are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢). 

#include<stdio.h>

int main(void)
{
	float dollars;

	do{
		printf("Change owned: ");
		scanf("%f", &dollars);
	}while( dollars < 0 );

	int cents = (dollars * 100);
	int coins = 0;

	while(cents > 0)
	{
		if(cents >= 25)
		{
			cents -= 25;
			coins += 1;
		}

		else if(cents < 25 && cents >= 10)
		{
			cents -= 10;
			coins += 1;
		}

		else if(cents < 10 && cents >= 5)
		{
			cents -= 5;
			coins += 1;
		}

		else
		{
			cents -= 1;
			coins += 1;
		}
	}

	printf("%i", coins);

	return 0;
	
}
