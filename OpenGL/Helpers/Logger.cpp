#include "Logger.hpp"
#include <iostream>
#include <thread>

using namespace std;

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
void Logger::WriteLine(std::string msg)
{
	cout << msg << endl;
}
