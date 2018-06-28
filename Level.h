//
// Created by peixoto on 22/06/18.
//

#ifndef DUNGEONS_LEVEL_H
#define DUNGEONS_LEVEL_H
#include <vector>
#include "Cell.h"

using namespace std;

class Level {
private:
    int id;
    vector<Cell> cells;
    Cell* currentCell;
    bool drawn;

    void load();

public:
    Level(int id) : id(id), currentCell(nullptr), drawn(true) {
        this->load();
    }


    bool canMove(int x, int z);

    void loadTextures();

    Cell *getCurrentCell() const;
    void draw(int neighbors);
    void drawAll();

    void drawMap();
};


#endif //DUNGEONS_LEVEL_H
