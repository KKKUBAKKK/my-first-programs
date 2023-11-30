#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    //asking for input
    do
    {
        height = get_int("Height: ");
    }
    //rejecting some answers
    while (height < 1 || height > 8);
    //building the pyramid
    for (int i = 1; i <= height; i++)
    {
        //printing spaces
        for (int k = height - i; k > 0; k--)
        {
            printf(" ");
        }
        //printing 1st hashes
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        //printing double space
        printf("  ");
        //printing 2nd hashes
        for (int l = 1; l <= i; l++)
        {
            printf("#");
        }
        //move to the next line
        printf("\n");
    }
}