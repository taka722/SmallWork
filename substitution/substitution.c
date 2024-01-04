#include <cs50.h>
#include <stdio.h>

#include <assert.h>
#include <ctype.h>
#include <string.h>

bool checkValidKey(string key);
void encryptText(string text, string key);

void testvalidekey(void);
void testencrypt(void);

int main(int argc, string argv[])
{
    // test
    // if you type ./substitution test -> test will be started.
    // And print out the result at the terminal.
    if (argc == 2 && strcmp(argv[1], "test") == 0)
    {
        testvalidekey();
        testencrypt();
        return 0;
    }

    // check the user input (whether they provide key or not)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (!checkValidKey(argv[1]))
    {
        return 1;
    }

    // get user input  normal text
    string text = get_string("plaintext: ");

    // encrypt the text
    printf("ciphertext: ");
    encryptText(text, argv[1]);
    printf("\n");

    return 0;
}

bool checkValidKey(string key)
{
    // check the valid key
    int num = strlen(key);
    if (num != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int i = 0; i < num; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return false;
        }
        for (int j = i + 1; j < num; j++)
        {
            // compare the character and next character ex. aa -> false
            if (tolower(key[i]) == tolower(key[j]))
            {
                printf("Key must not contain repeated characters.\n");
                return false;
            }
        }
    }
    return true;
}

void encryptText(string text, string key)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                printf("%c", toupper(key[text[i] - 'A']));
            }
            else
            {
                printf("%c", tolower(key[text[i] - 'a']));
            }
        }
        else
        {
            printf("%c", text[i]);
        }
    }
}

void testvalidekey(void)
{

    // test the function  checkValidKey().
    assert(checkValidKey("YTNSHKVEFXRBAUQZCLWDMIPGJO") == true);
    assert(checkValidKey("VCHPRZGJNTLSKFBDQWAXEUYMOI") == true);
    assert(checkValidKey("abcdefghijklmnopqrstuvwxyz") == true);
    assert(checkValidKey("ABC") == false);                        // must 26
    assert(checkValidKey("1 2 3") == false);                      // must 26
    assert(checkValidKey("abcdefghijklmnopqrstuvwxy") == false);  // must 26
    assert(checkValidKey("YTNS3KVE5XRBAUQZ4LWDMIPGJ3") == false); // contain number is not allowed
    assert(checkValidKey("abcefghijklmnopqrstuvwxyzz") == false); // repeated character
}

void testencrypt(void)
{
    // check the function encrypttext().
    // Should print "EHBBQ"
    encryptText("HELLO", "YTNSHKVEFXRBAUQZCLWDMIPGJO");
    // Should print "jrssb, ybwsp"
    encryptText("hello, world", "VCHPRZGJNTLSKFBDQWAXEUYMOI");
}
