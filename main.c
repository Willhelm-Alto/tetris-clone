#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <time.h>
#include "pieces.c"
#define FPS 60

struct point_s{ float x, y; };
typedef struct point_s Point; 

struct offset_s{ int x, y; };
typedef struct offset_s Offset;

int initalTime, finalTime, deltaTime, frameCount = 0;

int windowWidth = 500, windowHeight = 500;

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

Point gridPos = {350, 0};
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

Offset offset = { 0, 0 };
void drawPiece(Piece piece){ 
  int x, y;
  for (int i = 0; i < 4; i++) {
    x = piece.vertices[i][0] + offset.x;
    y = piece.vertices[i][1] + offset.y;
    map[y][x] = 1;
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
      Point p = {i * (size + 2), j * (size + 2)};
      drawSquare(p, size);
    }
  }
}

void gameLoop(int){
  glutPostRedisplay();
  glutTimerFunc(1000/FPS, gameLoop, 0);
}

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  drawPiece(T);
  drawGridMap();
  glutSwapBuffers();

  frameCount++;
  finalTime = time(NULL);
  deltaTime = finalTime - initalTime;
  if(deltaTime > 0){
    printf("%f", frameCount / deltaTime);
    frameCount = 0;
    initalTime = finalTime;
  };
}

void input(unsigned char key, int x, int y){
  if(key == 'd'){
    offset.x++;
  }
  glutPostRedisplay();
}

void init(){
  glClearColor(0.7, 0.7, 0.7, 0);
  gluOrtho2D(0,1024,512,0);  
  initalTime = time(NULL);
}

void resize(int w, int h){
  windowWidth = w;
  windowHeight = h;
  glViewport(0,0,windowWidth, windowHeight);
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
    glutTimerFunc(1000 / FPS, gameLoop, 0);
    glutMainLoop();
}
