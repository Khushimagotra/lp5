#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void merge(int arr[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } 
        else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void merge_para(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                merge_para(arr, l, m);
            }
            #pragma omp section
            {
                merge_para(arr, m + 1, r);
            }
        }
        merge(arr, l, m, r);
    }
}

void bubbleSort(int arr[], int n) {
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            } 
        }
    }
}

void swap_para(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_para(int arr[], int n) {
    int i = 0, j = 0;
    #pragma omp parallel for shared(arr, n) private(i, j)
    for (i = 0; i < n - 1; i++) {
        #pragma omp parallel for default(none), shared(arr, f, n)
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap_para(&arr[j], &arr[j + 1]);
            } 
        }
    }
}

int main() {
    int n;
    cout << "Enter no of elements in array:";
    cin >> n;
    int arr1[n], arr2[n], arr3[n], arr4[n];
    for (int i = 0; i < n; i++) {
        arr1[i] = rand() % n;
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        arr4[i] = arr1[i];
    }

    auto start = chrono::steady_clock::now();
    mergeSort(arr1, 0, n - 1);
    auto end = chrono::steady_clock::now();
    chrono::duration<double, micro> fp = end - start;
    cout << "Sequential Merge Sort Time: " << fp.count() << " microseconds" << endl;

    auto start1 = chrono::steady_clock::now();
    auto end1 = chrono::steady_clock::now();
    chrono::duration<double, micro> fp1 = end1 - start1;
    cout << "Parallel Merge Sort Time: " << fp1.count() << " microseconds" << endl;

    auto start2 = chrono::steady_clock::now();
    bubbleSort(arr3, n);
    auto end2 = chrono::steady_clock::now();
    chrono::duration<double, micro> fp2 = end2 - start2;
    cout << "Sequential Bubble Sort Time: " << fp2.count() << " microseconds" << endl;

    auto start3 = chrono::steady_clock::now();
    bubble_para(arr4, n);
    auto end3 = chrono::steady_clock::now();
    chrono::duration<double, micro> fp3 = end3 - start3;
    cout << "Parallel Bubble Sort Time: " << fp3.count() << " microseconds" << endl;


    // Calculate speedup for Merge Sort
    double SortSpeedup = fp.count() / fp1.count();
    cout << "Speedup Merge Sort: " << SortSpeedup << endl;
        // Calculate speedup for Bubble Sort
    double BSortSpeedup = fp2.count() / fp3.count();
    cout << "Speedup Bubble Sort: " << BSortSpeedup << endl;

    

    return 0;
}


