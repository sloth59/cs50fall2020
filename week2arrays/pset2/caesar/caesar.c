// caesar 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
				// check valididty of argument/key provided
				if(argc != 2)
				{
								printf("Usage: ./caesar key\n");
								return 1;
				}
				else
				{
					for(int i=0,n=strlen(argv[1]); i<n; i+=1)
					{
						if(!isdigit(argv[1][i]))
						{
								printf("Usage: ./caesar key\n");
								return 1;
						}
					}

					// take input and initialize the reuired variables
					char plaintext[99],ciphertext[99];
					int key = atoi(argv[1]);
					key %= 26;
					printf("plaintext: ");
					fgets(plaintext, 99, stdin);

					// implement the caesar
					for(int i=0,n=strlen(plaintext); i<n; i+=1)
					{
						if(islower(plaintext[i]))
						{
							ciphertext[i] = plaintext[i] + key;
							if(!islower(ciphertext[i]))
								ciphertext[i] -= 26;
						}

						else if(isupper(plaintext[i]))
						{
							ciphertext[i] = plaintext[i] + key;
							if(!isupper(ciphertext[i]))
								ciphertext[i] -= 26;
						}

						else
							ciphertext[i] = plaintext[i];

					}

					// print the ciphertext
					printf("ciphertext: %s\n", ciphertext);

					return 0;
				}
}
