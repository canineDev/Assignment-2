#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;
using namespace chrono;

// Recursive Algorithm
int recursiveAlgo(vector<int>& A, int k, int i, int write) {
    if (i == A.size()) return write;

    write = recursiveAlgo(A, k, i + 1, write);

    if (A[i] <= k) {
        int val = A[i];
        for (int j = i; j > write; j--) {
            A[j] = A[j - 1];
        }
        A[write] = val;
        write++;
    }
    return write;
}

// Recursive function wrapper
void recursiveWrapper(vector<int>& A, int k) {
    recursiveAlgo(A, k, 0, 0);
}

// Iterative Algorithm 
void iterativeAlgo(vector<int>& A, int k) {
    vector<int> B;
    B.reserve(A.size());

    for (int i = 0; i < (int)A.size(); i++) {
        if (A[i] <= k) B.push_back(A[i]);
    }
    for (int i = 0; i < (int)A.size(); i++) {
        if (A[i] > k) B.push_back(A[i]);
    }
    for (int i = 0; i < (int)A.size(); i++) {
        A[i] = B[i];
    }
}

int main() {
    vector<int> sizes = {100, 1000, 10000}; // Array of difference sizes
    int N = 100;    // Random number generation range

    cout << "Input Array Size\tRecursive\tIterative\n";

    for (int n : sizes) {
        int trials = (n == 10 ? 5000 : (n == 100 ? 1000 : 200));
        long long totalRec = 0, totalIt = 0;    // Time totals

        for (int t = 0; t < trials; t++) {
            // Create array with random numbers
            vector<int> A(n);
            for (int i = 0; i < n; i++){A[i] = rand() % N;} // Random number generation

            // Recurisve array time capture
            auto Arec = A; // copy array
            auto startRec = high_resolution_clock::now();   // Start funny clock
            recursiveWrapper(Arec, 500);
            auto stopRec = high_resolution_clock::now();    // End funny clock
            totalRec += duration_cast<microseconds>(stopRec - startRec).count();
            
            // Iterative array time capture
            auto Ait = A; // copy array
            auto startIt = high_resolution_clock::now();
            iterativeAlgo(Ait, 500);
            auto stopIt = high_resolution_clock::now();
            totalIt += duration_cast<microseconds>(stopIt - startIt).count();
        }

        cout << n << "\t\t\t" 
             << (totalRec / trials) << "\t\t"
             << (totalIt / trials) << "\n";
    }

    return 0;
}
