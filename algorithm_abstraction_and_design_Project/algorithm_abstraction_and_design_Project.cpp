#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <tuple>
#include <queue>

#include "functions.h"
#include "tests.h"

using namespace std;


///helper functions

void print_A(vector<vector<int>> A) {
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
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

vector<vector<int>> problem_two_file_to_vec(string filename, int* k) {
    ifstream infile(filename);
    vector<vector<int>> result;
    string line;
    int m, n;

    // Read the first line to get k
    getline(infile, line);
    *k = stoi(line);
    // Read the second line to get m and n
    getline(infile, line);
    istringstream bss(line);
    bss >> m >> n;

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

void problem_two_create_file(string filename, int k, int m, int n) {
    ofstream outfile(filename);
    outfile << k << endl;
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


//------------------------------------------------------------------------------------------------------------

///Problem 1

//Brute force O(m * n^2) WORKS
void Alg1(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    //set m number of stocks with n number of days
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 1 Brute force" << endl;
    int profit = 0;

    //for each stock initialize the profit to 0 and loop through the rows
    for (int i = 0; i < m; i++) {
        int buy = 0;
        int sell = 0;
        int current_profit = A[i][1] - A[i][0];

        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (A[i][k] - A[i][j] > current_profit) {
                    current_profit = A[i][k] - A[i][j];
                    buy = j;
                    sell = k;
                }
            }
        }

        if (current_profit > profit) {
            profit = current_profit;
            *stock = i;
            *buy_day = buy;
            *sell_day = sell;
        }
    }
    return;
}

//Brute force O(m * n^2) LINUX way
void Alg1(string filename) {
    //set m number of stocks with n number of days
    vector<vector<int>> A = problem_one_file_to_vec(filename);
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 1 Brute force" << endl;
    int profit = 0;
    int stock = -1;
    int buy_day = -1;
    int sell_day = -1;

    //for each stock initialize the profit to 0 and loop through the rows
    for (int i = 0; i < m; i++) {
        int buy = 0;
        int sell = 0;
        int current_profit = A[i][1] - A[i][0];

        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (A[i][k] - A[i][j] > current_profit) {
                    current_profit = A[i][k] - A[i][j];
                    buy = j;
                    sell = k;
                }
            }
        }

        if (current_profit > profit) {
            profit = current_profit;
            stock = i;
            buy_day = buy;
            sell_day = sell;
        }
    }
    cout << stock << " " << buy_day << " " << sell_day << endl;
    return;
}

//Greedy O(m*n)
void Alg2(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 2 Greedy approach" << endl;

    int profit = 0;
    for (int i = 0; i < m; i++) {

        int buy = 0;
        int sell_pos = 0;
        int buy_pos = 0;
        int max_diff = A[i][1] - A[i][0];

        for (int j = 1; j < n; j++) {

            if (A[i][j] - A[i][buy] > max_diff) {
                buy_pos = buy;
                max_diff = A[i][j] - A[i][buy_pos];
                sell_pos = j;
            }

            if (A[i][j] < A[i][buy]) {
                buy = j;
            }
        }

        if (max_diff > profit) {
            profit = max_diff;
            *stock = i;
            *buy_day = buy_pos;
            *sell_day = sell_pos;
        }
    }
    return;
}

//Greedy O(m*n) LINUX WAY
void Alg2(string filename) {
    vector<vector<int>> A = problem_one_file_to_vec(filename);
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 2 Greedy approach" << endl;
    int profit = 0;
    int stock = -1;
    int buy_day = -1;
    int sell_day = -1;

    for (int i = 0; i < m; i++) {

        int buy = 0;
        int sell_pos = 0;
        int buy_pos = 0;
        int max_diff = A[i][1] - A[i][0];

        for (int j = 1; j < n; j++) {

            if (A[i][j] - A[i][buy] > max_diff) {
                buy_pos = buy;
                max_diff = A[i][j] - A[i][buy_pos];
                sell_pos = j;
            }

            if (A[i][j] < A[i][buy]) {
                buy = j;
            }
        }

        if (max_diff > profit) {
            profit = max_diff;
            stock = i;
            buy_day = buy_pos;
            sell_day = sell_pos;
        }
    }
    cout << stock << " " << buy_day << " " << sell_day << endl;
    return;
}

