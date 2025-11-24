#include <cstddef>
#include <iostream>

template <typename T> class Vector {
private:
  T *data;
  std::size_t n;

public:
  Vector();
  Vector(std::initializer_list<T> list);
  template <typename... Args> Vector(Args &&...args);

  ~Vector();

  void afdrukken() const;
};
template <typename T> Vector<T>::Vector() : data(nullptr), n(0) {}
template <typename T>
Vector<T>::Vector(std::initializer_list<T> list)
    : data(nullptr), n(list.size()) {
  if (n > 0) {
    data = new T[n];
    std::size_t i = 0;
    for (const T &value : list)
      data[i++] = value;
  }
}
template <typename T> void Vector<T>::afdrukken() const {
  for (size_t i = 0; i < n; ++i) {
    std::cout << data[i] << " ";
  }
  std::cout << "\n";
}

int main() {
  Vector<int> v = Vector<int>(1, 2, 3);
  v.afdrukken();
  return 0;
}