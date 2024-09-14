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

// include the user library "core" so we can use those functions
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
    if (patient == NULL) {
        // Handle the case when patient is null
        printf("ERROR: Patient pointer is null\n");
        return; // Return to avoid further processing
    }

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
// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
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
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->patients, data->maxAppointments);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) {
    int i;

    // Find the first available slot
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == 0) {
            // Increment patient number
            patient[i].patientNumber = nextPatientNumber(patient, max);

            // Call the inputPatient function for the found slot
            inputPatient(&patient[i]);
            

            printf("\n");
            printf("*** New patient record added ***\n");
            printf("\n");

            return; // Exit the function after adding the patient
        }
    }

    // If the loop completes without finding an available slot, the listing is full
    printf("ERROR: Patient listing is FULL!\n");
    printf("\n");
}
// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    int pNumber, index = -1;
    printf("Enter the patient number: ");
    pNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(pNumber, patient, max);

    if (index >= 0)
    {
        printf("\n");

        int nameLength = strlen(patient[index].name);

        menuPatientEdit(&patient[index]);
        
        if (nameLength > NAME_LEN)
        {
            patient[index].name[NAME_LEN] = '\0';
            printf("ERROR: String length must be no more than %d chars: %s\n", NAME_LEN, patient[index].name);
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n");
    }
}
// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    int uniquePatientNum, indexofRecord;
    char answer, ch;

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

        int flag = 1;

        do
        {
            scanf(" %c%c", &answer, &ch);
            if ((answer == 'n' || answer == 'N') && (ch == '\n'))
            {
                printf("Operation aborted.\n\n");
                flag = 0;
                clearInputBuffer();
            }


            else if ((answer == 'y' || answer == 'Y') && (ch == '\n'))
            {
                patient[indexofRecord].patientNumber = 0;
                printf("Patient record has been removed!\n\n");
                flag = 0;
            }
            else
            {
                clearInputBuffer();
                printf("ERROR: Character must be one of [yn]: ");
            }
        } while (flag);
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{
    sort(data->appointments, data->maxAppointments);
    int i, j;

    printf("Clinic Appointments for the Date: <ALL>\n");
    printf("\n");
    printf("Date       Time  Pat.# Name            Phone#\n");
    printf("---------- ----- ----- --------------- --------------------\n");
    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->appointments[i].patientNumber > 0 && data->patients[j].patientNumber > 0)
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                {
                    // Print appointment data for each matched patient
                    printf("%04d-%02d-%02d %02d:%02d %05d %-15s ",
                        data->appointments[i].date.year, data->appointments[i].date.month, data->appointments[i].date.day,
                        data->appointments[i].time.hour, data->appointments[i].time.min,
                        data->patients[j].patientNumber, data->patients[j].name);

                    displayFormattedPhone(data->patients[j].phone.number);

                    printf(" (%s)\n", data->patients[j].phone.description);
                }
            }
        }
    }
    printf("\n");
}


/// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int lastDay = 31;
    int i, j;
    struct Date date;

    printf("Year        : ");
    date.year = inputIntPositive();
    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    printf("Day (1-");

    if (date.month == 4 || date.month == 9 || date.month == 11)
    {
        lastDay = 30;
    }
    if (date.month == 2)
    {
        lastDay = 28;
    }
    if (date.year % 4 == 0 && date.month == 2)
    {
        lastDay = 29;
    }
    printf("%d)  : ", lastDay
    );

    date.day = inputIntRange(1, lastDay);

    printf("\n");

    sort(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(&date, 0);
    for (i = 0; i < data->maxAppointments; i++)
    {
        for (j = 0; j < data->maxPatient; j++)
        {
            if (data->appointments[i].patientNumber && data->patients[j].patientNumber)
            {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber)
                {
                    if (data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day)
                    {
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                    }
                }
            }
        }
    }    printf("\n");
}
// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* app, struct Patient* patients, int maxAppointments)
{
    int patientNumber, index, slotNotAvailable = 1;
    struct Date date;
    struct Time time;
    int lastDay = 31;

    // Ask for patient number only once
    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    index = findPatientIndexByPatientNum(patientNumber, patients, maxAppointments);

    if (index != -1)
    {
        while (slotNotAvailable)
        {
            printf("Year        : ");
            date.year = inputIntPositive();

            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            printf("Day (1-");
            if (date.month == 2)
            {
                lastDay = 28;
            }
            if (date.month == 4 || date.month == 9 || date.month == 11)
            {
                lastDay = 30;
            }
            if (date.year % 4 == 0 && date.month == 2)
            {
                lastDay = 29;
            }


            printf("%d)  : ", lastDay);
            date.day = inputIntRange(1, lastDay);

            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            // Validate time within the loop
            if (timeSlotAvailable(date, time, app, maxAppointments))
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else {
                while
                    ((time.hour < START_HOUR || time.hour > END_HOUR) ||
                        (time.hour == END_HOUR && time.min > 0) || (time.min % MINUTE_INTERVAL != 0))
                {
                    printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", START_HOUR, END_HOUR, MINUTE_INTERVAL);

                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);
                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);
                }
                slotNotAvailable = 0;
            }
        }
                // nextSlotAvailable(struct Appointment* appoints, int max)
                index = nextSlotAvailable(app, maxAppointments);

                app[index].date = date;
                app[index].time = time;
                app[index].patientNumber = patientNumber;
                printf("\n*** Appointment scheduled! ***\n\n");
          
                }
                else
                {
                printf("\nError: Patient record not found!\n\n");
                }
    return;
}
// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, struct Patient* patients, int maxPatient)
{
    struct Date date;
    int index, patientNumber, lastDay = 0, aptIndex, maxAppointment = 200;

    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    index = findPatientIndexByPatientNum(patientNumber, patients, maxPatient);


    if (index >= 0 )
    {
        printf("Year        : ");
        date.year = inputIntPositive();

        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);

        printf("Day (1-");

        if (date.month == 4 || date.month == 9 || date.month == 11)
        {
            lastDay = 30;
        }
        
        if (date.month == 2)
        {
            lastDay = 28;
        }
        if (date.year % 4 == 0 && date.month == 2)
        {
            lastDay = 29;
        }

        printf("%d)  : ", lastDay);
        date.day = inputIntRange(1, lastDay);

        
        aptIndex = validAppointment(patientNumber, date, appointments, maxAppointment);

        if (aptIndex >= 0)
        {
            printf("\n");
            
            displayPatientData(&patients[index], FMT_FORM);

            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y')
            {
               
                printf("\n");
                printf("Appointment record has been removed!\n\n");

                appointments[aptIndex].patientNumber = 0;
                appointments[aptIndex].time.hour = 0;
                appointments[aptIndex].time.min = 0;
                appointments[aptIndex].date.day = 0;
                appointments[aptIndex].date.month = 0;
                appointments[aptIndex].date.year = 0;
                
            }
            else
            {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
    else {
        printf("ERROR: Patient record not found!\n\n");
    }
}
//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
//Sort the output in order of date (oldest to earliest)
void sort(struct Appointment appoints[], int max)
{
    int i, j;
    struct Appointment tempappoints;

    
    for (i = 0; i < max; i++)
    {
        appoints[i].time.min = (appoints[i].date.year * 12 * 30 * 24 * 60) +
            (appoints[i].date.month * 30 * 24 * 60) +
            (appoints[i].date.day * 24 * 60) +
            (appoints[i].time.hour * 60) +
            appoints[i].time.min;
    }

    for (i = max - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (appoints[j].time.min > appoints[j + 1].time.min)
            {
                tempappoints = appoints[j];
                appoints[j] = appoints[j + 1];
                appoints[j + 1] = tempappoints;
            }
        }
    }
    for (i = 0; i < max; i++)
    {
        appoints[i].time.min = appoints[i].time.min - (appoints[i].date.year * 12 * 30 * 24 * 60) -
            (appoints[i].date.month * 30 * 24 * 60) -
            (appoints[i].date.day * 24 * 60) -
            (appoints[i].time.hour * 60);
    }
}


// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    //plus 1 for null terminator or error
    char searchPhoneNumber[PHONE_LEN + 1];
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
// (Copy your code from MS#2)
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
// (Copy your code from MS#2)
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

int timeSlotAvailable(struct Date date, struct Time time, struct Appointment* app, int maxAppointments)
{
    int i, slotAvaiable = 0;

    for (i = 0; i < maxAppointments; i++)
    {
        if (date.year == app[i].date.year && date.month == app[i].date.month && date.day == app[i].date.day
            && time.hour == app[i].time.hour && time.min == app[i].time.min)
        {
           slotAvaiable = 1; // when slot is available
        }
    }
    return slotAvaiable;
}

int nextSlotAvailable(struct Appointment* app, int maxAppointments)
{
    int i = 0, available = 0;

    while (available == 0 && i < maxAppointments)
    {
        if (app[i].patientNumber < 1)
        {
            available= 1;
        }
        i++;
    }

    return i;
}

int validAppointment(int patientNumber, struct Date date, struct Appointment* app, int maxApp)
{
    int i = 0, valid = 0;

    while (valid == 0 && i < maxApp)
    {
        if ((app[i].patientNumber == patientNumber) && (app[i].date.day == date.day) &&
            (app[i].date.month == date.month) && (app[i].date.year == date.year))
        {
            valid = 1;
        }
        i++;
    }
    return i - 1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);

    printf("Name  : ");
    // Limit the name to 15 characters
    scanf(" %[^\n]", patient->name);
    

    // Check if the entered name exceeds the allowed length
    if (strlen(patient->name) > NAME_LEN)
    {
        // Truncate the name to 15 characters
        patient->name[NAME_LEN-1] = '\0';
        printf("ERROR: String length must be no more than %d chars: %s\n", NAME_LEN, patient->name);
    }

    printf("\n");
    inputPhoneData(&patient->phone);
}
// Get user input for phone contact information
// (Copy your code from MS#2)
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
        clearInputBuffer();
        printf("Number : ");
        do {
            
            scanf("%s", phone->number);
            if (strlen(phone->number) != 10)
            {
                printf("Invalid 10-digit number! Number: ");
            }
        } while (strlen(phone->number) != 10);
        break;
    

    case 2:
        strcpy(phone->description, "HOME");
        printf("Contact: %s\n", phone->description);
        clearInputBuffer();
        do {
            printf("Number: ");
            scanf("%s", phone->number);
            if (strlen(phone->number) != 10)
            {
                printf("Invalid 10-digit number! ");
            }
        } while (strlen(phone->number) != 10);
        printf("\n");
        break;

    case 3:
        strcpy(phone->description, "WORK");
        printf("Contact: %s\n", phone->description);
        clearInputBuffer();
        do {
            printf("Number : ");
            scanf("%s", phone->number);
            if (strlen(phone->number) != 10)
            {
                printf("Invalid 10-digit number! ");
            }
        } while (strlen(phone->number) != 10);
        printf("\n");
        break;


    case 4:
        strcpy(phone->description, "TBD");
        //the phone number should be set to a safe empty state
        phone->number[PHONE_LEN] = '\0';
        break;
    }
    clearInputBuffer();
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;

    FILE* fp;
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {

        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber,
            patients[i].name, patients[i].phone.description, patients[i].phone.number) != EOF)
        {
            i++;

            if (i >= max)
            {
                break;
            }
        }
        fclose(fp);

        return i;
    }
    //Return statement in case fp is NULL
    return -1; // 
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i, count = 0;

    FILE* fp;
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        for (i = 0; i < max && !feof(fp); i++)
        {
            fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day,
                &appoints[i].time.hour, &appoints[i].time.min);

            if (!feof(fp))
            {
                count++;
            }
        }
        fclose(fp);

        return count;
    }
    // Return statement in case fp is NULL
    return -1;
}