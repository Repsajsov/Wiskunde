#include <iostream>

using namespace std;
bool zoek(int A[], int X, int n) {
    for (int i = 0; i < n; i++) {
        cout << "call: " << i << endl;
        if (A[i] == X) return true;
    }
    return false;
}

int invers(int A[], int n) {
    int teller = 0;
    for (int i = 1; i < n; i++)
        if (A[i - 1] > A[i]) teller++;
    return teller;
}
void drie(int A[], int i, int n) {
    int temp;
    if (A[i] > A[i + 1]) {
        temp = A[i];
        A[i] = A[i + 1];
        A[i + 1] = temp;
    }
    if (A[i + 1] > A[i + 2]) {
        temp = A[i + 1];
        A[i + 1] = A[i + 2];
        A[i + 2] = temp;
    }
    if (A[i] > A[i + 1]) {
        temp = A[i];
        A[i] = A[i + 1];
        A[i + 1] = temp;
    }
}

int sort(int A[], int n) {
    int teller = 0;
    while (invers(A, n) != 0) {
        for (int i = 0; i < n - 2; i++) drie(A, i, n);
        teller++;
    }
    return teller;
}

int main() {
    int A[] = {1, 4, 3, 6, 5, 5, 5, 5, 340, 3};
    int n = sizeof(A) / sizeof(int);
    cout << invers(A, n);

    return 0;
}