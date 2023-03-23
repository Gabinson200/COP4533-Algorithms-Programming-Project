#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

using namespace std;

//Brute force O(m * n^2)
void Alg1(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    //set m number of stocks with n number of days
    int m = A.size();
    int n = A[0].size();
    cout << "Vector size: " << m << "x" << n << endl;
    int profit = 0;

    //for each stock initialize the profit to 0 and loop through the rows
    for (int i = 0; i < m; i++) {
        int sell = 1;
        int buy = 0;
        //loop through the columns and find the maximum value
        for (int j = 1; j < n; j++) {
            if (A[i][j] >= A[i][sell]) {
                sell = j;
            }
            //in the column find the minimum value before the position of the maximum value
            for (int k = 0; k < sell; k++) {
                if (A[i][k] < A[i][buy]) {
                    buy = k;
                }
            }
        }
        //if the current row's max profit is the highest profit update profit value and note row position
        int current_profit = A[i][sell] - A[i][buy];
        if (current_profit > profit) {
            profit = current_profit;
            *stock = i;
            *buy_day = buy;
            *sell_day = sell;
        }
    }
}

//Greedy O(m*n)
void Alg2(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    //set m number of stocks with n number of days
    int m = A.size();
    int n = A[0].size();
    cout << "Vector size: " << m << "x" << n << endl;
    int profit = 0;

    //for each stock initialize the profit to 0 and loop through the rows
    for (int i = 0; i < m; i++) {
        int sell = 1;
        int buy = 0;

        //loop through the columns
        for (int j = 1; j < n; j++) {
            //find the maximum value
            if (A[i][j] >= A[i][sell]) {
                sell = j;
            }
        }

        for (int k = 0; k < sell; k++) {
            //in the column find the minimum value before the position of the maximum value
            if (A[i][k] < A[i][buy]) {
                buy = k;
            }
        }

        //if the current row's max profit is the highest profit update profit value and note row position
        int current_profit = A[i][sell] - A[i][buy];
        if (current_profit > profit) {
            profit = current_profit;
            *stock = i;
            *buy_day = buy;
            *sell_day = sell;

        }
    }
}

vector<vector<int>> problem_one_file_to_vec(string filename) {
    ifstream infile(filename);
    vector<vector<int>> result;
    string line;
    int m, n;

    // Read the first line to get m and n
    getline(infile, line);
    istringstream iss(line);
    iss >> m >> n;

    // Read each of the next m lines to get the n integers in each row
    for (int i = 0; i < m; i++) {
        vector<int> row;
        getline(infile, line);
        istringstream iss(line);
        for (int j = 0; j < n; j++) {
            int val;
            iss >> val;
            row.push_back(val);
        }
        result.push_back(row);
    }

    return result;
}

void problem_one_create_file(string filename, int m, int n) {
    ofstream outfile(filename);
    outfile << m << " " << n << endl;

    // Generate and write m lines of n random integers each
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 10000);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            outfile << dist(gen) << " ";
        }
        outfile << std::endl;
    }
}


int main() {
    //Declare variables
    int stock = -1;
    int buy_day = 0;
    int sell_day = 1;

    vector<vector<int>> A
    {
        {6, 8, 22, 1},
        {1, 0, 3, 8},
        {4, 5, 6, 10},
        {25, 8, 9, 1 }
    };

    vector<vector<int>> B
    {
        {7, 6, 22, 1},
        {1, 0, 3, 8},
        {0, 5, 6, 100},
        {25, 8, 9, 1 }
    };

    vector<vector<int>> C
    {
        {7, 6, 22, 1},
        {1, 0, 3, 8},
        {4, 5, 100, 10},
        {25, 8, 9, 1 }
    };

    cout << "algos on A" << endl;
    Alg1(A, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg2(A, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    cout << "algos on B" << endl;
    Alg1(B, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg2(B, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    cout << "algos on C" << endl;
    Alg1(C, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg2(C, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;


    cout << endl << "NOW TESTING P1 WITH READ FILE FUNCTION AND RANDOMLY GENERATED VALUES 5 by 10" << endl;

    problem_one_create_file("P1_5_10.txt", 5, 10);
    vector<vector<int>> P1_5_10 = problem_one_file_to_vec("P1_5_10.txt");

    Alg1(P1_5_10, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg2(P1_5_10, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;

    cout << endl << "NOW TESTING P1 WITH READ FILE FUNCTION AND RANDOMLY GENERATED VALUES 10 by 20" << endl;

    problem_one_create_file("P1_10_20.txt", 10, 20);
    vector<vector<int>> P1_10_20 = problem_one_file_to_vec("P1_10_20.txt");

    Alg1(P1_10_20, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg2(P1_10_20, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;

    return 0;
}
