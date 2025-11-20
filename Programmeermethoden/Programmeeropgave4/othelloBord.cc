#include "othelloBord.h"
#include "inputHandler.h"
#include "overige.h"
#include "speler.h"
#include <ctime>
#include <iostream>

using namespace std;

int OthelloBord::krijgM() { return m; }
int OthelloBord::krijgN() { return n; }
vak **OthelloBord::krijgVakjes() { return vakjes; }

OthelloBord::OthelloBord(int m, int n, Speler *speler1, Speler *speler2) {
  this->m = m;
  this->n = n;
  this->speler1 = speler1;
  this->speler2 = speler2;

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

  valideZetten = new mogelijkeZet[m * n];
}

OthelloBord::~OthelloBord() {
  for (int i = 0; i < m * n; i++) {
    delete vakjes[i];
  }
  delete[] vakjes;
  delete[] valideZetten;
}

OthelloBord *OthelloBord::kopieer() {
  OthelloBord *kopieBord = new OthelloBord(m, n, speler1, speler2);
  for (int i = 0; i < m * n; i++) {
    kopieBord->vakjes[i]->teken = this->vakjes[i]->teken;
  }
  return kopieBord;
}

void OthelloBord::afdrukken() {
  vak *rij = linksboven;
  int rijNummer = 1;
  cout << "Speler " << speler1->krijgSymbool() << ": " << speler1->krijgScore()
       << ", Speler " << speler2->krijgSymbool() << ": "
       << speler2->krijgScore() << endl
       << endl;
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

Speler *OthelloBord::krijgTegenstander(Speler *speler) {
  return (speler == speler1) ? speler2 : speler1;
}

mogelijkeZet *OthelloBord::vindZet(vak *vakje) {
  for (int i = 0; i < aantalMogelijkeZetten; i++) {
    if (vakje == valideZetten[i].vakje) {
      return &valideZetten[i];
    }
  }
  return nullptr;
}

mogelijkeZet *OthelloBord::kiesVak() {
  mogelijkeZet *zet = nullptr;
  while (aantalMogelijkeZetten != 0) {
    cout << "Geef coordinaat: ";
    char kolom = InputHandler::leesOptie();
    kolom = int(kolom - 'A');
    int rij = InputHandler::leesGetal(10) - 1;

    if (rij >= 0 && rij < m && kolom >= 0 && kolom < n) {
      zet = vindZet(vakjes[rij * n + kolom]);
      if (zet != nullptr) {
        return zet;
      }
    }
  }
  return nullptr;
}

bool OthelloBord::mensZet(Speler *speler) {
  berekenValideZetten(speler);
  if (aantalMogelijkeZetten == 0) {
    return false;
  }
  mogelijkeZet *gekozenVak = kiesVak();
  if (gekozenVak == nullptr) {
    return false;
  }

  voerZetUit(gekozenVak->vakje, gekozenVak->aantalFlips, speler);
  return true;
}

void OthelloBord::voerZetUit(vak *vakje, int aantalFlips, Speler *speler) {
  Speler *tegenstander = krijgTegenstander(speler);
  tegenstander->veranderScore(-aantalFlips);
  speler->veranderScore(aantalFlips + 1);

  for (int richting = NOORD; richting <= NOORDWEST; richting++) {
    if (vakje->buren[richting] &&
        vakje->buren[richting]->teken == tegenstander->krijgSymbool()) {
      flipVakken(vakje, richting, speler->krijgSymbool());
    }
  }
  vakje->teken = speler->krijgSymbool();
}

bool OthelloBord::computerZet(Speler *speler) {
  berekenValideZetten(speler);
  if (aantalMogelijkeZetten == 0) {
    return false;
  }
  int keuze = Overige::absoluut(Overige::randomGetal(aantalMogelijkeZetten));
  mogelijkeZet *zet = &valideZetten[keuze];
  voerZetUit(zet->vakje, zet->aantalFlips, speler);
  return true;
}

bool OthelloBord::isKlaar() {
  berekenValideZetten(speler1);
  int speler1AantalZetten = aantalMogelijkeZetten;
  berekenValideZetten(speler2);
  int speler2AantalZetten = aantalMogelijkeZetten;
  return (speler1AantalZetten == 0 && speler2AantalZetten == 0);
}

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

bool OthelloBord::flipVakken(vak *huidigVak, int richting, char symbool) {
  vak *volgende = huidigVak->buren[richting];

  if (!volgende || volgende->teken == '.') {
    return false;
  }
  if (volgende->teken == symbool) {
    return true;
  }
  if (flipVakken(volgende, richting, symbool)) {
    volgende->teken = symbool;
    return true;
  }
  return false;
}

bool OthelloBord::isGeldig(vak *huidigVakje, int richting, char symbool) {
  vak *volgende = huidigVakje->buren[richting];
  if (!volgende || volgende->teken == '.') {
    return false;
  }
  if (volgende->teken == symbool) {
    return true;
  }
  if (isGeldig(volgende, richting, symbool)) {
    return true;
  }
  return false;
}

int OthelloBord::telFlips(vak *huidigVakje, int richting, char symbool) {
  vak *volgende = huidigVakje->buren[richting];
  if (!volgende || volgende->teken == '.') {
    return -1;
  }
  if (volgende->teken == symbool) {
    return 0;
  }
  int count = telFlips(volgende, richting, symbool);
  if (count < 0) {
    return -1;
  }
  return count + 1;
}

void OthelloBord::berekenValideZetten(Speler *speler) {
  aantalMogelijkeZetten = 0;

  Speler *tegenstander = krijgTegenstander(speler);
  vak *rij = linksboven;
  while (rij) {
    vak *huidigVakje = rij;
    while (huidigVakje) {
      if (huidigVakje->teken == '.') {
        int totaalFlips = 0;

        for (int richting = NOORD; richting <= NOORDWEST; richting++) {
          if (huidigVakje->buren[richting] &&
              huidigVakje->buren[richting]->teken ==
                  tegenstander->krijgSymbool()) {
            int flips = telFlips(huidigVakje, richting, speler->krijgSymbool());
            if (flips > 0) {
              totaalFlips += flips;
            }
          }
        }
        if (totaalFlips > 0) {
          valideZetten[aantalMogelijkeZetten].vakje = huidigVakje;
          valideZetten[aantalMogelijkeZetten].aantalFlips = totaalFlips;
          aantalMogelijkeZetten++;
        }
      }
      huidigVakje = huidigVakje->buren[OOST];
    }
    rij = rij->buren[ZUID];
  }
}