#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
	float temp = 800/(value[0].size()-1),tempc=0;
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
				glViewport(temp*z,temp*j,temp,temp);
				//points
				glColor3f(0, 0, 0);
				glPointSize(4);
				glBegin(GL_POINTS);
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
					glVertex2f(x*0.8,y*0.8);
				}
				glEnd();
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

				glFlush(); 
			}
		}
	}
}

int main(int argc, char** argv)
{
	//Read File
	value = read_file(argv[1]);
	getMaxMin(value);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(800,800);
	glutCreateWindow("Lab1.c");

	glutDisplayFunc(display);

	glutMainLoop();
	return 0;	
}