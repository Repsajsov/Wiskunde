#include "spel.h"
#include "othelloBord.h"
#include "speler.h"
#include "stapel.h"
#include <iostream>
#include <unistd.h>

using namespace std;

int Spel::seed = time(0);

Spel::Spel() {
  bord = nullptr;
  speler1 = nullptr;
  speler2 = nullptr;
  huidigeSpeler = nullptr;
  stapel = nullptr;
  spelActief = true;
  isExperiment = false;
  aantalSpellen = 1;
}

Spel::~Spel() {
  delete bord;
  delete speler1;
  delete speler2;
  delete stapel;
}

void Spel::experiment() {
  int winstZ = 0, winstW = 0, gelijk = 0;

  for (int i = 0; i < aantalSpellen; i++) {
    if (i > 0 && i % (aantalSpellen / 10) == 0) {
      cout << "Spellen gespeeld: " << i << "/" << aantalSpellen << endl;
    }

    speelZonderStapel();

    if (speler1->krijgScore() > speler2->krijgScore())
      winstZ++;
    else if (speler2->krijgScore() > speler1->krijgScore())
      winstW++;
    else
      gelijk++;

    int aantalRijen = bord->krijgAantalRijen();
    int aantalKolommen = bord->krijgAantalKolommen();
    delete bord;
    speler1->zetScore(2);
    speler2->zetScore(2);
    bord = new OthelloBord(aantalRijen, aantalKolommen, speler1, speler2);
  }

  cout << endl
       << "Z: " << winstZ << " | W: " << winstW << " | Gelijk: " << gelijk
       << endl;
}

void Spel::start() {
  opstarten();
  if (aantalSpellen == 1) {
    spelen();
    resultaat();
  } else {
    experiment();
  }
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

  aantalSpellen = 1;
  if (speler1Computer == speler2Computer) {
    cout << "Wil je een experiment doen (j/n):" << endl;
    if (leesOptie() == 'J') {
      isExperiment = true;
      cout << "Hoeveel spelletjes voor statistieken: ";
      aantalSpellen = leesGetal(10000);
    }
  }

  speler1 = new Speler('Z', speler1Computer);
  speler2 = new Speler('W', speler2Computer);
  bord = new OthelloBord(rijen, kolommen, speler1, speler2);
  if (aantalSpellen == 1) {
    stapel = new Stapel(bord, 2, 2);
  }
  huidigeSpeler = speler1;
}

void Spel::resultaat() {
  if (speler1->krijgScore() > speler2->krijgScore()) {
    cout << "Speler " << speler1->krijgSymbool() << " heeft gewonnen!" << endl;
  } else if (speler1->krijgScore() < speler2->krijgScore()) {
    cout << "Speler " << speler2->krijgScore() << " heeft gewonnen!" << endl;
  } else {
    cout << "Gelijkspel!" << endl;
  }
}

void Spel::speelZonderStapel() {
  huidigeSpeler = speler1;
  int nietGespeeld = 0;

  while (nietGespeeld < 2) {
    bord->berekenValideZetten(huidigeSpeler);

    if (bord->krijgAantalMogelijkeZetten() == 0) {
      nietGespeeld++;
      huidigeSpeler = bord->krijgTegenstander(huidigeSpeler);
      continue;
    }

    nietGespeeld = 0;
    bord->computerZet(huidigeSpeler);
    huidigeSpeler = bord->krijgTegenstander(huidigeSpeler);
  }
}
void Spel::spelen() {
  while (!bord->geenMogelijkeZetten() && spelActief) {
    schermSchoonmaken();
    bord->afdrukken();
    bord->berekenValideZetten(huidigeSpeler);

    if (bord->krijgAantalMogelijkeZetten() == 0) {
      cout << "Speler " << huidigeSpeler->krijgSymbool()
           << " kan niet zetten! Beurt overgeslagen." << endl;
      if (!isExperiment)
        wacht(1);
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
        if (!isExperiment)
          wacht(1);
        continue;
      }
    } else {
      zetGelukt = bord->computerZet(huidigeSpeler);
    }
    cout << "Speler " << huidigeSpeler->krijgSymbool() << " heeft gezet!"
         << endl;
    if (!isExperiment)
      wacht(1);

    if (!isExperiment) {
      stapel->push(bord, speler1->krijgScore(), speler2->krijgScore());
    }
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
  int resultaat = 0;
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