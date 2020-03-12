// header files
#include <stdio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>



int userType;
int taskType;


void menuOne();
void menuTwo();
void menuThree();
void menuFour();
int registerUser();
int logIn();
void logOut();
void addRecord();
void deleteRecord();
void editUpdateRecord();
void viewRecord();
int selectUserType();
int selectTask();
int checkUserNameAvailability(char[]);
int verifyLogIn(char[], char[]);
void setLine(int, char[], char[]);


struct ExpenseRecord {
    char uName[30];
    char uPassword[30];
    int utilityCost;
    int housingCost;
    int houseHoldCost;
    int transportationCost;
    int foodCost;
    int medicalCost;
    int insuranceCost;
    int entertainmentCost;
    int clothingCost;
    int miscellaneousCost;
};

struct ExpenseRecord eRecord;

// main function
int main() {
    while(1) {
        menuOne();
        system("color 4e");
        int ok = 0;
        int choice = selectUserType();

        if(choice == 1) {
            while(ok == 0) {
                ok = registerUser();
            }
            ok = 0;

        } else if(choice == 2) {
            while(ok == 0) {
                ok = logIn();
            }
            ok = 0;

            while(1) {
                menuTwo();
                choice = selectTask();
                 system("color 1E");

                if(choice == 1) {
                    addRecord();
                } else if(choice == 2) {
                    viewRecord();
                } else if(choice == 3) {
                    editUpdateRecord();
                } else if(choice == 4) {
                    deleteRecord();
                } else if(choice == 5) {
                    logOut();
                    break;
                } else {
                    printf("\n\tWrong input. Try again!\n");
                }
            }

        } else if(choice == 3) {
            exit(0);
            break;
        } else {
            printf("\n\tWrong input. Try again!\n");
        }
    }

    return 0;
}

void menuOne() {
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t\t\t\t\t\t-------------------------------------");
    printf("\n\t\t\t\t\t\t\t\t ** Daily Expense Management System **\n");
    printf("\t\t\t\t\t\t\t\t-------------------------------------");
    printf("\n\n");

    printf("\tPlease choose user type :\n\n");
    printf("\t\t1. New User\t\n \t\t2. Existing User\t\n \t\t3. Exit\n");
}

void menuTwo() {
    menuThree();

    printf("\tPlease choose your task :\n\n");
    printf("\t 1. Add New Record\n\n");
    printf("\t 2. View Record\n\n");
    printf("\t 3. Edit & Update Record\n\n");
    printf("\t 4. Delete Record\n\n");
    printf("\t 5. Log Out Account\n\n");
}

void menuThree() {
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t\t\t\t\t-------------------------------------");
    printf("\n\t \t\t\t\t\t\t * Daily Expense Management System *\n");
    printf("\t\t\t\t\t\t\t-------------------------------------");
    printf("\n\n\n\tUser : %s\n\n\n\n", eRecord.uName);
}

void menuFour() {
    printf("\n\n\tWhat would you like to edit?\n");
    printf("\n\t  1. Housing Expense\n");
    printf("\n\t  2. Utility Expense\n");
    printf("\n\t  3. Household Expense\n");
    printf("\n\t  4. Transportation Expense\n");
    printf("\n\t  5. Food Expense\n");
    printf("\n\t  6. Medical Expense\n");
    printf("\n\t  7. Insurance Expense\n");
    printf("\n\t  8. Entertainment Expense\n");
    printf("\n\t  9. Clothing Expense\n");
    printf("\n\t 10. Miscellaneous Expense\n");
    printf("\n\t 11. Go Back To Menu\n");
}

int selectUserType() {
    printf("\n\tChoose (enter 1 or 2 or 3) : ");
    scanf("%d", &userType);
    return userType;
}

int selectTask() {
    printf("\n\tEnter your choice : ");
    scanf("%d", &taskType); // select task for add / view / edit / delete
    return taskType;
}

