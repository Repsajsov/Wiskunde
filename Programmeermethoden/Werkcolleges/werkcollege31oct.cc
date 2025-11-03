#include <iostream>

int hoevaak(int A[], int X, int n) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (A[i] == X) {
      count++;
    }
  }
  return count;
}

int uniek();

using namespace std;
int main() {

  int A[] = {0, 2, 3, 4, 5, 6, 2, 2, 3, 4, 5, 2, 3};
  cout << hoevaak(A, 2, 13);

  return 0;
}