#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

char patientName[MAX_PATIENTS][50];
int patientAge[MAX_PATIENTS];
int patientEmergencyLevel[MAX_PATIENTS];
int patientSpecialtyID[MAX_PATIENTS];
int patientAdmitted[MAX_PATIENTS];
int patientWardID[MAX_PATIENTS];
int patientBedID[MAX_PATIENTS];
int patientDays[MAX_PATIENTS];

float patientWaitingTime[MAX_PATIENTS];
float patientSurcharge[MAX_PATIENTS];
float patientWardCost[MAX_PATIENTS];

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

int specialtyQueueCount[4] = {0, 0, 0, 0};

float calculateEmergencySurcharge(float baseFee, int emergencyLevel)
{
    if(emergencyLevel == 2)
    {
        return baseFee * 0.20f;
    }
    else if(emergencyLevel == 3)
    {
        return baseFee * 0.50f;
    }
    else
    {
        return 0.0f;
    }
}

void printMoney(float amount)
{
  long totalCents = (long)(amount * 100 + 0.5f);
  long rupees = totalCents / 100;
  int cents = totalCents % 100;

  if (rupees >= 1000000)
  {
     printf("%ld,%03ld,%03ld.%02d",
            rupees / 1000000,
            (rupees / 1000) % 1000,
            rupees % 1000,
            cents);
  }
  else if (rupees >= 1000)
  {
     printf("%ld,%03ld.%02d",
            rupees / 1000,
            rupees % 1000,
            cents);
  }
  else
  {
      printf("%ld.%02d", rupees, cents);
  }
}

void savePatientRecords()
{
    FILE *file;
    int i;

    file = fopen("patient_records.txt", "a");
    if(file == NULL)
    {
        printf("Error opening patient_records.txt\n");
        return;
    }

    i = patientCount - 1;

    fprintf(file, "SMART HOSPITAL PATIENT RECORDS\n");
    fprintf(file, "========================================\n\n");

    fprintf(file, "Patient %d\n", i + 1);
    fprintf(file, "Name: %s\n", patientName[i]);
    fprintf(file, "Age: %d\n", patientAge[i]);

     fprintf(file, "Emergency Level: %d\n",
            patientEmergencyLevel[i]);
     fprintf(file, "Specialty ID: %d\n",
            patientSpecialtyID[i]);
     fprintf(file, "Admitted: %s\n",
            patientAdmitted[i] == 1 ? "Yes" : "No");

     if(patientAdmitted[i] == 1)
     {
         fprintf(file, "Ward ID: %d\n",
                patientWardID[i]);
         fprintf(file, "Bed ID: %d\n",
                patientBedID[i]);
         fprintf(file, "Days Admitted: %d\n",
                patientDays[i]);
      }

      fprintf(file, "Waiting Time: %.0f minutes\n",
             patientWaitingTime[i]);
      fprintf(file, "Surcharge: %.2f\n",
             patientSurcharge[i]);
      fprintf(file, "Ward Cost: %.2f\n",
             patientWardCost[i]);
      fprintf(file, "----------------------------------------\n");


      fclose(file);

      printf("Patient record saved to patient_records.txt\n");
}

void saveBillingRecord(int patientNumber,
                       float consultationFeeAmount,
                       float surcharge,
                       float wardCost,
                       float grossBill,
                       float discount,
                       float finalBill)

{
     FILE *file;
     int p;

     p = patientNumber - 1;

     file = fopen("patient_records.txt", "a");

     if(file == NULL)
     {
         printf("Error opening patient_records.txt\n");
         return;
     }

     fprintf(file, "\n");
     fprintf(file, "SMART HOSPITAL BILLING RECORD\n");
     fprintf(file, "========================================\n");

     fprintf(file, "Patient ID: PAT-%04d\n", patientNumber);
     fprintf(file, "Patient Name: %s\n", patientName[p]);
     fprintf(file, "Age: %d\n", patientAge[p]);

     fprintf(file, "Emergency Level: %d\n",
             patientEmergencyLevel[p]);

     if(patientAdmitted[p] == 1)
     {
         fprintf(file, "Ward: %s\n",
                 wardName[patientWardID[p] - 1]);

         fprintf(file, "Bed ID: %d\n",
                 patientBedID[p]);

         fprintf(file, "Days Admitted: %d\n",
                 patientDays[p]);
     }
     else
     {
         fprintf(file, "Ward: Not Admitted\n");
     }

     fprintf(file, "Waiting Time: %.0f minutes\n",
             patientWaitingTime[p]);

     fprintf(file, "----------------------------------------\n");

     fprintf(file, "Consultation Fee: LKR %.2f\n",
             consultationFeeAmount);

     fprintf(file, "Emergency Surcharge: LKR %.2f\n",
             surcharge);

     fprintf(file, "Ward Stay Cost: LKR %.2f\n",
             wardCost);

     fprintf(file, "Gross Total Bill: LKR %.2f\n",
             grossBill);

     fprintf(file, "Age Subsidy Discount: LKR %.2f\n",
             discount);

     fprintf(file, "Final Payable Amount: LKR %.2f\n",
             finalBill);

     fprintf(file, "========================================\n");

     fclose(file);

     printf("Complete billing record saved to patient_records.txt\n");

}