int registerUser() {
    char uName[30];
    char uPassword[30];
    char c;
    int m = 0;

    printf("\n\t\t\t\t   Welcome To User Registration\n");
    printf("\t\t\t\t ---------------------------------");
    printf("\n\tEnter Username : ");
    scanf("%s", uName);

    int nameOK = checkUserNameAvailability(uName);

    if(nameOK == 1) {
        printf("\n\tEnter Password : ");

        while((c = getch()) != 13) {
            if(c == 8) {
                putch('\b');
                putch('\0');
                putch('\b');
                uPassword[m--] = '\0';
            } else {
                uPassword[m++] = c;
                printf("%c", '*');
            }
        }
        uPassword[m] = '\0';
        strcpy(eRecord.uName, uName);
        strcpy(eRecord.uPassword, uPassword);
    } else {
        return 0;
    }

    CreateDirectory(uName, NULL);
    FILE *fp = fopen(strcat(uName, "\\log.txt"), "w");
    fputs(eRecord.uName, fp);
    fputs("\n", fp);
    fputs(eRecord.uPassword, fp);
    fputs("\n", fp);
    fclose(fp);

    fp = fopen("name_exist.txt", "a+");
    fputs(eRecord.uName, fp);
    fputs("\n", fp);
    fclose(fp);

    printf("\n\tRegistration Completed Successfully!\n\tPress any key to continue...");
    getch();
    return 1;
}

int checkUserNameAvailability(char name[30]) {
    char str[30] = {'\0'}, s[1] = {'\0'};
    int c, i = 0;
    FILE *fp = fopen("name_exist.txt", "r");

    if(fp == NULL) {
        perror("Error opening file");
    } else {
        while ((c = fgetc(fp)) != EOF) {

            if(c == '\n') {
                str[i] = '\0';
                //puts(str);

                if(strcmp(name, str) == 0) {
                    printf("\n\tUser already exists! Choose another username.\n");
                    fclose(fp);
                    return 0;
                } else {
                    i = 0;
                }
            } else {
                str[i++] = (char) c;
            }
        }
    }
    fclose(fp);
    return 1;
}

int logIn() {
    char uName[30];
    char uPassword[30];
    char c;
    int m = 0, n = 0;

    printf("\n\t\t\t\t Welcome To User Login\n");
    printf("\t\t\t\t-------------------------");
    printf("\n\tEnter Username : ");
    scanf("%s", uName);
    printf("\n\tEnter Password : ");

    while((c = getch()) != 13) {
        if(c == 8) {
            putch('\b');
            putch('\0');
            putch('\b');
            uPassword[m--] = '\0';
        } else {
            uPassword[m++] = c;
            printf("%c", '*');
        }
    }
    uPassword[m] = '\0';

    int ok = verifyLogIn(uName, uPassword);

    if(ok) {
        printf("\n\tLogin successful!\n\tPress any key to continue...");
        strcpy(eRecord.uName, uName);

    } else {
        return 0;
    }

    return 1;
}