//DP w/ Memo
void Alg3a(vector<vector<int>> A, int* stock, int* buy_day, int* sell_day) {
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 3A Dynamic programming with memoization" << endl;
    //allocate the arrays
    int** dp = new int* [m];
    for (int i = 0; i < m; i++)
        dp[i] = new int[n - 1] {0};

    int max_profit = 0;

    for (int i = 0; i < m; i++) {
        //fill it with differences
        for (int j = 0; j < n - 1; j++) {
            dp[i][j] = A[i][j + 1] - A[i][j];
        }

        int profit = dp[i][0];
        int buy = 0;
        int sell = 1;
        int count = 0;

        //find maximum sum subarray 
        //cout << dp[i][0] << " ";
        for (int j = 1; j < n - 1; j++) {

            if (dp[i][j - 1] > 0) {
                dp[i][j] += dp[i][j - 1];
                count += 1;
            }
            else {
                count = 0;
            }

            if (dp[i][j] > profit) {
                profit = dp[i][j];
                sell = j + 1;
                buy = sell - count - 1;
            }

        }

        if (profit > max_profit) {
            max_profit = profit;
            //cout << "Max profit: " << max_profit << endl;
            *stock = i;
            *buy_day = buy;
            *sell_day = sell;
        }
    }

    //deallocate array
    for (int i = 0; i < m; i++)
        delete[] dp[i];
    delete[] dp;
}

//DP w/ Memo LINUX WAY
void Alg3a(string filename) {
    vector<vector<int>> A = problem_one_file_to_vec(filename);
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 3A Dynamic programming with memoization" << endl;
    //allocate the arrays
    int** dp = new int* [m];
    for (int i = 0; i < m; i++)
        dp[i] = new int[n - 1] {0};

    int max_profit = 0;
    int stock = -1;
    int buy_day = -1;
    int sell_day = -1;

    for (int i = 0; i < m; i++) {
        //fill it with differences
        for (int j = 0; j < n - 1; j++) {
            dp[i][j] = A[i][j + 1] - A[i][j];
        }

        int profit = dp[i][0];
        int buy = 0;
        int sell = 1;
        int count = 0;

        //find maximum sum subarray 
        //cout << dp[i][0] << " ";
        for (int j = 1; j < n - 1; j++) {

            if (dp[i][j - 1] > 0) {
                dp[i][j] += dp[i][j - 1];
                count += 1;
            }
            else {
                count = 0;
            }

            if (dp[i][j] > profit) {
                profit = dp[i][j];
                sell = j + 1;
                buy = sell - count - 1;
            }

        }

        if (profit > max_profit) {
            max_profit = profit;
            //cout << "Max profit: " << max_profit << endl;
            stock = i;
            buy_day = buy;
            sell_day = sell;
        }
    }

    cout << stock << " " << buy_day << " " << sell_day << endl;

    //deallocate array
    for (int i = 0; i < m; i++)
        delete[] dp[i];
    delete[] dp;

    return;
}

//DP Bottom UP 
void Alg3b(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    //set m number of stocks with n number of days
    cout << "In algorithm 3B Dynamic programming " << endl;
    int m = A.size();
    int n = A[0].size();
    //cout << "In 3B DP approach" << endl;
    int profit = 0;

    for (int i = 0; i < m; i++) {
        int sell = 0;
        int buy = 0;
        // Initialize diff, current sum and max sum
        int diff = A[i][1] - A[i][0];
        int curr_sum = diff;
        int max_sum = curr_sum;
        int count = 0;

        for (int j = 1; j < n - 1; j++) {
            if (A[i][j] != -1) {

                // Calculate current diff
                diff = A[i][j + 1] - A[i][j];

                // Calculate current sum
                if (curr_sum > 0) {
                    curr_sum += diff;
                    count += 1;
                }
                else {
                    curr_sum = diff;
                    count = 0;
                }

                // Update max sum, if needed
                if (curr_sum > max_sum) {
                    max_sum = curr_sum;
                    sell = j + 1;
                    buy = sell - count - 1;
                }
            }
        }

        //if the current row's max profit is the highest profit update profit value and note row position
        if (max_sum > profit) {
            profit = max_sum;
            *stock = i;
            *buy_day = buy;
            *sell_day = sell;
        }
    }
}

