#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool only_digits(string s);
char rotate(char c, int i);

int main(int argc, string argv[])
{
    // Accept only one argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Accept only digits (if only digits no need to check if it's a positive integer)
    if (only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argument into an int
    int key = atoi(argv[1]);

    // Prompt for plaintext
    string plaintext = get_string("plaintext: ");

    // Rotate every letter and print ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");

    return 0;
}

// Accepts only digits
bool only_digits(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (isdigit(s[i]));
        else
        {
            return 1;
        }
    }
    return 0;
}

// Rotates letters
char rotate(char c, int i)
{
    if (isalpha(c))
    {
        if (isupper(c))
        {
            c = (c - 64 + i) % 26 + 64;
        }
        if (islower(c))
        {
            c = (c - 96 + i) % 26 + 96;
        }
    }
    return c;
}