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
int size; 
float *vertices; 
GLubyte *pindices; 

////////////////////////////////////////////


GLuint vboHandle[1]; 
GLuint indexVBO; 

void InitVBO() 
{
 glGenBuffers(1, &vboHandle[0]);   // create a VBO handle
  glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]);   // bind the handle to the current VBO 
  glBufferData(GL_ARRAY_BUFFER, size*2*4, vertices, GL_STATIC_DRAW); // allocate space and copy the data over where 2 stand for x and y, 4 stands for float suze 4 byte.
  glBindBuffer(GL_ARRAY_BUFFER, 0);   // clean up 


//connectivity buffer
  glGenBuffers(1, &indexVBO); 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO); 
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte)*size, pindices, GL_STATIC_DRAW); 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  //clean up 

} 

void display()
{

  glClearColor(1,1,1,1); 
  glClear(GL_COLOR_BUFFER_BIT); 
  glColor4f(0,0,1,1);   // note that here we are still using glColor*, a deprecated feature 

  glPointSize(7);

  glEnableClientState(GL_VERTEX_ARRAY); // enable the vertex array 
  glBindBuffer(GL_ARRAY_BUFFER, vboHandle[0]); 
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO); 

  // the following code tells OpenGL how to walk through the vertex array 
  glVertexPointer(2,GL_FLOAT, 0,0); //number of coordinates per vertex (2 here), type of the coordinates, 
                                    // stride between consecutive vertices, and pointers to the first coordinate

  glDrawElements(GL_POINTS, size, GL_UNSIGNED_BYTE, (char*)NULL+0); 
  //  glDrawArrays(GL_POINTS, 0, size); 

  glDisableClientState(GL_VERTEX_ARRAY); 

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
  
  char header1[20], header2[20], header3[20], header4[20], header5[20]; 
  char name[20]; 

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

  size = cnt; 
  vertices = new float[size*2]; 
  pindices = new GLubyte[size]; 

  // this is a bit of a hack - only plot v1 and v2 
  for (int i=0; i<size; i++) {
    float x = (v1[i]-min_v1)*2/scale_v1 - 1 ;
    float y = (v2[i]-min_v2)*2/scale_v2 - 1 ;
    vertices[2*i] = x; 
    vertices[2*i+1] = y; 
    pindices[i] = i; 
  }


  // init glut drawing window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
  glutInitWindowSize(width,height);
  glutCreateWindow("Han-Wei Shen's simple program");


  glutDisplayFunc(display);
  
  /* 
  glutReshapeFunc(resize);
  glutMouseFunc(mymouse);
  glutKeyboardFunc(mykey);

  // create menu
  glutCreateMenu(mymenu);
  glutAddMenuEntry("Point", 1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  */

#ifdef __APPLE__
#else
  glewInit(); 
#endif


  InitVBO(); 

  // enter the event loop
  glutMainLoop();

}

