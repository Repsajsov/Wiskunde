#include <iostream>

using namespace std;
enum {
  NOORD = 0,
  NOORDOOST = 1,
  OOST = 2,
  ZUIDOOST = 3,
  ZUID = 4,
  ZUIDWEST = 5,
  WEST = 6,
  NOORDWEST = 7
};

struct vak {
  char teken = '.';
  vak *buren[8] = {nullptr};
};

class Bord {
private:
  vak *linksboven = nullptr;
  int m;
  int n;
  vak **vakjes;

public:
  Bord(int m, int n) {
    vakjes = new vak *[m * n];
    for (int i = 0; i < m * n; i++) {
      vakjes[i] = new vak;
      vakjes[i]->teken = 'X';
    }
    linksboven = vakjes[0];

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        int index = i * n + j;
        if (i > 0) {
          vakjes[index]->buren[NOORD] = vakjes[(i - 1) * n + j];
        }
        if (i > 0 && j < n - 1) {
          vakjes[index]->buren[NOORDOOST] = vakjes[(i - 1) * n + (j + 1)];
        }
        if (j < n - 1) {
          vakjes[index]->buren[OOST] = vakjes[i * n + (j + 1)];
        }
        if (j < n - 1 && i < m - 1) {
          vakjes[index]->buren[ZUIDOOST] = vakjes[(i + 1) * n + (j + 1)];
        }
        if (i < m - 1) {
          vakjes[index]->buren[ZUID] = vakjes[(i + 1) * n + j];
        }
        if (j > 0) {
          vakjes[index]->buren[WEST] = vakjes[i * n + (j - 1)];
        }
      }
    }
  }
  void afdrukken() {
    vak *rijStart = linksboven;
    while (rijStart) {
      vak *huidigVakje = rijStart;
      while (huidigVakje) {
        cout << huidigVakje->teken << " ";
        huidigVakje = huidigVakje->buren[OOST];
      }
      cout << endl;
      rijStart = rijStart->buren[ZUID];
    }
  }
};

int main() {
  Bord spel = Bord(8, 8);
  spel.afdrukken();

  return 0;
}