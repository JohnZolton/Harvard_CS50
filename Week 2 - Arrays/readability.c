#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

//gives a reading score (grade level) for a given text

int count_letters(string s);
int count_words(string t);
int count_sentences(string u);

int main(void)
{
    //prompt user for a string
    string text = get_string("paste in your text: ");
    printf("%s\n", text);

    //count number of letters
    float letters = count_letters(text);
    printf("%.f letters\n", letters);

    //count number of words (' ' = end of word)
    float words = count_words(text);
    printf("%.f words\n", words);

    //count number of sentences (',' '.' '!' = end of sentence)
    float sentences = count_sentences(text);
    printf("%.f sentences\n", sentences);

    // Coleman-Liau reading index score
    // L = average number of letters per 100 words
    // S = average number of sentences per 100 words
    float L = letters/words * 100;
    float S = sentences/words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    int num = round(index);

    if (num <1)
    {
        printf("Before grade 1\n");
    }
    if (num >= 16)
    {
        printf("Grade 16+\n");
    }
    if (num >= 1 && num <=15)
    {
        printf("Grade %i\n", num);
    }
}

//helper function to count number of letters
int count_letters(string s)
{
    int counter = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        char a = s[i];
        if (isalpha(a))
        {
            counter = counter +1;
        }
    }
    return counter;
}

//helper function to count number of words
int count_words(string t)
{
    int counter = 1; //because the first sentence doesn't start with a space
    for (int i = 0; i < strlen(t); i++)
    {
        char a = t[i];
        if (a == ' ')
        {
            counter = counter +1;
        }
    }
    return counter;
}

    //helper function to count sentences
int count_sentences(string u)
{
    int counter = 0;
    for (int i = 0; i < strlen(u); i++)
    {
        char a = u[i];
        if (a == '?' || a=='.' || a=='!')
        {
            counter = counter +1;
        }
    }
    return counter;
}