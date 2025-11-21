#include "spel.h"
#include "othelloBord.h"
#include "speler.h"
#include "stapel.h"
#include <iostream>
#include <unistd.h>

using namespace std;

Spel::Spel() {
  bord = nullptr;
  speler1 = nullptr;
  speler2 = nullptr;
  huidigeSpeler = nullptr;
  stapel = nullptr;
  seed = time(0);
  spelActief = true;
}

Spel::~Spel() {
  delete bord;
  delete speler1;
  delete speler2;
  delete stapel;
}

void Spel::start() {
  opstarten();
  spelen();
}

void Spel::opstarten() {
  schermSchoonmaken();
  cout << "Speler Z - [M]ens of [C]omputer: ";
  bool speler1Computer = (leesOptie() == 'C');
  cout << "Speler W - [M]ens of [C]omputer: ";
  bool speler2Computer = (leesOptie() == 'C');
  cout << "Aantal rijen: ";
  int rijen = leesGetal(20);
  cout << "Aantal kolommen: ";
  int kolommen = leesGetal(20);

  speler1 = new Speler('Z', speler1Computer);
  speler2 = new Speler('W', speler2Computer);
  bord = new OthelloBord(rijen, kolommen, speler1, speler2);
  stapel = new Stapel(bord, 2, 2);
  huidigeSpeler = speler1;
}

void Spel::spelen() {
  while (!bord->geenMogelijkeZetten() && spelActief) {
    schermSchoonmaken();
    bord->afdrukken();
    bord->berekenValideZetten(huidigeSpeler);

    if (bord->krijgAantalMogelijkeZetten() == 0) {
      cout << "Speler " << huidigeSpeler->krijgSymbool()
           << " kan niet zetten! Beurt overgeslagen." << endl;
      wacht(2);
      huidigeSpeler = bord->krijgTegenstander(huidigeSpeler);
      continue;
    }

    bool zetGelukt = false;
    if (!huidigeSpeler->isComputerSpeler()) {
      cout << "[Coordinaat] | [U]ndo | [S]toppen" << endl;
      char input = leesOptie();

      if (input == 'U') {
        stapel->undo(bord, speler1, speler2);
        continue;
      } else if (input == 'S') {
        spelActief = false;
        break;
      }

      int kolom = input - 'A';
      int rij = leesGetal(20) - 1;
      mogelijkeZet *gekozenZet = bord->vindZet(rij, kolom);
      zetGelukt = bord->mensZet(huidigeSpeler, gekozenZet);

      if (!zetGelukt) {
        cout << "Ongeldige zet! Probeer opnieuw." << endl;
        wacht(1);
        continue;
      }
    } else {
      zetGelukt = bord->computerZet(huidigeSpeler);
    }
    cout << "Speler " << huidigeSpeler->krijgSymbool() << " heeft gezet!"
         << endl;
    wacht(1);

    stapel->push(bord, speler1->krijgScore(), speler2->krijgScore());
    huidigeSpeler = bord->krijgTegenstander(huidigeSpeler);
  }
}

char Spel::leesOptie() {
  char resultaat;
  do {
    cin.get(resultaat);
  } while (resultaat == '\n');
  if (resultaat >= 'a' && resultaat <= 'z') {
    resultaat = (resultaat - 'a') + 'A';
  }
  return resultaat;
}

int Spel::leesGetal(int max) {
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

int Spel::randomGetal(int max) {
  seed = (221 * seed + 1) % 1000;
  int resultaat = seed % max;
  if (resultaat < 0) {
    resultaat = -resultaat;
  }

  return resultaat;
}

void Spel::schermSchoonmaken() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void Spel::wacht(int seconden) { sleep(seconden); }