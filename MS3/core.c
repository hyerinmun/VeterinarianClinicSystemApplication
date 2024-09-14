/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
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

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
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


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//
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

    do {
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

        for (i = 0; inputChar[i] != '\0' && flag == 0; i++)
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

void inputCString(char* str, int minChar, int maxChar)
{
    int flag = 1;
    char ch = 'a';

    while (flag)
    {
        int len = 0;
        while (ch != '\n' && len <= maxChar)
        {
            ch = getchar();
            str[len] = ch;
            len++;
        };
        if (ch == '\n' && len <= (maxChar + 1))
        {
            len--;
            str[len] = '\0';
        }
        else
        {
            str[maxChar] = '\0';
            clearInputBuffer();
        }
        if (minChar == maxChar && len != minChar)
        {
            printf("ERROR: Sring length must be exactly %d chars: ", minChar);
            ch = 'a';
        }
        else if (len < minChar || len > maxChar)
        {
            if (len > maxChar)
            {
                printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
                ch = 'a';
            }
        }
        else
        {
            flag = 0;
        }
    }
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

