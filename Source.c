/*
Jordan King
*
ITT-310 | Jeremy Wright
*
5/5/2022
*
Grand Canyon University
*
*/

#include <stdio.h>

#include <ctype.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

#include <limits.h>

#include <errno.h>

#include <stdbool.h>

// enums to be used for simplified loops and switch cases
typedef enum { YES, NO } Choice;

typedef enum { Encrypt, Decrypt, Restart, End, } ProgramOperation;

// User Menu 
// 	Choose option ,1,2,3,4
// 	Do -> 1, 2, 3, 4;
// 	3 means to restart again.
//	4 is end the program.
ProgramOperation get_menu_selection() 
{
    int x;

    printf("\nPlease choose following options:\n");

    printf("1 = Encrypt the string.\n");

    printf("2 = Decrypt the string.\n");

    printf("3 = Restart the program.\n");

    printf("4 = End the program.\n");

    scanf_s("%d", &x);

    switch (x)
    {
    case 1: return Encrypt;
    case 2: return Decrypt;
    case 3: return Restart;
    case 4: return End;
    default: exit(1);
    }
}

// Structure to take the string and key size and send it as a group 
typedef struct cipher_request
{
    char* string;
    int key;
} cipher_request;

// Function to scramble text with Caesar Cipher
void cipher(cipher_request name)
{
    int i = 0;
   
    for (i = 0; (i < 100 && name.string[i] != '\0'); i++)
    {
        if (name.string[i] >= 'A' && name.string[1] <= 'Z')
            name.string[i] = (((name.string[i] % 65) + (name.key % 26)) % 26) + 65;

        if (name.string[i] >= 'a' && name.string[1] <= 'z')
            name.string[i] = (((name.string[i] % 97) + (name.key % 26)) % 26) + 97;
    }

    printf("\nEncrypted string: %s\n", name.string);
}

// Function to unscramble text 
void decipher(cipher_request name)
{
    int i = 0;
    char c;
    for (i = 0; (i < 100 && name.string[i] != '\0'); i++)
    {
        c = name.string[i];
        if (c >= 'a' && c <= 'z')
        {
            c = c - (name.key % 26);
            if (c < 'a')
            {
                c = c + 'z' - 'a' + 1;
            }
            name.string[i] = c;
        }
        else if (c >= 'A' && c <= 'Z')
        {
            c = c - (name.key % 26);
            if (c < 'A')
            {
                c = c + 'Z' - 'A' + 1;
            }
            name.string[i] = c;
        }

    }

    printf("\nDecrypted string: %s\n", name.string);
}



// Commenting out for now until I can fix to work correctly
// Function to validate string input from user
/*bool containsspace(char* str)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        if (isspace(str) == 0)
        {
            return true;
        }
        return false;
    }

}*/

int main()

{
   
    // Declare/initialize variables to be used
    cipher_request myrequest;
    myrequest.string = "";
    int size, num, i = 0;
    ProgramOperation op = Restart;
    char str[100], term;
    memset(str, 0, 100);
    Choice programloop = NO;

    // Introduction
    printf("Welcome to my program! \n");
    printf("\nThis program will use the Caesar Cipher to scramble and unscramble a string.\n");



    do // loop to keep within program
    {


        // Loop to start program over completely if it sees length of str is 0
        if (strlen(myrequest.string) == 0)
        {
            // Prompt user for a string
            printf("\nPlease enter a single word to be encrypted:\t");
            scanf_s("%s", str, 100);

            //Commenting out for now until I can fix so it functions correctly
            /*if (containsspace(str[i]) == 0)
            {
                printf("Input needs to be a single word.\n");
                printf("Please try again:\t");
                scanf_s("%s", str, 100);
            }*/
            
            myrequest.string = str;
            
            
            

            // Prompt user for key size for Caesar Cipher
            printf("\nFor the cipher you will need to select a key size between 1-51 and excluding 26:\n");
            printf("(Selecting 26 will shift through the alphabet back to the same characters giving an unchanged output)\n");
            printf("\nPlease enter your value: \t");
            scanf_s("%i", &size);
            
            // Need to work on loop to verify input is an integer also
            // Loop to validate key size stays between 1 and 52 and does not equal 26 or 52
            while (size < 1 || size > 51 || size == 26)
            {
                printf("\nYou did not enter a valid key size.\n");
                printf("(Remember, between 1-51 and excluding 26)\n");
                printf("Please try again: \t");
                scanf_s("%i", &size);

            } 
            
            myrequest.key = size;
            
        }

        // Calling function above for menu selection
        op = get_menu_selection();



        switch (op) // Switch cases are used here for transition between user inputs

        {
            
        // Calls function to perform Caesar cipher to scramble the text and outputs to the console
        case Encrypt: 

            cipher(myrequest);

            break;


        // Calls function to unscramble the text from above
        case Decrypt: 

            decipher(myrequest);

            break;


        // Switch case to restart program
        case Restart:

        // Memset to 0 if user decides to restart the program
            memset(myrequest.string, 0, 100);

            break;

        // Switch case to end program
        case End:

            return 0;
        }

        // End of loop mentioned above to keep program running
    } while (op != End);

    return 0;
}