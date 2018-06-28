#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <GL/freeglut.h>
#include <iostream>
#include <string>
#include <random>
#include "Level.h"

#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)

using namespace std;

const double FPS_CONST = 0.017;
#define ORTHO_WIDTH  (orthoHalfWidth*2)
#define ORTHO_HEIGHT (orthoHalfHeight*2)

#define KEY_ESC 27

bool* keyStates = new bool[127];
bool* specialKeyStates = new bool[127];

int windowWidth,
    windowHeight;

double angleX = 0.0, angleY = 0.0, angleYTarget = 0.0;

double x = 0.0, y = 0.0, z = 0.0;
double xTarget = 0.0, zTarget = 0.0;

double orthoHalfWidth, orthoHalfHeight;

Level l0(0);

bool map = false;

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    if(map) {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glPushMatrix();
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-2, 27, 23, -2, -1.0, 1.0);
            glMatrixMode(GL_MODELVIEW);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                l0.drawMap();
        glPopMatrix();
        glutSwapBuffers();
        glClearColor(0.0, 0.0, 0.0, 1.0);
        return;
    } else {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(60.0, (float)windowWidth/(float)windowHeight, 0.0001, 1000.0);

        glMatrixMode(GL_MODELVIEW);
    }

    /*gluLookAt(x   ,  y,  z,
              x+(10*cos(degreesToRadians(angleY))),  y,  z+(10*sin(degreesToRadians(angleY))),
              0,     1,  0);*/
    gluLookAt(x   ,  y,  z,
              (x+(10*cos(degreesToRadians(angleY)))),  y,  (z+(10*sin(degreesToRadians(angleY)))),
              0,     1,  0);

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(-100, 0.0, 0.0);
        glVertex3f(100, 0.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
        glVertex3f(0, -100.0, 0.0);
        glVertex3f(0, 100.0, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0, 0.0, -100.0);
    glVertex3f(0, 0.0, 100.0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        l0.drawAll();
        //l0.draw(1);
    glPopMatrix();

    // Diz ao OpenGL para colocar o que desenhamos na tela
    glutSwapBuffers();
}

void restart() {}

// Inicia algumas vari�veis de estado
void inicializa(void) {

    // cor para limpar a tela
    glClearColor(0, 0, 0.0, 0);
    glEnable(GL_DEPTH_TEST);

    //anti-aliasing
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // Não mostrar faces do lado de dentro

    // Esconder o ponteiro do mouse quando dentro da janela
    glutSetCursor(GLUT_CURSOR_NONE);

    x = xTarget = -l0.getCurrentCell()->getGrid()[0]*32;
    z = zTarget = l0.getCurrentCell()->getGrid()[1]*32;

    l0.loadTextures();

    glPointSize(4);
    glLineWidth(5);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// Callback de redimensionamento
void resizeScreen(int w, int h) {
    double windowAspectRatio = ((double)w)/h;
    double worldAspectRatio = ((ORTHO_WIDTH)/(ORTHO_HEIGHT));
    if (windowAspectRatio < worldAspectRatio) {
        double viewportHeight = w / worldAspectRatio;
        double viewportY = (h - viewportHeight)/2;
        glViewport(0, viewportY, w, viewportHeight);
    }
    else if (windowAspectRatio > worldAspectRatio) {
        double viewportWidth = (h) * worldAspectRatio;
        double viewportX = (w - viewportWidth)/2;
        glViewport(viewportX, 0, viewportWidth, h);
    } else {
        glViewport(0, 0, w, h);
    }

    windowWidth = w;
    windowHeight = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0, (float)w/(float)h, 0.0001, 1000.0);

    glMatrixMode(GL_MODELVIEW);
}

void keyboardHandle() {
    if(keyStates['[']) {
        y += 1.0;
        //position += paceY;
    }
    if(keyStates[']']) {
        y -= 1.0;
        //position -= paceY;
    }
    if(keyStates['+']) {
        angleX += 1.0;
    }
    if(keyStates['-']) {
        angleX -= 1.0;
    }

    glutPostRedisplay();
}

void atualiza(int time) {
    double pace = 4.5;
    double wPace = 1.0;
    glutTimerFunc(time, atualiza, time);

    if(angleY < angleYTarget) angleY += pace;
    if(angleY > angleYTarget) angleY -= pace;

    if(x < xTarget) x += wPace;
    if(x > xTarget) x -= wPace;

    if(z < zTarget) z += wPace;
    if(z > zTarget) z -= wPace;
    keyboardHandle();
    //cout << x << " | " << xTarget << "\t" << z << " | " << zTarget << endl;
}


void keyDown(unsigned char key, int keyX, int keyY) {
    keyStates[key] = true;

    int paceX = 0, paceZ = 0;

    bool moving = false;

    if(key == KEY_ESC) {
        exit(0);
    }

    if(x > xTarget-0.00001 && x < xTarget+0.00001 &&
       z > zTarget-0.00001 && z < zTarget+0.00001) {
        if (keyStates['q']) {
            //angleY -= 90.0;
            angleYTarget -= 90.0;
        }
        if (keyStates['e']) {
            //angleY += 90.0;
            angleYTarget += 90.0;
        }
    }
    if(angleY > angleYTarget-0.00001 && angleY < angleYTarget+0.00001) {
        if (keyStates['d']) {
            //z += 1.0;
            paceX += 32 * sin(degreesToRadians(angleY));
            paceZ += 32 * cos(degreesToRadians(angleY));
            //position += 32* paceX;
            moving = true;
        }
        if (keyStates['a']) {
            //z -= 32* 1.0;
            paceX -= 32 * sin(degreesToRadians(angleY));
            paceZ -= 32 * cos(degreesToRadians(angleY));
            //position -= 32* paceX;
            moving = true;
        }
        if (keyStates['w']) {
            //paceX += 32* 1.0;
            paceX += 32 * cos(degreesToRadians(angleY));
            paceZ += 32 * sin(degreesToRadians(angleY));
            //position += 32* paceY;
            moving = true;
        }
        if (keyStates['s']) {
            //paceX -= 32* 1.0;
            paceX -= 32 * cos(degreesToRadians(angleY));
            paceZ -= 32 * sin(degreesToRadians(angleY));
            //position -= paceY;
            moving = true;
        }
    }
    if(key == '\t') {
        map = !map;
    }

    if(moving && l0.canMove(paceX, paceZ)) {
        xTarget += paceX;
        zTarget += paceZ;
    }
    //cout << paceX << " " << z << " " << angleY << endl;
}

void specialKeyDown(int key, int x, int y) {
    specialKeyStates[key] = true;
}

void keyUp(unsigned char key, int x, int y) {
    keyStates[key] = false;
}

void specialKeyUp(int key, int x, int y) {
    specialKeyStates[key] = false;
}

// Rotina principal
int main(int argc, char **argv) {
    // Acordando o GLUT
    glutInit(&argc, argv);

    // Definindo a vers�o do OpenGL que vamos usar
    glutInitContextVersion(1, 1);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    windowWidth  = glutGet(GLUT_SCREEN_WIDTH);
    windowHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Configura��o inicial da janela do GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(0, 0);

    // Abre a janela
    glutCreateWindow("GameBoilerplate");
    glutFullScreen();

    // Registra callbacks para alguns eventos
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resizeScreen);

    // Keyboard up and down callbacks
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    // Special keyboard up and down callbacks
    glutSpecialFunc(specialKeyDown);
    glutSpecialUpFunc(specialKeyUp);

    inicializa();
    glutTimerFunc(0, atualiza, 17);

    // Entra em loop e nunca sai
    glutMainLoop();

    return 0;
}