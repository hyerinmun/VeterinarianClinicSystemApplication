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

//// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

 //!!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
 //Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

//// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
//// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    int eligible_record = 0;

  
    displayPatientTableHeader();
   

    for (i = 0; i < max; i++)
     {
         if (patient[i].patientNumber != 0)
         {
            displayPatientData(&patient[i], fmt);
            eligible_record = 1;
         }
     }

    if (!eligible_record)
    {
        printf("*** No records found ***\n\n");
    }
    printf("\n");
}


// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        scanf("%d", &selection);
        printf("\n");

        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
        }
        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
        }
    } while (selection != 0);
}

// Add a new patient record to the patient array
// Test to see if the patient array has a free element for a new record
// This is identified when the patient number value is zero
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max)
{
    int i;
    int patientCurrentSize = 0;
    
    //max = 7
    for (i = 0; i < max; i++)
    {
        /*Count the current size until it reaches the patient number value zero */
        if (patient[i].patientNumber != 0)
        {
            patientCurrentSize++;
        }
    }
    // //current size is 5
    if (max > patientCurrentSize)
    {
        patient[patientCurrentSize].patientNumber = nextPatientNumber(patient, max);

        //void inputPatient(struct Patient* patient);
        //patient is the address of the array of patients
        //patient+ patientCurrentSize equals the address of next slot    
        inputPatient(patient + patientCurrentSize);
        
        printf("*** New patient record added ***\n");
        getchar();
        printf("\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n");
        printf("\n");
    }
   
}

 //Edit a patient record from the patient array
 //(ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max)
{
    int uniquePatientNum, indexofRecord;

    printf("Enter the patient number: ");
    scanf("%d", &uniquePatientNum);
    printf("\n");

    //-1 means not found
    // != -1 found 
    if (findPatientIndexByPatientNum(uniquePatientNum, patient, max) != -1)
    {
        indexofRecord = findPatientIndexByPatientNum(uniquePatientNum, patient, max);
        menuPatientEdit(patient + indexofRecord);
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
        getchar();
    }
}

 //Remove a patient record from the patient array
 //(ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max)
{
    int uniquePatientNum, indexofRecord, i;
    char answer;

    printf("Enter the patient number: ");
    scanf("%d", &uniquePatientNum);
    printf("\n");

    //-1 means not found
    // != -1 found 
    if (findPatientIndexByPatientNum(uniquePatientNum, patient, max) != -1)
    {
        indexofRecord = findPatientIndexByPatientNum(uniquePatientNum, patient, max);

        printf("Name  : %s\n", patient[indexofRecord].name);
        printf("Number: %05d\n", patient[indexofRecord].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[indexofRecord].phone.number);
        printf(" (%s)", patient[indexofRecord].phone.description);
        printf("\n\n");

        printf("Are you sure you want to remove this patient record? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y')
        {
            for (i = indexofRecord; i < max - 1; i++)
            {
                patient[i] = patient[i + 1];
            }
            patient[max - 1].patientNumber = 0;
            patient[max - 1].name[0] = '\0';
            patient[max - 1].phone.number[0] = '\0';
            patient[max - 1].phone.description[0] = '\0';

            printf("Patient record has been removed!\n\n");
            getchar();
        }
        else
        {
            printf("Operation aborted.\n\n"); 
            getchar();

        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
        getchar();
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNumber;
    printf("Search by patient number: ");
    scanf("%d", &patientNumber);
    printf("\n");
 
  
    //if the patient record exists, then you must display the record to the user in "form" format
    //Find the patient array index by patient number (returns -1 if not found)
    //stop when the array index is -1 which means not found 

    int index;

    if (findPatientIndexByPatientNum(patientNumber, patient, max) != -1)
    {

        index = findPatientIndexByPatientNum(patientNumber, patient, max);
       
        {
            printf("Name  : %s\n", patient[index].name);
            printf("Number: %05d\n", patient[index].patientNumber);
            printf("Phone : "); displayFormattedPhone(patient[index].phone.number);
            printf(" (%s)\n", patient[index].phone.description);
            printf("\n");
            suspend();
            printf("\n");
        }
    }
    else
    {
        printf("*** No records found ***\n");
        printf("\n");
        suspend();
        printf("\n");
    }
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    //plus 1 for null terminator or error
    char searchPhoneNumber[PHONE_LEN+1];
    int i, flag = 0;

    printf("Search by phone number: ");
    scanf("%14s", searchPhoneNumber);
    searchPhoneNumber[PHONE_LEN] = '\0';
    printf("\n");

    displayPatientTableHeader();

    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, searchPhoneNumber) == 0)
        {
            //displayFormattedPhone(patient[i].phone.number);
            printf("%05d", patient[i].patientNumber);
            printf(" %-15s ", patient[i].name);
            displayFormattedPhone(patient[i].phone.number); 
            printf(" (%s)\n", patient[i].phone.description);
            flag = 1;
        }
    }
    if (!flag)
    {    
      printf("\n");
      printf("*** No records found ***\n");
     }
    printf("\n");
    suspend();
    printf("\n");

}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i, nextPNum, largestPNum = patient[0].patientNumber;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > largestPNum)
        {
            largestPNum = patient[i].patientNumber;
        }
    }
    /*The next patient number is determined by adding one to the largest patient number (largestpNum) in the patient array*/
    nextPNum = largestPNum + 1;

    return nextPNum;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i;

    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber)
        {
            return i;
        }
    }
    //If the record can't be located (matched) then -1 should be returned.
        return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient)
{

    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    scanf(" %[^\n]", patient->name);
    
    printf("\n");
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone) {

    int selection;

    printf("Phone Information\n");
    printf("-----------------\n");

    printf("How will the patient like to be contacted?\n");
    
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
  
    printf("Selection: ");
    scanf("%d", &selection);
    printf("\n");

    //The phone description should be assigned the UPPERCASE equivalent of the user selection
    //(example, if the user enters option 3, then "WORK" will be assigned to the phone description.)
    switch (selection)
    {
    case 1: 
        strcpy(phone->description, "CELL");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        scanf("%s", phone->number);
        break;
        
    case 2:
        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        scanf("%s", phone->number);
        printf("\n");
        break;
     
    case 3:
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        scanf("%s", phone->number);
        break;
      
    case 4:
        strcpy(phone->description, "TBD");
        //the phone number should be set to a safe empty state
        phone->number[PHONE_LEN] = '\0';
        break;
      
    }
}


