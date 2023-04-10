#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <tuple>
using namespace std;

//Helper functions
void print_A(vector<vector<int>> A);

vector<vector<int>> problem_one_file_to_vec(string filename);

vector<vector<int>> problem_two_file_to_vec(string filename, int* k);

void problem_one_create_file(string filename, int m, int n);

void problem_two_create_file(string filename, int k, int m, int n);

//Problem 1 functions
void Alg1(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day);
void Alg1(string filename);

void Alg2(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day);
void Alg2(string filename);

void Alg3a(vector<vector<int>> A, int* stock, int* buy_day, int* sell_day);
void Alg3a(string filename);

void Alg3b(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day);
void Alg3b(string filename);

//Problem 2 functions

typedef pair<int, int> pii;
void Alg5(vector<vector<int>> A, int k);
void Alg5(string filename);

