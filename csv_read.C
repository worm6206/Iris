#include <stdio.h>
#include <stdlib.h>
#include <vector>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif

int width, height;
std::vector<float> v1, v2, v3, v4;

float max_v1 = -10000, min_v1 = 10000;
float max_v2 = -10000, min_v2 = 10000;
float max_v3 = -10000, min_v3 = 10000;
float max_v4 = -10000, min_v4 = 10000;


float scale_v1, scale_v2, scale_v3, scale_v4; 

////////////////////////////////////////////

void display()
{

int size = v1.size();
printf("size = %d\n", size);

glClearColor(1, 1, 1, 1); 
glClear(GL_COLOR_BUFFER_BIT); 
glViewport(0,0,width/2,height/2);
glColor3f(0, 0, 0);     //glColor* have been deprecated in OpenGL 3

glPointSize(10);
glBegin(GL_POINTS);
for (int i=0; i<size; i++) {
  float x = (v1[i]-min_v1)*2/scale_v1 - 1 ;
  float y = (v2[i]-min_v2)*2/scale_v2 - 1 ;
  glVertex2f(x,y);
}
glEnd();
glFlush(); 

}


int main(int argc, char** argv) {


  float f1, f2, f3, f4;
  float *d1, *d2, *d3, *d4;

  if (argc != 4) {
    printf(" usage: %s width height csv_file\n", argv[0]); 
    exit(1); 
  }

  width = atoi(argv[1]);
  height = atoi(argv[2]);

  printf(" width %d  height %d  file %s \n", width, height, argv[3]); 

  FILE* fp = fopen(argv[3], "r");
  

  int cnt = 0; 
  while (fscanf(fp, "%g,%g,%g,%g \n", &f1, &f2, &f3, &f4)==4) {

    if (f1 < min_v1) min_v1 = f1;
    if (f1 > max_v1) max_v1 = f1;
    
    if (f2 < min_v2) min_v2 = f2;
    if (f2 > max_v2) max_v2 = f2;

    if (f3 < min_v3) min_v3 = f3;
    if (f3 > max_v3) max_v3 = f3;
    
    if (f4 < min_v4) min_v4 = f4;
    if (f4 > max_v4) max_v4 = f4;

    
    v1.push_back(f1);
    v2.push_back(f2);
    v3.push_back(f3);
    v4.push_back(f4); 
    cnt++; 
  }
  scale_v1 = max_v1 - min_v1;
  scale_v2 = max_v2 - min_v2;
  scale_v3 = max_v3 - min_v3;
  scale_v4 = max_v4 - min_v4; 

  // init glut drawing window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  glutInitWindowSize(width,height);
  glutCreateWindow("Han-Wei Shen's simple program");

  glutDisplayFunc(display);

  // enter the event loop
  glutMainLoop();

}

