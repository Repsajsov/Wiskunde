// file othellobord.cc
#include "othellobord.h"
#include <iostream>
#include <unistd.h>
using namespace std;

BordVakje::BordVakje() {
  kleur = '.';
  for (int i = 0; i < 8; i++) {
    buren[i] = nullptr;
  }
}

GeldigeZet::GeldigeZet() {
  vakje = nullptr;
  volgende = nullptr;
  for (int i = 0; i < 8; i++) {
    richtingen[i] = false;
  }
  aantalGeslagen = 0;
}

GeldigeZet *OthelloBord::zoekGeldigeZet(BordVakje *vakje) {
  GeldigeZet *huidig = geldigeZetten;
  while (huidig != nullptr) {
    if (huidig->vakje == vakje) {
      return huidig;
    }
    huidig = huidig->volgende;
  }
  return nullptr;
}

BordVakje *OthelloBord::vindVakje(int kolom, int rij) {
  if (kolom < 0 || kolom >= n || rij < 0 || rij >= m) {
    return nullptr;
  }

  BordVakje *huidig = bordStart;

  for (int i = 0; i < rij; i++) {
    huidig = huidig->buren[4];
  }

  for (int i = 0; i < kolom; i++) {
    huidig = huidig->buren[2];
  }

  return huidig;
}

void OthelloBord::voegVoor(GeldigeZet *&rij_ingang, BordVakje *vakje,
                           int richting) {
  GeldigeZet *bestaand = zoekGeldigeZet(vakje);
  if (bestaand != nullptr) {
    bestaand->richtingen[richting] = true;
    return;
  }

  GeldigeZet *hulp = new GeldigeZet;
  hulp->vakje = vakje;
  hulp->richtingen[richting] = true;
  hulp->volgende = rij_ingang;
  rij_ingang = hulp;
}

char OthelloBord::getTegenstander(char speler) {
  char tegenstander = '\0';
  if (speler == 'Z') {
    tegenstander = 'W';
  } // if
  else {
    tegenstander = 'Z';
  } // else
  return tegenstander;
}

