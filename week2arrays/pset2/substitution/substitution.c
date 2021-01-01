// substitution

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    // check the valididty of argument/key provided
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        int l = strlen(argv[1]);
        if (l != 26)
        {
            printf("Usage: ./substitution key\n");
            printf("The key must be exactly 26 characters long!\n");
            return 1;
        }

        for (int i = 0; i < l; i += 1)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./substitution key\n");
                printf("The key must not contain non-alphabetic values!\n");
                return 1;
            }

            for (int j = i + 1; j < l; j += 1)
            {
                if (argv[1][i] == argv[1][j])
                {
                    printf("Usage: ./substituion key\n");
                    printf("The key must not contain repeated characters!\n");
                    return 1;
                }
            }
        }


        // take input
        // string plaintext = get_string("plaintext: ");
        // char ciphertext[strlen(plaintext) + 1];
        char plaintext[99], ciphertext[99];
        printf("plaintext: ");
        fgets(plaintext, 99, stdin);

        // implement the substitution
        for (int i = 0, n = strlen(plaintext); i < n; i += 1)
        {
            if (islower(plaintext[i]))
            {
                int pos = plaintext[i] - 32 - 65;
                ciphertext[i] = tolower(argv[1][pos]);
            }

            else if (isupper(plaintext[i]))
            {
                int pos = plaintext[i] - 65;
                ciphertext[i] = toupper(argv[1][pos]);
            }

            else
            {
                ciphertext[i] = plaintext[i];
            }

        }
        ciphertext[strlen(plaintext)] = '\0';

        // print the ciphertext
        printf("ciphertext: %s\n", ciphertext);

        return 0;
    }
}
