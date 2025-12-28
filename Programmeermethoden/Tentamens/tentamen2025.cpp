#include <iostream>

void negPos(int *A, int n, int &pos, int &neg) {
  for (int i = 0; i < n; i++) {
    if (A[i] < 0)
      pos += A[i];
    else
      neg += A[i];
  }
}

void swap(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

void splits(int *A, int n) {
  int i = 0;
  int j = n - 1;
  while (i < j) {
    if (A[j] < 0) {
      if (A[i] < 0) {
        i++;
      } else {
        swap(A[i], A[j]);
        j--;
        i++;
      }
    } else {
      j--;
    }
  }
}

void sorteer(int *A, const int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < (n - 1) - i; j++) {
      if (A[j] > A[j + 1]) {
        swap(A[j], A[j + 1]);
      }
    }
  }
}

bool som3(const int *A, const int n) {
  for (int i = 0; i < n - 2; i++) {
    for (int j = i + 1; j < n - 1; j++) {
      for (int k = j + 1; k < n; k++) {
        if (A[i] + A[j] + A[k] == 0)
          return true;
      }
    }
  }
  return false;
}

void afdrukken(int *A, int n) {
  for (int i = 0; i < n; i++) {
    std::cout << A[i] << " ";
  }
}

int tellen(char puzzel[4][5]) {
  int resultaat = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      if (j < 4 && i < 3) {
        if (puzzel[i][j] == puzzel[i + 1][j + 1]) {
          resultaat++;
        }
      }
      if (j > 0 && i > 0) {
        if (puzzel[i][j] == puzzel[i - 1][j - 1]) {
          resultaat++;
        }
      }
      if (j < 4 && i > 0) {
        if (puzzel[i][j] == puzzel[i - 1][j + 1]) {
          resultaat++;
        }
      }
      if (j > 0 && i < 3) {
        if (puzzel[i][j] == puzzel[i + 1][j - 1]) {
          resultaat++;
        }
      }
    }
  }
  return resultaat;
}

int gr(char puzzel[4][5]) {
  char kar = '\0';
  int maxSom = 0;
  int grootsteKolom = 0;
  for (int j = 0; j < 5; j++) {
    int som = 0;
    for (int i = 0; i < 4; i++) {
      kar = puzzel[i][j];
      if (kar - '0' < 10 && kar - '0' >= 0) {
        som += int(kar - '0');
      }
    }
    if (som > maxSom) {
      maxSom = som;
      grootsteKolom = j;
    }
  }
  std::cout << "Som grootste kolom: " << maxSom << std::endl;
  return grootsteKolom;
}

void print(char puzzel[4][5], int c) {
  char kar = '\0';
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      kar = puzzel[i][j];
      if (int(kar - '0') == c) {
        for (int k = i + 1; k < 4; k++) {
          kar = puzzel[k][j];
          if (int(kar - 'a') >= 0 && int(kar - 'a') < int('z' - 'A')) {
            std::cout << kar;
          }
        }
      }
    }
  }
}

int main() {
  int m = 4;
  int n = 5;
  char puzzel[4][5] = {{'1', 'k', '2', 'a', '3'},
                       {'h', 'a', 'p', 'J', 'e'},
                       {'a', 'r', '2', 'a', 'l'},
                       {'L', '5', 'a', '7', 'k'}};

  //   std::cout << tellen(puzzel);
  print(puzzel, 1);

  return 0;
}
