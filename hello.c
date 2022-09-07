#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //takes the name
    string name = get_string("What's your name? ");

    //print the message with the name
    printf("Hello %s!\n",name);
}