//DP Bottom UP LINUX WAY
void Alg3b(string filename) {
    cout << "In algorithm 3B Dynamic programming " << endl;
    vector<vector<int>> A = problem_one_file_to_vec(filename);
    //set m number of stocks with n number of days
    int m = A.size();
    int n = A[0].size();
    //cout << "In 3B DP approach" << endl;
    int profit = 0;
    int stock = -1;
    int buy_day = -1;
    int sell_day = -1;

    for (int i = 0; i < m; i++) {
        int sell = 0;
        int buy = 0;
        // Initialize diff, current sum and max sum
        int diff = A[i][1] - A[i][0];
        int curr_sum = diff;
        int max_sum = curr_sum;
        int count = 0;

        for (int j = 1; j < n - 1; j++) {
            if (A[i][j] != -1) {

                // Calculate current diff
                diff = A[i][j + 1] - A[i][j];

                // Calculate current sum
                if (curr_sum > 0) {
                    curr_sum += diff;
                    count += 1;
                }
                else {
                    curr_sum = diff;
                    count = 0;
                }

                // Update max sum, if needed
                if (curr_sum > max_sum) {
                    max_sum = curr_sum;
                    sell = j + 1;
                    buy = sell - count - 1;
                }
            }
        }

        //if the current row's max profit is the highest profit update profit value and note row position
        if (max_sum > profit) {
            profit = max_sum;
            stock = i;
            buy_day = buy;
            sell_day = sell;
        }
    }
    cout << stock << " " << buy_day << " " << sell_day << endl;

    return;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

/// Part 2 


//recursive function used by Algo 4
void get_greatest_profits(vector<vector<int>> A, int k, int begin,
    vector<vector<vector<int>>>& combos, vector<vector<int>>& combo,
    vector<vector<int>>& trans, int& max_profit) {
    int m = A.size();
    int n = A[0].size();
    

    if (k == 0) {
        combos.push_back(combo);
        int total_profit = 0;
        for (int i = 0; i < combo.size(); i++) {
            int stock = combo[i][0];
            int buy = combo[i][1];
            int sell = combo[i][2];

            if (A[stock][sell] - A[stock][buy] > 0)
                total_profit += A[stock][sell] - A[stock][buy];
        }

        if (total_profit > max_profit) {
            max_profit = total_profit;
            trans.clear();

            for (int g = 0; g < combo.size(); g++) {
                if (A[combo[g][0]][combo[g][2]] - A[combo[g][0]][combo[g][1]] > 0)
                    trans.push_back(combo[g]);
            }
        }
        return;
    }

    //cout << "works up unitl here" << endl;
    for (int i = begin; i < n; ++i){
        for (int j = i + 1; j < n; ++j) {
            for (int l = 0; l < m; ++l) {
                //cout << l << " " << i << " " << j << endl;
                vector<int> v = {l, i, j};
                combo.push_back(v);
                get_greatest_profits(A, k - 1, j, combos, combo, trans, max_profit);
                //cout << "didnt reach this" << endl;
                combo.pop_back();
            }
        }
    }
}


//Algo4 (m * (n chose k))
void Alg4(vector<vector<int>> A, int k) {
    cout << "In Algo 4" << endl;
    int begin = 0;
    vector<vector<vector<int>>> combos;
    vector<vector<int>> combo;
    vector<vector<int>> trans;
    int max_profit;
    get_greatest_profits(A, k, begin, combos, combo, trans, max_profit);
    print_A(trans);
    return; 
}

//Algo4 (m * (n chose k))
void Alg4(string filename) {
    int k;
    vector<vector<int>> A = problem_two_file_to_vec(filename, &k);
    cout << "In Algo 4" << endl;
    int begin = 0;
    vector<vector<vector<int>>> combos;
    vector<vector<int>> combo;
    vector<vector<int>> trans;
    int max_profit;
    get_greatest_profits(A, k, begin, combos, combo, trans, max_profit);
    print_A(trans);
    return;
}

typedef pair<int, int> pii;

//DP (m x n^2 x k)
void Alg5(vector<vector<int>> A, int k) {
    cout << "In algo 5" << endl;
    int m = A.size();
    int n = A[0].size();
    cout << "k: " << k << " m: " << m << " n: " << n << endl;
    vector<vector<int>> stocks(k + 1, vector<int>(n, -1));
    vector<vector<int>> DP(k + 1, vector<int>(n, 0));
    vector<vector<pii>> prev(k + 1, vector<pii>(n, make_pair(-1, -1)));
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j < n; j++) {
            int max_profit = 0;
            int buy_day = -1, sell_day = -1;
            int stock = -1;
            for (int l = 0; l < j; l++) {
                int max_diff = 0;
                int c_stock = -1;
                for (int p = 0; p < m; p++) {
                    if (max_diff >= A[p][j] - A[p][l])
                        max_diff = max_diff;
                    else if (max_diff < A[p][j] - A[p][l]) {
                        max_diff = A[p][j] - A[p][l];
                        c_stock = p;
                    }
                }
                int profit = DP[i - 1][l] + max_diff;
                if (profit > max_profit) {
                    max_profit = profit;
                    buy_day = l;
                    sell_day = j;
                    stock = c_stock;
                }
            }

            if (max_profit > DP[i][j - 1]) {
                DP[i][j] = max_profit;
                prev[i][j] = make_pair(buy_day, sell_day);
                stocks[i][j] = stock;
            }
            else {
                DP[i][j] = DP[i][j - 1];
            }
        }
    }
    //backtracking to find stocks, buy, and sell days 
    //print_A(DP);
    //cout << endl << endl;
    //print_A(stocks);
    /*
    for (int i = 0; i < prev.size(); i++) {
        for (int j = 0; j < prev[i].size(); j++) {
            cout << "(" << prev[i][j].first << ", " << prev[i][j].second << ") ";
        }
        cout << endl;
    }
    */
    int total_profit = DP[k][n - 1];
    cout << "Total profit: " << total_profit << endl;

    vector<pii> res;
    vector<int> stocky;
    int i = k, j = n - 1;
    while (i > 0 && j > 0) {
        pii p = prev[i][j];
        int stck = stocks[i][j];
        if (p.first == -1 || p.second == -1) {
            //i--;
            j--;
            //break;
        }
        else {
            //cout << stck << " " << p.first << " " << p.second << endl;
            res.push_back(p);
            stocky.push_back(stck);
            i--;
            j = p.first;
        }
    }
    reverse(res.begin(), res.end());
    reverse(stocky.begin(), stocky.end());

    for (int i = 0; i < k; i++) {
        cout << stocky[i] << ", " << res[i].first << ", " << res[i].second << endl;
    }

    return;
}

