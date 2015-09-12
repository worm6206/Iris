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
	glColor3f(0, 0, 0);

	glPointSize(10);
	glBegin(GL_POINTS);
	for (int i=0; i<value.size(); i++) {
		float x = (atof(value[i][1].c_str())-min_v[1])*2/(max_v[1]- min_v[1]) - 1 ;
		float y = (atof(value[i][2].c_str())-min_v[2])*2/(max_v[2]- min_v[2]) - 1 ;
		glVertex2f(x,y);
	}
	glEnd();
	glFlush(); 
}

int main(int argc, char** argv)
{
	//Read File
	value = read_file(argv[1]);
	getMaxMin(value);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowSize(500,500);
	glutCreateWindow("Lab1.c");

	glutDisplayFunc(display);

	glutMainLoop();
	return 0;	
}