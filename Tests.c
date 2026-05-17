#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Globals.h"
#include "Globals.c"
#include "BookMeals.c"
#include "CheckIn.c"
#include "CheckOut.c"

void printUserStruct(User* userStruct) {
  printf("Name: %s, %s\n", userStruct->fName, userStruct->sName);
  printf("DOB: %s\n", userStruct->DOB);
  printf("BookingID: %s\n", userStruct->bookingID);
  printf("Child count: %d\n", userStruct->numChildren);
  printf("Adult count: %d\n", userStruct->numAdults);
  printf("Stay Length: %d\n", userStruct->stayLength);
  printf("dailyNewspaper: %d\n", userStruct->dailyNewspaper);
  printf("boardType: %d\n", userStruct->boardType);
  printf("Room Num: %d\n", userStruct->roomType);
}

void printBillStruct(struct Bill bill);

void printBillStruct(struct Bill bill) {
  printf("%f", bill.total);
  printf("%d", bill.daysStayed);
  printf("%d", bill.greaterThan65);
  for (int i = 0; i < 4; i++) {
    if (bill.subTotalCount[i] > 0) {
      for (int j = 0; j < bill.subTotalCount[i]; j++) {
        printf("%f", bill.subTotal[i]);
      }
    }
  }
}

int main(void) {
  User testUser, Guests[6];
  bool occupiedRooms[6] = {false, false, false, false, true, false};
  for(int i = 0; i<6; i++) {
      printf("%d", occupiedRooms[i]);
    }
  GetCheckInData(&testUser, &occupiedRooms);

  Guests[testUser.roomType - 1] = testUser;

  printUserStruct(&testUser);
  for(int i = 0; i < 6; i++) {
    printf("%d", occupiedRooms[i]);
  }
  for(int i = 0; i < 6; i++) {
    printUserStruct(&Guests[i]);
  }

  //TESTS BOOKMEALS.c
  char validBookingID[33] = "Sherwood56";   //need to be all added into the User users[6]
  GetMealBookingData(validBookingID);

  char invalidBookingID[33] = ""; //not in current users
  GetMealBookingData(invalidBookingID);

  char boundaryBookingID[33] = "SherwoodTheSigmaSkibidiBlueGri67";
  GetMealBookingData(boundaryBookingID);

  //TESTS CheckOut.c
  //There is no real invalid data aside from no data, which is not possible.
  printBillStruct(CalculateBill(&testUser));

  DisplayBill(&testUser);

  IsSenior(&testUser);
}