void saveBedStatus()
{
    FILE *file;
    int w,b;

    file = fopen("beds_status.txt", "w");

    if(file == NULL)
    {
        printf("Error opening beds_status.txt\n");
        return;
    }


    for(w = 0; w < 4; w++)
    {
        for(b = 0; b < wardCapacity[w]; b++)
        {
            fprintf(file, "%d %d %d\n",
                    w + 1,
                    b + 1,
                    bedOccupancy[w][b]);
         }
    }

    fclose(file);
}


void loadBedStatus()
{
    FILE *file;
    int w, b, status;

    file = fopen("beds_status.txt", "r");

    if(file == NULL)
    {
        printf("No previous bed status found.\n");
        return;
    }

    while(fscanf(file, "%d %d %d", &w, &b, &status) == 3)
    {
        if(w >= 1 && w <= 4 &&
           b >= 1 && b <= wardCapacity[w - 1] &&
           (status == 0 || status == 1))
        {
            bedOccupancy[w - 1][b - 1] = status;
        }

    }

    fclose(file);

    printf("Previous bed status loaded successfully.\n");

}

int main()
{
    int choice;

    loadBedStatus();

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

        if (scanf("%d", &choice) != 1)
        {
            while(getchar() != '\n');
            choice = 0;
            continue;
        }

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

                if(patientAge[i] < 0 || patientAge[i] > 120)
                {
                    printf("Invalid age! Please enter age between 0 and 120.\n");
                    break;
                }

                printf("\nEmergency Level\n");
                printf("1. Normal\n");
                printf("2. Urgent\n");
                printf("3. Critical\n");

                printf("Enter Emergency Level: ");
                scanf("%d", &patientEmergencyLevel[i]);

                if(patientEmergencyLevel[i] < 1 ||
                   patientEmergencyLevel[i] > 3)
                {
                    printf("Invalid emergency level! Please enter 1, 2, or 3.\n");
                    break;
                }

                printf("\nSpecialty\n");
                printf("1. General Practice\n");
                printf("2. Paediatrics\n");
                printf("3. Cardiology\n");
                printf("4. Neurology\n");

                printf("Enter Specialty ID: ");
                scanf("%d", &patientSpecialtyID[i]);

                if(patientSpecialtyID[i] < 1 ||
                   patientSpecialtyID[i] > 4)
                {
                    printf("Invalid specialty ID! Please enter 1 to 4.\n");
                    break;
                }

                int specialtyIndex = patientSpecialtyID[i] - 1;

                patientWaitingTime[i] =
                    specialtyQueueCount[specialtyIndex] *
                    consultationTime[specialtyIndex];

                specialtyQueueCount[specialtyIndex]++;


                printf("\nAdmitted to Ward?\n");
                printf("1. Yes\n");
                printf("0. No\n");

                printf("Enter choice: ");
                scanf("%d", &patientAdmitted[i]);

                if(patientAdmitted[i] != 0 && patientAdmitted[i] != 1)
                {
                    printf("Invalid choice! Enter 1 for Yes or 0 for No.\n");
                    break;
                }

                if(patientAdmitted[i] == 1)
                {
                     int w;
                     int b;
                     int bedFound = 0;

                     printf("\nWard\n");
                     printf("1. General Ward\n");
                     printf("2. Paediatric Ward\n");
                     printf("3. Surgical Ward\n");
                     printf("4. ICU\n");


                     printf("Enter Ward ID: ");
                     scanf("%d", &patientWardID[i]);

                     if(patientWardID[i] < 1 || patientWardID[i] > 4)
                     {
                         printf("Invalid Ward ID! Please enter 1 to 4.\n");
                         break;
                     }

                     printf("Enter Days Admitted: ");
                     scanf("%d", &patientDays[i]);

                     if(patientDays[i] <= 0)
                     {
                         printf("Invalid number of days!\n");
                         break;
                     }

                     w = patientWardID[i] - 1;


                     for(b = 0; b < wardCapacity[w]; b++)
                     {
                         if(bedOccupancy[w][b] == 0)
                         {
                             bedOccupancy[w][b] = 1;
                             patientBedID[i] = b + 1;
                             bedFound = 1;

                             printf("\nBed Assigned Successfully!\n");
                             printf("Ward: %s\n", wardName[w]);
                             printf("Bed Number: %d\n", patientBedID[i]);

                             break;

                         }
                     }

                     if(bedFound == 0)
                     {
                         patientBedID[i] = 0;
                         printf("\nNo available bed in this ward!\n");

                     }
                }
                else
                {
                  patientWardID[i] = 0;
                  patientBedID[i] = 0;
                  patientDays[i] = 0;
                }



                patientSurcharge[i] =
                     calculateEmergencySurcharge(
                         consultationFee[specialtyIndex],
                         patientEmergencyLevel[i]
                      );
                if(patientAdmitted[i] == 1)
                {
                    patientWardCost[i] =
                    patientDays[i] * wardDailyRate[patientWardID[i] - 1];
                }
                else
                {
                    patientWardCost[i] = 0;
                }

                patientCount++;

                printf("\nPatient Registered Successfully!\n");
                printf("Patient Name: %s\n", patientName[i]);

                savePatientRecords();
                saveBedStatus();

                printf("Age: %d\n", patientAge[i]);
                printf("Emergency Level: %d\n",
                       patientEmergencyLevel[i]);
                printf("Specialty ID: %d\n",
                       patientSpecialtyID[i]);
                printf("Ward ID: %d\n",
                       patientWardID[i]);
                printf("Bed ID          : %d\n",
                       patientBedID[i]);
                printf("Days Admitted: %d\n",
                       patientDays[i]);
                printf("Waiting Time    : %.0f minutes\n",
                       patientWaitingTime[i]);
                printf("Surcharge       : LKR %.2f\n",
                       patientSurcharge[i]);
                printf("Ward Stay Cost  : LKR %.2f\n",
                       patientWardCost[i]);

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
                          printf("Bed ID          : %d\n", patientBedID[i]);
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
            {
                int patientNumber;
                int p;
                int specialtyIndex;
                int wardIndex;

                float consultationFeeAmount;
                float surcharge;
                float wardCost;
                float grossBill;
                float discount;
                float finalBill;

                FILE *file;

                int  surchargePercent;
                const char *urgencyText;

                if(patientCount == 0)
                {
                   printf("\nNo patients registered.\n");
                   break;
                }


                printf("\n====================================================\n");
                printf(" SMART HOSPITAL ADMISSION & BILL\n");
                printf("====================================================\n");

                printf("Enter Patient Number: ");
                scanf("%d", &patientNumber);

                p = patientNumber - 1;


                if(p < 0 || p >= patientCount)
                {
                    printf("\nInvalid patient number!\n");
                    break;
                }

                specialtyIndex = patientSpecialtyID[p] - 1;


                consultationFeeAmount = consultationFee[specialtyIndex];
                surcharge = patientSurcharge[p];
                wardCost = patientWardCost[p];

                grossBill = consultationFeeAmount + surcharge + wardCost;

                if(patientAge[p] < 5 ||
                   patientAge[p] > 65)
                {
                    discount = grossBill * 0.15f;
                }
                else
                {
                    discount = 0.0f;
                }

                finalBill = grossBill - discount;

                if(patientEmergencyLevel[p] == 3)
                {
                    urgencyText = "Critical";
                    surchargePercent = 50;
                }
                else if(patientEmergencyLevel[p] == 2)
                {
                    urgencyText = "Urgent";
                    surchargePercent = 20;
                }
                else
                {
                    urgencyText = "Normal";
                    surchargePercent = 0;
                }


                printf("Patient ID : PAT-%04d\n",patientNumber );

                printf("Patient Name : Mr. %s\n",patientName[p]);

                if(patientAge[p] < 5 || patientAge[p] > 65)

                {
                    printf("Age : %d Years (15%% Subsidy Eligible)\n",
                           patientAge[p]);
                }
                else
                {
                    printf("Age : %d Years\n",patientAge[p]);
                }

                printf("Specialty : %s\n",specialtyName[specialtyIndex]);


                if(patientAdmitted[p] == 1)
                {
                    wardIndex = patientWardID[p] - 1;


                    printf("Assigned Ward : %s (Bed #%02d)\n",
                           wardName[wardIndex],
                           patientBedID[p]);
                }
                else
                {
                    printf("Assigned Ward : Not Admitted\n");
                }

                printf("Urgency Level : Level %d (%s)\n",
                       patientEmergencyLevel[p],
                       urgencyText);

                printf("----------------------------------------------------------------------------------------\n");

                printf("Base Consultation Fee : LKR ");
                printMoney(consultationFeeAmount);
                printf("\n");


                printf("Emergency Surcharge: LKR ");
                printMoney(surcharge);
                printf(" (%d%%)\n", surchargePercent);

                printf("Ward Stay Cost (%d Days) : LKR ",
                       patientDays[p]);
                printMoney(wardCost);
                printf("\n");

                printf("----------------------------------------------------------------------------------------\n");

                printf("Gross Total Bill : LKR ");
                printMoney(grossBill);
                printf("\n");

                printf("Age Subsidy Discount : LKR -");
                printMoney(discount);

                if(discount > 0)
                {
                   printf(" (15%%)\n");
                }
                else
                {
                    printf(" (0%%)\n");
                }

                printf("----------------------------------------------------------------------------------------\n");

                printf("Final Payable Amount : LKR ");
                printMoney(finalBill);
                printf("\n");

                printf("Estimated Waiting Time : %.2f mins",
                       patientWaitingTime[p]);

                if(patientWaitingTime[p] == 0)
                {
                    printf(" (Immediate Attention)");
                }


                printf("\n====================================================\n");


                file = fopen("patient_records.txt", "a");

                if(file == NULL)
                {
                    printf("Error opening patient_records.txt\n");
                }
                else
                {
                    fprintf(file, "\n========================================\n");
                    fprintf(file, "PATIENT BILL\n");
                    fprintf(file, "========================================\n");

                    fprintf(file, "Patient ID : PAT-%04d\n", patientNumber);
                    fprintf(file, "Patient Name : Mr. %s\n", patientName[p]);
                    fprintf(file, "Age : %d\n", patientAge[p]);
                    fprintf(file, "Specialty : %s\n", specialtyName[specialtyIndex]);

                    if(patientAdmitted[p] == 1)
                    {
                        fprintf(file, "Ward : %s\n", wardName[wardIndex]);
                        fprintf(file, "Bed : %d\n", patientBedID[p]);
                        fprintf(file, "Days : %d\n", patientDays[p]);
                    }

                    fprintf(file, "Urgency : %s\n", urgencyText);
                    fprintf(file, "Base Consultation Fee : LKR %.2f\n",
                            consultationFeeAmount);
                    fprintf(file, "Emergency Surcharge : LKR %.2f\n",
                            surcharge);
                    fprintf(file, "Ward Stay Cost : LKR %.2f\n",
                            wardCost);
                    fprintf(file, "Gross Total Bill : LKR %.2f\n",
                            grossBill);
                    fprintf(file, "Age Subsidy Discount : LKR %.2f\n",
                            discount);
                    fprintf(file, "Final Payable Amount : LKR %.2f\n",
                            finalBill);
                    fprintf(file, "Estimated Waiting Time : %.0f minutes\n",
                            patientWaitingTime[p]);

                    fprintf(file, "========================================\n\n");

                    fclose(file);

                    printf("Complete patient bill saved to patient_records.txt\n");


                }


                break;

            }

            case 5:
            {
                int order[MAX_PATIENTS];
                int i, j, temp;


                printf("\n========== PRIORITY PATIENT LIST ==========\n");

                if(patientCount == 0)
                {
                    printf("No patients registered yet.\n");
                    break;
                }

                for(i = 0; i < patientCount; i++)
                {
                    order[i] = i;
                }

                for(i = 0;i < patientCount -  1; i++)
                {
                    for(j = 0; j < patientCount - i - 1; j++)
                    {
                        if(patientEmergencyLevel[order[j]] <
                            patientEmergencyLevel[order[j + 1]])
                        {
                            temp = order[j];
                            order[j] = order[j + 1];
                            order[j + 1] = temp;
                        }
                    }
                }

                for(i = 0; i < patientCount; i++)
                {
                    int p = order[i];

                    printf("\nPriority %d\n", i + 1);
                    printf("-----------------------------\n");
                    printf("Name            : %s\n", patientName[p]);
                    printf("Age             : %d\n", patientAge[p]);
                    printf("Emergency Level : %d\n", patientEmergencyLevel[p]);
                    printf("Specialty ID    : %d\n", patientSpecialtyID[p]);
                    printf("Waiting Time    : %.0f minutes\n",
                           patientWaitingTime[p]);

                    if(patientAdmitted[p] == 1)
                    {
                        printf("Ward ID         : %d\n", patientWardID[p]);
                        printf("Bed ID          : %d\n", patientBedID[p]);
                    }
                    else
                    {
                      printf("Ward ID         : Not Admitted\n");
                      printf("Bed ID          : Not Assigned\n");
                    }
                }

                break;
            }

            case 6:
            {
                int i;
                int normalCount = 0;
                int urgentCount = 0;
                int criticalCount = 0;
                int admittedCount = 0;

                int occupiedBeds;
                float occupancyPercetage;

                float totalRevenue = 0.0f;
                float totalDiscount = 0.0f;

                float highestBill = 0.0f;
                int highestPatient = -1;

                printf("\n========== REPORTS AND ANALYTICS ==========\n");

                if(patientCount == 0)
                {
                    printf("No patients registered yet.\n");
                    break;
                }

                    for(i = 0; i < patientCount; i++)
                    {

                        if(patientEmergencyLevel[i]==1)
                        {
                            normalCount++;

                        }
                        else if (patientEmergencyLevel[i]==2)
                        {
                            urgentCount++;
                        }

                        else if (patientEmergencyLevel[i]==3)
                        {
                            criticalCount++;
                        }

                        if(patientAdmitted[i] == 1)
                        {
                            admittedCount++;

                        }

                    }

                    for(i = 0; i < patientCount; i++)
                    {
                        int specialtyIndex;
                        float consultation;
                        float surcharge;
                        float wardCost;
                        float grossBill;
                        float discount;
                        float finalBill;

                        specialtyIndex = patientSpecialtyID[i] - 1;

                        consultation = consultationFee[specialtyIndex];
                        surcharge = patientSurcharge[i];
                        wardCost = patientWardCost[i];

                        grossBill = consultation + surcharge + wardCost;

                        if(patientAge[i] < 5 || patientAge[i] > 65)
                        {
                            discount = grossBill * 0.15f;
                        }
                        else
                        {
                            discount = 0.0f;
                        }

                        finalBill = grossBill - discount;

                        totalDiscount += discount;
                        totalRevenue += finalBill;

                        if(finalBill > highestBill)
                        {
                            highestBill = finalBill;
                            highestPatient = i;
                        }
                    }

                    printf("\n----- Patient Statistics -----\n");
                    printf("Total Patients       : %d\n", patientCount);
                    printf("Normal Patients      : %d\n", normalCount);
                    printf("Urgent Patients      : %d\n", urgentCount);
                    printf("Critical Patients    : %d\n", criticalCount);
                    printf("Admitted Patients    : %d\n", admittedCount);


                    printf("\n----- Financial Statistics -----\n");
                    printf("Total Revenue        : LKR %.2f\n", totalRevenue);
                    printf("Total Discounts      : LKR %.2f\n", totalDiscount);

                    printf("\n----- Bed Occupancy -----\n");


                    for(i = 0; i < 4; i++)
                    {
                        int b;

                        occupiedBeds = 0;

                        for(b = 0; b < wardCapacity[i]; b++)
                        {
                            if(bedOccupancy[i][b] == 1)
                            {
                                occupiedBeds++;
                            }
                        }

                        occupancyPercetage =
                            ((float)occupiedBeds / wardCapacity[i]) * 100;

                        printf("%s: %.2f%% occupied\n",
                                wardName[i],
                                occupancyPercetage);
                    }

                    printf("\n----- Highest-Paying Patient -----\n");

                    if(highestPatient != -1)
                    {
                        printf("Patient Name : %s\n",
                               patientName[highestPatient]);

                        printf("Final Bill   : LKR %.2f\n",
                               highestBill);
                    }




                break;

            }

            case 7:
                printf("\nExiting Smart Hospital System...\n");
                printf("Thank you!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while(choice != 7);

    return 0;
}
