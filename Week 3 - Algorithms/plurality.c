#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    //takes the name of candidate voted for
    //if name matches one of the candidates, add the vote to the count
        //return true
    for (int i=0; i< candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name)==0)
        {
            candidates[i].votes = candidates[i].votes + 1;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
        //print name of candidate with most votes
    int x[candidate_count];
    for(int j = 0; j < candidate_count; j++)
    {
        for(int i = 0; i < candidate_count; i++)
        {
            //compare and put into new array
            if (candidates[j].votes >= candidates[i].votes)
            {
                //larger number first
                x[i] = j;
            }
            else
            {
                x[i] = i;
            }
        }
    }
    for(int i=0; i<candidate_count; i++)
    {
        if (candidates[x[0]].votes == candidates[x[i]].votes)
        printf("the winner is %s!\n", candidates[x[i]].name);
    }
    return;
}