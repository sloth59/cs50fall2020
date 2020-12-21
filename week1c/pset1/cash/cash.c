// Ask the user how much change is owed and then print the minimum number of coins with which that change can be made.Assume that the only coins available are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢). 

#include<stdio.h>

int main(void)
{
	float dollars;

	// get the total changes owned
	do{
		printf("Change owned: ");
		scanf("%f", &dollars);
	}while( dollars < 0 );

	// convert to dollars/int
	int cents = (dollars * 100);
	int coins = 0;

	// calculations
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

	// display output
	printf("%i", coins);

	return 0;
	
}
