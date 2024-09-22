#ifndef LOCATION_H
#define LOCATION_H

using namespace std;
#include <string>
#include <iostream>
#include "map.hpp"

enum class LocationType {
    CORPORATE_BUILDING,
    ENTERTAINMENT_PLACE,
    PRIVATE_PROPERTY,
    SHOPPING_CENTER,
    LOCAL_SHOP,
};

class Location {
private:
    Point pointPath;
    Point pointDoor;
    string name;
    LocationType type;

public:
    Location();  // default
    Location(Point pointPath,  Point pointDoor, const string &name, LocationType type);
    
    // Setter fonksiyonları
    void setPointPath(const Point& path);
    void setPointDoor(const Point& door);
    void setName(const string &newName);
    void setType(LocationType t);

    // Getter fonksiyonları
    Point getPointPath() const;
    Point getPointDoor() const;
    string getName() const;
    LocationType getType() const;

    // Diğer fonksiyonlar
    static Location getLocationChoice(Location locations[]);
    static Location getDestinationChoice(Location locations[]);
    static void printLocations(Location locations[]);
    void showLocation(const Location& destination) const;
    void showDestination(const Location& destination) const;
};

 #endif