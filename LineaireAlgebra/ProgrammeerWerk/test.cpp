#include <iostream>

// void swap(int &a, int &b) {
//   int temp = a;
//   a = b;
//   b = temp;
// }

// void print(int value) {
//     std::cout << value << "\n";
// }

template <typename T> void swap(T &a, T &b) {
  T temp = a;
  a = b;
  b = temp;
}

template <typename T> void print(T value) { std::cout << value << std::endl; }

int main() {
  int a = 5;
  int b = 10;

  print(a);
  print(b);
  swap(a, b);
  print(a);
  print(b);

  a = static_cast<char>(a);
  b = static_cast<char>(b);
  a = 'a';
  b = 'b';

  print(a);
  print(b);
  swap(a, b);
  print(a);
  print(b);

  return 0;
}