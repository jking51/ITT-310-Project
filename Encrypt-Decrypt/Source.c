/*
Jordan King
*
ITT-310 | Jeremy Wright
*
5/1/2022
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

// enums to be used for simplified loops and swtich cases
typedef enum { YES, NO } Choice;

typedef enum { Encrypt, Decrypt, Restart, End } ProgramOperation;

// User Menu 
// 	Choose option ,1,2,3,4
// 	Do -> 1, 2, 3, 4;
// 	3 means to restart again.
//	4 is end the program.
ProgramOperation get_menu_selection() {
    int x;
    // Prompt user for encryption or decryption

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




int main()

{


    // Declare/initialize variables to be used

    int i, size;
    int y = 3;
    ProgramOperation op = Restart;
    char str[100];
    memset(str, 0, 100);
    Choice programloop = NO;

    // Introduction
    printf("Welcome to my program! \n");

    printf("\nThis program will use the Caesar Cipher to encrypt and decrypt a string.\n");



    do // loop to keep within program
    {


        // Loop to start program over completely if it sees length of str is 0
        if (strlen(str) == 0)
        {
            // Prompt user for a string
            printf("\nPlease enter a string to be encrypted:\t");
            scanf_s("%s", str, 100);


            // Prompt user for key size for Caesar Cipher
            printf("\nPlease enter a key size:\t");
            scanf_s("%i", &size);
        }

        // calling function above for menu selection
        op = get_menu_selection();



        switch (op) // Switch cases are used here for transition between user inputs

        {



        case Encrypt: // Performs Caesar cipher to encrypt the text and outputs to the console


            for (i = 0; (i < 100 && str[i] != '\0'); i++)

                str[i] = str[i] + size; // key number is added to ASCII value for encryption


            printf("\nEncrypted string: %s\n", str);


            break;



        case Decrypt: // Uses Caesar cipher to decrypt the text and outputs to the console


            for (i = 0; (i < 100 && str[i] != '\0'); i++)

                str[i] = str[i] - size; // key number is subtracted from ASCII value for encryption


            printf("\nDecrypted string: %s\n", str);

            break;



        case Restart: // Switch case to restart program



        //Erase string
            memset(str, 0, 100);


            break;


        case End: // Switch case to end program


            return 0;
        }

        // Loop mentioned above to keep program running
    } while (op != End);

    return 0;
}