#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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

vector< vector<string> > read_file(string filename)
{
	ifstream file (filename);
	if (!file.is_open()) throw runtime_error("File not found");
	vector<string> temp;
	vector< vector<string> > output;
	string line;
	while(getline(file, line))
	{
		temp = string_into_vector(line);
		output.push_back(temp);
	}	

	return output;
}

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

int main(int argc, char** argv)
{
	vector< vector<string> > value;
	value = read_file(argv[1]);
	cout_2d_vector(value);
	return 0;	
}