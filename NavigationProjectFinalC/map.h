#ifndef MAP_H
#define MAP_H

#define SHAPE_SIZE 5

typedef struct Point {    
    int x;
    int y;
    
} Point;

typedef struct RectangPoints {
    Point lower_right_point;
    Point lower_left_point;
    Point upper_right_point;
    Point upper_left_point;
} Rectang;

typedef struct Line {
    Point p1;
    Point p2;
} Line;

typedef struct Shape {
     char *name;  // Şeklin adı
     char *lines[5];
}Shape;

typedef void (*DrawLineFunction)(Line*, Point, Point);

void drawShape( Shape *shape, int x, int y);
void gotoxy(int x, int y);
void PrintBorder(Rectang r);
void drawHorizontalLine(Line *line, Point spaceStart1, Point spaceStart2);
void drawVerticalLine(Line *line, Point spaceStart1, Point spaceStart2); 
void drawSpaceAt( Point *points, int size);
void PrintMap();

#endif