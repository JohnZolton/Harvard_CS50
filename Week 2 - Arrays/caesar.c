#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// making a Ceasar cipher
// shift input message by specified number

int main(int argc, string argv[])
{
    //checking for valid key (numbers only)
    // reject if more than one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //reject if the command-line argument isn't a number
    for (int i=0; i<strlen(argv[1]); i++)
        {
            char a = argv[1][i];
            if (isdigit(a)==0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

    //getting plaintext input
    string plaintext = get_string("what is your message?\n");
    printf("plaintext: %s\n", plaintext);
    int k = atoi(argv[1]);
    string ciphertext = plaintext;
    for (int i=0; i< strlen(plaintext); i++)
    {
        //only selecting alphabet characters
        if (plaintext[i] >= 'A' && plaintext[i] <= 'z')
        {
            //selecting lowercase that would cipher past 'z'
            if (plaintext[i]+k>'Z' && plaintext[i] <= 'Z')
            {
                ciphertext[i] = plaintext[i] + k%26 -'Z'+'A'-1;
            }
            // selecting uppercase that would cipher past 'Z'
            if (plaintext[i]+k >'z' && plaintext[i] > 'Z')
            {
                ciphertext[i] = plaintext[i] + k%26 - 'z' + 'a'-1;
            }
            // default, shifting character by given amount
            else
            {
                ciphertext[i] = (plaintext[i] + k);
            }
        }

    }

    printf("ciphertext: %s\n", (string) ciphertext);
}