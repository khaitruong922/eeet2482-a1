#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Please provide exactly 1 file name for this program";
		return 0;
	}
	char* file_name = argv[1];
	std::cout << file_name << endl;
	ifstream infile(file_name);
	if (!infile)
	{
		cout << "Cannot open file " << file_name << endl;
		return 0;
	}
	string line;
	while (getline(infile, line)) {
		cout << line << endl;
	}
	infile.close();
	return 0;
}