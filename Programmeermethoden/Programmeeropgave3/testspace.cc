#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

void wissel(int &a, int &b) {
  int temp = a;
  a = b;
  b = temp;
}

class Random {
private:
  long seed;

public:
  Random() { seed = time(0); }
  int randomGetal();
  void randomGetallen(int grootte, int bereik, int resultaat[]);
};

int Random::randomGetal() {
  seed = (221 * seed + 1) % 1000;
  return seed;
}

void Random::randomGetallen(int grootte, int bereik, int resultaat[]) {
  int bereikGetallen[bereik];
  for (int i = 0; i < bereik; i++) {
    bereikGetallen[i] = i;
  }
  for (int i = 0; i < grootte; i++) {
    int r = i + randomGetal() % (bereik - i);
    wissel(bereikGetallen[i], bereikGetallen[r]);
  }

  for (int i = 0; i < grootte; i++) {
    resultaat[i] = bereikGetallen[i];
  }
}

int main() {
  Random r = Random();

  int getallen[12];
  r.randomGetallen(12, 25, getallen);

  for (int i = 0; i < 12; i++) {
    cout << getallen[i] << endl;
  }

  return 0;
}