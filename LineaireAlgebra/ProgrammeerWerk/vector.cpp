#include <cstddef>
#include <iostream>

template <typename T> class Vector {
private:
  T *data;
  size_t n;

public:
  Vector() : data(nullptr), n(0) {};
  template <typename... Args>
  Vector(Args... args) : data(new T[sizeof...(args)]), n(sizeof...(args)) {
    size_t i = 0;
    ((data[i++] = args), ...);
  }
  Vector(const Vector<T> &andereVector)
      : data(new T[andereVector.n]), n(andereVector.n) {
    for (size_t i = 0; i < n; i++) {
      data[i] = andereVector.data[i];
    }
  }
  ~Vector() { delete[] data; }
  void afdrukken() const {
    for (size_t i = 0; i < n; i++) {
      std::cout << data[i] << " ";
    }
    std::cout << std::endl;
  }
  static Vector<T> nullen(size_t n) {
    Vector<T> resultaat;
    resultaat.data = new T[n]();
    resultaat.n = n;
    return resultaat;
  }
  static Vector<T> eentjes(size_t n) {
    Vector<T> resultaat;
    resultaat.data = new T[n];
    resultaat.n = n;
    for (size_t i = 0; i < n; i++) {
      resultaat.data[i] = T(1);
    }
    return resultaat;
  }
  // Operatoren
  Vector<T>& operator=(const Vector<T> &andereVector) {
    if (this != &andereVector) {
      delete[] data;

      n = andereVector.n;
      data = new T[n];
      for (size_t i = 0; i < n; i++) {
        data[i] = andereVector.data[i];
      }
    }
    return *this;
  }

  Vector<T> operator*(T scalair) const {
    Vector<T> resultaat = nullen(n);
    for (size_t i = 0; i < n; i++) {
      resultaat.data[i] = (scalair * data[i]);
    }
    return resultaat;
  }

  friend Vector<T> operator*(T scalair, const Vector<T> &vector) {
    return vector * scalair;
  }

  T dot(const Vector<T> &andereVector) const {
    T resultaat = 0;
    for (size_t i = 0; i < n; i++) {
      resultaat += (data[i] * andereVector.data[i]);
    }
    return resultaat;
  }

  Vector<T> operator+(const Vector<T> &andereVec) const {
    Vector<T> resultaat = nullen(n);
    for (size_t i = 0; i < n; i++) {
      resultaat.data[i] = (data[i] + andereVec.data[i]);
    }
    return resultaat;
  }
};

int main() {
  Vector<int> nullen(3);
  Vector<int> v1(1, 2, 3, 4);
  Vector<int> v2(1, 2, 3, 4);
  Vector<int> v3 = v1 + v2;
  v3 = 4 * v3;
  v3.afdrukken();
  return 0;
}