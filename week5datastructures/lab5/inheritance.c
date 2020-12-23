// Simulate genetic inheritance of blood type

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Each person has two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)
{
    int i;
    // Allocate memory for new person
    person* list = NULL;
    person* child = malloc(sizeof(person));

    // Generation with parent data
    if (generations > 1)
    {
        person* mother = malloc(sizeof(person));
        person* father = malloc(sizeof(person));
        person* elders[] = {mother, father};
        // Recursively create blood type histories for parents
        for(i=0; i<2; i++)
        {
            elders[i] = create_family(generations - 1);
            child->parents[i] = elders[i];
            elders[i] = NULL;
        }
        // Randomly assign child alleles based on parents
        for(i=0; i<2; i++)
        {
            child->alleles[i] = child->parents[i]->alleles[rand()%2];
        }
    }

    // Generation without parent data
    else
    {
        for(i=0; i<2; i++)
        {
            // Set parent pointers to NULL
            child->parents[i] = NULL;
            // Randomly assign alleles
            child->alleles[i] = random_allele();
        }
    }

    list = child;
    child = NULL;
    // Return newly created person
    return list;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)
{
    int i;
    // Handle base case
    for(i=0; i<2; i++)
    {
        if(p->parents[i] != NULL)
        {
            // Free parents
            free_family(p->parents[i]);
        }
    }
    // Free child
    free(p);
    return;
}

// Print each family member and their alleles.
void print_family(person *p, int generation)
{
    // Handle base case
    if (p == NULL)
    {
        return;
    }

    // Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Print person
    printf("Generation %i, blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Randomly chooses a blood type allele.
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
