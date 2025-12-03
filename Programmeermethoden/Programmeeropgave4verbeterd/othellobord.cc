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

geldigeZet::geldigeZet() {
  vakje = nullptr;
  volgende = nullptr;
  for (int i = 0; i < 8; i++) {
    richtingen[i] = false;
  }
  aantalGeslagen = 0;
}

geldigeZet *othellobord::zoekGeldigeZet(bordvakje *vakje) {
  geldigeZet *huidig = geldigeZetten;
  while (huidig != nullptr) {
    if (huidig->vakje == vakje) {
      return huidig;
    }
    huidig = huidig->volgende;
  }
  return nullptr;
}

bordvakje *othellobord::vindVakje(int kolom, int rij) {
  if (kolom < 0 || kolom >= n || rij < 0 || rij >= m) {
    return nullptr;
  }

  bordvakje *huidig = bordStart;

  for (int i = 0; i < rij; i++) {
    huidig = huidig->buren[4];
  }

  for (int i = 0; i < kolom; i++) {
    huidig = huidig->buren[2];
  }

  return huidig;
}

void othellobord::voegVoor(geldigeZet *&rij_ingang, bordvakje *vakje,
                           int richting) {
  geldigeZet *bestaand = zoekGeldigeZet(vakje);
  if (bestaand != nullptr) {
    bestaand->richtingen[richting] = true;
    return;
  }

  geldigeZet *hulp = new geldigeZet;
  hulp->vakje = vakje;
  hulp->richtingen[richting] = true;
  hulp->volgende = rij_ingang;
  rij_ingang = hulp;
}

char othellobord::getTegenstander(char huidigespeler) {
  char tegenstander = '\0';
  if (huidigespeler == 'Z') {
    tegenstander = 'W';
  } // if
  else {
    tegenstander = 'Z';
  } // else
  return tegenstander;
}

void othellobord::controleerZet(bordvakje *huidigVakje, char tegenstander,
                                char speler) {
  for (int i = 0; i < 8; i++) {
    if (huidigVakje->buren[i] != nullptr) {
      if (huidigVakje->buren[i]->kleur == tegenstander) {
        bordvakje *hulp = huidigVakje->buren[i];
        while (hulp != nullptr && hulp->kleur != '.') {
          if (hulp->kleur == speler) {
            voegVoor(geldigeZetten, huidigVakje, i);
            break;
          } // if
          hulp = hulp->buren[i];
        } // if
      } // if
    }
  } // for
}

bool othellobord::berekenGeldigeZetten(char speler) {
  resetGeldigeZetten();
  char tegenstander = getTegenstander(speler);
  bordvakje *rij = bordStart;
  while (rij != nullptr) {
    bordvakje *huidigvakje = rij;
    while (huidigvakje != nullptr) {
      if (huidigvakje->kleur == '.') {
        controleerZet(huidigvakje, tegenstander, speler);
      } // if
      huidigvakje = huidigvakje->buren[2];
    } // while
    rij = rij->buren[4];
  } // while
  if (geldigeZetten != nullptr) {
    return true;
  }
  return false;
} // isgeldig

bool othellobord::computerzet(char huidigspeler, char tegenstander) {
  if (!berekenGeldigeZetten(huidigspeler)) {
    return false;
  }

  doeZet(geldigeZetten->vakje, geldigeZetten, huidigspeler);
  return true;
}

void othellobord::doeZet(bordvakje *vakje, geldigeZet *geldig, char speler) {
  vakje->kleur = speler;
  char tegen = getTegenstander(speler);

  for (int i = 0; i < 8; i++) {
    if (geldig->richtingen[i]) {
      bordvakje *hulp = vakje->buren[i];
      while (hulp != nullptr && hulp->kleur == tegen) {
        hulp->kleur = speler;
        hulp = hulp->buren[i];
      }
    }
  }
}
bool othellobord::menszet(char speler, char tegenstander) {
  berekenGeldigeZetten(speler);
  bool isGeldigeZet = false;
  while (!isGeldigeZet) {
    cout << "Kolom: ";
    int kolom = int(leesOptie() - 'A');
    int rij = leesGetal(m);
    if (kolom < 0 || kolom >= n || rij < 1 || rij > m) {
      cout << "Deze coordinaten liggen buiten het bord!" << endl;
    } else {
      bordvakje *gekozen = vindVakje(kolom, rij - 1);
      geldigeZet *gekozenGeldig = zoekGeldigeZet(gekozen);
      if (gekozenGeldig == nullptr) {
        cout << "Ongeldige zet!" << endl;
      } else {
        doeZet(gekozen, gekozenGeldig, speler);
        isGeldigeZet = true;
      }
    }
  }
  return true;
}

int othellobord::leesGetal(int maxWaarde) {
  char huidigKarakter;
  bool geenEnter = false;
  int getal = 0;

  while (true) {                // begin van de leeslus
    huidigKarakter = cin.get(); // ingevoerd karakter lezen

    // cijfer controleren
    if (huidigKarakter >= '0' && huidigKarakter <= '9') {
      geenEnter = true;
      int cijfer = huidigKarakter - '0';
      int nieuwgetal = 10 * getal + cijfer;

      // controleren van de maximale waarde
      if (nieuwgetal <= maxWaarde) {
        getal = nieuwgetal;
      }
    }
    if (geenEnter && huidigKarakter == '\n') {
      return getal;
    }
  }
}

char othellobord::leesOptie() {
  char optie = cin.get();
  while (optie == '\n') {
    optie = cin.get();
  } // while
  if (optie >= 'a' && optie <= 'z') {
    optie = optie - 'a' + 'A';
  } // if
  return optie;
} // leesoptie

void othellobord::voegVoor(bordvakje *&rij_ingang) {
  bordvakje *hulp = new bordvakje;
  hulp->buren[2] = rij_ingang;
  if (rij_ingang != nullptr) {
    rij_ingang->buren[6] = hulp;
  }
  rij_ingang = hulp;
}

bordvakje *othellobord::maakRij() {
  bordvakje *rij_ingang = nullptr;
  for (int i = 0; i < n; i++) {
    voegVoor(rij_ingang);
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

void othellobord::bouwBord() {
  bordvakje *boven = maakRij();
  bordStart = boven;
  for (int i = 1; i < m; i++) {
    bordvakje *onder = maakRij();
    ritsen(boven, onder);
    boven = onder;
  }
  zetBeginStenen();
}

void othellobord::zetBeginStenen() {
  bordvakje *huidigvakje = bordStart;
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

void othellobord::resetGeldigeZetten() {
  while (geldigeZetten != nullptr) {
    geldigeZet *oudeZet = geldigeZetten;
    geldigeZetten = geldigeZetten->volgende;
    delete oudeZet;
  }
}

void othellobord::spel() {
  int beurtenovergeslagen = 0;
  char speler = 'Z';
  char tegenstander = 'W';
  bordAfdrukken();
  while (beurtenovergeslagen < 2) {
    if (!computerzet(speler, tegenstander)) {
      beurtenovergeslagen += 1;
    } else {
      beurtenovergeslagen = 0;
    }
    swap(speler, tegenstander);
    sleep(1);
    system("clear");
    bordAfdrukken();
  }
}

void othellobord::swap(char &a, char &b) {
  char temp = a;
  a = b;
  b = temp;
}

othellobord::othellobord() {
  bouwBord();
  geldigeZetten = nullptr;
} // othellobord::othellobord

othellobord::~othellobord() {
  // TODO
} // othellobord::~othellobord

void othellobord::bordAfdrukken() {
  bordvakje *rij = bordStart;
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