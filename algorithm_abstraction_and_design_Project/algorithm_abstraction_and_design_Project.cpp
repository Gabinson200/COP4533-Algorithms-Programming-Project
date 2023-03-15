#include <iostream>
#include <vector>
using namespace std;

//Brute force O(m * n^2)
void Alg1(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    //set m number of stocks with n number of days
    int m = A.size();
    int n = A[0].size();

    //for each stock initialize the profit to 0 and loop through the rows
    for (int i = 0; i < m; i++) {
        int profit = 0;
        //loop through the columns and find the maximum value
        for (int j = 1; j < n; j++) {
            if (A[i][j] > A[i][*sell_day]) {
                *sell_day = j;
            }
            //in the column find the minimum value before the position of the maximum value
            for (int k = 0; k < j; k++) {
                if (A[i][k] < A[i][*buy_day]) {
                    *buy_day = k;
                }
            }
        }
        //if the current row's max profit is the highest profit update profit value and note row position
        if ((A[i][*sell_day] - A[i][*buy_day]) > profit){
            profit = (A[i][*sell_day] - A[i][*buy_day]);
            *stock = i;
        }
    }
}

//Greedy O(m*n)
void Alg2(vector<vector<int>>& A, int* stock, int* buy_day, int* sell_day) {
    //set m number of stocks with n number of days
    int m = A.size();
    int n = A[0].size();

    //for each stock initialize the profit to 0 and loop through the rows
    for (int i = 0; i < m; i++) {
        int profit = 0;
        //loop through the columns
        for (int j = 1; j < n; j++) {
            //find the maximum value
            if (A[i][j] > A[i][*sell_day]) {
                *sell_day = j;
            }
            //in the column find the minimum value before the position of the maximum value
            if (A[i][j-1] < A[i][*buy_day]) {
                *buy_day = j-1;
            }
        }

        //if the current row's max profit is the highest profit update profit value and note row position
        if ((A[i][*sell_day] - A[i][*buy_day]) > profit) {
            profit = (A[i][*sell_day] - A[i][*buy_day]);
            *stock = i;
        }
    }
}

int main() {
    //Declare variables
    int stock = -1;
    int buy_day = 0;
    int sell_day = 0;

    vector<vector<int>> A
    {
        {1, 0, 3, 8},
        {4, 5, 6, 10},
        {7, 6, 22, 11}
    };

    Alg1(A, &stock, &buy_day, &sell_day);
    cout << "Algorithm 1 Brute Force O(m*n^2)" << endl;
    cout << "Stock: " << stock << endl;
    cout << "Day to buy: " << buy_day << endl;
    cout << "Day to sell: " << sell_day << endl;

    //Reset variables
    stock = -1;
    buy_day = 0;
    sell_day = 0;
    cout << endl;

    Alg2(A, &stock, &buy_day, &sell_day);
    cout << "Algorithm 2 Greedy  O(m*n)" << endl;
    cout << "Stock: " << stock << endl;
    cout << "Day to buy: " << buy_day << endl;
    cout << "Day to sell: " << sell_day << endl;


    return 0;
}
