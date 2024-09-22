#include "../header/location.hpp"
#include <iostream>

using namespace std;



Location::Location() : pointPath(0, 0), pointDoor(0, 0), name(""), type(LocationType::CORPORATE_BUILDING) {}


Location::Location(Point path, Point door, const string& n, LocationType t)
    : pointPath(path), pointDoor(door), name(n), type(t) {
   
}

// Setter functions 
void Location::setPointPath(const Point& path) {
    pointPath = path;
}

void Location::setPointDoor(const Point& door) {
    pointDoor = door;
}

void Location::setName(const string& newName) {
    name = newName;
}

void Location::setType(LocationType t) {
    type = t;
}

// Getter functions 
Point Location::getPointPath() const {
    return pointPath;
}

Point Location::getPointDoor() const {
    return pointDoor;
}

std::string Location::getName() const {
    return name;
}

LocationType Location::getType() const {
    return type;
}


void printLocations(Location locations[]) {
    std::cout << "\nLokasyonlar:" << std::endl;
    for (size_t i = 0; i < 9; ++i) {
        std::cout << i + 1 << "-> " << locations[i].getName() << std::endl;
    }
}

void showLocation(Location location) {
    gotoxy(location.getPointDoor().getX(), location.getPointDoor().getY());
    std::cout << "\x1b[31m" << 'o' << "\x1b[0m" << std::endl; // Kırmızı renk
}

void showDestination(Location destination) {
    gotoxy(destination.getPointDoor().getX(), destination.getPointDoor().getY());
    std::cout << "\x1b[34m" << 'o' << "\x1b[0m" << std::endl; // Mavi renk
}

Location getLocationChoice(Location locations[]) {
    size_t choice;
    do {
        printLocations(locations);
        std::cout << "Hangi konumdasiniz? (1-9): ";
        std::cin >> choice;

        if (choice < 1 || choice > 9) {
            std::cout << "Gecersiz secim. Lutfen 1 ile 9 arasinda bir sayi girin." << std::endl;
        }

    } while (choice < 1 || choice > 9);

    // Seçilen konumu döndür
    return locations[choice - 1];
}

Location getDestinationChoice(Location locations[]) {
    size_t choice;
    do {
        printLocations(locations);
        std::cout << "Hangi konuma gitmek istersiniz? (1-9): ";
        std::cin >> choice;

        if (choice < 1 || choice > 9) {
            std::cout << "Gecersiz secim. Lutfen 1 ile 9 arasinda bir sayi girin." << std::endl;
        }

    } while (choice < 1 || choice > 9);

    // Seçilen konumu döndür
    return locations[choice - 1];
}

