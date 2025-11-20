#include "othelloBord.h"
#include "overige.h"
#include "speler.h"
#include "stapel.h"
#include <iostream>

using namespace std;

int main() {
  // Speler *speler1 = new Speler('W', true);
  // Speler *speler2 = new Speler('Z', true);

  // OthelloBord *spel = new OthelloBord(8, 8, speler1, speler2);

  // Speler *huidigeSpeler = speler1;

  // while (!spel->isKlaar()) {
  //   Overige::schermSchoonmaken();
  //   spel->afdrukken();
  //   bool zetGelukt = false;

  //   if (huidigeSpeler->isComputerSpeler()) {
  //     zetGelukt = spel->computerZet(huidigeSpeler);
  //     if (zetGelukt) {
  //       cout << "Speler " << huidigeSpeler->krijgSymbool() << " heeft
  //       geslagen!"
  //            << endl;
  //       Overige::wacht(1);
  //     } else {
  //       cout << "Speler " << huidigeSpeler->krijgSymbool()
  //            << " kan niks doen! Beurt wordt overgeslagen." << endl;
  //       Overige::wacht(2);
  //     }
  //   } else {
  //     zetGelukt = spel->mensZet(huidigeSpeler);
  //     if (zetGelukt) {
  //       cout << "Speler " << huidigeSpeler->krijgSymbool() << " heeft
  //       geslagen!"
  //            << endl;
  //     } else {
  //       cout << "Speler " << huidigeSpeler->krijgSymbool()
  //            << " kan niks doen! Beurt wordt overgeslagen." << endl;
  //       Overige::wacht(2);
  //     }
  //   }
  //   huidigeSpeler = spel->krijgTegenstander(huidigeSpeler);
  // }
  // if (speler1->krijgScore() > speler2->krijgScore()) {
  //   cout << "Speler " << speler1->krijgSymbool() << " heeft gewonnen!" <<
  //   endl;
  // } else if (speler1->krijgScore() < speler2->krijgScore()) {
  //   cout << "Speler " << speler2->krijgSymbool() << " heeft gewonnen!" <<
  //   endl;
  // } else {
  //   cout << "Gelijkspel!" << endl;
  // }

  // delete spel;
  // delete speler1;
  // delete speler2;

  return 0;
}
