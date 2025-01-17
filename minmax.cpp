#include <iostream>
#include <climits>
#include <cstdlib>
#include <chrono>
#include <omp.h>

using namespace std;


int findMinSequential(int arr[], int n) {
    int min_value = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    return min_value;
}

int findMaxSequential(int arr[], int n) {
    int max_value = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    return max_value;
}

int calculateSumSequential(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int calculateAverageSequential(int arr[], int n) {
    int sum = calculateSumSequential(arr, n);
    return sum / n;
}

int findMinParallel(int arr[], int n) {
    int min_value = INT_MAX;
#pragma omp parallel for reduction(min: min_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }
    return min_value;
}

int findMaxParallel(int arr[], int n) {
    int max_value = INT_MIN;
#pragma omp parallel for reduction(max: max_value)
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }
    return max_value;
}

int calculateSumParallel(int arr[], int n) {
    int sum = 0;
#pragma omp parallel for reduction(+: sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

int calculateAverageParallel(int arr[], int n) {
    int sum = calculateSumParallel(arr, n);
    return sum / n;
}

int main() {
    int *arr, n;
    cout << "\nEnter total number of elements: ";
    cin >> n;

    int lb = 0;
    int ub = n;
    arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = (rand() % (ub - lb + 1));
    }

    cout << "Generated array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Sequential version
    auto startSeq = chrono::steady_clock::now();
    cout << "Sequential Min = " << findMinSequential(arr, n) << endl;
    auto endSeq = chrono::steady_clock::now();
     chrono::duration<double, micro> sqMin = endSeq - startSeq;
    cout << "Sequential Elapsed time for Min in microseconds: " << sqMin.count() << " microsecs" << endl;

    startSeq = chrono::steady_clock::now();
    cout << "Sequential Max = " << findMaxSequential(arr, n) << endl;
    endSeq = chrono::steady_clock::now();
      chrono::duration<double, micro> sqMax = endSeq - startSeq;
    cout << "Sequential Elapsed time for Max in microseconds: " << sqMax.count() << " microsecs" << endl;

    startSeq = chrono::steady_clock::now();
    cout << "Sequential Sum = " << calculateSumSequential(arr, n) << endl;
    endSeq = chrono::steady_clock::now();
      chrono::duration<double, micro> sqSum = endSeq - startSeq;
    cout << "Sequential Elapsed time for Sum in microseconds: " <<sqSum.count() << " microsecs" << endl;

    startSeq = chrono::steady_clock::now();
    cout << "Sequential Average = " << calculateAverageSequential(arr, n) << endl;
    endSeq = chrono::steady_clock::now();
      chrono::duration<double, micro> sqAvg = endSeq - startSeq;
    cout << "Sequential Elapsed time for Average in microseconds: " << sqAvg.count() << " microsecs" << endl;

    // OpenMP Parallel version
    auto startParallel = chrono::steady_clock::now();
    cout << "Parallel Min = " << findMinParallel(arr, n) << endl;
    auto endParallel = chrono::steady_clock::now();
      chrono::duration<double, micro> parrMin = endParallel - startParallel;
    cout << "Parallel Elapsed time for Min in microseconds: " << parrMin.count() << " microsecs" << endl;

    startParallel = chrono::steady_clock::now();
    cout << "Parallel Max = " << findMaxParallel(arr, n) << endl;
    endParallel = chrono::steady_clock::now();
      chrono::duration<double, micro> parrMax = endParallel - startParallel;
    cout << "Parallel Elapsed time for Max in microseconds: " << parrMax.count() << " microsecs" << endl;

    startParallel = chrono::steady_clock::now();
    cout << "Parallel Sum = " << calculateSumParallel(arr, n) << endl;
    endParallel = chrono::steady_clock::now();
      chrono::duration<double, micro> parrSum = endParallel - startParallel;
    cout << "Parallel Elapsed time for Sum in microseconds: " << parrSum.count() << " microsecs" << endl;

    startParallel = chrono::steady_clock::now();
    cout << "Parallel Average = " << calculateAverageParallel(arr, n) << endl;
    endParallel = chrono::steady_clock::now();
      chrono::duration<double, micro>  parrAvg = endParallel - startParallel;
    cout << "Parallel Elapsed time for Average in microseconds: " << parrAvg.count() << " microsecs" << endl;
    double MinSpeedup = sqMin.count() / parrMin.count();
    cout << "Speedup Min: " << MinSpeedup << endl;
        double MaxSpeedup = sqMax.count() / parrMax.count();
    cout << "Speedup Max: " << MaxSpeedup << endl;
        double SumSpeedup = sqSum.count() / parrSum.count();
    cout << "Speedup Sum: " << SumSpeedup<< endl;
     double AvgSpeedup = sqAvg.count() / parrAvg.count();
    cout << "Speedup Avg: " << AvgSpeedup << endl;

    delete[] arr; // Don't forget to release the allocated memory
    return 0;
}





