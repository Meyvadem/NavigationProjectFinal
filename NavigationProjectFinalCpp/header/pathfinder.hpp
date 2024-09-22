#ifndef PATHFINDER_H
#define PATHFINDER_H

#define MY_ABS(x) (((x) < 0) ? (-(x)) : (x))

#include "location.hpp"

#define ROWS 29
#define COLS 83

class Node {
private:
    Point point; // Noktanın konumu
    int f, g, h; // A* algoritması için gerekli değerler
    Node* parent; // Bir önceki düğümün referansı

public:
   
    Node(Point p, int f_val, int g_val, int h_val, Node* parent_node);
     
    friend Node* createNode(Point point);
       
    // Getter and setter methods
    Point getPoint() const;
    int getF() const;
    int getG() const;
    int getH() const;
    Node* getParent() const;
  
    void setPoint(Point p);
    void setF(int f_val);
    void setG(int g_val);
    void setH(int h_val);
    void setParent(Node* parent_node);
};

extern int grid[ROWS][COLS];

int isValid(int x, int y);
int isDestination(int x, int y, Node* dest);
int calculateHValue(int x, int y, Node* dest);
Node* aStarSearch(int grid[ROWS][COLS],Node* start, Node* dest);
void printColoredPath(Node* path, int grid[ROWS][COLS]);
void drawCharacter(Point character);
void clearCharacter(Point character);
void runAStarExample(Location currentLoc, Location destination);

#endif
