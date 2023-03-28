#include <iostream>
#include <fstream>
#include <sstream>
//#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
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
                //in the column find the minimum value before the position of the maximum value
                for (int k = 0; k < sell; k++) {
                    if (A[i][k] < A[i][buy]) {
                        buy = k;
                    }
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

/*
//Dynamic programming using recursion and memoization O(m*n)
int Alg3a(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day, int day) {
    //set m number of stocks with n number of days
    int m = A.size();
    int n = A[0].size();
    cout << "Vector size: " << m << "x" << n << endl;
    int profit = 0;

    if (day == n) return 0; 
    if (memo[day] != -1) return memo[day];

    int ans = 0, min_price = A[0][day];
    for (int i = 1; i < m; i++) {
        min_price = min(min_price, A[i][day]);
        ans = max(ans, A[i][day] - min_price);
    }

    return memo[day] = max(ans, Alg3a(day + 1));
  
}
*/

void Alg3a(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    int m = A.size();
    int n = A[0].size();
    cout << "Vector size: " << m << "x" << n << endl;
    //allocate the arrays
    int** dp = new int* [m];
    for (int i = 0; i < m; i++)
        dp[i] = new int[n];

    int** bd = new int* [m];
    for (int i = 0; i < m; i++)
        bd[i] = new int[n];

    int profit = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) { 
            dp[i][j] = dp[i][j - 1] + A[i][j] - A[i][j - 1];

            if (dp[i][j] > profit) {
                profit = dp[i][j];
                *stock = i;
                *sell_day = j;
                *buy_day = bd[i][j - 1];
            }

            bd[i][j] = bd[i][j - 1];
            if (dp[i][j - 1] < 0) {
                bd[i][j] = j - 1;
            }
            //for visualization
            //cout << dp[i][j] << " ";
        }
        //for visualization
        //cout << endl;
    }
    

    //deallocate the arrays
    for (int i = 0; i < m; i++)
        delete[] dp[i];
    delete[] dp;

    for (int i = 0; i < m; i++)
        delete[] bd[i];
    delete[] bd;
}


void Alg3b(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    int m = A.size();
    int n = A[0].size();
    cout << "Vector size: " << m << "x" << n << endl;
  
    int profit = 0;
    for (int i = 0; i < m; i++) {
        int buy = 0;
        int sell = 0;
        int current_profit = 0;

        for (int j = 1; j < n; j++) {

            if (A[i][j] < A[i][buy]) {
                buy = j;
            }

            if (A[i][j] - A[i][buy] > current_profit) {
                profit = A[i][j] - A[i][buy];
                sell = j;
            }
        }

        if (current_profit > profit && buy < sell) {
            profit = current_profit;
            *stock = i;
            *buy_day = buy;
            *sell_day = sell;
        }
    }
}




vector<vector<int>> getSubsets(vector<int>& nums, int k) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int i = 2; i < k; i++) {
        vector<int> subset;
        for (int j = 0; j < nums.size(); j++) {
            subset.push_back(nums[j]);
            if (subset.size() == i) {
                res.push_back(subset);
                subset.pop_back();
            }
            else {
                for (int k = j + 1; k < nums.size(); k++) {
                    subset.push_back(nums[k]);
                    if (subset.size() == i) {
                        res.push_back(subset);
                        subset.pop_back();
                    }
                }
            }
            subset.pop_back();
        }
    }
    return res;
}


vector<vector<int>> get_2k_subset(vector<int> nums, int k) {
    vector<vector<int>> subsets = { {} };
    for (int i = 0; i < nums.size(); i++) {
        int n = subsets.size();
        for (int j = 0; j < n; j++) {
            if (subsets[j].size() <= 2 * k) {
                vector<int> subset = subsets[j];
                subset.push_back(nums[i]);
                subsets.push_back(subset);
            }
        }
    }
    return subsets;
}


void Alg4(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day, int k) {
    int m = A.size();
    int n = A[0].size();
    cout << "Vector size: " << m << "x" << n << endl;
    for (int i = 0; i < m; i++) {
        vector<int> subset = {};
        for (int j = 0; j < n; j++) {
            subset.push_back(A[i][j]);
        }
        vector<vector<int>> subsets = get_2k_subset(subset, k);




        //visualization
        for (int i = 0; i < subsets.size(); i++) {
            // Loop over the elements of the row
            for (int j = 0; j < subsets[i].size(); j++) {
                // Print the element
                cout << subsets[i][j] << " ";
            }
            // Move to a new line after printing each row
            cout << endl;
        }
    }
}

/*
void Alg6(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day, int k) {
    int B;
    vector<int> A;
    int dp[501][201][2];
    int solve(int j, int i, int b){
        // if the result has already been calculated return that result
        if (dp[i][j][b] != -1)
            return dp[i][j][b];
        // if i has reached the end of the array return 0
        if (i == B)
            return 0;
        // if we have exhausted the number of transaction return 0
        if (j == 0)
            return 0;
        int res;
        // if we are to buy stocks
        if (b == 1)
            res = max(-A[i] + solve(j, i + 1, 0), solve(j, i + 1, 1));
        // if we are to sell stock and complete one transaction
        else
            res = max(A[i] + solve(j - 1, i + 1, 1), solve(j, i + 1, 0));
        // return the result
        return dp[i][j][b] = res;
    }
    int maxProfit(int K, int N, int C[])
    {
        A = vector<int>(N, 0);
        // Copying C to global A
        for (int i = 0; i < N; i++)
            A[i] = C[i];
        // Initializing DP with -1
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= K; j++)
            {
                dp[i][j][1] = -1;
                dp[i][j][0] = -1;
            }
        // Copying n to global B
        B = N;
        return solve(K, 0, 1);
    }
}
*/

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
        {8, 5, 100, 10},
        {25, 8, 1, 100}
    };

    cout << "algos on A" << endl;
    Alg1(A, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg2(A, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg3a(A, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg3b(A, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    //Alg4(A, &stock, &buy_day, &sell_day, 2);

    cout << "algos on B" << endl;
    Alg1(B, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg2(B, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg3a(B, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg3b(B, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    //Alg4(B, &stock, &buy_day, &sell_day, 2);

    cout << "algos on C" << endl;
    Alg1(C, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg2(C, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg3a(C, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg3b(C, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    //Alg4(C, &stock, &buy_day, &sell_day, 2);


    cout << endl << "NOW TESTING P1 WITH READ FILE FUNCTION AND RANDOMLY GENERATED VALUES 5 by 10" << endl;

    problem_one_create_file("P1_5_10.txt", 5, 10);
    vector<vector<int>> P1_5_10 = problem_one_file_to_vec("P1_5_10.txt");

    Alg1(P1_5_10, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg2(P1_5_10, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg3a(P1_5_10, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg3b(P1_5_10, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;

    cout << endl << "NOW TESTING P1 WITH READ FILE FUNCTION AND RANDOMLY GENERATED VALUES 10 by 20" << endl;

    problem_one_create_file("P1_10_20.txt", 10, 20);
    vector<vector<int>> P1_10_20 = problem_one_file_to_vec("P1_10_20.txt");

    Alg1(P1_10_20, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg2(P1_10_20, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg3a(P1_10_20, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;
    Alg3b(P1_10_20, &stock, &buy_day, &sell_day);
    cout << stock << " " << buy_day << " " << sell_day << endl;

    return 0;
}
