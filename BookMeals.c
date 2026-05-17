#include <stdio.h>
#include <stdbool.h>

int GetMealBookingData(User (*users)[6]) {
    int isEligible;
    int userID=0;

    printf("Please enter your room number:");
    scanf("%d", &userID);


        if (((*users)[userID] . boardType == halfBoard || (*users)[userID] . boardType == fullBoard)) {
            isEligible = userID;
        }
        else {
            isEligible = -1;
            printf("Sorry, no dinner for you. Not eligible.");
        }

    return isEligible;
}

void ShowMealOptions(User* userData, bool freeTablesSeven[3], bool freeTablesNine[3]) {
    bool tableSpace = false;
    bool tableSpaceSeven = false;
    bool tableSpaceNine = false;
    int tableChoice = 0;
    int timeChoice = 0;

    for (int i = 0; i < 3; i++) {
        if (freeTablesSeven[i] == true) {
            tableSpaceSeven = true;
            tableSpace = true;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (freeTablesNine[i] == true) {
            tableSpaceNine = true;
            tableSpace = true;
        }
    }

    if (tableSpace == true) {
        printf("Which time 7 / 9: ");
        scanf("%d", &timeChoice);
            if (timeChoice == 7 && tableSpaceSeven == true) { //SELECTS THE TIME AS 7PM
                printf("Free tables: \n");
                for (int i = 0; i<3; i++) {
                    if (freeTablesSeven[i] == true && i == 0) {
                        printf("(%d) Endor\n",i+1);
                    }
                    else if (freeTablesSeven[i] == true && i == 1) {
                        printf("(%d) Naboo\n",i+1);
                    }
                    else if (freeTablesSeven[i] == true && i == 2) {
                        printf("(%d) Tatooine\n",i+1);
                    }
                }
                printf("Which table: ");
                scanf("%d",&tableChoice);

                if (freeTablesSeven[tableChoice-1] == true) {
                    freeTablesSeven[tableChoice-1] = false;
                    printf("Booking Successful\n");
                }
                else if (freeTablesSeven[tableChoice-1] == false) {
                    printf("Sorry, that table at that time is unavailable\n");
                }
            }

            else if (timeChoice == 9 && tableSpaceNine == true) { //SELECTS THE TIME AS 9PM
                printf("Free tables: ");
                for (int i = 0; i<3; i++) {
                    for (int i = 0; i<3; i++) {
                        if (freeTablesNine[i] == true && i == 0) {
                            printf("(%d) Endor\n",i+1);
                        }
                        else if (freeTablesNine[i] == true && i == 1) {
                            printf("(%d) Naboo\n",i+1);
                        }
                        else if (freeTablesNine[i] == true && i == 2) {
                            printf("(%d) Tatooine\n",i+1);
                        }
                    }
                }
                printf("Which table: ");
                scanf("%d",&tableChoice);


                if (freeTablesNine[tableChoice-1] == true) {
                    freeTablesNine[tableChoice-1] = false;
                    printf("Booking Successful\n");
                }
                else if (freeTablesNine[tableChoice-1] == false) {
                    printf("Sorry, that table at that time is unavailable");
                }
                else{printf("Sorry, you didn't enter an available time");}
            }



    }
    else {printf("Sorry no available tables :<");}
}
