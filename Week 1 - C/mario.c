#include <cs50.h>
#include <stdio.h>

//making a ascii art pyramid
int main(void)
{
    int n; // do while loop to error check user input
    do
    {
        n = get_int("height: ");
    }
    while (n<1);
//we want to make a pyramid
//print n-1 spaces and 1 #
//print n-2 spaces and 2 # etc
    //for each row
    for (int i = 0; i<n; i++)
    {
        for (int j=n-1; j>i; j--)
        {
            printf(" ");
        }
        for (int k=n+1; k>n-i; k--)
        {
            printf("#");
        }
        // now for the right side
        printf("_");
        for (int l=n+1; l>n-i; l--)
            {
                printf("#");
            }
        printf("\n");
    }
}