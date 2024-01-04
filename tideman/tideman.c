#include <assert.h>
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
} pair;

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
// my fucntion
bool createCircles(int start, int end);
void testCreateCircles(void);

int main(int argc, string argv[])
{
    // call test
    // testCreateCircles();

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
    // TODO
    // i think i need to fix this. handling user input and candidates
    // same way as runoff.c
    // cut the space from the user input
    int length = strlen(name);
    while (length > 0 && name[length - 1] == ' ')
    {
        name[--length] = '\0';
    }

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
    // TODO
    // upgrade global preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    // return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
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
    // return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            int strength1 = preferences[pairs[i].winner][pairs[i].loser];
            int strength2 = preferences[pairs[j].winner][pairs[j].loser];

            if (strength1 < strength2)
            {
                // sorting
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }

    // return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!createCircles(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        // if (createCircles(pairs[i].loser, pairs[i].winner))
        // {
        //     locked[pairs[i].winner][pairs[i].loser] = false;
        // }
    }
    // return;
}

// create circles
// i need to do testing
bool createCircles(int start, int end)
{
    if (start == end)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][start])
        {
            if (createCircles(i, end))
            {
                return true;
            }
        }
        // if (locked[start][i])
        // {
        //     if (createCircles())
        // }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        bool source = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                source = false;
                break;
            }
        }
        if (source)
        {
            printf("%s\n", candidates[i]);
            break;
            // return;
        }
    }
    // return;
}

// I checked my function (createCircles) by assertion.
// when i try to check50, it took so much time, so I commented out here.
// i already check all of the test passed.
// void testCreateCircles(void)
// {
//     // test function create circles which is created by myself.
//     // set up the locked array and candidate count -> defined the specific scenerio
//     candidate_count = 3;
//     bool tempLocked1[MAX][MAX] = {
//         {false, true, false},
//         {false, false, true},
//         {false, false, false}
//     };
//     memcpy(locked, tempLocked1, sizeof(tempLocked1));
//     assert(createCircles(0, 2) == false);
//     assert(createCircles(1, 0) == true);
//     // printf("test2 passed\n");

//     // when the graph has no edges.
//     bool tempLocked2[MAX][MAX] = {
//         {false, false, false},
//         {false, false, false},
//         {false, false, false}
//     };
//     memcpy(locked, tempLocked2, sizeof(tempLocked2));
//     assert(createCircles(0, 2) == false);
//     assert(createCircles(2, 0) == false);
//     // printf("test3 passed\n");

//     // test case count 4
//     candidate_count = 4;
//     bool tempLocked3[MAX][MAX] = {
//         {false, true, false, false},
//         {false, false, true, false},
//         {false, false, false, true},
//         {false, false, false, false}
//     };
//     // 0 -> 1 -> 2 -> 3
//     memcpy(locked, tempLocked3, sizeof(tempLocked3));
//     assert(createCircles(0, 3) == false);
//     assert(createCircles(2, 0) == true);
//     // assert(createCircles(2, 3) == true);
//     // printf("test4 passed\n");

//     // Test case count is 5
//     candidate_count = 5;
//     bool tempLocked4[MAX][MAX] = {
//         {false, true, false, false, false},
//         {false, false, true, false, false},
//         {false, false, false, true, false},
//         {false, false, false, false, true},
//         {true, false, false, false, false}
//     };
//     // 0 -> 1 -> 2 -> 3 -> 4 -> 0
//     memcpy(locked, tempLocked4, sizeof(tempLocked4));
//     assert(createCircles(0, 4) == true);
//     assert(createCircles(3, 1) == true);
//     // printf("test5 passed\n");

//     // Test case count is 6
//     candidate_count = 6;
//     bool tempLocked5[MAX][MAX] = {
//         {false, true, false, false, false, false},
//         {false, false, false, false, false, false},
//         {false, false, false, true, false, false},
//         {false, false, false, false, false, false},
//         {false, false, false, false, false, true},
//         {false, false, false, false, false, false}

//     };
//     // 0 -> 1
//     // 2 -> 3
//     // 4 -> 5
//     memcpy(locked, tempLocked5, sizeof(tempLocked5));
//     assert(createCircles(0, 5) == false);
//     assert(createCircles(2, 4) == false);

//     // printf("ALL test passed\n");

// }