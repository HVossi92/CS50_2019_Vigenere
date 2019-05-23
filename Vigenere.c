#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void cipher(string userKey);
string moveAscii(int k, int i, string userKey, int min, int max, string ciphTxt);

int main(int argc, string argv[])
{
    // Check whether there are precisely 2 cmd args
    if (argc == 2)
    {   
        // Check the second argv (user input)
        string userKey = argv[1];

        // Loop through each char
        for (int i = 0; i < strlen(userKey); i++)
        {   
            // if any char is no a digit, exit
            if (!isalpha(userKey[i]))
            {
                printf("Usage: ./vigenere keyword\n");
                return 1;
            } 
        }          
        cipher(userKey);
    }
    // Else print and exit the program
    else
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }    
}

//Function to get User message and decrypt it
void cipher(string userKey)
{
    string plainTxt = get_string("Enter you message: \n");
    string ciphTxt = plainTxt;
    
    printf("Plaintext: %s\n", plainTxt);
    
    // Loop through the chars, and offset them in ascii
    int k = 0;
    for (int i = 0; i < strlen(plainTxt); i++)
    {
        // Check if punctuation
        if (isalnum(ciphTxt[i]))
        {
            // min / max = starting / end point in ascii lower / upper alphabet
            int min;
            int max;
            string applyKey = userKey;

            if (k >= strlen(applyKey))
            {
                k = 0;
            }
            
            // Check upper or lower case
            if (isupper(ciphTxt[i]))
            {
                min = 65;
                max = 90;
                moveAscii(k, i, applyKey, min, max, ciphTxt);                     
            }
            else
            {
                min = 97;
                max = 122;
                moveAscii(k, i, applyKey, min, max, ciphTxt);   
            }     
            k++;
            if (k > strlen(userKey))
            {
                k = 0;
            }             
        }
        else
        {
            continue;
        }
    }        
    printf("Ciphertext: %s\n", ciphTxt);
}

string moveAscii(int k, int i, string userKey, int min, int max, string ciphTxt)
{
    // Create my key, and check if the current Userkey is upper or lowercase
    int curKey;

    if (isupper(userKey[k]))
    {
        curKey = userKey[k] - 65;
    }
    else
    {
        curKey = userKey[k] - 97;
    }
    
    int counter = 0;
    // Go through upper chars
    while (counter < curKey)
    {
        // Wrap from every loop add one, as long as the ascii is < 90
        if (ciphTxt[i] < max)
        {
            ciphTxt[i]++;   
            counter++;                        
        }
        // if the ascii is >= 90, wrap back to A
        else
        {
            ciphTxt[i] = min; 
            counter++;
        }
    } 
    return ciphTxt;
}
