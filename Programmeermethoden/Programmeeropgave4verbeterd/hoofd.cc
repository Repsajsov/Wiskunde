// file hoofd.cc
#include "othellobord.h"
#include <iostream>
using namespace std;

int leesgetal(int maxwaarde) {
  char huidigkarakter;
  bool geenenter = false;
  int getal = 0;

  while (true) {                // begin van de leeslus
    huidigkarakter = cin.get(); // ingevoerd karakter lezen

    // cijfer controleren
    if (huidigkarakter >= '0' && huidigkarakter <= '9') {
      geenenter = true;
      int cijfer = huidigkarakter - '0';
      int nieuwgetal = 10 * getal + cijfer;

      // controleren van de maximale waarde
      if (nieuwgetal <= maxwaarde) {
        getal = nieuwgetal;
      }
    }
    if (geenenter && huidigkarakter == '\n') {
      return getal;
    }
  }
}

// functie om opties intelezen van de gebruiker
char leesoptie() {
  char optie = cin.get();
  while (optie == '\n') {
    optie = cin.get();
  } // while
  if (optie >= 'a' && optie <= 'z') {
    optie = optie - 'a' + 'A';
  } // if
  return optie;
} // leesoptie

// void othellobord::mensofpc() {
//   cout << "Is zwart een mens of computer? [C]omputer  [M]ens" << endl;
//   zmensofpc = leesoptie();
//   cout << "Is wit een mens of computer? [C]omputer  [M]ens" << endl;
//   wmensofpc = leesoptie();
// }

void OthelloBord::groottebord() {
  cout << "Hoeveel kollomen wil je hebben? [>2] , [2|]" << endl;
  m = leesgetal(20);
  cout << "Hoeveel rijen wil je hebben?" << endl;
  n = leesgetal(20);
}

// void othellobord::spelteller() {
//   if (zmensofpc == 'C' && wmensofpc == 'M') {
//     cout << "Hoeveel spellen wil je spelen?" << endl;
//     aantalspellen = leesgetal(1000000000);
//   }
// }

int main() {
  OthelloBord game;
  game.spel();
  return 0;
} // main