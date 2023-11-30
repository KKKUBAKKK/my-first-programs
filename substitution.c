#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Accept only a single argument
    if (argc != 2)
    {
        printf("ERROR - Usage: ./substitution key\n");
        return 1;
    }

    // Accept only exactly 26 chars
    if (strlen(argv[1]) != 26)
    {
        printf("ERROR - Key must contain 26 characters.\n");
        return 1;
    }

    // Accept only letters
    for (int i = 0; i < 26; i++)
    {
        if (isalpha((argv[1])[i]));
        else
        {
            printf("ERROR - Key must only contain alphabetical characters.\n");
            return 1;
        }
    }

    //Save lowercase key
    string lkey = argv[1];
    for (int i = 0; i < 26; i++)
    {
        lkey[i] = tolower((argv[1])[i]);
    }

    // Don't accept the same letter 2 times
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (i != j)
            {
                if (lkey[i] == lkey[j])
                {
                    printf("ERROR - Key must not contain the same characters multiple times.\n");
                    return 1;
                }
            }
        }
    }

    //Ask for plaintext
    string plaintext = get_string("plaintext: ");

    //Turn plaintext into ciphertext
    string ciphertext = plaintext;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = toupper(lkey[plaintext[i] - 65]);
            }
            else
            {
                ciphertext[i] = lkey[plaintext[i] - 97];
            }
        }
    }

    //Print ciphertext
    printf("ciphertext: %s\n", ciphertext);

    return 0;

}