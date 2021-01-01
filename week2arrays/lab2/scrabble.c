#include <string.h>
#include <stdio.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(char *word);

int main(void)
{
    // Get input words from both players
    char word1[20];
    printf("Player 1: ");
    scanf("%s", word1);
    char word2[20];
    printf("Player 2: ");
    scanf("%s", word2);

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }

    return 0;
}

int compute_score(char *word)
{
    // Compute and return score for string
    int pos, value = 0;
    for (int i = 0, n = strlen(word); i < n; i += 1)
    {
        if (word[i] >= 'a' && word[i] <= 'z')
        {
            pos = word[i] - 65 - 32;
        }
        else
        {
            pos = word[i] - 65;
        }

        if (pos >= 0 && pos <= 25)
        {
            value += POINTS[pos];
        }
    }

    return value;
}
