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
  Bord(int m, int n);
  ~Bord();
  void afdrukken();
  void menszet();
  void computerzet();

  // helpers
  void bindVakjes();
};

Bord::Bord(int m, int n) {
  this->m = m;
  this->n = n;
  int middenRij = m / 2;
  int middenKolom = n / 2;

  vakjes = new vak *[m * n];
  for (int i = 0; i < m * n; i++) {
    vakjes[i] = new vak;
  }
  this->linksboven = vakjes[0];

  vakjes[(middenRij - 1) * n + (middenKolom - 1)]->teken = 'W';
  vakjes[(middenRij - 1) * n + middenKolom]->teken = 'Z';
  vakjes[middenRij * n + (middenKolom - 1)]->teken = 'Z';
  vakjes[middenRij * n + middenKolom]->teken = 'W';
  bindVakjes();
}

Bord::~Bord() {
  for (int i = 0; i < m * n; i++) {
    delete vakjes[i];
  }
  delete[] vakjes;
}

void Bord::afdrukken() {
  vak *rij = linksboven;
  int rijNummer = 1;
  cout << "  ";
  for (int i = 1; i <= n; i++) {
    cout << char(64 + i) << " ";
  }
  cout << endl;
  while (rij) {
    if (rijNummer < 10) {
      cout << rijNummer << " ";
    } else {
      cout << rijNummer;
    }
    vak *huidigVakje = rij;
    while (huidigVakje) {
      cout << huidigVakje->teken << " ";
      huidigVakje = huidigVakje->buren[OOST];
    }
    cout << endl;
    rij = rij->buren[ZUID];
    rijNummer += 1;
  }
}

void Bord::bindVakjes() {
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
      if (j > 0 && i < m - 1) {
        vakjes[index]->buren[ZUIDWEST] = vakjes[(i + 1) * n + (j - 1)];
      }
      if (j > 0) {
        vakjes[index]->buren[WEST] = vakjes[i * n + (j - 1)];
      }
      if (j > 0 && i > 0) {
        vakjes[index]->buren[NOORDWEST] = vakjes[(i - 1) * n + (j - 1)];
      }
    }
  }
}

int main() {
  Bord spel = Bord(12, 8);
  spel.afdrukken();

  return 0;
}