//  we have a population of n llamas. Each year, n / 3 new llamas are born, and n / 4 llamas pass away. Determine how long it takes for a population to reach a particular size.

#include<stdio.h>

int main(void)
{
				int startPop,targetPop,currentPop,years = 0;

				// get initial population
				do{
								printf("Start size: ");
								scanf("%d", &startPop);
				}while(startPop < 9);

				// get target population
				do{
								printf("End size: ");
								scanf("%d", &targetPop);
				}while(targetPop < startPop);

				// calcualte years reuired
				for (currentPop = startPop; currentPop < targetPop; currentPop += currentPop/3 - currentPop/4)
				{
								years += 1;
				}

				// display the output
				printf("Years: %d\n", years);

				return 0;
}
