/*
Jordan King

ITT-310 | Jeremy Wright

5/29/2022

Grand Canyon University

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
    int x = 0;
    char line[100];
    printf("\nPlease choose following options:\n");

    printf("1 = Encrypt the string.\n");

    printf("2 = Decrypt the string.\n");

    printf("3 = Restart the program.\n");

    printf("4 = End the program.\n");

    if (fgets(line, 100, stdin) && sscanf_s(line, "%d", &x) != 1) 
    {
        x = 0;
    }

    switch (x)
    {
    case 1: return Encrypt;
    case 2: return Decrypt;
    case 3: return Restart;
    case 4: return End;
    default: exit(1);
    }
}

// Structure for string, filestring, and key size
typedef struct cipher_request
{
    char* string;
    char* filestring;
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

// Function to take string from input file, scramble it, and return value
char fileCipher(char* filestring, cipher_request name)
{
    int i = 0;

    for (i = 0; (i < 100 && filestring[i] != '\0'); i++)
    {
        if (filestring[i] >= 'A' && filestring[1] <= 'Z')
            filestring[i] = (((filestring[i] % 65) + (name.key % 26)) % 26) + 65;

        if (filestring[i] >= 'a' && filestring[1] <= 'z')
            filestring[i] = (((filestring[i] % 97) + (name.key % 26)) % 26) + 97;
    }
    return filestring;
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

int main()
{
    // Declare/initialize variables to be used
    cipher_request myrequest;
    int size = 0;
    int z = 0;
    int x = 0;
    int i = 0;
    ProgramOperation op = Restart;
    char str[100];
    memset(str, 0, 100);
    Choice programloop = NO;
    char line[100];
    memset(line, 0, 100);
    char inputline[100];
    memset(inputline, 0, 100);
    char menuselection[100];
    memset(menuselection, 0, 100);
    FILE* in = "file_in.txt";
    FILE* out = "file_out.txt";
    char fileCH[100];
    myrequest.string = str;
    
    

    // Introduction
    printf("Welcome to my program! \n");
    printf("\nThis program will use the Caesar Cipher to scramble and unscramble a string or text file.\n");
    printf("\nThere is a file named file_in.txt that you can alter the contents of. This will be used when you select the file option.\n");
    printf("The contents will be scrambled using the cipher and output into the file 'file_out.txt' for you to read.\n");

    do // loop to keep within program
    {
        // Loop to start program over completely if it sees length of str is 0
        if (strlen(myrequest.string) == 0)
        {
            //Prompt user for String or file
            printf("\nPlease choose from the following: \n");
            printf("1. Input a string \n");
            printf("2. Input a text file:\n");
            printf("Selection:\t");
            fgets(inputline, 100, stdin);
            sscanf_s(inputline, "%d", &z);

            // Input validation for previous menu
            while (z < 1 || z > 2)
            {
                printf("Invalid selection. Try again. \n");
                printf("1. Input a string \n");
                printf("2. Input a text file:\t");
                scanf_s("%d", &z);
            }

            // If user selects file option
            if (z == 2) 
            {
                // Prompt user for key size for Caesar Cipher
                printf("\nFor the cipher you will need to select a key size between 1-51 and excluding 26:\n");
                printf("(Selecting 26 will shift through the alphabet back to the original characters giving an unchanged output)\n");
                printf("\nPlease enter your value: \t");

                // Input validation to make sure user does not enter a letter
                do 
                {
                    if (fgets(line, 100, stdin) && sscanf_s(line, "%d", &size) != 1) 
                    {
                        size = 0;
                    }
                    if (size == 0)
                    {
                        printf("Please try again:\t ");
                    }
                } while (size == 0);

                // Loop to validate key size stays between 1 and 52 and does not equal 26 or 52
                while (size < 1 || size > 51 || size == 26)
                {
                    printf("\nYou did not enter a valid key size.\n");
                    printf("(Remember, between 1-51 and excluding 26)\n");
                    printf("Please try again: \t");
                    scanf_s("%i", &size);
                }
                myrequest.key = size;

                // Open file in and error check
                int didOpenFail = fopen_s(&in, "file_in.txt", "r");
                if (in == NULL || didOpenFail != 0) 
                {
                    puts("Error opening file_in.txt.");
                    exit(1);
                }

                // Open file out and error check
                int didOpen2Fail = fopen_s(&out, "file_out.txt", "w");
                if (out == NULL || didOpen2Fail != 0) 
                {
                    puts("Error opening file_out.txt.");
                    exit(1);
                }

                // Take text from file in, scramble it using cipher, and then write it to file out.
                if (fgets(fileCH, sizeof(fileCH), in) != NULL)
                {
                    fileCipher(&fileCH, myrequest);
                    fwrite(fileCH, sizeof(char), strlen(fileCH), out);
                }
                
                // Inform user that the above actions were successful
                printf("\nThe text from file_in.txt file has been successfully encrypted using the Caesar Cipher.\n");
                printf("The file_out.txt file has been generated successfully.\n");

                // Close both files
                fclose(in);
                fclose(out);

                // Menu selection after file option
                printf("\nPlease make a selection.\n");
                printf("1. Restart program (Selected restart from following menu).\n");
                printf("2. End program.\n");
                fgets(menuselection, 100, stdin);
                sscanf_s(menuselection, "%d", &x); 

                // Input validation for menu selection above
                while (x < 1 || x > 2)
                {
                    printf("Invalid selection. Try again. \n");
                    printf("1. Restart program (Selected restart from following menu). \n");
                    printf("2. End program: \t");
                    fgets(menuselection, 100, stdin);
                    sscanf_s(menuselection, "%d", &x);
                }
                
                // If user chooses to restart program
                if (x == 1)
                {
                    memset(myrequest.string, 0, 100);
                    size = 0;
                    
                }

                // If user chooses to end program
                else if (x == 2)
                {
                    return 0;
                }
            }

            // If user selects to encrypt a single string rather than a file
            else if (z == 1)
            {
                // Prompt user for a string
                printf("\nPlease enter a string to be encrypted:\t");
                fgets(str, 100, stdin);
                myrequest.string = str;

                // Prompt user for a key size for Caesar Cipher
                printf("\nFor the cipher you will need to select a key size between 1-51 and excluding 26:\n");
                printf("(Selecting 26 will shift through the alphabet back to the original characters giving an unchanged output)\n");
                printf("\nPlease enter your value: \t");

                // Input validation to make sure user does not enter a letter
                do 
                {
                    if (fgets(line, 100, stdin) && sscanf_s(line, "%d", &size) != 1) 
                    {
                        size = 0;
                    }
                    if (size == 0)
                    {
                        printf("Please try again:\t ");
                    }
                } while (size == 0);

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
        }

        // Calling function above for menu selection
        op = get_menu_selection();

        // Switch cases are used here for transition between user inputs
        switch (op) 
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
            size = 0;
            break;

            // Switch case to end program
        case End:

            return 0;
        }

        // End of loop mentioned above to keep program running
    } while (op != End);

    return 0;
}