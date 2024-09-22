#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "pathfinder.h" 


void printLocations( Location locations[]) {
    printf("Lokasyonlar:\n");
    for (size_t i = 0; i < 9; ++i) {
        printf("%d-> %s\n", i + 1, locations[i].name);
    }
}


void showLocation(Location location){
      gotoxy(location.pointDoor.x,location.pointDoor.y);
      char kirmizi_o = 'o';
      printf("\x1b[31m%c\x1b[0m\n", kirmizi_o);
   } 

void showDestination(Location destination){
      gotoxy(destination.pointDoor.x,destination.pointDoor.y);
      char mavi_o = 'o';
      printf("\x1b[34m%c\x1b[0m\n", mavi_o);  // Mavi renk
   }   

   
Location getLocationChoice(Location locations[]) {
    size_t choice;
    do {
        printLocations(locations);
        printf("Hangi konumdasiniz? (1-9): ");
        scanf("%zu", &choice);

        if (choice < 1 || choice > 9) {
            printf("Gecersiz secim. Lutfen 1 ile 9 arasinda bir sayi girin.\n");
        }

    } while (choice < 1 || choice > 9);

    // Seçilen konumu döndür
    return locations[choice - 1];
}

Location getDestinationChoice(Location locations[]) {
    size_t choice;
    do {
        printLocations(locations);
        printf("Hangi konuma gitmek istersiniz? (1-9): ");
        scanf("%zu", &choice);

        if (choice < 1 || choice > 9) {
            printf("Gecersiz secim. Lutfen 1 ile 9 arasinda bir sayi girin.\n");
        }

    } while (choice < 1 || choice > 9);

    // Seçilen konumu döndür
    return locations[choice - 1];
}


// Dosyaya personları yazma
void writePeopleToFile(const char *filename, Person people[], size_t size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Dosya açma hatası");
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        fprintf(file, "%s %s\n", people[i].name, people[i].surname);
    }

    fclose(file);
}

void printPerson(const Person *person) {
    printf("Name: %s, Surname: %s\n", person->name, person->surname);
}


// Dosyadan personları okuma
void readPeopleFromFile(const char *filename, Person people[], size_t size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Dosya açma hatası");
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        if (fscanf(file, "%s %s", people[i].name, people[i].surname) != 2) {
            break; // Dosyanın sonuna ulaşıldığında veya hata olduğunda döngüyü sonlandır
        }

        // Okunan değerleri ekrana yazdır
        printPerson(&people[i]);
    }

    fclose(file);
}

void deletePersonFromFile(const char *filename, const char *name, const char *surname) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Dosya açma hatası");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Geçici dosya oluşturma hatası");
        fclose(file);
        return;
    }

    Person currentPerson;

    while (fscanf(file, "%s %s", currentPerson.name, currentPerson.surname) == 2) {
        // Silinecek kişiyi bulma
        if (strcmp(currentPerson.name, name) == 0 && strcmp(currentPerson.surname, surname) == 0) {
            continue; // Kişiyi sil ve devam et
        }

        // Geçici dosyaya yazma
        fprintf(tempFile, "%s %s\n", currentPerson.name, currentPerson.surname);
    }

    fclose(file);
    fclose(tempFile);

    // Eski dosyayı silme ve geçici dosyayı yeni dosya olarak adlandırma
    remove(filename);
    rename("temp.txt", filename);
}

