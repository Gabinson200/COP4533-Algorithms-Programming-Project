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
        }
        //in the column find the minimum value before the position of the maximum value
        for (int j = 0; j < *sell_day; j++) {
            if (A[i][j] < A[i][*buy_day]) {
                *buy_day = j;
            }
        }
        //if the current row's max profit is the highest profit update profit value and note row position
        if ((A[i][*sell_day] - A[i][*buy_day]) > profit){
            profit = (A[i][*sell_day] - A[i][*buy_day]);
            *stock = i;
        }
    }
}

int main() {
    int stock = -1;
    int buy_day = 0;
    int sell_day = 1;

    vector<vector<int>> A
    {
        {1, 0, 3, 8},
        {4, 5, 6, 10},
        {7, 8, 9, 22}
    };

    Alg1(A, &stock, &buy_day, &sell_day);
    cout << "Stock: " << stock << endl;
    cout << "Day to buy: " << buy_day << endl;
    cout << "Day to sell: " << sell_day << endl;
    return 0;
}
