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
bool check_loop(int loser, int cur);
void check_src(int node, int winners[], int count);

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
        //comparing to the name of candidates, if present then update the ranks
        if (strcmp(candidates[i], name) == 0)
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
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            //for this part, I have to ensure if the value of the element
            //in the array is initialised before I insert any value
            if (preferences[ranks[i]][ranks[j]] >= 0)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
            else
            {
                //initialising the value to 1
                preferences[ranks[i]][ranks[j]] = 1;//
            }

        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            //comparing each preferences of the candidates in the array
            //j is i+1 as I do not need to compare the same two candidates
            //twice
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
    //I used an insertion sort here,
    //initially planned to use merge sort or quicksort
    //but I can't return an array in C so mergesort fails
    //and I can't modify the arguments of the function , and I am
    //a bit lazy to make another recursive function, so quicksort didn't come.
    int count = 0;
    int max, ind;//I sorted with max to the left first
    pair temp;
    while (count != pair_count)
    {
        max = 0;
        ind = 0;
        for (int i = count; i < pair_count; i++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] > max)
            {
                ind = i;
                max = preferences[pairs[i].winner][pairs[i].loser];
            }
        }
        temp = pairs[count];
        pairs[count] = pairs[ind];
        pairs[ind] = temp;
        count++;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int temp, temp2;
    for (int i = 0; i < pair_count; i++)
    {
        if (check_loop(pairs[i].winner, pairs[i].loser) == false) //the crucial part to check if any cycles
        {
            //no cycle so set the lock
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int cur = pairs[0].winner;
    int winners[candidate_count];
    check_src(cur, winners, 0);//update the winners' array
    //I am not sure why but it only passes the last test
    //When I considered there's multiple winners
    for (int i = 0; i < candidate_count; i++)
    {
        //if the position has values:
        if (winners[i] >= 0)
        {
            printf("%s\n", candidates[winners[i]]);
        }
        else
        {
            break;
        }
    }

}

//A recursive function that checks if there's and cycle
bool check_loop(int winner, int cur)
{
    //base case where the current position links back to original pair's winner
    if (winner == cur)
    {
        return true; 
    }
    //If the current node links to another node, I call this function again
    //with the another node.
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[cur][i] == true)
        {
            //checks if true
            if (check_loop(winner, i) == true)
            {
                return true;
            }
        }
    }
    return false;
}

//updates the winner array with all the winners
//another recursive function
void check_src(int node, int winners[], int count)
{
    int temp = 0;
    int cur = count;
    //similar to check_loop, if current candidate lost to other candidates,
    //calls the check_src function again.
    for (int i = 0; i < candidate_count; i++)
    {

        if (locked[i][node] == true)
        {
            temp++;
            check_src(i, winners, ++count);
        }
    }
    //If the current candidate is not won by others,temp = 0:
    if (temp == 0)
    {
        winners[cur] = node;
    }
}
