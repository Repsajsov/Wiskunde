#include "othellobord.h"
#include <iostream>
using namespace std;

void infoBlok() {
  cout << "-----------------------------------------------------" << endl
       << "|                      Othello                      |" << endl
       << "-----------------------------------------------------" << endl
       << endl
       << "Vincent van der Velden - s4494059 - Wiskunde 2024" << endl
       << "Jasper Vos - s2911159 - Wiskunde 2025" << endl
       << "Programmeeropgave 4 - 6/12/2025" << endl
       << endl
       << "-----------------------------------------------------" << endl
       << "Functies:" << endl
       << "- Speel Othello!" << endl
       << "- Maak experimenten!" << endl
       << "-----------------------------------------------------" << endl;
} // infoBlok

char leesOptie() {
  // Leest input van gebruiker per karakter
  char resultaat;
  do {
    cin.get(resultaat);
  } while (resultaat == '\n'); // while
  if (resultaat >= 'a' && resultaat <= 'z') {
    resultaat = (resultaat - 'a') + 'A';
  } // if
  return resultaat;
} // leesOptie

int leesGetal(int max) {
  // Controleert of de input een getal is
  int resultaat = 0;
  char karakter = leesOptie();
  if (karakter >= '0' && karakter <= '9') {
    resultaat = karakter - '0';
  } // if
  while (cin.get(karakter) && karakter != '\n') {
    if (karakter >= '0' && karakter <= '9') {
      resultaat = resultaat * 10 + (karakter - '0');
      if (resultaat >= max) {
        resultaat = max;
      } // if
    } // if
  } // while
  return resultaat;
} // leesGetal

int main() {
  infoBlok();

  char zType = ' ';
  while (zType != 'M' && zType != 'C') {
    cout << "Is Zwart [M]ens of [C]omputer? ";
    zType = leesOptie();
  } // while
  char wType = ' ';
  while (wType != 'M' && wType != 'C') {
    cout << "Is Wit [M]ens of [C]omputer? ";
    wType = leesOptie();
  } // while

  int m = 0;
  while (m < 2) {
    cout << "Aantal rijen (minimaal 2): ";
    m = leesGetal(100);
  } // while
  int n = 0;
  while (n < 2) {
    cout << "Aantal kolommen (minimaal 2): ";
    n = leesGetal(100);
  } // while

  int aantalSpellen = 1;
  if (zType == 'C' && wType == 'C') {
    aantalSpellen = 0;
    while (aantalSpellen < 1) {
      cout << "Hoeveel spellen? ";
      aantalSpellen = leesGetal(1000000);
    } // while
  } // if

  OthelloBord game(m, n, zType == 'C', wType == 'C');

  if (aantalSpellen == 1) {
    game.spel();
  } else {
    game.experiment(aantalSpellen);
  }

  return 0;
} // main