void OthelloBord::controleerZet(BordVakje *huidigVakje, char tegenstander,
                                char speler) {
  for (int i = 0; i < 8; i++) {
    if (huidigVakje->buren[i] != nullptr) {
      if (huidigVakje->buren[i]->kleur == tegenstander) {
        BordVakje *hulp = huidigVakje->buren[i];
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

bool OthelloBord::berekenGeldigeZetten(char speler) {
  resetGeldigeZetten();
  char tegenstander = getTegenstander(speler);
  BordVakje *rij = bordStart;
  while (rij != nullptr) {
    BordVakje *huidigVakje = rij;
    while (huidigVakje != nullptr) {
      if (huidigVakje->kleur == '.') {
        controleerZet(huidigVakje, tegenstander, speler);
      } // if
      huidigVakje = huidigVakje->buren[2];
    } // while
    rij = rij->buren[4];
  } // while
  if (geldigeZetten != nullptr) {
    return true;
  }
  return false;
} // isgeldig

bool OthelloBord::computerzet(char speler, char tegenstander) {
  if (!berekenGeldigeZetten(speler)) {
    return false;
  }

  doeZet(geldigeZetten->vakje, geldigeZetten, speler);
  return true;
}

void OthelloBord::doeZet(BordVakje *startVakje, GeldigeZet *geldig, char speler) {
  startVakje->kleur = speler;
  char tegenstander = getTegenstander(speler);

  for (int i = 0; i < 8; i++) {
    if (geldig->richtingen[i]) {
      BordVakje *hulp = startVakje->buren[i];
      while (hulp != nullptr && hulp->kleur == tegenstander) {
        hulp->kleur = speler;
        hulp = hulp->buren[i];
      }
    }
  }
}
bool OthelloBord::mensZet(char speler, char tegenstander) {
  berekenGeldigeZetten(speler);
  bool isGeldigeZet = false;
  while (!isGeldigeZet) {
    cout << "Kolom: ";
    int kolom = int(leesOptie() - 'A');
    int rij = leesGetal(m);
    if (kolom < 0 || kolom >= n || rij < 1 || rij > m) {
      cout << "Deze coordinaten liggen buiten het bord!" << endl;
    } else {
      BordVakje *gekozenVakje = vindVakje(kolom, rij - 1);
      GeldigeZet *gekozenZet = zoekGeldigeZet(gekozenVakje);
      if (gekozenZet == nullptr) {
        cout << "Ongeldige zet!" << endl;
      } else {
        doeZet(gekozenVakje, gekozenZet, speler);
        isGeldigeZet = true;
      }
    }
  }
  return true;
}

int OthelloBord::leesGetal(int maxWaarde) {
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

char OthelloBord::leesOptie() {
  char optie = cin.get();
  while (optie == '\n') {
    optie = cin.get();
  } // while
  if (optie >= 'a' && optie <= 'z') {
    optie = optie - 'a' + 'A';
  } // if
  return optie;
} // leesoptie

void OthelloBord::voegVoor(BordVakje *&startVakje) {
  BordVakje *hulp = new BordVakje;
  hulp->buren[2] = startVakje;
  if (startVakje != nullptr) {
    startVakje->buren[6] = hulp;
  }
  startVakje = hulp;
}

BordVakje *OthelloBord::maakRij() {
  BordVakje *rijStart = nullptr;
  for (int i = 0; i < n; i++) {
    voegVoor(rijStart);
  }
  return rijStart;
}

void OthelloBord::ritsen(BordVakje *bovenRijVakje, BordVakje *onderRijVakje) {
  while (bovenRijVakje != nullptr && onderRijVakje != nullptr) {
    bovenRijVakje->buren[4] = onderRijVakje;
    onderRijVakje->buren[0] = bovenRijVakje;
    bovenRijVakje->buren[3] = onderRijVakje->buren[2];
    bovenRijVakje->buren[5] = onderRijVakje->buren[6];
    onderRijVakje->buren[1] = bovenRijVakje->buren[2];
    onderRijVakje->buren[7] = bovenRijVakje->buren[6];

    bovenRijVakje = bovenRijVakje->buren[2];
    onderRijVakje = onderRijVakje->buren[2];
  }
}

void OthelloBord::bouwBord() {
  BordVakje *bovenRijVakje = maakRij();
  bordStart = bovenRijVakje;
  for (int i = 1; i < m; i++) {
    BordVakje *onderRijVakje = maakRij();
    ritsen(bovenRijVakje, onderRijVakje);
    bovenRijVakje = onderRijVakje;
  }
  zetBeginStenen();
}

void OthelloBord::zetBeginStenen() {
  BordVakje *huidigVakje = bordStart;
  for (int i = 0; i < (n / 2) - 1; i++) {
    huidigVakje = huidigVakje->buren[2];
  }
  for (int j = 0; j < (m / 2) - 1; j++) {
    huidigVakje = huidigVakje->buren[4];
  }
  huidigVakje->kleur = 'W';
  huidigVakje->buren[2]->kleur = 'Z';
  huidigVakje->buren[4]->kleur = 'Z';
  huidigVakje->buren[3]->kleur = 'W';
}

void OthelloBord::resetGeldigeZetten() {
  while (geldigeZetten != nullptr) {
    GeldigeZet *oudeZet = geldigeZetten;
    geldigeZetten = geldigeZetten->volgende;
    delete oudeZet;
  }
}

void OthelloBord::spel() {
  int beurtenOvergeslagen = 0;
  char speler = 'Z';
  char tegenstander = 'W';
  bordAfdrukken();
  while (beurtenOvergeslagen < 2) {
    if (!computerzet(speler, tegenstander)) {
      beurtenOvergeslagen += 1;
    } else {
      beurtenOvergeslagen = 0;
    }
    swap(speler, tegenstander);
    sleep(1);
    system("clear");
    bordAfdrukken();
  }
}

void OthelloBord::swap(char &a, char &b) {
  char temp = a;
  a = b;
  b = temp;
}

OthelloBord::OthelloBord() {
  bouwBord();
  geldigeZetten = nullptr;
} // othellobord::othellobord

OthelloBord::~OthelloBord() {
  // TODO
} // othellobord::~othellobord

void OthelloBord::bordAfdrukken() {
  BordVakje *rij = bordStart;
  cout << "  ";
  for (int i = 0; i < n; i++) {
    cout << char('A' + i) << " ";
  }
  cout << endl;
  int k = 1;
  while (rij != nullptr) {
    cout << k << " ";
    BordVakje *kolom = rij;
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