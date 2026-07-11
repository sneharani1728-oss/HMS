#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient
{
    int patientID;
    char patientName[50];
    int age;
    char gender[10];
    char disease[50];
    char doctorName[50];
    char phone[15];
};

struct Bill
{
    int patientID;
    char patientName[50];
    float consultationFee;
    float medicineFee;
    float roomCharge;
    float totalAmount;
};
void login()
{
    char username[20];
    char password[20];
    int attempts = 3;

    while(attempts > 0)
    {
        printf("\n=================================");
        printf("\n        ADMIN LOGIN");
        printf("\n=================================");

        printf("\nEnter Username: ");
        scanf("%s", username);

        printf("Enter Password: ");
        scanf("%s", password);

        if(strcmp(username, "admin") == 0 &&
           strcmp(password, "admin123") == 0)
        {
            printf("\nLogin Successful!");
            printf("\nWelcome to Hospital Management System\n");
            return;
        }
        else
        {
            attempts--;

            printf("\nInvalid Username or Password!");

            if(attempts > 0)
            {
                printf("\nAttempts remaining: %d\n", attempts);
            }
            else
            {
                printf("\nToo many failed attempts.");
                printf("\nSystem Exit.");
                exit(0);
            }
        }
    }
}
void addPatient()
{
    struct Patient p;
    FILE *fp;

    fp = fopen("patients.dat", "ab");

    if(fp == NULL)
    {
        printf("\nError opening patient file!");
        return;
    }

    printf("\n========== ADD PATIENT ==========");

    printf("\nEnter Patient ID: ");
    scanf("%d", &p.patientID);

    printf("Enter Patient Name: ");
    scanf(" %[^\n]", p.patientName);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Gender: ");
    scanf("%s", p.gender);

    printf("Enter Disease: ");
    scanf(" %[^\n]", p.disease);

    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", p.doctorName);

    printf("Enter Phone Number: ");
    scanf("%s", p.phone);

    fwrite(&p, sizeof(struct Patient), 1, fp);

    fclose(fp);

    printf("\nPatient Added Successfully!\n");
}
void viewPatients()
{
    struct Patient p;
    FILE *fp;

    fp = fopen("patients.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo patient records found!");
        return;
    }

    printf("\n========== PATIENT DETAILS ==========\n");

    while(fread(&p, sizeof(struct Patient), 1, fp))
    {
        printf("\nPatient ID    : %d", p.patientID);
        printf("\nName          : %s", p.patientName);
        printf("\nAge           : %d", p.age);
        printf("\nGender        : %s", p.gender);
        printf("\nDisease       : %s", p.disease);
        printf("\nDoctor Name   : %s", p.doctorName);
        printf("\nPhone Number  : %s", p.phone);

        printf("\n------------------------------------\n");
    }

    fclose(fp);
}
void searchPatient()
{
    struct Patient p;
    FILE *fp;
    int searchID;
    int found = 0;

    fp = fopen("patients.dat", "rb");

    if(fp == NULL)
    {
        printf("\nPatient file not found!");
        return;
    }

    printf("\nEnter Patient ID to search: ");
    scanf("%d", &searchID);

    while(fread(&p, sizeof(struct Patient), 1, fp))
    {
        if(p.patientID == searchID)
        {
            printf("\n========== PATIENT FOUND ==========\n");

            printf("\nPatient ID    : %d", p.patientID);
            printf("\nName          : %s", p.patientName);
            printf("\nAge           : %d", p.age);
            printf("\nGender        : %s", p.gender);
            printf("\nDisease       : %s", p.disease);
            printf("\nDoctor Name   : %s", p.doctorName);
            printf("\nPhone Number  : %s\n", p.phone);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nPatient record not found!");
    }

    fclose(fp);
}
void deletePatient()
{
    struct Patient p;
    FILE *fp, *temp;
    int deleteID;
    int found = 0;

    fp = fopen("patients.dat", "rb");

    if(fp == NULL)
    {
        printf("\nPatient file not found!");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if(temp == NULL)
    {
        printf("\nError creating temporary file!");
        fclose(fp);
        return;
    }

    printf("\nEnter Patient ID to delete: ");
    scanf("%d", &deleteID);

    while(fread(&p, sizeof(struct Patient), 1, fp))
    {
        if(p.patientID == deleteID)
        {
            found = 1;
            printf("\nPatient record deleted successfully!");
        }
        else
        {
            fwrite(&p, sizeof(struct Patient), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if(found)
    {
        remove("patients.dat");
        rename("temp.dat", "patients.dat");
    }
    else
    {
        remove("temp.dat");
        printf("\nPatient record not found!");
    }
}
void generateBill()
{
    struct Bill b;
    FILE *fp;

    fp = fopen("bills.dat", "ab");

    if(fp == NULL)
    {
        printf("\nError opening bill file!");
        return;
    }

    printf("\n========== GENERATE BILL ==========\n");

    printf("Enter Patient ID: ");
    scanf("%d", &b.patientID);

    printf("Enter Patient Name: ");
    scanf(" %[^\n]", b.patientName);

    printf("Enter Consultation Fee: ");
    scanf("%f", &b.consultationFee);

    printf("Enter Medicine Fee: ");
    scanf("%f", &b.medicineFee);

    printf("Enter Room Charge: ");
    scanf("%f", &b.roomCharge);

    b.totalAmount = b.consultationFee +
                    b.medicineFee +
                    b.roomCharge;

    fwrite(&b, sizeof(struct Bill), 1, fp);

    fclose(fp);

    printf("\n=========== BILL RECEIPT ===========");
    printf("\nPatient ID        : %d", b.patientID);
    printf("\nPatient Name      : %s", b.patientName);
    printf("\nConsultation Fee  : %.2f", b.consultationFee);
    printf("\nMedicine Fee      : %.2f", b.medicineFee);
    printf("\nRoom Charge       : %.2f", b.roomCharge);
    printf("\n------------------------------------");
    printf("\nTotal Amount      : %.2f", b.totalAmount);
    printf("\n====================================");

    printf("\n\nBill Generated Successfully!\n");
}
int main()
{
    int choice;

    login();

    while(1)
    {
        printf("\n\n=================================");
        printf("\n   HOSPITAL MANAGEMENT SYSTEM");
        printf("\n=================================");

        printf("\n1. Add Patient");
        printf("\n2. View Patients");
        printf("\n3. Search Patient");
        printf("\n4. Delete Patient");
        printf("\n5. Generate Bill");
        printf("\n6. Exit");

        printf("\n\nEnter your choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("\nInvalid Input! Enter numbers only.");

            while(getchar() != '\n');

            continue;
        }

        switch(choice)
        {
            case 1:
                addPatient();
                break;

            case 2:
                viewPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 4:
                deletePatient();
                break;

            case 5:
                generateBill();
                break;

            case 6:
                printf("\nExiting Hospital Management System...");
                exit(0);

            default:
                printf("\nInvalid Choice! Please select between 1-6.");
        }
    }

    return 0;
}
