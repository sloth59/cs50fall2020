
#include<stdio.h>

int main(void)
{
    int height;
    do
    {
        printf("Height: ");
        scanf("%i", &height);
    }
    while (height > 8 || height < 1);

    for (int i = 0; i < height; i += 1)
    {
        for (int j = 0; j < height - i - 1; j += 1)
        {
            printf(" ");
        }

        for (int j = 0; j < i + 1; j += 1)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j < i + 1; j += 1)
        {
            printf("#");
        }

        printf("\n");
    }

    return 0;
}
