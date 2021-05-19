#include <objbase.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <comdef.h>

#ifndef PRINT_LOG_FUNCTION
#define PRINT_LOG_FUNCTION
void inline PrintLog(char *msg)
{
	std::ofstream myfile;
	myfile.open("C:\\example.txt", std::ios::app);
	myfile << msg << "\n";
	myfile.close();
}

void inline print(char *msg)
{
	std::cout << msg << std::endl;
}
#endif