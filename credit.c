#include <cs50.h>
#include <stdio.h>

long calculate_sum_multiplied(long number);
long calculate_sum_left(long number);

int main(void)
{
    //ask for credit card number
    long number;
    number = get_long("Number:");

    //calculate the checksum
    long sum_multiplied = calculate_sum_multiplied(number);
    long sum_left = calculate_sum_left(number);

    long checksum = sum_multiplied + sum_left;

    //check for length and special digits
    if (checksum % 10 == 0)
    {
        //check if it's AMEX
        if ((number < 350000000000000 && number > 339999999999999) || (number > 369999999999999 && number < 380000000000000))
        {
            printf("AMEX\n");
        }
        //check if it's MASTERCARD
        else if (number < 5600000000000000 && number > 5099999999999999)
        {
            printf("MASTERCARD\n");
        }
        //check if it's VISA
        else if ((number > 3999999999999 && number < 5000000000000) || (number > 3999999999999999 && number < 5000000000000000))
        {
            printf("VISA\n");
        }
        //if not any of the above it's INVALID
        else
        {
            printf("INVALID\n");
        }
    }
    //if the checksum doesn't match the card is invalid
    else
    {
        printf("INVALID\n");
    }
}

//calculate the sum of the multiplied numbers
long calculate_sum_multiplied(long number)
{
    long k = 100;
    long n = 0;
    long m;

    //note: both 'for' and 'do while' are correct here
    for (long l = k / 10; l <= 1000000000000000;)
    {
        m = (number % k - number % l) / l * 2 % 10 + ((number % k - number % l) / l * 2 - (number % k - number % l) / l * 2 % 10) / 10;
        n = n + m;
        k = k * 100;
        l = l * 100;
    }
    return n;
}

//calculate the sum of the left numbers
long calculate_sum_left(long number)
{
    long k = 10;
    long n = 0;
    long m;
    long l = 1;

    //note: both 'for' and 'do while' are correct here
    do
    {
        m = (number % k - number % l) / l;
        n = n + m;
        k = k * 100;
        l = l * 100;
    }
    while (l <= 100000000000000);
    return n;
}