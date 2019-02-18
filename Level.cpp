//
// Created by peixoto on 22/06/18.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <Vector3.h>
#include "Level.h"

void Level::drawAll() {
    for(Cell c : cells)
        c.draw();
}

void Level::draw(int neighbors) {
    if(currentCell != nullptr) {
        currentCell->draw(neighbors, drawn);
        drawn = !drawn;
    }
}
//25x21
void Level::drawMap() {
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, mapTextureId);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0, 0.0); glVertex3d(-2, -2, -0.1);
        glTexCoord2f(1.0, 0.0); glVertex3d(27*1.77,  -2, -0.1);
        glTexCoord2f(1.0, 1.0); glVertex3d(27*1.77,  23, -0.1);
        glTexCoord2f(0.0, 1.0); glVertex3d(-2, 23,  -0.1);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    for(Cell c : cells)
        if(c.isVisited()) c.drawWalls();
    currentCell->drawPlayer();
}

void Level::load() {
    // abre o arquivo para leitura
    ifstream in(string("../levels/") + std::to_string(id), ios::in);
    if (!in) {
        cerr << "Erro ao abrir o arquivo " << "../levels/" << std::to_string(id) << endl;
        exit(1);
    }

    string line;
    while (getline(in, line)) {
        if (line[0] == '#') { /* Comentário */ }
        if (line.find("level:") != string::npos) continue;
        if (line.find("initial:") != string::npos) {
            istringstream initialLine(line.substr(8));

            int initial;

            initialLine >> initial;
            currentCell = &cells[initial-1];
            currentCell->setVisited(true);
        }
        if (line.find("cellSize:") != string::npos) {
            istringstream sizeLine(line.substr(9));

            sizeLine >> Cell::width;
            sizeLine >> Cell::height;
            sizeLine >> Cell::depth;
        }
        else if (line.substr(0, 2) == "c ") {
            istringstream cellLine(line.substr(2));
            cells.emplace_back(cellLine);
        } else if (line.substr(0, 2) == "rl") {
            // stream de string para facilitar a vida
            istringstream relationLine(line.substr(2));

            int id, left, right, front, back;

            relationLine >> id;
            relationLine >> left;
            relationLine >> right;
            relationLine >> front;
            relationLine >> back;

            id--;

            cells[id].setLeft(left   == 0 ? nullptr : &cells[left-1]);
            cells[id].setRight(right == 0 ? nullptr : &cells[right-1]);
            cells[id].setFront(front == 0 ? nullptr : &cells[front-1]);
            cells[id].setBack(back   == 0 ? nullptr : &cells[back-1]);
        } else { /* Ignora */ }
    }
}

bool Level::canMove(int x, int z) {
    bool canMove = false;
    Cell* nextCell = nullptr;
    if(x > 0) {
        canMove  = currentCell->getFront() != nullptr;
        nextCell = currentCell->getFront();
    } else if(x < 0) {
        canMove  = currentCell->getBack() != nullptr;
        nextCell = currentCell->getBack();
    } else if(z > 0) {
        canMove  = currentCell->getRight() != nullptr;
        nextCell = currentCell->getRight();
    } else if(z < 0) {
        canMove  = currentCell->getLeft() != nullptr;
        nextCell = currentCell->getLeft();
    }
    if(canMove) {
        currentCell = nextCell;
        currentCell->setVisited(true);
    }
    return canMove;

}

Cell *Level::getCurrentCell() const {
    return currentCell;
}

void Level::loadTextures() {
    mapTextureId = SOIL_load_OGL_texture(
            "../images/OldPaper.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            0
    );

    if (mapTextureId == 0) {
        cout << "Erro do SOIL: " << SOIL_last_result() << ": " << "../images/OldPaper.png" << endl;
    }

    for(auto& c : cells)
        c.loadTexture();
}
