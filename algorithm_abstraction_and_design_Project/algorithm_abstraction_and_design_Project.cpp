#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>
#include <tuple>
using namespace std;


//helper function
void print_A(vector<vector<int>> A) {
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < A[i].size(); j++) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//Problem 1

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

        for (int j = 0; j < n; j++){
            for (int k = j + 1; k < n; k++){
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

//Greedy O(m*n) WORKS
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

//DP w/ Memo
void Alg3a(vector<vector<int>> A, int* stock, int* buy_day, int* sell_day) {
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 3A Dynamic programming with memoization" << endl;
    //allocate the arrays
    int** dp = new int* [m];
    for (int i = 0; i < m; i++)
        dp[i] = new int[n-1]{0};

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
                sell = j+1;
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

//DP Bottom UP 
void Alg3b(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    //set m number of stocks with n number of days
    cout << "In algorithm 3B Dynamic programming" << endl;
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
    if (profit == 0 || (*buy_day < 0 || *buy_day > n - 1) || (*sell_day < 1 && *sell_day > n)) {
        //cout << "No viable stock to buy and sell" << endl;
        *stock = -1;
        return;
    }
}


vector<vector<int>> combinations(int n, int k, vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> curr;

    // base case: if k is zero, return empty vector
    if (k == 0) {
        res.push_back(curr);
        return res;
    }

    // base case: if n is less than k, return empty vector
    if (n < k) {
        return res;
    }

    // recursive case 1: choose the first element
    curr.push_back(nums[n - 1]);
    vector<vector<int>> res1 = combinations(n - 1, k - 1, nums);

    // append the current element to each combination
    for (auto& c : res1) {
        c.push_back(nums[n - 1]);
        res.push_back(c);
    }

    // recursive case 2: don't choose the first element
    curr.pop_back();
    vector<vector<int>> res2 = combinations(n - 1, k, nums);

    // append the combinations from recursive case 2 to the result
    for (auto& c : res2) {
        res.push_back(c);
    }

    return res;
}

void Alg4(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day, int k) {
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 4" << endl;
    for (int i = 0; i < m; i++) {
        vector<vector<int>> res = combinations(n, k, A[i]);
        // print the result
        //for (auto& c : res) {
        //    for (auto& i : c) {
        //        cout << i << " ";
        //    }
        //    cout << endl;
        //}
    }
}



int computeProfit(vector<vector<int>>& A, vector<int>& transactions) {
    int profit = 0;
    int m = A.size();
    int n = A[0].size();
    int k = transactions.size() / 2;
    for (int i = 0; i < k; i++) {
        int buy = transactions[2 * i];
        int sell = transactions[2 * i + 1];
        if (A[0][buy] < A[0][sell]) {
            profit += A[0][sell] - A[0][buy];
        }
    }
    return profit;
}

int maxProfit(vector<vector<int>>& A, int k) {
    int m = A.size();
    int n = A[0].size();
    int maxProfit = 0;
    vector<int> transactions;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i; j < n; j++) {
            transactions.push_back(i);
            transactions.push_back(j);
            maxProfit = max(maxProfit, computeProfit(A, transactions));
            transactions.pop_back();
            transactions.pop_back();
        }
    }
    return maxProfit;
}

void Alg5(vector<vector<int>>& A, int k) {
    cout << "In algo 5" << endl;
    int m = A.size();
    int n = A[0].size();

    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k + 1, 0)));

    for (int i = 0; i < m; ++i) {
        for (int t = 1; t <= k; ++t) {
            for (int j = 1; j < n; ++j) {
                int maxProfit = 0;
                for (int x = 0; x < j; ++x) {
                    maxProfit = max(maxProfit, A[i][j] - A[i][x] + dp[i][x][t - 1]);
                }
                dp[i][j][t] = max(dp[i][j - 1][t], maxProfit);
            }
        }
    }

    int result = 0;
    for (int i = 0; i < m; ++i) {
        result = max(result, dp[i][n - 1][k]);
        cout << result << endl;
    }

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

//Algo 6
/*
int maxProfit(vector<vector<int>>& A, int k) {
    int m = A.size();
    int n = A[0].size();
    cout << "In algorithm 6" << endl;
    if (k >= n / 2){
        int ans = 0;
        for (int i = 1; i < n; i++){
            ans += max(0, A[0][i] - A[0][i - 1]);
        }
        return ans;
    }
    vector<vector<int>> dp(k + 1, vector<int>(n, 0));
    for (int i = 1; i <= k; i++) {
        int maxDiff = INT_MIN;
        for (int j = 1; j < n; j++) {
            maxDiff = max(maxDiff, dp[i - 1][j - 1] - A[0][j - 1]);
            dp[i][j] = max(dp[i][j - 1], maxDiff + A[0][j]);
        }
    }
    return dp[k][n - 1];
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
        {0, 8, 3, 8},
        {1, 0, 0, 9},
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
        {5, 7, 100, 10},
        {25, 8, 1, 100}
    };

    cout << "algos on A" << endl;
    cout << maxProfit(A, 2) << endl;
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
    Alg4(B, &stock, &buy_day, &sell_day, 2);
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg5(A, 2);

    stock = -1;
    buy_day = 0;
    sell_day = 1;

    cout << "algos on B" << endl;
    cout << maxProfit(B, 2) << endl;
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
    Alg4(B, &stock, &buy_day, &sell_day, 2);
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg5(B, 2);
    stock = -1;
    buy_day = 0;
    sell_day = 1;

    cout << "algos on C" << endl;
    cout << maxProfit(C, 2) << endl;
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
    Alg4(C, &stock, &buy_day, &sell_day, 2);
    stock = -1;
    buy_day = 0;
    sell_day = 1;
    Alg5(C, 2);
    stock = -1;
    buy_day = 0;
    sell_day = 1;


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
        Alg3a(P1_10_20, &stock, &buy_day, &sell_day);
        cout << stock << " " << buy_day << " " << sell_day << endl;
        Alg3b(P1_10_20, &stock, &buy_day, &sell_day);
        cout << stock << " " << buy_day << " " << sell_day << endl;
    }

    return 0;
}
