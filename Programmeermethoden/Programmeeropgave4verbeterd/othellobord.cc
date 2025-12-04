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

Speler::Speler(char kleur, bool isComputer) {
  this->kleur = kleur;
  this->isComputer = isComputer;
  this->score = 2;
}
void Speler::verhoogScore(int punten) { score += punten; }
void Speler::setScore(int nieuweScore) { score = nieuweScore; }

Speler *OthelloBord::getTegenstander() {
  if (huidigeSpeler == speler1) {
    return speler2;
  }
  return speler1;
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

void OthelloBord::voegVoor(GeldigeZet *&startZet, BordVakje *vakje,
                           int richting, int geslagen) {
  GeldigeZet *bestaandeZet = zoekGeldigeZet(vakje);
  if (bestaandeZet != nullptr) {
    bestaandeZet->richtingen[richting] = true;
    bestaandeZet->aantalGeslagen += geslagen;
    return;
  }

  GeldigeZet *nieuweZet = new GeldigeZet;
  nieuweZet->vakje = vakje;
  nieuweZet->richtingen[richting] = true;
  nieuweZet->aantalGeslagen = geslagen;
  nieuweZet->volgende = startZet;
  startZet = nieuweZet;
}

void OthelloBord::controleerZet(BordVakje *huidigVakje) {
  Speler *tegenstander = getTegenstander();
  for (int i = 0; i < 8; i++) {
    if (huidigVakje->buren[i] != nullptr) {
      if (huidigVakje->buren[i]->kleur == tegenstander->kleur) {
        BordVakje *hulp = huidigVakje->buren[i];
        int aantalGeslagen = 0;
        while (hulp != nullptr && hulp->kleur != '.') {
          if (hulp->kleur == huidigeSpeler->kleur) {
            voegVoor(geldigeZetten, huidigVakje, i, aantalGeslagen);
            break;
          } // if
          aantalGeslagen++;
          hulp = hulp->buren[i];
        } // if
      } // if
    }
  } // for
}

bool OthelloBord::berekenGeldigeZetten() {
  resetGeldigeZetten();
  BordVakje *rij = bordStart;
  while (rij != nullptr) {
    BordVakje *huidigVakje = rij;
    while (huidigVakje != nullptr) {
      if (huidigVakje->kleur == '.') {
        controleerZet(huidigVakje);
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

bool OthelloBord::computerzet() {
  if (!berekenGeldigeZetten()) {
    return false;
  }

  flipVakken(geldigeZetten->vakje, geldigeZetten);
  return true;
}

void OthelloBord::flipVakken(BordVakje *startVakje, GeldigeZet *zet) {
  startVakje->kleur = huidigeSpeler->kleur;
  Speler *tegenstander = getTegenstander();

  for (int i = 0; i < 8; i++) {
    if (zet->richtingen[i]) {
      BordVakje *hulp = startVakje->buren[i];
      while (hulp != nullptr && hulp->kleur == tegenstander->kleur) {
        hulp->kleur = huidigeSpeler->kleur;
        hulp = hulp->buren[i];
      }
    }
  }
  huidigeSpeler->verhoogScore(zet->aantalGeslagen + 1);
  tegenstander->verhoogScore(-zet->aantalGeslagen);
}

bool OthelloBord::speelZet() {
  if (huidigeSpeler->isComputer) {
    return computerzet();
  }
  return mensZet();
}

bool OthelloBord::mensZet() {
  berekenGeldigeZetten();
  bool isGeldigeZet = false;
  while (!isGeldigeZet) {
    cout << "Geef Coordinaat (A1, B2, ...) of ga een zet terug (U)ndo:" << endl;
    char eersteKarakter = leesOptie();
    if (eersteKarakter == 'U') {
      cout << "Undo nog niet beschikbaar!" << endl;
      continue;
    }
    int kolom = int(eersteKarakter - 'A');
    int rij = leesGetal(m);
    if (kolom < 0 || kolom >= n || rij < 1 || rij > m) {
      cout << "Deze coordinaten liggen buiten het bord!" << endl;
    } else {
      BordVakje *gekozenVakje = vindVakje(kolom, rij - 1);
      GeldigeZet *gekozenZet = zoekGeldigeZet(gekozenVakje);
      if (gekozenZet == nullptr) {
        cout << "Ongeldige zet!" << endl;
      } else {
        flipVakken(gekozenVakje, gekozenZet);
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

void OthelloBord::verwisselSpelers() {
  if (huidigeSpeler == speler1) {
    huidigeSpeler = speler2;
  } else {
    huidigeSpeler = speler1;
  }
}

void OthelloBord::spel() {
  int beurtenOvergeslagen = 0;

  bordAfdrukken();
  while (beurtenOvergeslagen < 2) {
    if (!speelZet()) {
      beurtenOvergeslagen += 1;
    } else {
      beurtenOvergeslagen = 0;
    }
    verwisselSpelers();
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

  cout << "Speler 1 [M]ens of [C]omputer?" << endl;
  char antwoord1 = leesOptie();
  if (antwoord1 == 'M') {
    speler1 = new Speler('Z', false);
  } else {
    speler1 = new Speler('Z', true);
  }
  cout << "Speler 2 [M]ens of [C]omputer?" << endl;
  char antwoord2 = leesOptie();
  if (antwoord2 == 'M') {
    speler2 = new Speler('W', false);
  } else {
    speler2 = new Speler('W', true);
  }

  huidigeSpeler = speler1;
} // othellobord::othellobord

OthelloBord::~OthelloBord() {
  // TODO
} // othellobord::~othellobord

void OthelloBord::bordAfdrukken() {
  BordVakje *rij = bordStart;
  cout << "Speler 1: " << speler1->score << ", Speler 2: " << speler2->score
       << endl
       << endl;
  ;
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