#include "othelloBord.h"
#include <iostream>

using namespace std;

int main() {
  OthelloBord spel = OthelloBord(8, 8);
  bool beurtSpeler = true;

  while (!spel.isKlaar()) {
    spel.afdrukken();
    bool zetGelukt = false;
    while (!zetGelukt) {
      if (beurtSpeler)
        zetGelukt = spel.mensZet();
      else {
        zetGelukt = spel.computerZet();
      }
    }
    beurtSpeler = !beurtSpeler;
    system("clear");
  }
  return 0;
}
