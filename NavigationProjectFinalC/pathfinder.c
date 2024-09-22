#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>

#include "pathfinder.h"



Node *createNode(Point point){
    Node* node = (Node*)malloc(sizeof(Node));
    node->point.x = point.x;
    node->point.y = point.y;
    node->f = node->g = node->h = 0;
    node->parent = NULL;
    return node;
}


int isValid(int x, int y){
   return (x >= 0 && x < ROWS && y >= 0 && y < COLS);
}


int isDestination(int x, int y, Node* dest) {
    return (x == dest->point.x && y == dest->point.y);
}


int calculateHValue(int x, int y, Node* dest) {
    return abs(x - dest->point.x) + abs(y - dest->point.y);
}


Node* aStarSearch(int grid[ROWS][COLS], Node* start, Node* dest) {
    if (!isValid(start->point.x, start->point.y) || !isValid(dest->point.x, dest->point.y)) {
        printf("Geçersiz başlangıç veya hedef konumu.\n");
        return NULL;
    }

    if (grid[start->point.x][start->point.y] == 0 || grid[dest->point.x][dest->point.y] == 0) {
        printf("Başlangıç veya hedef engellidir.\n");
        return NULL;
    }

    int dx[] = {-1, 0, 1, 0}; // Komşu hücrelerin x koordinatları
    int dy[] = {0, 1, 0, -1}; // Komşu hücrelerin y koordinatları

    // Açık ve kapalı listeler
    Node* openList[ROWS * COLS];
    Node* closedList[ROWS * COLS];
    int openListCount = 0, closedListCount = 0;

    // Başlangıç düğümünü açık listeye ekle
    openList[openListCount++] = start;

    while (openListCount > 0) {
        // Açık listeyi düğüm maliyetine göre küçükten büyüğe sırala
        for (int i = 0; i < openListCount - 1; i++) {
            for (int j = 0; j < openListCount - i - 1; j++) {
                if (openList[j]->f > openList[j + 1]->f) {
                    Node* temp = openList[j];
                    openList[j] = openList[j + 1];
                    openList[j + 1] = temp;
                }
            }
        }

        // Açık listeden en düşük maliyetli düğümü al
        Node* current = openList[0];
        openListCount--;

        // Açık listeyi güncelle
        for (int i = 0; i < openListCount; i++) {
            openList[i] = openList[i + 1];
        }

        // Düğümü kapalı listeye ekle
        closedList[closedListCount++] = current;

        // Hedefe ulaşıldı mı kontrol et
        if (isDestination(current->point.x, current->point.y, dest)) {
            return current; // Hedefe ulaşıldıysa, son düğümü döndür
        }

        // Komşu düğümleri kontrol et
        for (int i = 0; i < 4; i++) {
            int newX = current->point.x + dx[i];
            int newY = current->point.y + dy[i];
            Point p = {newX,newY};

            // Yeni konum geçerli mi kontrol et
            if (isValid(newX, newY) && grid[newX][newY] == 1) {
                // Yeni düğümü oluştur
                
                Node* neighbor = createNode(p);

                // Komşu düğüm kapalı listeye zaten ekli mi kontrol et
                int isNeighborInClosedList = 0;
                for (int j = 0; j < closedListCount; j++) {
                    if (closedList[j]->point.x == neighbor->point.x && closedList[j]->point.y == neighbor->point.y) {
                        isNeighborInClosedList = 1;
                        break;
                    }
                }

                if (isNeighborInClosedList) {
                    free(neighbor);
                    continue;
                }

                // G ve H değerlerini hesapla
                neighbor->g = current->g + 1;
                neighbor->h = calculateHValue(newX, newY, dest);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;

                // Komşu düğüm açık listeye zaten ekli mi kontrol et
                int isNeighborInOpenList = 0;
                for (int j = 0; j < openListCount; j++) {
                    if (openList[j]->point.x == neighbor->point.x && openList[j]->point.y == neighbor->point.y) {
                        isNeighborInOpenList = 1;
                        break;
                    }
                }

                // Eğer açık listeye ekli değilse, açık listeye ekle
                if (!isNeighborInOpenList) {
                    openList[openListCount++] = neighbor;  
                }
                // Eğer açık listeye ekliyse ve yeni g değeri daha küçükse, güncelle
                else {
                    for (int j = 0; j < openListCount; j++) {
                        if (openList[j]->point.x == neighbor->point.x && openList[j]->point.y == neighbor->point.y) {
                            if (neighbor->g < openList[j]->g) {
                                openList[j]->g = neighbor->g;
                                openList[j]->f = neighbor->f;
                                openList[j]->parent = neighbor->parent;
                            }
                            break;
                        }
                    }
                }
            }
        }
    }

    // Hedefe ulaşılamadıysa, NULL döndür
    return NULL;
}


void printColoredPath(Node* path, int grid[ROWS][COLS]) {
    if (path == NULL) {
        printf("Yol bulunamadı.\n");
        return;
    }

    // Yolu çiz
   
    while (path != NULL) {
        grid[path->point.x][path->point.y] = 2; // 2, kırmızı renk için bir kod
        path = path->parent;
    }

    // Konsolu temizle
     system("cls"); 

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
             if (grid[i][j] == 2) {
                printf("\x1b[42m\x1b[37m \x1b[0m");  // Yeşil renkli yol
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void drawCharacter(Point character) {
    gotoxy(character.x,character.y);
    printf("*");
    fflush(stdout);
}


void clearCharacter(Point character) {
     gotoxy(character.x,character.y);
    printf(" ");
    fflush(stdout);
}



void runAStarExample(Location currentLoc, Location destination) {

    Node* start = createNode(currentLoc.pointPath);
    Node* dest = createNode(destination.pointPath);

    Node* path = aStarSearch(grid, start, dest);

    printColoredPath(path, grid);
    PrintMap();



    Point startPoint = {1,1}; 
    Point endPoint = {83,30};
    Point character = currentLoc.pointDoor;
    char key;

    // Başlangıç pozisyonunda karakteri çiz
    drawCharacter(character);  

    do {
        key = getch();  // Kullanıcının tuş girişini bekler

        // Önceki pozisyonda karakteri sil 
        clearCharacter(character);
        
        // Karakterin yeni pozisyonunu belirle
        switch (key) {
            case 'w':
                if (character.y > startPoint.y) {
                    character.y--;
                }
                break;
            case 's':
                if (character.y < endPoint.y) {
                    character.y++;
                }
                break;
            case 'a':
                if (character.x > startPoint.x) {
                    character.x--;
                }
                break;
            case 'd':
                if (character.x < endPoint.x) {
                    character.x++;
                }
                break;
        }
        
        printColoredPath(path, grid);
        PrintMap();
        
        // Yeni pozisyonda karakteri çiz
        drawCharacter(character);

        if(character.x == destination.pointDoor.x && character.y == destination.pointDoor.y){
            gotoxy(100, 10);
            printf("You reached %s!",destination.name);
        }

    } while (key != 'q');  // 'q' tuşuna basılana kadar devam et

    free(start);
    free(dest);
     
}
    



