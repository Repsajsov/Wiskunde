#include "othelloBord.h"
#include <iostream>
#include <unistd.h>

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
    sleep(1);
    system("clear");
  }
  return 0;
}
