#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* 
  i hope you like this code!!! 🤪 

  please ignore any // {{{ // }}} things - they're there so vim folds lines properly.
*/
int IsOldEnough(User* ptr);

int IsOldEnough(User* ptr) {
  time_t now = time(NULL);
  int date[3];
  char nowstr[11];


  strftime(nowstr, sizeof(nowstr), "%d/%m/%Y", localtime(&now));

  sscanf(nowstr, "%d/%d/%d", &date[0], &date[1], &date[2]);
  date[2] -= 18;
  if(date[2] < ptr->DOB[2]) {
    return 0;
  }
  if(date[1] < ptr->DOB[1]) {
    return 0;
  }
  if(date[0] < ptr->DOB[0]) {
    return 0;
  }

  return 1;
}


void ShowRoomOptions(User* ptr, int (*occupiedRooms)[6]) {// {{{
  bool flag = false;
  printf("Room Rates (per night)\n\n");
  printf("Room | Cost\n");
  printf("1    | %-3d GBP\n", room1);
  printf("3    | %-3d GBP\n", room3);
  printf("2    | %-3d GBP\n", room2);
  printf("4    | %-3d GBP\n", room4);
  printf("5    | %-3d GBP\n", room5);
  printf("6    | %-3d GBP\n", room6);

  printf("Board Rates (per night)\n\n");
  printf("Type | Price \n");
  printf("Full | %d GBP  \n", fullBoard);
  printf("Half | %d GBP  \n", halfBoard);
  printf("B&B  | %d GBP  \n", bedAndBreakfast);

  do { 
    printf("Please enter your preferred room: ");
    int roomChoice;
    flag = false;
    scanf("%d", &roomChoice); fflush(stdin);

    switch (roomChoice) {
      case 1:
        if((*occupiedRooms)[roomChoice - 1] == 0) {ptr -> roomType = roomChoice;(*occupiedRooms)[roomChoice - 1] = 1; flag = true;}
        else {printf("That room is occupied; please try another.\n");}
        break;
      case 2:
        if((*occupiedRooms)[roomChoice - 1] == 0) {ptr -> roomType = roomChoice;(*occupiedRooms)[roomChoice - 1] = 1; flag = true;}
        else {printf("That room is occupied; please try another.\n");}
        break;
      case 3:
        if((*occupiedRooms)[roomChoice - 1] == 0) {ptr -> roomType = roomChoice;(*occupiedRooms)[roomChoice - 1] = 1; flag = true;}
        else {printf("That room is occupied; please try another.\n");}
        break;
      case 4:
        if((*occupiedRooms)[roomChoice - 1] == 0) {ptr -> roomType = roomChoice;(*occupiedRooms)[roomChoice - 1] = 1; flag = true;}
        else {printf("That room is occupied; please try another.\n");}
        break;
      case 5:
        if((*occupiedRooms)[roomChoice - 1] == 0) {ptr -> roomType = roomChoice;(*occupiedRooms)[roomChoice - 1] = 1; flag = true;}
        else {printf("That room is occupied; please try another.\n");}
        break;
      case 6:
        if((*occupiedRooms)[roomChoice - 1] == 0) {ptr -> roomType = roomChoice;(*occupiedRooms)[roomChoice - 1] = true; flag = true;}
        else {printf("That room is occupied; please try another.\n");}
        break;
      default:
        printf("That wasn't a valid room; try again! ");
        break;
      }
  }while(flag == false);

  flag = false;

  do {
    printf("Please enter your chosen board type:\n a) Full Board\n b) Half Board\n c) Bed and Breakfast\n\n> ");
    char boardType;
    scanf("%c", &boardType); fflush(stdin);

    switch (boardType) {
    case 'a':
      ptr -> boardType = fullBoard; flag = true;
      break;
    case 'b':
      ptr -> boardType = halfBoard; flag = true;
      break;
    case 'c':
      ptr -> boardType = bedAndBreakfast; flag = true;
      break;
    default:
      printf("That wasn't a valid option, try again!");
      break;
    }
  }while (flag == false);
}// }}}

