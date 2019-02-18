//
// Created by peixoto on 21/06/18.
//

#include <GL/glew.h>
#include "Cell.h"

void Cell::drawCube() {
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, wallTextureId);
    glColor3f(1.0, 1.0, 1.0);
    //Front wall
    if(front == nullptr) {
        //glColor3f(0.5, 0.0, 0.0);
        glBegin(GL_POLYGON);
            //glColor3f(0.5, 0.0, 0.0);glTexCoord2f(0.0, 0.0); glVertex3d(0.5, 0.5, -0.5); glColor3f(1.0, 1.0, 1.0);
            glTexCoord2f(0.0, 0.0); glVertex3d(0.5, 0.5, -0.5);
            glTexCoord2f(1.0, 0.0); glVertex3d(0.5, 0.5, 0.5);
            glTexCoord2f(1.0, 1.0); glVertex3d(0.5, -0.5, 0.5);
            glTexCoord2f(0.0, 1.0); glVertex3d(0.5, -0.5, -0.5);
        glEnd();
    }

    //Back wall
    if(back == nullptr) {
       // glColor3f(0.0, 0.5, 0.5);
        glBegin(GL_POLYGON);
            glTexCoord2f(0.0, 0.0); glVertex3d(-0.5, 0.5,  -0.5);
            glTexCoord2f(1.0, 0.0); glVertex3d(-0.5,  0.5,  0.5);
            glTexCoord2f(1.0, 1.0); glVertex3d(-0.5,  -0.5, 0.5);
            glTexCoord2f(0.0, 1.0); glVertex3d(-0.5, -0.5, -0.5);
        glEnd();
    }

    //Right wall
    if(right == nullptr) {
        //glColor3f(0.5, 0.5, 0.5);
        glBegin(GL_POLYGON);
            glTexCoord2f(0.0, 0.0); glVertex3d(0.5, 0.5, 0.5);
            glTexCoord2f(1.0, 0.0); glVertex3d(-0.5, 0.5, 0.5);
            glTexCoord2f(1.0, 1.0); glVertex3d(-0.5, -0.5, 0.5);
            glTexCoord2f(0.0, 1.0); glVertex3d(0.5, -0.5, 0.5);
        glEnd();
    }

    //Left wall
    if(left == nullptr) {
        //glColor3f(0.7, 0.7, 0.7);
        glBegin(GL_POLYGON);
            glTexCoord2f(0.0, 0.0); glVertex3d(-0.5, 0.5, -0.5);
            glTexCoord2f(1.0, 0.0); glVertex3d(0.5, 0.5, -0.5);
            glTexCoord2f(1.0, 1.0); glVertex3d(0.5, -0.5, -0.5);
            glTexCoord2f(0.0, 1.0); glVertex3d(-0.5, -0.5, -0.5);
        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, floorTextureId);
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_POLYGON);
        //glColor3f(0.0, 0.5, 0.0);
        glTexCoord2f(0.0, 0.0); glVertex3d( 0.5,  0.5,  0.5);
        glTexCoord2f(1.0, 0.0); glVertex3d( 0.5,  0.5, -0.5);
        glTexCoord2f(1.0, 1.0); glVertex3d(-0.5,  0.5, -0.5);
        glTexCoord2f(0.0, 1.0); glVertex3d(-0.5,  0.5,  0.5);
    glEnd();

    glBegin(GL_POLYGON);
        //glColor3f(0.5, 0.0, 0.5);
        glTexCoord2f(0.0, 0.0); glVertex3d( 0.5, -0.5, -0.5);
        glTexCoord2f(1.0, 0.0); glVertex3d( 0.5, -0.5,  0.5);
        glTexCoord2f(1.0, 1.0); glVertex3d(-0.5, -0.5,  0.5);
        glTexCoord2f(0.0, 1.0); glVertex3d(-0.5, -0.5, -0.5);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Cell::drawEdges() {
    glColor3f(0.0, 0.0, 0.0);
    //Front wall
    glBegin(GL_LINE_LOOP);
        glVertex3d(0.5, -0.5, -0.5);
        glVertex3d(0.5, 0.5, -0.5);
        glVertex3d(0.5, 0.5, 0.5);
        glVertex3d(0.5, -0.5, 0.5);
    glEnd();

    //Back wall
    glBegin(GL_LINE_LOOP);
        glVertex3d(-0.5, -0.5,  0.5);
        glVertex3d(-0.5,  0.5,  0.5);
        glVertex3d(-0.5,  0.5, -0.5);
        glVertex3d(-0.5, -0.5, -0.5);
    glEnd();

    //Right wall
    glBegin(GL_LINE_LOOP);
        glVertex3d(0.5, 0.5, 0.5);
        glVertex3d(0.5, -0.5, 0.5);
        glVertex3d(-0.5, -0.5, 0.5);
        glVertex3d(-0.5, 0.5, 0.5);
    glEnd();

    //Left wall
    glBegin(GL_LINE_LOOP);
        glVertex3d(0.5, -0.5, -0.5);
        glVertex3d(0.5, 0.5, -0.5);
        glVertex3d(-0.5, 0.5, -0.5);
        glVertex3d(-0.5, -0.5, -0.5);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3d( 0.5,  0.5,  0.5);
        glVertex3d( 0.5,  0.5, -0.5);
        glVertex3d(-0.5,  0.5, -0.5);
        glVertex3d(-0.5,  0.5,  0.5);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glVertex3d( 0.5, -0.5, -0.5);
        glVertex3d( 0.5, -0.5,  0.5);
        glVertex3d(-0.5, -0.5,  0.5);
        glVertex3d(-0.5, -0.5, -0.5);
    glEnd();
}

