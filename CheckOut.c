#include "Globals.c"
#include <stdio.h>
#include <time.h>

const float NEWSPAPER_COST = 5.5f;

float IsSenior(User* ptr);

struct Bill CalculateBill(User* userData);

void FreeRoom(User* userData,int (*occupiedRooms)[6]);

void DisplayBill(User* userData);
struct Bill CalculateBill(User* userData);

struct Bill {
    float total;
    int subTotalCount[4];//Stores the count of each individual section, e.g. the number of children.
    int daysStayed;
    bool greaterThan65;
    float subTotal[400];
};

void DisplayBill(User* userData) {

    struct Bill bill = CalculateBill(userData);
    puts(userData->bookingID);
    printf("Total:    %.*fGBP \n",2,bill.total);
    printf("===========Subtotal===========\n");
    int index = 0;
    //SubTotalCount stores the count of each individual item, which means that we can iterate over it,
    //then iterating over the amount of items in that to display all items in the subTotal list.
    for (int i = 0; i < 4; i++) {
        if (bill.subTotalCount[i] > 0) {
            for (int j = 0; j < bill.subTotalCount[i]; j++) {
                bool flag = false;//flag to determine if values are multiplied by daysStayed or not
                //we can then do a switch case based on the value of i (which indicates what type of item we have) and display an appropriate message.
                switch (i) {
                    case 0://children
                        printf(" Child Board x %d days: ", bill.daysStayed);
                        flag = true;
                        break;
                    case 1://adults
                        printf(" Adult Board x %d days: ", bill.daysStayed);
                        flag = true;
                        break;
                    case 2://room price
                        printf(" Room Cost x %d days: ", bill.daysStayed);
                        flag = true;
                        break;
                    case 3://newspaper
                        printf(" Newspaper: ");
                        break;

                    default:
                        printf("error");
                        break;
                }
                if (flag == true) {
                    printf("%.*fGBP\n",2, bill.subTotal[index]*bill.daysStayed);
                }
                else {
                    printf("%.*fGBP\n",2, bill.subTotal[index]);
                }
                index++;
            }

        }

    }

}

struct Bill CalculateBill(User* userData) {
    struct Bill bill;
    //subtotals
    int index = 0;



    //children
    bill.subTotalCount[0] = userData->numChildren;
    for (index = 0; index < userData->numChildren; index++) {

        bill.subTotal[index] = (userData->boardType*0.5);
    }


    //adults
    bill.subTotalCount[1] = userData->numAdults;

    for (int i=0; i < userData->numAdults; i++) {
        index++;
        bill.subTotal[index] = (userData->boardType);
    }

    //room price
    bill.subTotalCount[2] = 1;


    bill.subTotal[index] = userData->roomType*IsSenior(userData);
    if (IsSenior(userData) == 0.9f) {
        bill.greaterThan65 = true;
    }else{bill.greaterThan65 = false;}
    //newspaper
    bill.subTotalCount[3] = 1;
    index++;
    bill.subTotal[index] = NEWSPAPER_COST;




    //number of days stayed for
    bill.daysStayed = userData->stayLength;



    //calculating total
    bill.total = 0;
    bill.total += (userData->boardType*0.5*userData->numChildren);
    bill.total += (userData->boardType*userData->numAdults);

    bill.total += (userData->roomType*IsSenior(userData));
    bill.total *= userData->stayLength;
    if (userData->dailyNewspaper == true) {
        bill.total += NEWSPAPER_COST;
    }







    return bill;
}

void FreeRoom(User* userData,  int (*occupiedRooms)[6]) {
  (*occupiedRooms)[userData->roomType + 1] = false;
}

float IsSenior(User* ptr) {
    time_t now = time(NULL);
    int date[3];
    char nowstr[11];


    strftime(nowstr, sizeof(nowstr), "%d/%m/%Y", localtime(&now));

    sscanf(nowstr, "%d/%d/%d", &date[0], &date[1], &date[2]);
    date[2] -= 65;
    if(date[2] < ptr->DOB[2]) {
        return 1.0f;
    }
    if(date[1] < ptr->DOB[1]) {
        return 1;
    }
    if(date[0] < ptr->DOB[0]) {
        return 1.0f;
    }

    return 0.9f;//discount is 10%
}