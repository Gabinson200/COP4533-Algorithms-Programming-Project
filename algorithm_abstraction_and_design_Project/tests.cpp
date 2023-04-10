#include "functions.h"
#include "tests.h"
using namespace std;



template<typename Func>

float measureTime(Func&& func) {
	auto start = std::chrono::high_resolution_clock::now();

	// Call the passed function
	std::invoke(std::forward<Func>(func));

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	//std::cout << "Elapsed time: " << duration.count() << " microseconds" << std::endl;
	return duration.count();
}



void plot1() {
	cout << endl << "DATA FOR PLOT 1 -----------------------" << endl;
	int m = 100;
	int ns[] = {100, 200, 300, 400, 500};
	vector<float> run_times;

	for (int i = 0; i < 5; i++) {
		string f_name = "P1_" + to_string(m) + "_" + to_string(ns[i]);

		problem_one_create_file(f_name, m, ns[i]);

		run_times.push_back(measureTime([&]() {
			Alg1(f_name);
		}));

		run_times.push_back(measureTime([&]() {
			Alg2(f_name);
		}));

		run_times.push_back(measureTime([&]() {
			Alg3a(f_name);
		}));

		run_times.push_back(measureTime([&]() {
			Alg3b(f_name);
		}));

		cout << endl << f_name << ": " << endl;
		for (int i = 0; i < run_times.size(); i++) {
			cout << run_times[i] << " ";
		}
		cout << endl<< endl;
		run_times.clear();

		char* charPtr = const_cast<char*>(f_name.c_str());
		remove(charPtr);
	}
	cout << "--------------------------------" << endl;
	return;
}


void plot2() {
	cout << endl << "DATA FOR PLOT 2 -----------------------" << endl;
	int n = 100;
	int ms[] = { 100, 200, 300, 400, 500 };
	vector<float> run_times;

	for (int i = 0; i < 5; i++) {
		string f_name = "P1_" + to_string(ms[i]) + "_" + to_string(n);

		problem_one_create_file(f_name, ms[i], n);

		run_times.push_back(measureTime([&]() {
			Alg1(f_name);
			}));

		run_times.push_back(measureTime([&]() {
			Alg2(f_name);
			}));

		run_times.push_back(measureTime([&]() {
			Alg3a(f_name);
			}));

		run_times.push_back(measureTime([&]() {
			Alg3b(f_name);
			}));

		cout << endl << f_name << ": " << endl;
		for (int i = 0; i < run_times.size(); i++) {
			cout << run_times[i] << " ";
		}
		cout << endl << endl;
		run_times.clear();

		char* charPtr = const_cast<char*>(f_name.c_str());
		remove(charPtr);
	}
	cout << "--------------------------------" << endl;
	return;
}


void plot3();
void plot4();
void plot5();