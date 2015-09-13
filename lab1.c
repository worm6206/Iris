#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#endif
using namespace std;


vector< vector<string> > value;
vector<float> max_v,min_v;
int width, height, cnt=0;
float ww,hh;

//Convert string into vector
vector<string> string_into_vector(string input)
{
	vector<string> output;
	string temp="";
	for(int i = 0; i<input.size();i++)
	{
		if(input[i]==',') 
		{
			output.push_back(temp);
			temp="";
		}else 	temp+=input[i];
	}
	output.push_back(temp);
	return output;
}

//Read file 
vector< vector<string> > read_file(string filename)
{
	ifstream file (filename);
	if (!file.is_open()) throw runtime_error("File not found");
	vector< vector<string> > output;
	string line;
	while(getline(file, line))
	{
		output.push_back(string_into_vector(line));
	}	

	return output;
}

//print the 2d vector, for debugging perpose.
void cout_2d_vector(vector< vector<string> > input)
{
	for(int i =0; i<input.size();i++)
	{
		for (int j = 0; j < input[i].size(); ++j)
		{
			cout<<input[i][j]<<"\t";
		}
		cout << endl;	
	}
}

void getMaxMin(vector< vector<string> > input)
{
	max_v.push_back(0);
	min_v.push_back(0);
	for (int i = 1; i < input[0].size(); ++i)
	{
		max_v.push_back(-10000);
		min_v.push_back(10000);
	}
	for (int i = 1; i < input[0].size(); ++i)
	{
		for (int j = 1; j < input.size(); ++j)
			{
				if(atof(input[j][i].c_str()) > max_v[i]) max_v[i]= atof(input[j][i].c_str());
				if(atof(input[j][i].c_str()) < min_v[i]) min_v[i]= atof(input[j][i].c_str());
			}	
	}
}

void display()
{
	glClearColor(1, 1, 1, 1); 
	glClear(GL_COLOR_BUFFER_BIT); 
	float wtemp = width/(value[0].size()-1), htemp = height/(value[0].size()-1),tempc=0;
	vector<string> namebank;
	float floatbank[6][3] = {(1,0,0),(0,1,0),(0,0,1),(1,1,0),(1,0,1),(0,1,1)};
	namebank.push_back(value[1][0]);
	for (int z = 0; z < value[0].size()-1; z++)
	{
		for (int j = 0; j < value[0].size()-1; j++)
		{
			if(z+j==3) {} else
			{
				//Viewport
				glViewport(wtemp*z,htemp*j,wtemp,htemp);
				//points
				glColor3f(0, 0, 0);
				for (int i=1; i<value.size(); i++) {
					if (value[i][0]=="setosa")
					{
						glColor3f(1,0,0);
					} else if (value[i][0]=="versicolor")
					{
						glColor3f(0,1,0);
					}else if (value[i][0]=="virginica")
					{
						glColor3f(0,0,1);
					}
					float x = (atof(value[i][z+1].c_str())-min_v[z+1])*2/(max_v[z+1]- min_v[z+1]) - 1 ;
					float y = (atof(value[i][4-j].c_str())-min_v[4-j])*2/(max_v[4-j]- min_v[4-j]) - 1 ;
					cnt++;
					glPointSize(2+cnt%4);
					glBegin(GL_POINTS);
					glVertex2f(x*0.8,y*0.8);
					glEnd();
				}
				//Borders
				glLineWidth(1); 
				glColor3f(0, 0, 0);
				glBegin(GL_LINES);
				glVertex2f(-0.85, -0.85);
				glVertex2f(-0.85, 0.85);
				glVertex2f(-0.85, -0.85);
				glVertex2f(0.85, -0.85);
				glVertex2f(0.85, 0.85);
				glVertex2f(0.85, -0.85);
				glVertex2f(0.85, 0.85);
				glVertex2f(-0.85, 0.85);
				glEnd();
				//ticks
				glLineWidth(1); 
				glColor3f(0, 0, 0);
				glBegin(GL_LINES);
				for (int i = 0; i < 12; ++i)
				{
					glVertex2f(-0.85+0.85*2*i/11, -0.87);
					glVertex2f(-0.85+0.85*2*i/11, -0.83);

					glVertex2f(-0.87,-0.85+0.85*2*i/11);
					glVertex2f(-0.83,-0.85+0.85*2*i/11);
				}


				glEnd();

				glFlush(); 
			}
		}
	}
}

void resize(int w, int h)
{
    width=w;
    height=h;
}

int main(int argc, char** argv)
{
	if (argc != 4) {
		printf(" usage: %s width height csv_file\n", argv[0]); 
		exit(1); 
	}
	width = atoi(argv[1]);
	height = atoi(argv[2]);
	//Read File
	value = read_file(argv[3]);
	getMaxMin(value);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(width,height);
	glutCreateWindow("Lab1.c");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutMainLoop();
	return 0;	
}