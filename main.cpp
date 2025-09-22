#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

int recursiveAlgo(vector<int>& A, int k, int i, int write) {    // Recursive algorithm
    if (i == A.size()) return write;    // Return if at end of array

    write = recursiveAlgo(A, k, i + 1, write);  // Make recursive call

    if (A[i] <= k) {    // Check if current element is less/equal to k
        int val = A[i];
        for (int j = i; j > write; j--) {
            A[j] = A[j - 1];
        }
        A[write] = val; // Set element at writing position to val; shift it over 
        write++;    // Increment writing position
    }
    return write;
}

void recursiveWrapper(vector<int>& A, int k) {  // Wrapper to make recursive calls
    recursiveAlgo(A, k, 0, 0);
}

void iterativeAlgo(vector<int>& A, int k) {
    vector<int> B;
    B.reserve(A.size());

    for (int i = 0; i < A.size(); i++) {
        if (A[i] <= k) B.push_back(A[i]);
    }
    for (int i = 0; i < A.size(); i++) {
        if (A[i] > k) B.push_back(A[i]);
    }
    for (int i = 0; i < A.size(); i++) {
        A[i] = B[i];
    }
}

// ===== Timing Harness =====
long long recursiveTime(int n, int trials) {
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, 1000);
    long long total = 0;

    for (int t = 0; t < trials; t++) {
        vector<int> A(n);
        for (int i = 0; i < n; i++) A[i] = dist(rng);

        auto start = high_resolution_clock::now();
        recursiveWrapper(A, 500); // pivot = 500
        auto stop = high_resolution_clock::now();
        total += duration_cast<microseconds>(stop - start).count();
    }
    return total / trials;
}

long long iterativeTime(int n, int trials) {
    mt19937 rng(1337);
    uniform_int_distribution<int> dist(0, 1000);
    long long total = 0;

    for (int t = 0; t < trials; t++) {
        vector<int> A(n);
        for (int i = 0; i < n; i++) A[i] = dist(rng);

        auto start = high_resolution_clock::now();
        iterativeAlgo(A, 500); // set pivot = 500
        auto stop = high_resolution_clock::now();
        total += duration_cast<microseconds>(stop - start).count();
    }
    return total / trials;
}

int main() {
    vector<int> sizes = {10, 100, 500}; // Different array sizes

    cout << "n, Recursive(us), Iterative(us)\n";
    for (int n : sizes) {
        int trials = (n == 10 ? 5000 : (n == 100 ? 1000 : 200));
        long long r = recursiveTime(n, trials);
        long long it = iterativeTime(n, trials);
        cout << n << ", " << r << ", " << it << "\n";
    }
}
