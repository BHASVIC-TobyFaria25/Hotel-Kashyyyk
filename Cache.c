#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Globals.h"
//This file is to cache the data and provide restoration functions in the event of the system crashing.

//Function caches all user data, freeRooms data and freeTables dat
void Cache(User Users[6], bool freeTablesSeven[3], bool freeTablesNine[3], int freeRooms[6]) {
    FILE *cache = fopen("Cache.txt", "w");
    if(cache == NULL) {
        //file is missing
        printf("Error caching data, file not found");
        return;
    }
    //'¦' is used as it is a very rare character and therefore unlikely the user will type it.
    //'~' Specifies user data
    // '_' specifies room data
    // '`' (backtick) specifies table data


    for(int i = 0; i<6; i++) {
        //Caches each users data, then starts a new line.
        if (sizeof(Users)/sizeof(Users[i]) != 0) {
            fprintf(cache, "~%s¦%s¦%d/%d/%d¦%s¦%d¦%d¦%d¦%d¦%d¦%d¦%d¦%s", Users[i].fName, Users[i].sName, Users[i].DOB[0], Users[i].DOB[1], Users[i].DOB[2], Users[i].bookingID, Users[i].numChildren, Users[i].numAdults, Users[i].numPeople, Users[i].stayLength, Users[i].dailyNewspaper, Users[i].boardType, Users[i].roomType, Users[i].tableBooked);
        }
    }
    fprintf(cache, "\n");

    for(int i = 0; i<3; i++) {
        if (sizeof(freeTablesSeven)/sizeof(freeTablesSeven[i]) != 0) {
            //Caches each users data, then starts a new line.
            fprintf(cache, "_%d",freeTablesSeven[i]);
        }
    }

    fprintf(cache, "\n");
    for(int i = 0; i<3; i++) {
        if (sizeof(freeTablesSeven)/sizeof(freeTablesSeven[i]) != 0) {
            //Caches each users data, then starts a new line.
            fprintf(cache, "_%d",freeTablesNine[i]);
        }
    }

    fprintf(cache, "\n");
    for(int i = 0; i<3; i++) {
        if (sizeof(freeTablesSeven)/sizeof(freeTablesSeven[i]) != 0) {
            //Caches each users data, then starts a new line.
            fprintf(cache, "'%d", freeRooms[i]);
        }
    }
    fclose(cache);

}



// safe copy helper
static void safe_copy(char *dest, const char *src, size_t size){
    if (!src) {
        dest[0] = '\0';
        return;
    }
    strncpy(dest, src, size - 1);
    dest[size - 1] = '\0';
}

//reutrning multiple datatypes in c is annoying so pass by reference
void Restore(User (*UserData)[6], bool (*freeTablesSeven)[3],bool (*freeTablesNine)[3], int (*freeRooms)[6]){

    FILE* cache = fopen("Cache.txt", "r");
    if (!cache) {
        printf("Error restoring data: Cache.txt not found.\n");
        return;
    }

    char line[512];

    // users
    for (int i = 0; i < 6; i++) {
        if (!fgets(line, sizeof(line), cache)) break;

        char *ptr = line;
        if (*ptr == '~') ptr++;

        char buffer[512];
        safe_copy(buffer, ptr, sizeof(buffer));

        char *token = strtok(buffer, "¦");
        if (!token) continue;
        safe_copy((*UserData)[i].fName, token, sizeof((*UserData)[i].fName));

        token = strtok(NULL, "¦");
        safe_copy((*UserData)[i].sName, token, sizeof((*UserData)[i].sName));

        token = strtok(NULL, "¦");
        if (token)
            sscanf(token, "%d/%d/%d",
                   &UserData[i]->DOB[0],
                   &UserData[i]->DOB[1],
                   &UserData[i]->DOB[2]);

        token = strtok(NULL, "¦");
        safe_copy((*UserData)[i].bookingID, token, sizeof((*UserData)[i].bookingID));

        token = strtok(NULL, "¦"); (*UserData)[i].numChildren    = token ? atoi(token) : 0;
        token = strtok(NULL, "¦"); (*UserData)[i].numAdults      = token ? atoi(token) : 0;
        token = strtok(NULL, "¦"); (*UserData)[i].numPeople      = token ? atoi(token) : 0;
        token = strtok(NULL, "¦"); (*UserData)[i].stayLength     = token ? atoi(token) : 0;
        token = strtok(NULL, "¦"); (*UserData)[i].dailyNewspaper = token ? atoi(token) : 0;
        token = strtok(NULL, "¦"); (*UserData)[i].boardType      = token ? atoi(token) : 0;
        token = strtok(NULL, "¦"); (*UserData)[i].roomType       = token ? atoi(token) : 0;

        token = strtok(NULL, "¦\n");
        safe_copy((*UserData)[i].tableBooked, token, sizeof((*UserData)[i].tableBooked));
    }

    // seven oclock tables
    if (fgets(line, sizeof(line), cache)) {
        char *ptr = line;
        for (int i = 0; i < 3; i++) {
            if (*ptr == '_') ptr++;
            *freeTablesSeven[i] = (atoi(ptr) != 0);
            ptr = strchr(ptr, '_');
            if (!ptr) break;
        }
    }

    // nine o clock tables
    if (fgets(line, sizeof(line), cache)) {
        char *ptr = line;
        for (int i = 0; i < 3; i++) {
            if (*ptr == '_') ptr++;
            *freeTablesNine[i] = (atoi(ptr) != 0);
            ptr = strchr(ptr, '_');
            if (!ptr) break;
        }
    }

    // freeRooms
    if (fgets(line, sizeof(line), cache)) {
        char *ptr = line;
        for (int i = 0; i < 6; i++) {
            if (*ptr == '\'') ptr++;
            *freeRooms[i] = (atoi(ptr) != 0);
            ptr = strchr(ptr, '\'');
            if (!ptr) break;
        }
    }

    fclose(cache);
}
