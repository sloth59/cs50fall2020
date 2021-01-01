// Coleman - Liau index
#include <string.h>
#include <stdio.h>
#include <math.h>

int count_letters(char *inputline);
int count_words(char *inputline);
int count_sentences(char *inputline);
int indexCalculate(int letters, int words, int sentences);

int main()
{
    // read the input line
    char textinput[999];
    printf("Text: ");
    fgets(textinput, 999, stdin);

    // calculate the no.of words , letters and sentences in line
    int letters = count_letters(textinput);
    int words = count_words(textinput);
    int sentences = count_sentences(textinput);

    // calculate the Coleman-Liau index
    int index = indexCalculate(letters, words, sentences);

    // display the index in required format
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }

    return 0;
}


int count_letters(char *inputline)
{
    int letters = 0;
    for (int i = 0, n = strlen(inputline); i < n; i += 1)
    {
        char temp = inputline[i];
        if ((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z'))
        {
            letters += 1;
        }
    }
    return letters;
}


int count_words(char *inputline)
{
    int words = 0;
    for (int i = 0, n = strlen(inputline); i < n; i += 1)
    {
        char temp = inputline[i];
        if (temp == ' ')
        {
            words += 1;
        }
    }

    return words + 1;
}


int count_sentences(char *inputline)
{
    int sentences = 0;
    for (int i = 0, n = strlen(inputline); i < n; i += 1)
    {
        char temp = inputline[i];
        if (temp == '.' || temp == '?' || temp == '!')
        {
            sentences += 1;
        }
    }

    return sentences;
}

int indexCalculate(int letters, int words, int sentences)
{
    // calculate the letters and sentences per 100 words
    float L = ((float)letters / words) * 100;
    float S = ((float)sentences / words) * 100;
    // calculate the index using the formula
    float index = 0.0588 * L - 0.296 * S - 15.8;
    // appropriately change the index to an integer
    int exactindex = (int)(round(index));

    return exactindex;
}
