#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
using namespace chrono;

// Recursive Algorithm
bool findPairRecursive(const vector<int>& A, int k, int left, int right) {
    if (left >= right) return false;

    int sum = A[left] + A[right];
    if (sum == k) return true;
    else if (sum < k) return findPairRecursive(A, k, left + 1, right);
    else return findPairRecursive(A, k, left, right - 1);
}

// Recursive wrapper
bool findPairRecursiveWrapper(const vector<int>& A, int k) {
    return findPairRecursive(A, k, 0, A.size() - 1);
}

// Iterative Algorithm
bool findPairIterative(const vector<int>& A, int k) {
    int left = 0, right = A.size() - 1;
    while (left < right) {
        int sum = A[left] + A[right];
        if (sum == k) return true;
        else if (sum < k) left++;
        else right--;
    }
    return false;
}

int main() {
    srand(time(0));
    vector<int> sizes = {10, 100, 500}; // Array of difference sizes
    int N = 100;    // Random number generation range

    cout << "Input Array Size\tRecursive\tIterative\n";

    for (int n : sizes) {
        vector<int> A(n);
        for (int i = 0; i < n; i++){A[i] = rand() % N;} // Random number generation
        sort(A.begin(), A.end());       // Sort array
        int k = A[0] + A[n - 1];        // always valid

        int trials = 1000;
        long long totalRec = 0, totalIt = 0;

        for (int t = 0; t < trials; t++) {
            auto startRec = high_resolution_clock::now();
            findPairRecursiveWrapper(A, k);
            auto stopRec = high_resolution_clock::now();
            totalRec += duration_cast<microseconds>(stopRec - startRec).count();

            auto startIt = high_resolution_clock::now();
            findPairIterative(A, k);
            auto stopIt = high_resolution_clock::now();
            totalIt += duration_cast<microseconds>(stopIt - startIt).count();
        }

        cout << n << "\t\t\t" 
             << (totalRec / trials) << "\t\t"
             << (totalIt / trials) << "\n";
    }
}