//DP (m x n^2 x k) LINUX WAY
void Alg5(string filename) {
    int k;
    vector<vector<int>> A = problem_two_file_to_vec(filename, &k);
    cout << "In algo 5" << endl;
    int m = A.size();
    int n = A[0].size();
    //cout << "k: " << k << " m: " << m << " n: " << n << endl;
    vector<vector<int>> stocks(k + 1, vector<int>(n, -1));
    vector<vector<int>> DP(k + 1, vector<int>(n, 0));
    vector<vector<pii>> prev(k + 1, vector<pii>(n, make_pair(-1, -1)));
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j < n; j++) {
            int max_profit = 0;
            int buy_day = -1, sell_day = -1;
            int stock = -1;
            for (int l = 0; l < j; l++) {
                int max_diff = 0;
                int c_stock = -1;
                for (int p = 0; p < m; p++) {
                    if (max_diff >= A[p][j] - A[p][l])
                        max_diff = max_diff;
                    else if (max_diff < A[p][j] - A[p][l]) {
                        max_diff = A[p][j] - A[p][l];
                        c_stock = p;
                    }
                }
                int profit = DP[i - 1][l] + max_diff;
                if (profit > max_profit) {
                    max_profit = profit;
                    buy_day = l;
                    sell_day = j;
                    stock = c_stock;
                }
            }

            if (max_profit > DP[i][j - 1]) {
                DP[i][j] = max_profit;
                prev[i][j] = make_pair(buy_day, sell_day);
                stocks[i][j] = stock;
            }
            else {
                DP[i][j] = DP[i][j - 1];
            }
        }
    }
    
    int total_profit = DP[k][n - 1];
    //cout << "Total profit: " << total_profit << endl;

    vector<pii> res;
    vector<int> stocky;
    int i = k, j = n - 1;
    while (i > 0 && j > 0) {
        pii p = prev[i][j];
        int stck = stocks[i][j];
        if (p.first == -1 || p.second == -1) {
            j--;
        }
        else {
            //cout << stck << " " << p.first << " " << p.second << endl;
            res.push_back(p);
            stocky.push_back(stck);
            i--;
            j = p.first;
        }
    }
    reverse(res.begin(), res.end());
    reverse(stocky.begin(), stocky.end());

    for (int i = 0; i < k; i++) {
        cout << stocky[i] << " " << res[i].first << " " << res[i].second << endl;
    }

    return;
}

