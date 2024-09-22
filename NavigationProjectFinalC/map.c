#include <stdio.h>
#include <windows.h>
#include "map.h" 


void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void drawShape( Shape *shape, int x, int y) {
    printf("\033[%d;%dH%s\n", y - 1, x, shape->name);

    for (int i = 0; i < SHAPE_SIZE; ++i) {
         printf("\033[%d;%dH%s\n", y + i, x, shape->lines[i]);
    }
}


void PrintBorder(Rectang r) {
    for (int i = r.lower_left_point.x ; i <= (r.lower_right_point.x); i++) {
        gotoxy(i, r.upper_left_point.y);   // first line
        printf("_");
        
        gotoxy(i, r.lower_left_point.y);    // last line
        printf("_");
        
    }

    for (int i = r.upper_left_point.y+1; i <= (r.lower_left_point.y); i++) {
        gotoxy((r.upper_left_point.x-1), i );    // First column
        printf("|");

        gotoxy((r.upper_right_point.x+1), i );     // Last column
        printf("|");
      
    }
    
    printf("\n \n \n \n \n \n \n ");
}



void drawHorizontalLine(Line *line, Point spaceStart1, Point spaceStart2) {
    if (line->p1.y != line->p2.y) {
        gotoxy(100, 1);
        printf("Y noktalari ayni olmadigindan x eksenine paralel dogru cizilemez.\n");
        return;
    }

    int startX = (line->p1.x < line->p2.x) ? line->p1.x : line->p2.x;
    int endX = (line->p1.x < line->p2.x) ? line->p2.x : line->p1.x;

    for (int i = 0; i < 6; i++) {
        for (int j = startX; j <= endX; j++) {
            gotoxy(j, line->p1.y);

            if (j == spaceStart1.x || j == spaceStart2.x) {
                j = j + 10;
            } else {
                printf("_");
            }
        }
        
        // Her iki durumda da y koordinatını güncelle
        line->p1.y += (i % 2 == 0) ? 7 : 3;
    }
}



void drawVerticalLine(Line *line, Point spaceStart1, Point spaceStart2) {
    if (line->p1.x != line->p2.x) {
        gotoxy(100, 1);
        printf("X noktalari ayni olmadigindan y eksenine paralel dogru cizilemez.\n");
        return;
    }

    int startY = (line->p1.y < line->p2.y) ? line->p1.y : line->p2.y;
    int endY = (line->p1.y < line->p2.y) ? line->p2.y : line->p1.y;

    for (int i = 0; i < 6; i++) {
        for (int j = startY; j <= endY; j++) {
            gotoxy(line->p1.x, j);

            if (j == spaceStart1.y || j == spaceStart2.y) {
                j = j + 2;
            } else {
                printf("|");
            }
        }
        
        // Her iki durumda da x koordinatını güncelle
        line->p1.x += (i % 2 == 0) ? 20 : 10;
    }
}


void drawSpaceAt( Point *points, int size) {
    for (int i = 0; i < size; ++i) {
        gotoxy(points[i].x, points[i].y);
        printf(" ");
    }
}


void PrintMap() {
 
    Shape shapes[] = {
        { "Home1", { "  /\\\\", " /--\\\\", "/----\\\\", "|____||","" } },
        { "Bim Market", { "  /\\\\", " /--\\\\", " |___||", "","" } },
        { "Home2",{ "  /\\\\", " /--\\\\", "/----\\\\", "|____||",""  } },
        { "Cinema", { "   /\\\\","  /--\\\\", " /----\\\\", "/------\\\\", "|______||" } },
        { "Hospital", {"  /\\\\\\", " /--\\\\\\", "/----\\\\\\", "|_____||","|_____||"  } },
        { "Home3", { "  /\\\\", " /--\\\\", "/----\\\\", "|____||",""  }},
        { "Hakmar", { "  /\\\\", " /--\\\\", " |___||", "","" } },
        { "Shopping", { "  /\\\\", " /--\\\\", "/----\\\\", "|____||","|____||"  } },
        { "Police", { "  /\\\\", " /--\\\\", "/----\\\\", "|    ||", "|____||" } },
    };
    

    // Border points
    Point upper_left_p = {1, 1};  
    Point upper_right_p = {83, 1};
    Point lower_left_p = {1, 30};
    Point lower_right_p = {83, 30};
    
    // Houses' door points
    Point point[] = {{32,6},{62,6},{62,16},{62,26},{52,26},{22,26},{22,16},{11,9},{12,9},{13,9},{41,19},{42,19},{43,19}};

    // Border
    Rectang rtg = {lower_right_p, lower_left_p, upper_right_p, upper_left_p};

    // Print Horizental and Vertical Lines
    Point pH1 = {3,2}, pH2 = {81,2};
    Point pSpaceH3 = {22,2}, pSpaceH4 = {52,2};
    Line rH1 = {pH1,pH2};
    drawHorizontalLine(&rH1,pSpaceH3,pSpaceH4);      
    
    Point pV1 = {2,3}, pV2 = {2,29};
    Point pSpaceV3 = {2,10}, pSpaceV4 = {2,20};
    Line rV1 = {pV1,pV2};
    drawVerticalLine(&rV1,pSpaceV3,pSpaceV4);   

    drawSpaceAt(point, sizeof(point) / sizeof(point[0]));

    drawShape(&shapes[0], 10, 5); // İlk şekil, konum (5, 5)
    drawShape(&shapes[1], 39, 5); // İkinci şekil, konum (15, 5)
    drawShape(&shapes[2], 70, 5); // Üçüncü şekil, konum (5, 15)
    drawShape(&shapes[3], 10, 15); // Dördüncü şekil, konum (15, 15)
    drawShape(&shapes[4], 40, 15); // İkinci şekil, konum (15, 5)
    drawShape(&shapes[5], 70, 15); // Üçüncü şekil, konum (5, 15)
    drawShape(&shapes[6], 10, 25); // Dördüncü şekil, konum (15, 15)
    drawShape(&shapes[7], 40, 25); // Üçüncü şekil, konum (5, 15)
    drawShape(&shapes[8], 70, 25); // Dördüncü şekil, konum (15, 15)

    // Print Biggest Border
    PrintBorder(rtg);  

    
}
