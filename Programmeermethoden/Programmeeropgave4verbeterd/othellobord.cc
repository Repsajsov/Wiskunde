// file othellobord.cc
#include "othellobord.h"
#include <iostream>
#include <unistd.h>
using namespace std;

bordvakje::bordvakje() {
  kleur = '.';
  for (int i = 0; i < 8; i++) {
    buren[i] = nullptr;
  }
}

geldigvakje::geldigvakje() {
  vakje = nullptr;
  volgende = nullptr;
  for (int i = 0; i < 8; i++) {
    richtingen[i] = false;
  }
  aantalgeslagen = 0;
}

geldigvakje *othellobord::zoekGeldigVakje(bordvakje *vakje) {
  geldigvakje *huidig = inganggeldig;
  while (huidig != nullptr) {
    if (huidig->vakje == vakje) {
      return huidig;
    }
    huidig = huidig->volgende;
  }
  return nullptr;
}

void othellobord::voegvoor(geldigvakje *&rij_ingang, bordvakje *vakje,
                           int richting) {
  geldigvakje *bestaand = zoekGeldigVakje(vakje);
  if (bestaand != nullptr) {
    bestaand->richtingen[richting] = true;
    return;
  }

  geldigvakje *hulp = new geldigvakje;
  hulp->vakje = vakje;
  hulp->richtingen[richting] = true;
  hulp->volgende = rij_ingang;
  rij_ingang = hulp;
}

char othellobord::gettegenstander(char huidigespeler) {
  char tegenstander = '\0';
  if (huidigespeler == zwart) {
    tegenstander = wit;
  } // if
  else {
    tegenstander = zwart;
  } // else
  return tegenstander;
}

void othellobord::controleerzet(bordvakje *huidigvakje, char tegenstander,
                                char huidigespeler) {
  for (int i = 0; i < 8; i++) {
    if (huidigvakje->buren[i] != nullptr) {
      if (huidigvakje->buren[i]->kleur == tegenstander) {
        bordvakje *hulp = huidigvakje->buren[i];
        while (hulp != nullptr && hulp->kleur != '.') {
          if (hulp->kleur == huidigespeler) {
            voegvoor(inganggeldig, huidigvakje, i);
            break;
          } // if
          hulp = hulp->buren[i];
        } // if
      } // if
    }
  } // for
}

bool othellobord::isgeldig(char huidigespeler) {
  maakGeldigLijstLeeg();
  char tegenstander = gettegenstander(huidigespeler);
  bordvakje *rij = ingang;
  while (rij != nullptr) {
    bordvakje *huidigvakje = rij;
    while (huidigvakje != nullptr) {
      if (huidigvakje->kleur == '.') {
        controleerzet(huidigvakje, tegenstander, huidigespeler);
      } // if
      huidigvakje = huidigvakje->buren[2];
    } // while
    rij = rij->buren[4];
  } // while
  if (inganggeldig != nullptr) {
    return true;
  }
  return false;
} // isgeldig

bool othellobord::computerzet(char huidigspeler, char tegenstander) {
  if (!isgeldig(huidigspeler)) {
    return false;
  }

  bordvakje *vakje = inganggeldig->vakje;
  vakje->kleur = huidigspeler;

  for (int i = 0; i < 8; i++) {
    if (inganggeldig->richtingen[i]) {
      bordvakje *hulp = vakje->buren[i]; // ← start ELKE keer vanaf vakje
      while (hulp != nullptr &&
             hulp->kleur == tegenstander) { // ← check nullptr!
        hulp->kleur = huidigspeler;
        hulp = hulp->buren[i];
      }
    }
  }
  return true;
}

void othellobord::menszet(char huidigspeler, char tegenstander) {
  isgeldig(huidigspeler);
}

void othellobord::voegvoor(bordvakje *&rij_ingang) {
  bordvakje *hulp = new bordvakje;
  hulp->buren[2] = rij_ingang;
  if (rij_ingang != nullptr) {
    rij_ingang->buren[6] = hulp;
  }
  rij_ingang = hulp;
}

bordvakje *othellobord::maakrij() {
  bordvakje *rij_ingang = nullptr;
  for (int i = 0; i < n; i++) {
    voegvoor(rij_ingang);
  }
  return rij_ingang;
}

void othellobord::ritsen(bordvakje *boven, bordvakje *onder) {
  while (onder != nullptr && boven != nullptr) {
    boven->buren[4] = onder;
    onder->buren[0] = boven;
    boven->buren[3] = onder->buren[2];
    boven->buren[5] = onder->buren[6];
    onder->buren[1] = boven->buren[2];
    onder->buren[7] = boven->buren[6];

    boven = boven->buren[2];
    onder = onder->buren[2];
  }
}

void othellobord::bouwbord() {
  bordvakje *boven = maakrij();
  ingang = boven;
  for (int i = 1; i < m; i++) {
    bordvakje *onder = maakrij();
    ritsen(boven, onder);
    boven = onder;
  }
  zetBeginStenen();
}

void othellobord::zetBeginStenen() {
  bordvakje *huidigvakje = ingang;
  for (int i = 0; i < (n / 2) - 1; i++) {
    huidigvakje = huidigvakje->buren[2];
  }
  for (int j = 0; j < (m / 2) - 1; j++) {
    huidigvakje = huidigvakje->buren[4];
  }
  huidigvakje->kleur = 'W';
  huidigvakje->buren[2]->kleur = 'Z';
  huidigvakje->buren[4]->kleur = 'Z';
  huidigvakje->buren[3]->kleur = 'W';
}

void othellobord::maakGeldigLijstLeeg() {
  while (inganggeldig != nullptr) {
    geldigvakje *weg = inganggeldig;
    inganggeldig = inganggeldig->volgende;
    delete weg;
  }
}

void othellobord::spel() {
  int beurtenovergeslagen = 0;
  char huidigespeler = 'Z';
  char tegenstander = 'W';
  drukaf();
  while (beurtenovergeslagen < 2) {
    if (!computerzet(huidigespeler, tegenstander)) {
      beurtenovergeslagen += 1;
    } else {
      beurtenovergeslagen = 0;
    }
    swap(huidigespeler, tegenstander);
    sleep(1);
    system("clear");
    drukaf();
  }
}

void othellobord::swap(char &a, char &b) {
  char temp = a;
  a = b;
  b = temp;
}

othellobord::othellobord() {
  bouwbord();
  inganggeldig = nullptr;
} // othellobord::othellobord

othellobord::~othellobord() {
  // TODO
} // othellobord::~othellobord

void othellobord::drukaf() {
  bordvakje *rij = ingang;
  cout << "  ";
  for (int i = 0; i < n; i++) {
    cout << char('A' + i) << " ";
  }
  cout << endl;
  int k = 1;
  while (rij != nullptr) {
    cout << k << " ";
    bordvakje *kolom = rij;
    while (kolom != nullptr) {
      cout << kolom->kleur << ' ';
      kolom = kolom->buren[2];
    }
    cout << endl;
    rij = rij->buren[4];
    k += 1;
  }
  // TODO
} // othellobord::drukaf

// TODO