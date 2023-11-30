#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calculate_grade(float letters, float words, float sentences);

int main(void)
{
    // Asks for string input
    string text =  get_string("Text: ");

    // Counts and stores letters
    int letters = count_letters(text);

    // Counts and stores words
    int words = count_words(text);

    // Counts and stores sentences
    int sentences = count_sentences(text);

    // Calculates and stores the grade
    int grade = calculate_grade(letters, words, sentences);

    // Prints out the grade
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

// Counts letters
int count_letters(string text)
{
    int n = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            n++;
        }
    }
    return n;
}

// Counts words
int count_words(string text)
{
    int n = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isspace(text[i]))
        {
            n++;
        }
    }
    return n;
}

// Counts sentences
int count_sentences(string text)
{
    int n = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            n++;
        }
    }
    return n;
}

//Calculates the grade
int calculate_grade(float letters, float words, float sentences)
{
    float l = letters / words * 100;
    float s = sentences / words * 100;
    int n = round(0.0588 * l - 0.296 * s - 15.8);
    return n;
}