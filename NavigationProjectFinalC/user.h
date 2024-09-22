#ifndef USER_H
#define USER_H

#include "map.h"


typedef enum LocationType {
    CORPORATE_BUILDING,
    ENTERTAINMENT_PLACE,
    PRIVATE_PROPERTY,
    SHOPPING_CENTER,
    LOCAL_SHOP,
    
} LocationType;

typedef struct Location {
    Point pointPath;
    Point pointDoor;
    char name[50];
    LocationType type;
}Location;


typedef struct Person {
    char name[50];
    char surname[50];
    
}Person;


Location getLocationChoice(Location locations[]);
Location getDestinationChoice(Location locations[]); 
void printLocations( Location locations[]);
void showLocation(Location location);
void showDestination(Location destination);
void writePeopleToFile(const char *filename, Person people[], size_t size);
void printPerson(const Person *person);
void readPeopleFromFile(const char *filename, Person people[], size_t size);
void deletePersonFromFile(const char *filename, const char *name, const char *surname);


 #endif
