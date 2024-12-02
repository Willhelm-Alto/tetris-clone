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
Offset currentOffset = {0, 0};
Piece currentPiece;
Piece piecesArr[7];

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

void drawPiece(Piece piece, Offset offset){ 
  int x, y;
  for (int i = 0; i < 4; i++) {
    x = piece.vertices[i][0] + offset.x;
    y = piece.vertices[i][1] + offset.y;
    map[y][x] = 1;
    map[y][x - 1] = 0;
  } 
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

void update(){
  frameCount++;
  currentTime = glutGet(GLUT_ELAPSED_TIME);
   
  if(currentTime - initialTime > 1000){
    initialTime = currentTime;
    currentTime = 0;
    fps = frameCount * 1000 / (initialTime - currentTime); 
  }
}

Piece piecesArr[7];

void start(){ 
  srand(time(NULL));
  int r = rand() % 7;
}

//===============================================================================================//

void input(unsigned char key, int x, int y){
  if(key == 'd'){
    currentOffset.x++; 
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
  drawPiece(currentPiece, currentOffset);  
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
