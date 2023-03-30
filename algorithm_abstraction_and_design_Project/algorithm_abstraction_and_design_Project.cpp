#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <tuple>
using namespace std;

//Problem 1

//Brute force O(m * n^2)
void Alg1(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    //set m number of stocks with n number of days
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 1 Brute force" << endl;
    //cout << "Vector size: " << m << "x" << n << endl;
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

//Greedy O(m*n) find min and then find max val after the min
void Alg2(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    //set m number of stocks with n number of days
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 2 Greedy approach" << endl;
    //cout << "Vector size: " << m << "x" << n << endl;
    int profit = 0;

    //for each stock initialize the profit to 0 and loop through the rows
    for (int i = 0; i < m; i++) {
        int sell = 1;
        int buy = 0;

        //loop through the columns
        for (int j = 1; j < n; j++) {
            //find the minimum value
            if (A[i][j] < A[i][buy]) {
                buy = j;
            }
        }

        for (int k = buy; k < n; k++) {
            //in the column find the maximum value after the position of the minimum value
            if (A[i][k] > A[i][sell]) {
                sell = k;
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

//DP w/ Memo
void Alg3a(vector<vector<int>> A, int* stock, int* buy_day, int* sell_day) {
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 3A Dynamic programming with memoization" << endl;
    //allocate the arrays 
    int** dp = new int* [m];
    for (int i = 0; i < m; i++)
        dp[i] = new int[n]{0};

    int profit = 0;
    for (int i = 0; i < m; i++) {
        int max = -10000000;
        int min = 10000000;
        int buy = 0;
        int sell = 0;
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i][j - 1] + A[i][j] - A[i][j - 1];
        }

        for (int j = 0; j < n; j++) {
            if (dp[i][j] > max) {
                sell = j;
                max = dp[i][j];
            }

            if (dp[i][j] < min && j < sell) {
                buy = j;
                min = dp[i][j];
            }
            //for visualization
            //cout << dp[i][j] << " ";
        }

        if (dp[i][sell] - dp[i][buy] > profit) {
            profit = dp[i][sell] - dp[i][buy];
            *stock = i;
            *buy_day = buy;
            *sell_day = sell;
        }
        //for visualization
        //cout << endl;
    }
    
    //deallocate the arrays
    for (int i = 0; i < m; i++)
        delete[] dp[i];
    delete[] dp;
}

//DP Bottom up 
void Alg3b(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 3B Dynamic programming with bottom up approach" << endl;

    int profit = 0;
    for (int i = 0; i < m; i++) {
  
        int buy = 0;
        int sell_pos = 0;
        int buy_pos = 0;
        int max_diff = A[i][1] - A[i][0];

        for (int j = 1; j < n; j++){

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
    cout << "In algorithm 4" << endl;
    //cout << "Vector size: " << m << "x" << n << endl;
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


void Alg5(vector<vector<int>>& A, int k) {
    int m = A.size();
    int n = A[0].size();
    int stock = -1;
    int buy_day = 0;
    int sell_day = 1;

    //Alg3b(A, &stock, &buy_day, &sell_day);
    //cout << stock << " " << buy_day << " " << sell_day << endl;
    return;
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

/*
void Alg5(vector<vector<int>>& A, int k) {
    int m = A.size();
    int n = A[0].size();
    int c = 0;
    cout << "In algorithm 5 Dynamic programming O(m*n*n*k)" << endl;
    //cout << "Vector size: " << m << "x" << n << endl;
    //vector<vector<int>> trans(k + 1, vector<int>(n, 0));
    //for visualization
    while (c < k) {
        int stock = 0;
        int buy_day = 0;
        int sell_day = 1;
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
                stock = i;
                buy_day = buy;
                sell_day = sell;
            }
        }
        cout << stock << " " << buy_day << " " << sell_day << endl;
        //Updating matrix A
        // check if i is a valid index
        if (stock < 0 || stock >= A.size()) {
            cout << "Error: Invalid row index i" << endl;
            return;
        }
        // check if a and b are valid indices
        if (buy_day < 0 || sell_day < 0 || buy_day >= A[stock].size() || sell_day >= A[stock].size()) {
            cout << "Error: Invalid indices a and b" << endl;
            return;
        }
        // set the elements between index a and b to 0
        for (int j = buy_day; j <= sell_day; j++) {
            A[stock][j] = 0;
        }
        c += 1;
    }
    return;
}
*/

//DP approach with memoization
vector<pair<int, int>> Alg6(const vector<vector<int>>& prices, int k) {
    int m = prices.size(), n = prices[0].size();
    vector<vector<int>> dp(k + 1, vector<int>(n, 0));
    vector<vector<pair<int, int>>> transactions(k + 1, vector<pair<int, int>>(n, { -1, -1 }));

    for (int t = 1; t <= k; t++) {
        for (int stock = 0; stock < m; stock++) {
            int maxDiff = -prices[stock][0];
            for (int day = 1; day < n; day++) {
                int prevMaxDiff = maxDiff;
                maxDiff = max(maxDiff, dp[t - 1][day - 1] - prices[stock][day]);
                dp[t][day] = max(dp[t][day], prices[stock][day] + maxDiff);

                if (dp[t][day] > dp[t][day - 1]) {
                    transactions[t][day] = { stock, day };
                }
                else {
                    transactions[t][day] = transactions[t][day - 1];
                }
            }
        }
    }
    vector<pair<int, int>> bestTransactions;
    int remainingTransactions = k;
    int currentDay = n - 1;

    while (remainingTransactions > 0 && currentDay > 0) {
        if (transactions[remainingTransactions][currentDay] != transactions[remainingTransactions][currentDay - 1]) {
            int buyDay = transactions[remainingTransactions][currentDay].second;
            bestTransactions.push_back({ transactions[remainingTransactions][currentDay].first, buyDay });

            for (int day = buyDay - 1; day >= 0; day--) {
                if (dp[remainingTransactions - 1][day] == dp[remainingTransactions][buyDay] - prices[transactions[remainingTransactions][currentDay].first][buyDay]) {
                    bestTransactions.push_back({ transactions[remainingTransactions][currentDay].first, day });
                    currentDay = day;
                    break;
                }
            }

            remainingTransactions--;
        }
        else {
            currentDay--;
        }
    }

    reverse(bestTransactions.begin(), bestTransactions.end());
    return bestTransactions;
}

//Test case functions
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
    //Alg4(B, &stock, &buy_day, &sell_day, 2);
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

    for (int i = 0; i < 3; i++) {
        cout << endl << "NOW TESTING P1 WITH READ FILE FUNCTION AND RANDOMLY GENERATED VALUES 10 by 20" << endl;

        problem_one_create_file("P1_10_20.txt", 10, 20);
        vector<vector<int>> P1_10_20 = problem_one_file_to_vec("P1_10_20.txt");

        Alg1(P1_10_20, &stock, &buy_day, &sell_day);
        cout << stock << " " << buy_day << " " << sell_day << endl;
        Alg2(P1_10_20, &stock, &buy_day, &sell_day);
        cout << stock << " " << buy_day << " " << sell_day << endl;
        //Alg3a(P1_10_20, &stock, &buy_day, &sell_day);
        //cout << stock << " " << buy_day << " " << sell_day << endl;
        Alg3b(P1_10_20, &stock, &buy_day, &sell_day);
        cout << stock << " " << buy_day << " " << sell_day << endl;
    }

    return 0;
}
