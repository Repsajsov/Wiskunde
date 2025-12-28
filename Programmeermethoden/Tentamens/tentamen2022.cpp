#include <iostream>

bool oneven(const int A[], const int n) {
  int i = 1;
  int count = 1;
  while (i < n) {
    if (A[i] == A[i - 1]) {
      count++;
    } else {
      if (count % 2 == 1) {
        return true;
      } else {
        count = 1;
      }
    }
    i++;
  }
  return (count % 2 == 1);
}

void twee(const int A[], const int n, int &x, int &y, int &t) {
  for (int i = 1; i < n; i++) {
    if (A[i] < A[i - 1]) {
      x = A[i];
      y = A[i - 1];
      break;
    } else if (A[i] > A[i - 1]) {
      x = A[i - 1];
      y = A[i];
      break;
    }
  }
  t = 0;
  for (int i = 0; i < n; i++) {
    if (x == A[i]) {
      t++;
    }
  }
}
void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

void sorteer(int A[], const int n) {
  int x, y, t;
  twee(A, n, x, y, t);
  for (int i = 0; i < t; i++) {
    if (A[i] != x) {
      for (int j = i + 1; j < n; j++) {
        if (A[j] == x) {
          swap(A[i], A[j]);
          break;
        }
      }
    }
  }
}

void bubbleSort(int A[], const int n) {
  int right = n - 1;
  while (right > 0) {
    int k = 0;
    for (int i = 0; i < right; i++) {
      if (A[i] > A[i + 1]) {
        swap(A[i], A[i + 1]);
        k = i;
      }
    }
    right = k;
  }
}

void print(const int A[], const int n) {
  for (int i = 0; i < n; i++) {
    std::cout << A[i] << " ";
  }
  std::cout << std::endl;
}

int main() {
  int A[] = {1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1};
  const int n = sizeof(A) / sizeof(int);

  std::cout << oneven(A, n);
  int x = 0;
  int y = 0;
  int t = 0;
  twee(A, n, x, y, t);
  std::cout << "x: " << x << ", y: " << y << ", t: " << t;
  print(A, n);
  bubbleSort(A, n);
  print(A, n);

  return 0;
}