void GenerateBookingID(User* ptr) {// {{{
  srand(time(NULL));
  int randomNumber = rand()%99;
  char tempSurname[30];
  strcpy(tempSurname, ptr->sName);
  char randomString[3];
  sprintf(randomString, "%d", randomNumber);

  strcpy(ptr -> bookingID, strcat(tempSurname, randomString));

}// }}}

void GetCheckInData(User* ptr, int (*occupiedRooms)[6]) {// {{{
  char buf[11];
  int day, month, year;

  ptr->DOB[0] = ptr->DOB[1] = ptr->DOB[2] = 0;

  while (1) {
    printf("Please enter your date of birth in the format DD/MM/YYYY: ");

    if (!fgets(buf, sizeof(buf), stdin)) {
      printf("Input error. Try again.\n");
      continue;
    }
    fflush(stdin);
    if (sscanf(buf, "%d/%d/%d", &day, &month, &year) == 3) {
      ptr->DOB[0] = day;
      ptr->DOB[1] = month;
      ptr->DOB[2] = year;
      break;
    } else {
      printf("Invalid format. Please try again.\n");
    }
  }
  fflush(stdin);
  if (IsOldEnough(ptr) == 1) {
    fflush(stdin);
    do {
      printf("\nPlease enter your first name: ");
      fgets(ptr -> fName, sizeof(ptr -> fName), stdin); fflush(stdin);
    }while(strcmp(ptr -> fName, "") == 0 || strcmp(ptr -> fName, " ") == 0);

    do{
        printf("\nPlease enter your surname: ");
        fgets(ptr->sName, sizeof(ptr->sName), stdin); fflush(stdin);
        ptr->sName[strlen(ptr->sName) - 1] = '\0';
    }while(strcmp(ptr -> sName, "") == 0 || strcmp(ptr -> sName, " ") == 0);

    total:
    printf("\nPlease enter the total number of people staying with you: ");
    scanf("%d", &ptr -> numPeople); fflush(stdin);
    if(ptr -> numPeople < 1 || ptr -> numPeople > 10) {printf("You can't have more than ten or fewer than 1 person! Try again! \n"); goto total;}
    
    u16s:
    ptr -> numChildren = 0;
    printf("\nPlease enter the number of under-16s staying with you: ");
    scanf("%d", &ptr -> numChildren); fflush(stdin);
    if(ptr -> numChildren < 0 || ptr -> numChildren > ptr -> numPeople) {printf("You can't have that many children! \n"); goto u16s;}

    adults:
    ptr -> numAdults = 0;
    printf("\nPlease enter the number of adults staying with you: ");
    scanf("%d", &ptr -> numAdults); fflush(stdin);
    if(ptr->numAdults < 1 || (ptr -> numAdults + ptr -> numChildren) > ptr -> numPeople || ptr -> numAdults + ptr -> numChildren < ptr -> numPeople) {printf("You need at least one adult and cannot have fewer or more total people than you booked for. \n"); goto adults;}

    stay:

    printf("\nPlease enter the length of your stay: ");
    scanf("%d", &ptr -> stayLength); fflush(stdin);
    if(ptr -> stayLength < 1 || ptr -> stayLength > 15) {printf("You inputted an amount of days that was either invalid (i.e. < 1) or that was too high. Please try again or speak to the front desk."); goto stay;}

    char temp; 
    do {
    printf("\nWould you like a daily newspaper? (Y/N): ");
    scanf("%c", &temp);
    if(toupper(temp) == 'Y'){ptr -> dailyNewspaper = true;}
    else if(toupper(temp) == 'N'){ptr -> dailyNewspaper = false;}
    else {printf("Invalid input; please try again: \n");}
    fflush(stdin);
    }while(toupper(temp) != 'Y' && toupper(temp) != 'N');

    ShowRoomOptions(ptr, occupiedRooms);
  
    GenerateBookingID(ptr);
    printf("Your name is: %s %s\n", ptr -> fName, ptr -> sName);
    printf("Your booking ID is: %s\n" ,ptr -> bookingID);
  }
  else {
    printf("Sorry, you must be 18 or older to book a room!\n\n\n");
  }
}// }}}
