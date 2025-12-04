// file hoofd.cc
#include "othellobord.h"
#include <iostream>
using namespace std;

// void othellobord::mensofpc() {
//   cout << "Is zwart een mens of computer? [C]omputer  [M]ens" << endl;
//   zmensofpc = leesoptie();
//   cout << "Is wit een mens of computer? [C]omputer  [M]ens" << endl;
//   wmensofpc = leesoptie();
// }

// void OthelloBord::groottebord() {
//   cout << "Hoeveel kollomen wil je hebben? [>2] , [2|]" << endl;
//   m = leesgetal(20);
//   cout << "Hoeveel rijen wil je hebben?" << endl;
//   n = leesgetal(20);
// }

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