/*
    Name: Aqib Hussain
    Reg#: 200901013
    Batch: BS-CS-01 (A)

    Merge Sort Code Reference: https://www.programiz.com/dsa/merge-sort
*/

#include <iostream>
#include <pthread.h>
using namespace std;

int arrSize, maxThreads, currentThread = 0;
int* arr;

void merge(int start, int mid, int end) {

    int leftArrSize = mid - start + 1;
    int rightArrSize = end - mid;

    int* left = new int[leftArrSize], * right = new int[rightArrSize];

    for (int i = 0; i < leftArrSize; i++)
        left[i] = arr[start + i];
    for (int j = 0; j < rightArrSize; j++)
        right[j] = arr[mid + 1 + j];

    int i, j, k;
    i = 0;
    j = 0;
    k = start;

    while (i < leftArrSize && j < rightArrSize) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < leftArrSize) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < rightArrSize) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int start, int end) {
    if (start < end) {
        int mid = (start + end) / 2;

        mergeSort(start, mid);
        mergeSort(mid + 1, end);

        merge(start, mid, end);
    }
}

void* mergeSort(void* args) {
    int curThread = currentThread++;
    int start = curThread * (arrSize / maxThreads) + (curThread != 0 && arrSize % maxThreads != 0) + (curThread >= 2 && arrSize % maxThreads != 0) + (curThread == 3 && (arrSize % maxThreads == 1 || arrSize % maxThreads == 3));
    int end = (curThread + 1) * (arrSize / maxThreads) - 1 + (curThread < arrSize% maxThreads) + (curThread != 0 && arrSize % maxThreads != 0) + (curThread >= 2 && arrSize % maxThreads != 0) + (curThread == 3 && (arrSize % maxThreads == 1 || arrSize % maxThreads == 3));

    mergeSort(start, end);

    return 0;
}

int main() {
    cout << "Enter size of arr: ";
    cin >> arrSize;

    arr = new int[arrSize];

    for (int i = 0; i < arrSize; i++) {
        cout << "Enter number " << i + 1 << ": ";
        cin >> arr[i];
    }

    maxThreads = (arrSize < 4) ? 2 : 4;

    pthread_t threads[maxThreads];

    for (int i = 0; i < maxThreads; i++) {
        pthread_create(&threads[i], NULL, mergeSort, (void*)NULL);
    }

    for (int i = 0; i < maxThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    if (maxThreads == 2) {
        merge(0, (arrSize - 1) / 2, arrSize - 1);
    }
    else {
        if (arrSize % maxThreads != 0) {
            merge(0, ((arrSize / 2) - 1) / 2, (arrSize / 2));
            merge(arrSize / 2 + 1, (arrSize / 2) + (arrSize - 1 - (arrSize / 2)) / 2 + (2 < (arrSize % maxThreads)), arrSize - 1);
        }
        else {
            merge(0, ((arrSize / 2) - 1) / 2, (arrSize / 2) - 1);
            merge(arrSize / 2, (arrSize / 2) + (arrSize - 1 - (arrSize / 2)) / 2, arrSize - 1);
        }
        merge(0, (arrSize - 1) / 2 + (arrSize % maxThreads != 0 && arrSize % 2 == 0), arrSize - 1);
    }

    cout << "Sorted array: ";
    for (int i = 0; i < arrSize; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}