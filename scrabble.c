#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int compute_score(string);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    //Player 1 wins
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    //Player 2 wins
    if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    //equal
    if (score1 == score2)
    {
        printf("Tie!\n");
    }
}
//computing
int compute_score(string word1)
{
    int c[26] = {};
    int p[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int scr = 0;
    int l = strlen(word1);
    int i = 0;
    while (i < l)
    {
        //to lowercase
        if isupper(word1[i])
        {
            word1[i] = tolower(word1[i]);
        }

        c[i] = (word1[i] - 96);
        //check is A to Z
        if (c[i] >= 0 && c[i] < 26)
        {
            scr = scr + p[c[i] - 1];
        }
        else
        {
            scr = scr + 0;
        }
        i++;
    }
    printf("\nScore is %i\n", scr);
    return scr;
}
