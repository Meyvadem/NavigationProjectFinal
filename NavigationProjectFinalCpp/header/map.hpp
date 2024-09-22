#ifndef MAP_H
#define MAP_H

#define SHAPE_SIZE 5

using namespace std;
#include <iostream>
#include <initializer_list>
#include <string>


class Point {

  public:

    int x;
    int y;

    // Constructor
    Point(int x, int y);

    int& getX() ;
    int& getY() ;
    void setX(int newX);
    void setY(int newY);

};

class RectangPoints {
private:
    Point lower_right_point;
    Point lower_left_point;
    Point upper_right_point;
    Point upper_left_point;

public:
   
    // Constructor
    RectangPoints(Point lower_right_point, Point lower_left_point, Point upper_right_point, Point upper_left_point);

    Point& getLowerRightPoint() const;
    Point& getLowerLeftPoint() const;
    Point& getUpperRightPoint() const;
    Point& getUpperLeftPoint() const;

    void setLowerRightPoint(const Point& point);
    void setLowerLeftPoint(const Point& point);
    void setUpperRightPoint(const Point& point);
    void setUpperLeftPoint(const Point& point);

};

class Line {
private:
    Point p1;
    Point p2;

public:

// Constructor
    Line(Point p1, Point p2);

    Point& getP1() const;
    Point& getP2() const;
    void setP1(Point p1);
    void setP2(Point p2);
};

class Shape {
private:
    string name; 
    string lines[SHAPE_SIZE]; 

public:
    // Constructor
    Shape(const string& name, initializer_list<string> linesList);

    const string& getName() const;
    const string& getLine(size_t index) const;
    void setName(const string& newName);
    void setLine(size_t index, const string& newLine);
};


    void drawShape(const Shape& shape, int x, int y);
    void gotoxy(int x, int y);
    void printBorder(const RectangPoints& r);
    void drawHorizontalLine(const Line& line,  Point& spaceStart1,  Point& spaceStart2);
    void drawVerticalLine(const Line& line,  Point& spaceStart1,  Point& spaceStart2);
    void drawSpaceAt(const Point* points, int size);
    void printMap();



#endif