int verifyLogIn(char name[30], char key[30]) {
    char str[30] = {'\0'};
    char temp[30] = {'\0'};
    char s[1] = {'\0'};
    int c, i = 0, k = 0;

    for(i = 0; i < 30; i++) {
        if(name[i] == '\0') {
            temp[i] = '\0';
            break;
        }
        temp[i] = name[i];
    }

    i = 0;

    FILE *fp = fopen(strcat(temp, "\\log.txt"), "r");

    if(fp == NULL) {

        printf("\n\n\tHint : wrong username!\n");
        return 0;
    } else {
        while ((c = fgetc(fp)) != EOF) {

            if(c == '\n') {
                str[i] = '\0';
                if(k > 0) {
                    if(strcmp(key, str) == 0) {
                        k++;
                    }
                } else {
                    if(strcmp(name, str) == 0) {
                        k++;
                    }
                }

                if(k == 0) {
                    break;
                }
                i = 0;
            } else {
                str[i++] = (char) c;
            }
        }

        if(k < 2) {
            printf("\n\tIncorrect username or password. Please try again!");
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    return 1;
}

void addRecord() {
    char date[11] = {'\0'};
    char str[30] = {'\0'};

    menuThree();
    printf("\n\tEnter the date of your record  below.\n");
    printf("\n\tyyyy-mm-dd : ");
    scanf("%s", date);

    strcpy(str, eRecord.uName);
    strcat(str, "\\");
    strcat(str, date);

    FILE *fp = fopen(strcat(str, ".txt"), "a+");

    if(fp == NULL) {
        perror("\n\tError opening file");
    } else {
        fseek (fp, 0, SEEK_END);
        long size = ftell(fp);

        if(size > 0) {
            fclose (fp);
            printf("\n\tFile is not empty. Press any key to go back and edit expense...");
            getch();
            return;
        }

        printf("\n\t Enter your expenses below >\n\n");

        printf("\n\t Housing Expense : ");
        scanf("%d", &eRecord.housingCost);

        printf("\n\t Utility Expense : ");
        scanf("%d", &eRecord.utilityCost);

        printf("\n\t Household Expense : ");
        scanf("%d", &eRecord.houseHoldCost);

        printf("\n\t Transportation Expense : ");
        scanf("%d", &eRecord.transportationCost);

        printf("\n\t Food Expense : ");
        scanf("%d", &eRecord.foodCost);

        printf("\n\t Medical Expense : ");
        scanf("%d", &eRecord.medicalCost);

        printf("\n\t Insurance Expense : ");
        scanf("%d", &eRecord.insuranceCost);

        printf("\n\t Entertainment Expense : ");
        scanf("%d", &eRecord.entertainmentCost);

        printf("\n\t Clothing Expense : ");
        scanf("%d", &eRecord.clothingCost);

        printf("\n\t Miscellaneous Expense : ");
        scanf("%d", &eRecord.miscellaneousCost);

        fprintf(fp, "\t Housing Expense        : %d", eRecord.housingCost);
        fprintf(fp, "\n\t Utility Expense        : %d", eRecord.utilityCost);
        fprintf(fp, "\n\t Household Expense      : %d", eRecord.houseHoldCost);
        fprintf(fp, "\n\t Transportation Expense : %d", eRecord.transportationCost);
        fprintf(fp, "\n\t Food Expense           : %d", eRecord.foodCost);
        fprintf(fp, "\n\t Medical Expense        : %d", eRecord.medicalCost);
        fprintf(fp, "\n\t Insurance Expense      : %d", eRecord.insuranceCost);
        fprintf(fp, "\n\t Entertainment Expense  : %d", eRecord.entertainmentCost);
        fprintf(fp, "\n\t Clothing Expense       : %d", eRecord.clothingCost);
        fprintf(fp, "\n\t Miscellaneous Expense  : %d", eRecord.miscellaneousCost);
        fprintf(fp, "\n");

        printf("\n\t Records added successfully!\n");
    }

    fclose(fp); // closing file
    printf("\n\t Press any key to continue...\n");
    getch(); // wait
}

void deleteRecord() {
    char date[11] = {'\0'};
    char str[30] = {'\0'};
    char c;

    menuThree();
    printf("\n\tEnter the date of your record  below.\n");
    printf("\n\tyyyy-mm-dd : ");
    scanf("%s", date);

    strcpy(str, eRecord.uName);
    strcat(str, "\\");
    strcat(str, date);
    strcat(str, ".txt");

    int value = remove(str);

    if(value == 0) {
        printf("\n\t Record has been deleted successfully!");
    } else {
        printf("\n\t Can not delete the file. Try again!");
    }

    printf("\n\t Press any key to continue...\n");
    getch();
}

void editUpdateRecord() {
    char date[11] = {'\0'};
    char str[30] = {'\0'};
    char c;
    int m;

    menuThree();
    printf("\n\tEnter the date of your record  below.\n");
    printf("\n\tyyyy-mm-dd : ");
    scanf("%s", date);

    strcpy(str, eRecord.uName);
    strcat(str, "\\");
    strcat(str, date);

    FILE *fp = fopen(strcat(str, ".txt"), "r");

    if(fp == NULL) {
        perror("\n\t Error opening file");
    } else {
        menuThree();
        printf("\tDate : %s\t (current data)\n\n", date);

        while ((c = fgetc(fp)) != EOF) {
            printf("%c", (char) c);
        }
    }
    fclose(fp);

    menuFour();
    printf("\n\tEnter your choice : ");
    scanf("%d", &m);

    setLine(m, str, date);
}

void viewRecord() {
    char date[11] = {'\0'};
    char str[30] = {'\0'};
    char c;

    menuThree();
    printf("\n\tEnter the date of your record  below.\n");
    printf("\n\tyyyy-mm-dd : ");
    scanf("%s", date);

    strcpy(str, eRecord.uName);
    strcat(str, "\\");
    strcat(str, date);

    FILE *fp = fopen(strcat(str, ".txt"), "r");

    if(fp == NULL) {
        perror("\n\t Error opening file");
    } else {
        fseek (fp, 0, SEEK_END);
        long size = ftell(fp);
        rewind(fp);

        if(size <= 0) {
            fclose (fp);
            printf("\n\tRecord is empty. Press any key to go back and add data...");
            getch();
            return;
        }

        menuThree();
        printf("\tDate : %s\n\n", date);

        while ((c = fgetc(fp)) != EOF) {
            printf("%c", c);
        }
    }

    fclose(fp);
    printf("\n\n\t Press any key to continue...\n");
    getch();
}

void logOut() {
    return;
}

void setLine(int m, char file[], char date[]) {
    char str[100] = {'\0'};
    int amount, line = 0;
    int c, i = 0;

    menuThree();
    printf("\tDate : %s\n", date);

    FILE *fp, *fk;
    fp = fopen(file, "r");
    rewind(fp);
    fk = fopen("temp.txt", "a+");

    while((c = fgetc(fp)) != EOF) {

      if(c == '\n') {
        line++;

        if(line == m) {
            printf("\n\tEnter new amount : ");
            scanf("%d", &amount);

            if(m == 1) {
                fprintf(fk, "\t Housing Expense        : %d", amount);
            } else if(m == 2) {
                fprintf(fk, "\t Utility Expense        : %d", amount);
            } else if(m == 3) {
                fprintf(fk, "\t Household Expense      : %d", amount);
            } else if(m == 4) {
                fprintf(fk, "\t Transportation Expense : %d", amount);
            } else if(m == 5) {
                fprintf(fk, "\t` Food Expense           : %d", amount);
            } else if(m == 6) {
                fprintf(fk, "\t Medical Expense        : %d", amount);
            } else if(m == 7) {
                fprintf(fk, "\t Insurance Expense      : %d", amount);
            } else if(m == 8) {
                fprintf(fk, "\t Entertainment Expense  : %d", amount);
            } else if(m == 9) {
                fprintf(fk, "\t Clothing Expense       : %d", amount);
            } else if(m == 10) {
                fprintf(fk, "\t Miscellaneous Expense  : %d", amount);
            }

            for(i = 0; i < 100; i++) {
                str[i] = '\0';
            }

            i = 0;
            str[i] = '\n';
            i++;

        } else {
            str[i] = '\n';
            str[i+1] = '\0';
            i = 0;
            fputs(str, fk);

            for(i = 0; i < 100; i++) {
                str[i] = '\0';
            }
            i = 0;
        }
      } else {
            str[i++] = (char) c;
      }
    }
    fclose(fp);
    fclose(fk);

    remove(file);
    rename("temp.txt", file);

    fp = fopen(file, "r");

    while((c = fgetc(fp)) != EOF) {
        printf("%c", c);
    }
    fclose(fp);

    printf("\n\tRecord updated successfully!\n\tPress any key to continue...");
    getch();
    return;
}


