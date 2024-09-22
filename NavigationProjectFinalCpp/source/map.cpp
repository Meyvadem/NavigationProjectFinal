#include "../header/map.hpp"
#include <windows.h>
#include <iostream>

using namespace std;

// Implementations for Point class

Point::Point(int x, int y) : x(x), y(y) {}

int& Point::getX()  {
    return x;
}

int& Point::getY()  {
    return y;
}

void Point::setX(int newX) {
    x = newX;
}

void Point::setY(int newY) {
    y = newY;
}

// Implementations for RectangPoints class

RectangPoints::RectangPoints(Point lower_right_point, Point lower_left_point, Point upper_right_point, Point upper_left_point)
    : lower_right_point(lower_right_point), lower_left_point(lower_left_point), upper_right_point(upper_right_point), upper_left_point(upper_left_point) {}

Point& RectangPoints::getLowerRightPoint() const {
    return const_cast<Point&>(lower_right_point);
}

Point& RectangPoints::getLowerLeftPoint() const {
    return const_cast<Point&>(lower_left_point);
}

Point& RectangPoints::getUpperRightPoint() const {
    return const_cast<Point&>(upper_right_point);
}

Point& RectangPoints::getUpperLeftPoint() const {
    return const_cast<Point&>(upper_left_point);
}



void RectangPoints::setLowerRightPoint(const Point& point) {
    lower_right_point = point;
}

void RectangPoints::setLowerLeftPoint(const Point& point) {
    lower_left_point = point;
}

void RectangPoints::setUpperRightPoint(const Point& point) {
    upper_right_point = point;
}

void RectangPoints::setUpperLeftPoint(const Point& point) {
    upper_left_point = point;
}

// Implementations for Line class

Line::Line(Point p1, Point p2) : p1(p1), p2(p2) {}

Point& Line::getP1() const {
    return const_cast<Point&>(p1);
}

Point& Line::getP2() const {
    return const_cast<Point&>(p2);
}


void Line::setP1(Point newP1) {
    p1 = newP1;
}

void Line::setP2(Point newP2) {
    p2 = newP2;
}



// Implementations for Shape class

Shape::Shape(const string& name, initializer_list<string> linesList) {
    this->name = name;
    int i = 0;
    for (const auto& line : linesList) {
        this->lines[i++] = line;
    }
}


const string& Shape::getName() const {
    return name;
}

const string& Shape::getLine(size_t index) const {
    return lines[index];
}

void Shape::setName(const string& newName) {
    name = newName;
}

void Shape::setLine(size_t index, const string& newLine) {
    lines[index] = newLine;
}


// Implementations for other functions