void Cell::draw() {
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glTranslatef(-grid[0]*Cell::width, 0.0, grid[1]*Cell::depth);
        glScaled(Cell::width, Cell::height, Cell::depth);
        drawEdges();
        drawCube();
    glPopMatrix();
}

void Cell::drawWalls() {
    glColor3f(0.0, 0.0, 0.0);

    glPushMatrix();
        glTranslatef(grid[1], grid[0], 0.0);

        // Front wall
        if(front == nullptr) {
            glBegin(GL_LINES);
                glVertex3d(-0.5, -0.5, 0.0);
                glVertex3d( 0.5, -0.5, 0.0);
            glEnd();
        }

        //Back wall
        if(back == nullptr) {
            glBegin(GL_LINES);
                glVertex3d(-0.5, 0.5, 0.0);
                glVertex3d( 0.5, 0.5, 0.0);
            glEnd();
        }

        //Right wall
        if(right == nullptr) {
            glBegin(GL_LINES);
                glVertex3d(0.5, -0.5, 0.0);
                glVertex3d(0.5,  0.5, 0.0);
            glEnd();
        }

        //Left wall
        if(left == nullptr) {
            glBegin(GL_LINES);
                glVertex3d(-0.5, -0.5, 0.0);
                glVertex3d(-0.5,  0.5, 0.0);
            glEnd();
        }

    glPopMatrix();
}

void Cell::drawPlayer() {
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glTranslatef(grid[1], grid[0], 0.0);

    glBegin(GL_LINES);
        glVertex3d(-0.5, -0.5, 0.0);
        glVertex3d( 0.5,  0.5, 0.0);
    glEnd();

    glBegin(GL_LINES);
        glVertex3d( 0.5, -0.5, 0.0);
        glVertex3d(-0.5,  0.5, 0.0);
    glEnd();

    glPopMatrix();
}

void Cell::draw(int neighbors, bool drawn) {
    if(this->drawn == drawn) return;
    this->draw();
    this->drawn = drawn;
    if(neighbors > 0) {
        if(left  != nullptr) left->draw(neighbors-1,  drawn);
        if(right != nullptr) right->draw(neighbors-1, drawn);
        if(front != nullptr) front->draw(neighbors-1, drawn);
        if(back  != nullptr) back->draw(neighbors-1,  drawn);
    }

}

const int *Cell::getGrid() const {
    return grid;
}

int Cell::getId() const {
    return id;
}

void Cell::setId(int id) {
    Cell::id = id;
}

void Cell::setGrid(int x, int y) {
    grid[0] = x;
    grid[1] = y;
}

Cell *Cell::getLeft() const {
    return left;
}

void Cell::setLeft(Cell *left) {
    Cell::left = left;
}

Cell *Cell::getRight() const {
    return right;
}

void Cell::setRight(Cell *right) {
    Cell::right = right;
}

Cell *Cell::getFront() const {
    return front;
}

void Cell::setFront(Cell *front) {
    Cell::front = front;
}

Cell *Cell::getBack() const {
    return back;
}

void Cell::setBack(Cell *back) {
    Cell::back = back;
}

int Cell::width  = 0;
int Cell::height = 0;
int Cell::depth  = 0;

void Cell::loadTexture() {
    wallTextureId = SOIL_load_OGL_texture(
            //"../images/StoneWall.jpg",
            "../images/dungeon_wall_01_dif.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            0
    );

    if (wallTextureId == 0) {
        cout << "Erro do SOIL: " << SOIL_last_result() << ": " << "../images/dungeon_wall_01_dif.png" << endl;
    }

    floorTextureId = SOIL_load_OGL_texture(
            "../images/dungeon_floor_01_dif.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            0
    );

    if (floorTextureId == 0) {
        cout << "Erro do SOIL: " << SOIL_last_result() << ": " << "../images/dungeon_floor_01_dif.png" << endl;
    }
}

bool Cell::isVisited() const {
    return visited;
}

void Cell::setVisited(bool visited) {
    Cell::visited = visited;
}
