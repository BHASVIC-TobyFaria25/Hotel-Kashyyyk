#pragma once

#ifndef GLOBAL_H
enum boardTypes;

enum rooms;

typedef struct UserData {
    char fName[30];
    char sName[30];
    int DOB[3];
    char bookingID[33];
    int numChildren;
    int numAdults;
    int numPeople;
    int stayLength;
    bool dailyNewspaper;
    int boardType;
    int roomType;
    char tableBooked[30];

}User;

#define GLOBAL_H




#endif //GLOBAL_H
