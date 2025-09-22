#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

// ===== Recursive Partition =====
int partitionRecursive(vector<int>& A, int k, int i, int write) {
    if (i == A.size()) return write;

    write = partitionRecursive(A, k, i + 1, write);

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

void partitionWrapper(vector<int>& A, int k) {
    partitionRecursive(A, k, 0, 0);
}

// ===== Iterative Partition (stable, extra array) =====
void partitionIterative(vector<int>& A, int k) {
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
long long timeRecursive(int n, int trials) {
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, 1000);
    long long total = 0;

    for (int t = 0; t < trials; t++) {
        vector<int> A(n);
        for (int i = 0; i < n; i++) A[i] = dist(rng);

        auto start = high_resolution_clock::now();
        partitionWrapper(A, 500); // pivot = 500
        auto stop = high_resolution_clock::now();
        total += duration_cast<microseconds>(stop - start).count();
    }
    return total / trials;
}

long long timeIterative(int n, int trials) {
    mt19937 rng(1337);
    uniform_int_distribution<int> dist(0, 1000);
    long long total = 0;

    for (int t = 0; t < trials; t++) {
        vector<int> A(n);
        for (int i = 0; i < n; i++) A[i] = dist(rng);

        auto start = high_resolution_clock::now();
        partitionIterative(A, 500); // pivot = 500
        auto stop = high_resolution_clock::now();
        total += duration_cast<microseconds>(stop - start).count();
    }
    return total / trials;
}

int main() {
    vector<int> sizes = {10, 100, 500};

    cout << "n, Recursive(us), Iterative(us)\n";
    for (int n : sizes) {
        int trials = (n == 10 ? 5000 : (n == 100 ? 1000 : 200));
        long long r = timeRecursive(n, trials);
        long long it = timeIterative(n, trials);
        cout << n << ", " << r << ", " << it << "\n";
    }
}