void drawShape(const Shape& shape, int x, int y) {
    std::cout << "\033[" << y - 1 << ";" << x << "H" << shape.getName() << std::endl;

    for (int i = 0; i < SHAPE_SIZE; ++i) {
        std::cout << "\033[" << y + i << ";" << x << "H" << shape.getLine(i) << std::endl;
    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printBorder(const RectangPoints& r) {
    for (int i = r.getLowerLeftPoint().getX(); i <= r.getLowerRightPoint().getX(); ++i) {
        gotoxy(i, r.getUpperLeftPoint().getY());   // first line
        std::cout << "_";

        gotoxy(i, r.getLowerLeftPoint().getY());    // last line
        std::cout << "_";
    }

    for (int i = r.getUpperLeftPoint().getY() + 1; i <= r.getLowerLeftPoint().getY(); ++i) {
        gotoxy(r.getUpperLeftPoint().getX() - 1, i);    // First column
        std::cout << "|";

        gotoxy(r.getUpperRightPoint().getX() + 1, i);    // Last column
        std::cout << "|";
    }

    std::cout << "\n \n \n \n \n \n \n ";
}


void drawHorizontalLine(const Line& line,  Point& spaceStart1,  Point& spaceStart2) {
    if (line.getP1().getY() != line.getP2().getY()) {
        gotoxy(100, 1);
        std::cout << "Y noktalari ayni olmadigindan x eksenine paralel dogru cizilemez." << std::endl;
        return;
    }

    int startX = (line.getP1().getX() < line.getP2().getX()) ? line.getP1().getX() : line.getP2().getX();
    int endX = (line.getP1().getX() < line.getP2().getX()) ? line.getP2().getX() : line.getP1().getX();

    for (int i = 0; i < 6; i++) {
        for (int j = startX; j <= endX; j++) {
            gotoxy(j, line.getP1().getY());

            if (j == spaceStart1.getX() || j == spaceStart2.getX()) {
                j = j + 10;
            } else {
                std::cout << "_";
            }
        }

        // Her iki durumda da y koordinatını güncelle
        const_cast<Line&>(line).setP1(Point(line.getP1().getX(), (i % 2 == 0) ? line.getP1().getY() + 7 : line.getP1().getY() + 3));
    }
}


void drawVerticalLine(const Line& line,  Point& spaceStart1,  Point& spaceStart2) {
    if (line.getP1().getX() != line.getP2().getX()) {
        gotoxy(100, 1);
        std::cout << "X noktalari ayni olmadigindan y eksenine paralel dogru cizilemez." << std::endl;
        return;
    }

    int startY = (line.getP1().getY() < line.getP2().getY()) ? line.getP1().getY() : line.getP2().getY();
    int endY = (line.getP1().getY() < line.getP2().getY()) ? line.getP2().getY() : line.getP1().getY();

    for (int i = 0; i < 6; i++) {
        for (int j = startY; j <= endY; j++) {
            gotoxy(line.getP1().getX(), j);

            if (j == spaceStart1.getY() || j == spaceStart2.getY()) {
                j = j + 2;
            } else {
                std::cout << "|";
            }
        }

        // Her iki durumda da x koordinatını güncelle
        const_cast<Line&>(line).setP1(Point((i % 2 == 0) ? line.getP1().getX() + 20 : line.getP1().getX() + 10, line.getP1().getY()));
    }
}


void drawSpaceAt( Point* points, int size) {
    for (int i = 0; i < size; ++i) {
        gotoxy(points[i].getX(), points[i].getY());
        std::cout << " ";
    }
}


void printMap() {
     Shape shapes[] = {
        Shape("Home1", { "  /\\\\", " /--\\\\", "/----\\\\", "|____||","" }),
        Shape("Bim Market", { "  /\\\\", " /--\\\\", " |___||", "","" }),
        Shape("Home2",{ "  /\\\\", " /--\\\\", "/----\\\\", "|____||",""  }),
        Shape("Cinema", { "   /\\\\","  /--\\\\", " /----\\\\", "/------\\\\", "|______||" }),
        Shape("Hospital", {"  /\\\\\\", " /--\\\\\\", "/----\\\\\\", "|_____||","|_____||" }),
        Shape("Home3", { "  /\\\\", " /--\\\\", "/----\\\\", "|____||",""  }),
        Shape("Hakmar", { "  /\\\\", " /--\\\\", " |___||", "","" }),
        Shape("Shopping", { "  /\\\\", " /--\\\\", "/----\\\\", "|____||","|____||"  }),
        Shape("Police", { "  /\\\\", " /--\\\\", "/----\\\\", "|    ||", "|____||" }),
    };
  

    // Border points
    Point upper_left_p = {1, 1};  
    Point upper_right_p = {83, 1};
    Point lower_left_p = {1, 30};
    Point lower_right_p = {83, 30};

    // Houses' door points
    Point point[] = {{32,6},{62,6},{62,16},{62,26},{52,26},{22,26},{22,16},{11,9},{12,9},{13,9},{41,19},{42,19},{43,19}};

    // Border
    RectangPoints rtg = {lower_right_p, lower_left_p, upper_right_p, upper_left_p};

    // Print Horizontal and Vertical Lines
    Point pH1 = {3,2}, pH2 = {81,2};
    Point pSpaceH3 = {22,2}, pSpaceH4 = {52,2};
    Line rH1 = {pH1,pH2};
    drawHorizontalLine(rH1, pSpaceH3, pSpaceH4);

    Point pV1 = {2,3}, pV2 = {2,29};
    Point pSpaceV3 = {2,10}, pSpaceV4 = {2,20};
    Line rV1 = {pV1,pV2};
    drawVerticalLine(rV1, pSpaceV3, pSpaceV4);

    drawSpaceAt(point, sizeof(point) / sizeof(point[0]));

    drawShape(shapes[0], 10, 5); // İlk şekil, konum (5, 5)
    drawShape(shapes[1], 39, 5); // İkinci şekil, konum (15, 5)
    drawShape(shapes[2], 70, 5); // Üçüncü şekil, konum (5, 15)
    drawShape(shapes[3], 10, 15); // Dördüncü şekil, konum (15, 15)
    drawShape(shapes[4], 40, 15); // İkinci şekil, konum (15, 5)
    drawShape(shapes[5], 70, 15); // Üçüncü şekil, konum (5, 15)
    drawShape(shapes[6], 10, 25); // Dördüncü şekil, konum (15, 15)
    drawShape(shapes[7], 40, 25); // Üçüncü şekil, konum (5, 15)
    drawShape(shapes[8], 70, 25); // Dördüncü şekil, konum (15, 15)

    // Print Biggest Border
    printBorder(rtg);
}
