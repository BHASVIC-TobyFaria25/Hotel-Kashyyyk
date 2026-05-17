#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Globals.h"
#include "CheckOut.c"
#include "CheckIn.c"
#include "BookMeals.c"
#include "Cache.c"

int main(void) {
    //Variables to be passed as pointers to functions
    //NOT GLOBAL VARIABLES
    int freeRooms[6] = {0,0,0,1,0,1};
    int (*roomPtr)[6] = &freeRooms;
    bool freeTablesSeven[3]; //0: Endor, 1: Naboo, 2: Tatooine
    bool freeTablesNine[3];

    User users[6];
    User (*usersPtr)[6] = &users;
    User tempUser;


    Restore(&users, &freeTablesSeven, &freeTablesNine, &freeRooms);
    int input;
    while(true){
        printf("Please select an option: \n\t1-Check In\n\t2-Book meals \n\t3-Check out \n\t4-Reset Tables \n\t5-Quit program\n>");
        scanf("%d", &input); fflush(stdin);
        switch( input){
            case 1:
                printf("Check In: \n");
                GetCheckInData(&tempUser, roomPtr);
                users[tempUser.roomType - 1] = tempUser;
                break;
            case 2:
                printf("Book Meals\n");
                int uID = GetMealBookingData(usersPtr);
                if(uID != -1) {
                    ShowMealOptions(usersPtr[uID], freeTablesSeven, freeTablesNine);
                }
                break;
            case 3:
                printf("Check Out\n");
                int userID=0;

                printf("Please enter your room number:");
                scanf("%d", &userID);
                userID -= 1;



                if (((*usersPtr)[userID].stayLength > 0)) {
                    DisplayBill(&users[userID]);
                }
                else {
                    printf("Not a valid user.");
                }


                break;

            case 4:
                printf("Refresh tables\n");
                for(int i = 0; i<3; i++) {
                    freeTablesSeven[i] = true;
                }
            for(int i = 0; i<3; i++) {
                freeTablesNine[i] = true;
            }
                break;


            case 5:
                printf("Quit\n");
                break;
            default:
                printf("Not a valid option, sorry!\n");
                break;
        }

        //cache data
        Cache(users, freeTablesSeven, freeTablesNine, freeRooms);

    }

    return 0;
}
