#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <time.h>

#include "pieces.c"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

struct point_s{ float x, y; };
typedef struct point_s Point; 

struct offset_s{ int x, y; };
typedef struct offset_s Offset;

int fps, frameCount = 0, currentTime, initialTime = 0;
int mapSizeX = 10; 
int mapSizeY = 20; 
int size = 20;
int map[20][10] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0},
};

Point gridPos = {0, 0};
Offset offset = {0, 0}, newOffset = {0, 0};
Piece currentPiece, piecesArr[7], piecesQueue[5];
bool canMove = true;
int xMax = 0, xMin = 0, yMax = 0;

//===============================================================================================//

void drawSquare(Point point,int size){     
  glBegin(GL_TRIANGLES);
    glVertex2f(point.x, point.y);
    glVertex2f(point.x, point.y + size);
    glVertex2f(point.x + size, point.y + size);
  glEnd();
    glBegin(GL_TRIANGLES);
    glVertex2f(point.x + size, point.y + size);
    glVertex2f(point.x + size, point.y);
    glVertex2f(point.x, point.y);
  glEnd();
}

void drawPiece(){ 
  int x, y, x1, y1; 
    for (int i = 0; i < 4; i++) {
    x1 = currentPiece.vertices[i][0] + offset.x;
    y1 = currentPiece.vertices[i][1] + offset.y;
    map[y1][x1] = 0;
  } 
  
  xMax = 0;
  xMin = 100;
  yMax = 0;
  for (int i = 0; i < 4; i++) {
    x = currentPiece.vertices[i][0] + newOffset.x;
    y = currentPiece.vertices[i][1] + newOffset.y;
    if(x > xMax){
      xMax = x;
    }
    if(x < xMin){
      xMin = x;
    }
    if(y > yMax){
      yMax = y;
    }
    map[y][x] = 1;
  } 
  offset = newOffset;
}

void drawGridMap(){  
  for (int i = 0; i < mapSizeX; i++) {
    for (int j = 0; j < mapSizeY; j++) {
      if(map[j][i] == 1){
        glColor3f(1, 0, 0);
      } else {
        glColor3f(0, 0, 0);
      }
      Point p = {gridPos.x + i * (size + 2), gridPos.y + j * (size + 2)};
      drawSquare(p, size);
    }
  }
}

void setGridMapPos(int w, int h){
  gridPos.x = (w / 2);
  gridPos.y = h;
  drawGridMap();
}

int randInt(int maxNum){
  srand(time(NULL));
  int r = rand() % maxNum;
  return r;
}

void update(){
  frameCount++;
  currentTime = glutGet(GLUT_ELAPSED_TIME);

  if(currentTime - initialTime > 100){
    initialTime = currentTime;
    currentTime = 0;
    fps = frameCount * 1000 / (initialTime - currentTime); 
  }
}

void start(){
  piecesArr[0] = S;
  piecesArr[1] = Z;
  piecesArr[2] = L;
  piecesArr[3] = J;
  piecesArr[4] = T;
  piecesArr[5] = O;
  piecesArr[6] = I;
  
  for (int i = 0; i < 4; i++) {
    piecesQueue[i] = piecesArr[randInt(7)];
  }
  currentPiece = piecesArr[0];
}

//===============================================================================================//

void input(unsigned char key, int x, int y){
  switch(key){
    case 'd':
      if(xMax < 9){
        newOffset.x++;
      }
    break;
    case 'a':
      if(xMin > 0){
        newOffset.x--;
      }
    break;
    case 's':
      if(yMax < 19){
        newOffset.y++;
      }
    break;
  } 
  glutPostRedisplay();
}

void init(){
  glClearColor(0.7, 0.7, 0.7, 0);
  gluOrtho2D(0,1024,512,0);  
  currentTime = glutGet(GLUT_ELAPSED_TIME);
  start();
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  drawGridMap();
  drawPiece();  
  glutSwapBuffers();
  glutPostRedisplay();
}

void resize(int w, int h){
  glViewport(0,0, w, h);
  setGridMapPos(0, 0);
  glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1024, 512);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("tetris");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(input);
    glutIdleFunc(update);
    glutMainLoop();
}
