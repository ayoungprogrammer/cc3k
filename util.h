#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <sstream>

std::string toString(char ch);
std::string toString(int n);
std::string getDirName(int x,int y);
std::pair<int,int> getDirection(std::string str);

#endif