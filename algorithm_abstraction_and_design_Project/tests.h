#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <tuple>
#include <chrono>
#include <cstring>
#include <functional>
using namespace std;
/*
Plot1 Comparison of Task1, Task2, Task3A, Task3B with variable n and fixed m
Plot2 Comparison of Task1, Task2, Task3A, Task3B with variable m and fixed n
Plot3 Comparison of Task4, Task5, Task6 with variable n and fixed m and k
Plot4 Comparison of Task4, Task5, Task6 with variable m and fixed n and k
Plot5 Comparison of Task4, Task5, Task6 with variable k and fixed m and n
*/
template<typename Func>

float measureTime(Func&& func);
void plot1();
void plot2();
void plot3();
void plot4();
void plot5();