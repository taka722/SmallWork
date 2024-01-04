#include <cs50.h>
#include <stdio.h>

#include <assert.h>

int getLength(long number);
int checkSum(long number, int length);
void checkType(long number, int length);
void testLength(void);
void testCheckSum(void);

int main(void)
{
    // american express 15 digits start with 34 or 37
    // master card 16 digits start with 51, 52, 53, 54 or 55
    // visa 13 or 16 digits start with 4
    // prompt of input
    // calculate checksum
    // check card length and starting digits
    // print which card or invalid.

    // testing my function for length and checksum.
    testLength();
    testCheckSum();

    // user input by numbers.
    long numbers = get_long("Number: ");
    int lengths = getLength(numbers);

    // 1.Invalid: the number of digits for valid card should be 13, 15 or 16. Otherwise, invalid.
    if (lengths != 13 && lengths != 15 && lengths != 16)
    {
        printf("INVALID\n");
        // stop code when they get INVALID, the code should stop working
        //  avoid detecting other card types
        return 0;
    }
    if (!(checkSum(numbers, lengths)))
    {
        printf("INVALID\n");
        // stop code
        return 0;
    }
    checkType(numbers, lengths);
    return 0;
}

// the length of the digits.
int getLength(long number)
{
    int length = 0;
    while (number != 0)
    {
        number = number / 10;
        length++;
    }
    return length;
}

// need to caluculate Sum
// length & input
// hardest part
int checkSum(long number, int length)
{
    int sum = 0;
    int i = 0;
    while (i < length)
    {
        // to check i is even number.
        // count from 0.
        if (i % 2 == 0)
        {
            // to pick up the last digit.
            // printf("%ld\n", number%10);
            // sum without being multiply 2.
            sum = sum + number % 10;
            // printf("sum1 : %i\n", sum);
        }
        else
        {
            // multiply 2 to the digits.
            int digit = 2 * (number % 10);
            // if int digit is two-digit. I need to split each of it 12 -> 1 + 2
            sum += digit / 10 + digit % 10;
        }

        // delete the last digit of the number "123456" -> "12345"
        number = number / 10;
        // printf("%ld\n", number / 10);
        i++;
    }

    return sum % 10 == 0;
}

void checkType(long number, int length)
{
    // to get first second digit.
    while (number >= 100)
    {
        number = number / 10;
    }
    // american express 15 digits start with 34 or 37
    // master card 16 digits start with 51, 52, 53, 54 or 55
    // visa 13 or 16 digits start with 4
    if ((number == 34 || number == 37) && length == 15)
    {
        printf("AMEX\n");
    }
    else if ((number >= 51 && number <= 55) && length == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((number / 10 == 4) && ((length == 13 || length == 16)))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

void testLength(void)
{
    assert(getLength(12345) == 5);
    assert(getLength(1234560987216457) == 16);
    assert(getLength(1) == 1);
    assert(getLength(0) == 0);

    // printf("testLength passed\n");
}

void testCheckSum(void)
{
    // VISA
    long number1 = 4003600000000014;
    int length1 = getLength(number1);

    // it supposed to return 1.
    assert(checkSum(number1, length1) == 1);

    // invalid
    long number2 = 123451234567890;
    int length2 = getLength(number2);

    // it supposed to return 0.
    assert(checkSum(number2, length2) == 0);

    // another valid case
    long number3 = 378282246310005;
    int length3 = getLength(number3);

    // it supposed to return 1.
    assert(checkSum(number3, length3) == 1);
    // printf("checkSum passed\n");
}
