#include <cs50.h>
#include <stdio.h>

//func1 to set height and verifyed 1 to 8
int heightvalue();
//func2 to draw the bricks #
void draw(int hgt);

//main code
int main(void)
{
    int hgt = heightvalue();
    draw(hgt);
}

//func1
int heightvalue()
{
    int h;
    do
    {
        h = get_int("Height: "); //ask user height
    }
    while (h < 1 || h > 8); //verify if is betwen 1 and 8
    return h; //return h to heightvalue
}

//func2
void draw(int hgt)
{
    //Loop layer1 increase vars and go to a new line, row its 0
    for (int row = 0; row < hgt; row++)//row count
    {
        //Print spaces before bricks
        for (int spc = row + 1; spc < hgt; spc++)//spaces count
        {
            printf(" ");
        }

        //print bricks
        for (int brk = hgt + row + 1; brk > hgt; brk--)//bricks count
        {
            printf("#");
        }

        //print two spaces after bricks
        printf("  ");

        //print bricks after spaces
        for (int brk = hgt + row + 1; brk > hgt; brk--)//bricks count
        {
            printf("#");
        }

        printf("\n");
    }
}