//DP with memoization (m * n *k)
void Alg6(string filename) {
    int k;
    vector<vector<int>> A = problem_two_file_to_vec(filename, &k);
    cout << "In algo 6" << endl;
    int m = A.size();
    int n = A[0].size();
    //cout << "k: " << k << " m: " << m << " n: " << n << endl;
    vector<vector<int>> stocks(k + 1, vector<int>(n, -1));
    vector<vector<int>> DP(k + 1, vector<int>(n, 0));
    vector<vector<pii>> prev(k + 1, vector<pii>(n, make_pair(-1, -1)));
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j < n; j++) {
            int max_profit = 0;
            int buy_day = -1, sell_day = -1;
            int stock = -1;
            for (int l = 0; l < j; l++) {
                int max_diff = 0;
                int c_stock = -1;
                for (int p = 0; p < m; p++) {
                    if (max_diff >= A[p][j] - A[p][l])
                        max_diff = max_diff;
                    else if (max_diff < A[p][j] - A[p][l]) {
                        max_diff = A[p][j] - A[p][l];
                        c_stock = p;
                    }
                }
                int profit = DP[i - 1][l] + max_diff;
                if (profit > max_profit) {
                    max_profit = profit;
                    buy_day = l;
                    sell_day = j;
                    stock = c_stock;
                }
            }

            if (max_profit > DP[i][j - 1]) {
                DP[i][j] = max_profit;
                prev[i][j] = make_pair(buy_day, sell_day);
                stocks[i][j] = stock;
            }
            else {
                DP[i][j] = DP[i][j - 1];
            }
        }
    }

    int total_profit = DP[k][n - 1];
    //cout << "Total profit: " << total_profit << endl;

    vector<pii> res;
    vector<int> stocky;
    int i = k, j = n - 1;
    while (i > 0 && j > 0) {
        pii p = prev[i][j];
        int stck = stocks[i][j];
        if (p.first == -1 || p.second == -1) {
            j--;
        }
        else {
            //cout << stck << " " << p.first << " " << p.second << endl;
            res.push_back(p);
            stocky.push_back(stck);
            i--;
            j = p.first;
        }
    }
    reverse(res.begin(), res.end());
    reverse(stocky.begin(), stocky.end());

    for (int i = 0; i < k; i++) {
        cout << stocky[i] << " " << res[i].first << " " << res[i].second << endl;
    }

    return;

}




int main() {

    //plot1();
    //plot2();
    //plot3();
    //plot4();
    //plot5();







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
        {8, 5, 100, 10},
        {25, 8, 1, 100}
    };
    
    cout << "algos on A" << endl;
    Alg1(A, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg2(A, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg3a(A, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg3b(A, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg4(A, 2);
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg5(A, 2);

    stock = -1;
    buy_day = 0;
    sell_day = 1;

    cout << "algos on B" << endl;
    Alg1(B, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg2(B, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg3a(B, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg3b(B, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg4(B, 2);
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg5(B, 2);
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    cout << "algos on C" << endl;
    Alg1(C, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg2(C, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg3a(C, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg3b(C, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg4(C, 2);
    Alg5(C, 2);
    stock = -1;
    buy_day = 0;
    sell_day = 1;


    cout << endl << "NOW TESTING P1 WITH READ FILE FUNCTION AND RANDOMLY GENERATED VALUES 5 by 10" << endl;

    problem_one_create_file("P1_5_10.txt", 5, 10);
    vector<vector<int>> P1_5_10 = problem_one_file_to_vec("P1_5_10.txt");
    problem_two_create_file("P2_5_10.txt", 2, 5, 10);
    //vector<vector<int>> P2_5_10 = problem_two_file_to_vec("P2_5_10.txt");

    Alg1("P1_5_10.txt");
    Alg2("P1_5_10.txt");
    Alg3a("P1_5_10.txt");
    Alg3b("P1_5_10.txt");

    cout << endl << "NOW TESTING P2 WITH READ FILE FUNCTION AND RANDOMLY GENERATED VALUES 5 by 10" << endl;
    Alg4("P2_5_10.txt");
    Alg5("P2_5_10.txt");

    for (int i = 0; i < 3; i++) {
        cout << endl << "NOW TESTING P1 WITH READ FILE FUNCTION AND RANDOMLY GENERATED VALUES 10 by 20" << endl;

        problem_one_create_file("P1_10_20.txt", 10, 20);
        //vector<vector<int>> P1_10_20 = problem_one_file_to_vec("P1_10_20.txt");

        Alg1("P1_10_20.txt");
        Alg2("P1_10_20.txt");
        Alg3a("P1_10_20.txt");
        Alg3b("P1_10_20.txt");
    }

    //for (int i = 0; i < 3; i++) {
    cout << endl << "NOW TESTING P2 WITH READ FILE FUNCTION AND RANDOMLY GENERATED VALUES 10 by 20 and k value of 3" << endl;

    problem_two_create_file("P2_10_20.txt", 2, 10, 20);
        //vector<vector<int>> P1_10_20 = problem_one_file_to_vec("P1_10_20.txt");
    Alg4("P2_10_20.txt");
    Alg5("P2_10_20.txt");
    //}

    return 0;
}
