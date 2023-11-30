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
void lock_pairs(void);
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
    // Check if vote matches a candidate's name
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(candidates[i], name))
        {
            // Assign the name to a rank
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Repeat for every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Repeat for every candidate with lower rank
        for (int j = candidate_count - 1; j > i; j--)
        {
            // If the preferences value is known +1, if not give it the value of 1
            if (preferences[ranks[i]][ranks[j]] != 0)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
            else
            {
                preferences[ranks[i]][ranks[j]] = 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Repeat for every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Repeat for every candidate with lower rank
        for (int j = candidate_count - 1; j > i; j--)
        {
            // Save the winners and losers in the pairs, don't save tied pairs
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
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
    int strength = 0;
    int loser;
    int winner;

    // Repeat for every pair
    for (int k = 0; k < pair_count; k++)
    {
        // Find and save the strongest pairs left points
        for (int i = k; i < pair_count; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] > strength)
            {
                strength = preferences[pairs[i].winner][pairs[i].loser];
            }
        }

        // Find corresponding pair and move it to the beginning
        for (int j = k; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] == strength)
            {
                winner = pairs[k].winner;
                loser = pairs[k].loser;

                pairs[k].winner = pairs[j].winner;
                pairs[k].loser = pairs[j].loser;

                pairs[j].winner = winner;
                pairs[j].loser = loser;
            }
        }
    }
    return;
}

// Determines if locking a pair creates a cycle
bool cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true && cycle(winner, i))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Check every pair
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // Call function 'cycle' and if it returns false lock pair
        if (cycle(winner, loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int loser = -1;

    // Check every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If he is a marked pair's loser assign 'loser' his number
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                loser = i;
                break;
            }
        }

        // If candidates number isn't equal to 'loser' print him as a winner and break loop
        if (i != loser)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }



    return;
}