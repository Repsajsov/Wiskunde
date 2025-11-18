#include "othelloBord.h"
#include <iostream>

using namespace std;

OthelloBord::OthelloBord(int m, int n) {
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

OthelloBord::~OthelloBord() {
  for (int i = 0; i < m * n; i++) {
    delete vakjes[i];
  }
  delete[] vakjes;
}

void OthelloBord::afdrukken() {
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

bool OthelloBord::mensZet() {
  bool geldig = false;
  cout << "Geef coordinaat: ";
  char kolom = leesOptie();
  kolom = int(kolom - 'A');
  int rij = leesGetal(10) - 1;
  vak *gekozenVak = vakjes[rij * n + kolom];

  for (int richting = NOORD; richting <= NOORDWEST; richting++) {
    if (gekozenVak->buren[richting]->teken == karakterTegenstander) {
      // Recursie
      if (flipVakken(gekozenVak, richting, karakterSpeler)) {
        gekozenVak->teken = karakterSpeler;
        geldig = true;
      }
    }
  }
  return geldig;
}

bool OthelloBord::computerZet() {
  for (int i = 0; i < m * n; i++) {}
  return true;
}

bool OthelloBord::isKlaar() { return false; }

void OthelloBord::bindVakjes() {
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

bool OthelloBord::flipVakken(vak *huidigVak, int richting, char kleur) {
  vak *volgende = huidigVak->buren[richting];

  if (!volgende || volgende->teken == '.') {
    return false;
  }
  if (volgende->teken == kleur) {
    return true;
  }
  if (flipVakken(volgende, richting, kleur)) {
    volgende->teken = kleur;
    return true;
  }
  return false;
}

char OthelloBord::leesOptie() {
  char resultaat;
  do {
    cin.get(resultaat);
  } while (resultaat == '\n');
  if (resultaat >= 'a' && resultaat <= 'z') {
    resultaat = (resultaat - 'a') + 'A';
  }
  return resultaat;
}

int OthelloBord::leesGetal(int max) {
  char resultaat = 0;
  char karakter = leesOptie();
  if (karakter >= '0' && karakter <= '9') {
    resultaat = karakter - '0';
  }
  while (cin.get(karakter) && karakter != '\n') {
    if (karakter >= '0' && karakter <= '9') {
      resultaat = resultaat * 10 + (karakter - '0');
      if (resultaat >= max)
        resultaat = max;
    }
  }
  return resultaat;
}

vak **OthelloBord::berekenValideZetten() {
  vak *rij = linksboven;
  while (rij) {
    vak *huidigVakje = rij;
    while (huidigVakje) {
      huidigVakje->buren[OOST];
    }
    rij = rij->buren[ZUID]
  }
}
