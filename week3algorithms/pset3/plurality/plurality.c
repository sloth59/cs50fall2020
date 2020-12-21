// plurality vote, first-past-the-post, winner take all

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char name[20];
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char* name);
void print_winner(void);

int main(int argc, char* argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);

    // Loop over all voters
    char name[20];
    for (int i = 0; i < voter_count; i++)
    {
        printf("Vote: ");
        scanf("%s", name);

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();

    return 0;
}

// Update vote totals given a new vote
bool vote(char* name)
{
    for(int i=0; i<candidate_count; i+=1)
    {
        if(strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max;
    for(int i=0; i< candidate_count; i+=1)
    {
        for(int j=i+1; j< candidate_count; j+=1)
        {
            if(candidates[j].votes > candidates[i].votes)
                max = candidates[j].votes;
            else
                max = candidates[i].votes;
        }
    }

    for(int i=0; i<candidate_count; i+=1)
    {
        if(candidates[i].votes == max)
            printf("%s\n", candidates[i].name);
    }
    return;
}

