#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
int pair_weight(int);
void lock_pairs(void);
bool makes_circle(int, int);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int rank = 0; rank < candidate_count; rank++)
    {
        for (int col = rank + 1; col < candidate_count; col++)
        {
            preferences[ranks[rank]][ranks[col]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // fill array with winner preferences
    int strength[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    //sorting function
    while (1)
    {
        int swapped = 0;

        for (int i = 0; i < pair_count - 1; i++)
        {
            for (int j = i + 1; j < pair_count; j++)
            {
                if (strength[i] < strength[j])
                {

                    //sorting pairs
                    pair tmp = pairs[i];
                    pairs[i] = pairs[j];
                    pairs[j] = tmp;

                    //sorting strength
                    int tmp2 = strength[j];
                    strength[j] = strength[i];
                    strength[i] = tmp2;
                }
            }
        }

        if (swapped == 0)
        {
            break;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!makes_circle(pairs[i].winner, pairs[i].loser))
        {
            // Lock the pair unless it makes a circle
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Recursive function to check if entry makes a circle
bool makes_circle(int cycle_start, int loser)
{
    if (loser == cycle_start)
    {
        // If the current loser is the cycle start
        // The entry makes a circle
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (makes_circle(cycle_start, i))
            {
                // Forward progress through the circle
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    int i;
    for (i = 0; i < candidate_count; i++)
    {
        int x = 1;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                x = 0;
            }
        }
        if (x == 1)
        {
            break;
        }
    }
    printf("%s\n", candidates[i]);
    return;
}