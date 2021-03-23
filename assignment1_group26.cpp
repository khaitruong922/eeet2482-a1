#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Please provide exactly 1 file name for this program";
		return -1;
	}
	char* file_name = argv[1];
	std::cout << file_name << endl;
}