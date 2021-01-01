// Luhn's algorithm Hans peter luhn of IBM
//
#include<stdio.h>

int luhncheck(long num);
int gettwo(long num);
int getlength(long num);
void vendorcheck(int len, int firsttwo);

int main(void)
{
    long cardnum;
    int firsttwo, length;

    // get/validate the input card number
    do
    {
        printf("Number: ");
        scanf("%ld", &cardnum);
        length = getlength(cardnum);
    }
    while (cardnum <= 0 && (length != 13 || length != 15 || length != 16));

    // get first two digits of the card number
    firsttwo = gettwo(cardnum);

    // run luhns algorithm on the card number
    if (luhncheck(cardnum) == 1)
    {
        // run the vendor check for known vendor as per provided information
        vendorcheck(length, firsttwo);
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}


int luhncheck(long num)
{
    int count = 0, evensum = 0, oddsum = 0, lastn = 0;
    while (num != 0)
    {
        lastn = num % 10;
        num = num / 10;

        if (count % 2 == 0)
        {
            evensum += lastn;
        }

        else
        {
            lastn *= 2;

            if (lastn > 9)
            {
                lastn = lastn / 10 + lastn % 10;
            }

            oddsum += lastn;
        }
        count += 1;
    }

    int finalsum = evensum + oddsum;

    if (finalsum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}


int gettwo(long num)
{
    do
    {
        num = num / 10;
    }
    while (num > 99);
    return num;
}


int getlength(long num)
{
    int len = 0;
    do
    {
        num = num / 10;
        len += 1;
    }
    while (num != 0);
    return len;
}


void vendorcheck(int length, int firsttwo)
{
    if (length == 16)
    {
        if (firsttwo >= 51 && firsttwo <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if (firsttwo >= 40 && firsttwo <= 49)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (length == 15 && (firsttwo == 34 || firsttwo == 37))
    {
        printf("AMEX\n");
    }

    else if (length == 13)
    {
        if (firsttwo >= 40 && firsttwo <= 49)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }

}
