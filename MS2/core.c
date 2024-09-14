/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : Hyerin Mun
Student ID#: 121694236
Email      : hmun@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "core.h"

//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

void displayFormattedPhone(const char phoneNum[])
{
    int flag = 0;
    int i;

    if (phoneNum == NULL)
    {
        printf("(___)___-____");

        return;
    }

    int phoneLen = strlen(phoneNum);

    if (phoneLen != 10)
    {
        printf("(___)___-____");

        return;
    }

    for (i = 0; i < phoneLen; i++)
    {
        if (phoneNum[i] < '0' || phoneNum[i] > '9')
        {
            flag = 1;

            break;
        }
    }

    if (flag == 0 && phoneLen == 10)
    {
        printf("(%c%c%c)%c%c%c-%c%c%c%c", phoneNum[0], phoneNum[1], phoneNum[2], phoneNum[3],
            phoneNum[4], phoneNum[5], phoneNum[6], phoneNum[7], phoneNum[8], phoneNum[9]);
    }
    else
    {
        printf("(___)___-____");
    }
}


int inputInt(void)
{
    char newLine = 'x';
    int value;

    while (newLine != '\n')
    {
        scanf("%d%c", &value, &newLine);

        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } 
    //return 0; //1. just put 0 for now for checking
    return value;
}

int inputIntPositive()
{
    int value;

    do {

        value = inputInt();

        if (value <= 0)
        {
            printf("ERROR! Value must be > 0: ");
        }
    } while (value <= 0);
    return value;
}

int inputIntRange(int lowerBound, int upperBound)
{
    int value;
        
    do{
        value = inputInt();

        if (value < lowerBound || value > upperBound) 
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
    } while (value < lowerBound || value > upperBound);

    return value;
 }

char inputCharOption(const char inputChar[])
{
    char value;
    int i;
    int flag = 0;

    do {

        scanf("%c", &value);

        for (i = 0; inputChar[i] != '\0' && flag == 0 ; i++)
        {
            if (value == inputChar[i])
            {        
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("ERROR: Character must be one of [qwErty]: ");
            
        }
        clearInputBuffer();
    } while (flag != 1);

    return value;
}

void inputCString(char inputCString[], int minChar, int maxChar)
{
    char value[50];
    int i;
    int charLen = strlen(inputCString);

    do
    {
        scanf("%[^\n]%*c", value);

        for (charLen = 0, i = 0; value[i] != '\0'; i++)
        {
            charLen += 1;
        }
        if (charLen < minChar || charLen > maxChar)
        {
            if (minChar == maxChar)
            {
                printf("ERROR: String length must be exactly %d chars: ", maxChar);
            }
            else if (charLen > maxChar)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxChar);
            }
            else
            {
                printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
            }
        }
    } while (charLen < minChar || charLen > maxChar);

    for (i = 0; value[i] != '\0'; i++)
    {
        inputCString[i] = value[i];
    }
}
