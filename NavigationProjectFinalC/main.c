#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "user.c"
#include "pathfinder.c" 
#include "map.c"

#include "user.h"
#include "pathfinder.h"
#include "map.h"



int main()
{
   
Location locations[9] = {
    { {10,12},{12,9},"Home1",PRIVATE_PROPERTY},
    { {6,30},{32,6},"Bim",LOCAL_SHOP},
    { {6,60},{62,6},"Home2",PRIVATE_PROPERTY},
    { {16,24},{22,16},"Cinema",ENTERTAINMENT_PLACE},
    { {20,42},{42,19},"Hospital",CORPORATE_BUILDING},
    { {16,60},{62,16},"Home3",PRIVATE_PROPERTY},
    { {26,24},{22,26},"Hakmar",LOCAL_SHOP},
    { {26,54},{52,26},"Shopping Mall",SHOPPING_CENTER},
    { {26,60},{62,26},"Police",CORPORATE_BUILDING},
};

 Person people[] = { 
        {"Merve", "Demir"},
        {"Kerem", "Demir"},
        {"Rick", "Grimes"},
        {"Fatma", "Demir"},
    };
    size_t size = sizeof(people) / sizeof(people[0]);

    const char *filename = "people.txt";

    // Dosyaya yazma
    writePeopleToFile(filename, people, size);

    // Dosyadan okuma
    Person readPeople[size];
    
    printf("Person List:  \n\n");
    readPeopleFromFile(filename, readPeople, size);
    printf(" \n");

    
    deletePersonFromFile(filename, "Merve", "Demir");

    printf("Person List After Deletion:  \n\n");
    readPeopleFromFile(filename, people, sizeof(people) / sizeof(people[0]));
    

   printf(" \n");
   printf("Press 1 to start navigation program:");
   int startt;
   scanf("%d",&startt);
   
   system("cls");
   
   
    int loop = 1; // Döngüyü kontrol etmek için değişken
    while (loop) {
        system("cls");
        printf("WELCOME TO NAVIGATION SYSTEM \n");

        Location currentLocation = getLocationChoice(locations);
        system("cls");
        printf("WELCOME TO NAVIGATION SYSTEM \n");
        Location destination = getDestinationChoice(locations);

        system("cls");
        gotoxy(100, 2);
        printf("Current Location: %s\n", currentLocation.name);
        gotoxy(100, 4);
        printf("Destination: %s\n", destination.name);

        PrintMap();

        showLocation(currentLocation);
        showDestination(destination);

        gotoxy(100, 8);
        printf("Do you want to start traveling?\n ");
        gotoxy(100, 10);
        printf("To start press 1: ");
        int start;
        scanf("%d", &start);

        if (start == 1) {
            runAStarExample(currentLocation, destination);
        }

        // Kullanıcıdan devam etmek isteyip istemediğini sormak için döngü
        gotoxy(100, 10);
        printf("Press 'p' to stop, any other key to continue...\n");
        char choice = getch(); // Kullanıcının tuşa basmasını bekleyin
        if (choice == 'p' || choice == 'P') {
            loop = 0; // Döngüyü sonlandır
        }
    }

   

  gotoxy(1,40);

   return 0;
}

