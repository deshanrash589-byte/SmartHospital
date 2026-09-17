#include <stdio.h>

#define MAX_PATIENTS 100

char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS];
int patientEmergencyLevel[MAX_PATIENTS];
int patientSpecialtyID[MAX_PATIENTS];
int patientAdmitted[MAX_PATIENTS];
int patientWardID[MAX_PATIENTS];
int patientDays[MAX_PATIENTS];

int patientCount = 0;

const int specialtyID[4] = {1, 2, 3, 4};
const char specialtyName[4][30] = {
    "General Practice",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

const float consultationFee[4] = {
    1500.00,
    2500.00,
    4500.00,
    5000.00
};

const int consultationTime[4] = {
    15,
    20,
    30,
    30
};

const int dailyPatientCap[4] = {
    30,
    20,
    12,
    10
};

const int wardID[4] = {1, 2, 3, 4};

const char wardName[4][30] = {
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU"
};

const float wardDailyRate[4] = {
    3000.00,
    6000.00,
    12000.00,
    25000.00
};

const int wardCapacity[4] = {
    20,
    10,
    10,
    5
};

int bedOccupancy[4][20] = {0};

int main()
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("       SMART HOSPITAL SYSTEM\n");
        printf("========================================\n");

        printf("1. Register Patient\n");
        printf("2. Display Patients\n");
        printf("3. Display Bed Status\n");
        printf("4. Generate Patient Bill\n");
        printf("5. Priority Patient List\n");
        printf("6. Reports and Analytics\n");
        printf("7. Exit\n");

        printf("----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            {
                int i = patientCount;



                printf("\n========== PATIENT REGISTRATION ==========\n");

                printf("Enter patient Name: ");
                scanf(" %[^\n]", patientName[i]);

                printf("Enter Patient Age: ");
                scanf("%d", &patientAge[i]);

                printf("\nEmergency Level\n");
                printf("1. Normal\n");
                printf("2. Urgent\n");
                printf("3. Critical\n");

                printf("Enter Emergency Level: ");
                scanf("%d", &patientEmergencyLevel[i]);

                printf("\nSpecialty\n");
                printf("1. General Practice\n");
                printf("2. Paediatrics\n");
                printf("3. Cardiology\n");
                printf("4. Neurology\n");

                printf("Enter Specialty ID: ");
                scanf("%d", &patientSpecialtyID[i]);

                printf("\nAdmitted to Ward?\n");
                printf("1. Yes\n");
                printf("0. No\n");

                printf("Enter choice: ");
                scanf("%d", &patientAdmitted[i]);

                if(patientAdmitted[i] == 1)
                {
                     printf("\nWard\n");
                     printf("1. General Ward\n");
                     printf("2. Paediatric Ward\n");
                     printf("3. Surgical Ward\n");
                     printf("4. ICU\n");


                     printf("Enter Ward ID: ");
                     scanf("%d", &patientWardID[i]);

                     printf("Enter Days Admitted: ");
                     scanf("%d", &patientDays[i]);
                }
                else
                {
                  patientWardID[i] = 0;
                  patientDays[i] = 0;
                }

                patientCount++;

                printf("\nPatient Registered Successfully!\n");
                printf("Patient Name: %s\n", patientName[i]);
                printf("Age: %d\n", patientAge[i]);
                printf("Emergency Level: %d\n",
                       patientEmergencyLevel[i]);
                printf("Specialty ID: %d\n",
                       patientSpecialtyID[i]);
                printf("Ward ID: %d\n",
                       patientWardID[i]);
                printf("Days Admitted: %d\n",
                       patientDays[i]);

                break;

            }

            case 2:
            {
                int i;

                printf("\n========== REGISTERED PATIENTS ==========\n");

                if(patientCount == 0)
                {
                    printf("No patients registered yet.\n");
                }
                else
                {
                   for(i = 0; i < patientCount; i++)
                   {
                      printf("\nPatient %d\n", i + 1);
                      printf("-----------------------------\n");
                      printf("Name            : %s\n", patientName[i]);
                      printf("Age             : %d\n", patientAge[i]);
                      printf("Emergency Level : %d\n", patientEmergencyLevel[i]);
                      printf("Specialty ID    : %d\n", patientSpecialtyID[i]);
                      printf("Admitted        : %s\n",
                             patientAdmitted[i] == 1 ? "Yes" : "No");

                      if(patientAdmitted[i] == 1)
                      {
                          printf("Ward ID         : %d\n", patientWardID[i]);
                          printf("Days Admitted   : %d\n", patientDays[i]);
                      }
                   }
                }

                break;
            }

            case 3:
            {
                int w,b;

                printf("\n========== BED STATUS ==========\n");

                for(w = 0; w < 4; w++)
                {
                   printf("\nWard %d - %s\n", wardID[w], wardName[w]);
                   printf("Capacity: %d beds\n", wardCapacity[w]);

                   for(b = 0; b < wardCapacity[w]; b++)
                   {
                       if(bedOccupancy[w][b] == 0)
                       {
                          printf("Bed %d: Available\n", b + 1);
                       }
                       else
                       {
                         printf("Bed %d: Occupied\n", b + 1);
                       }
                   }
                }

                break;

            }

            case 4:
                printf("\nGenerate Patient Bill selected.\n");
                break;

            case 5:
                printf("\nPriority Patient List selected.\n");
                break;

            case 6:
                printf("\nReports and Analytics selected.\n");
                break;

            case 7:
                printf("\nThank you for using Smart Hospital System.\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while(choice != 7);

    return 0;
}
