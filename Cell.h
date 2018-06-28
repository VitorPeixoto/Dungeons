//
// Created by peixoto on 21/06/18.
//

#ifndef DUNGEONS_CELL_H
#define DUNGEONS_CELL_H


#include <sstream>
#include <SOIL/SOIL.h>
#include <iostream>
#include <GL/glew.h>

using namespace std;

class Cell {
private:
    Cell *left, *right, *front, *back;
    int grid[2];
    int id;
    GLuint floorTextureId, wallTextureId;
    bool drawn, visited;
    void drawCube();
    void drawEdges();

public:
    static int width, height, depth;
    Cell() : left(nullptr), right(nullptr), front(nullptr), back(nullptr), grid{0, 0}, drawn(false), visited(false) {}
    Cell(std::istringstream& is) : left(nullptr), right(nullptr), front(nullptr), back(nullptr), drawn(false), visited(false) {
        is >> id;
        is >> grid[0];
        is >> grid[1];
    }

    void draw();
    void draw(int neighbors, bool drawn);

    void loadTexture();

    const int *getGrid() const;
    void setGrid(int x, int y);
    int getId() const;
    void setId(int id);
    Cell *getLeft() const;
    void setLeft(Cell *left);
    Cell *getRight() const;
    void setRight(Cell *right);
    Cell *getFront() const;
    void setFront(Cell *front);
    Cell *getBack() const;
    void setBack(Cell *back);

    bool isVisited() const;

    void setVisited(bool visited);

    void drawWalls();
    void drawPlayer();
};


#endif //DUNGEONS_CELL_H
