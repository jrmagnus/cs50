#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//type functions
int count_letters(string, int);
int count_words(string, int);
int count_sent(string, int);
int coleman_liau(int, int, int);
void print_grade(void);

int main(void)
{
    //prompt to text
    string text = get_string("Text: ");
    int lenght = strlen(text);
    int n_letter = count_letters(text, lenght);
    int n_word = count_words(text, lenght);
    int n_sentence = count_sent(text, lenght);
    int grade = coleman_liau(n_word, n_sentence, n_letter);
    //print Result
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    //print grade upper 16
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    //print grade + value grade
    else
    {
        printf("Grade %i\n", grade);
    }

}
//counting letters
int count_letters(string text, int lenght)
{
    int n = 0;
    for (int i = 0; i < lenght; i++)
    {
        if isalpha(text[i])
        {
            n++;
        }
    }
    return n;
}
//counting words
int count_words(string text, int lenght)
{
    int n = 0;
    for (int i = 0; i < lenght; i++)
    {
        if isblank(text[i])
        {
            n++;
        }
    }
    return n + 1;
}
//counting sentences
int count_sent(string text, int lenght)
{
    int n = 0;
    for (int i = 0; i < lenght; i++)
    {
        if ((text[i]) == '.' || (text[i]) == '!' || (text[i]) == '?')
        {
            n++;
        }
    }
    return n;
}
//view grade || index = 0.0588 * L - 0.296 * S - 15.8 ||
int coleman_liau(int n_word, int n_sentence, int n_letter)
{
    double l = (n_letter / ((float) n_word / 100));
    double s = (n_sentence / ((float) n_word / 100));
    float n = (0.0588 * l - 0.296 * s - 15.8);
    return round(n);
}
