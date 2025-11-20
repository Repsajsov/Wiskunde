#include "overige.h"
#include <cstdlib>
#include <ctime>
#include <unistd.h>

int Overige::seed = 0;
bool Overige::geinitialiseerd = false;

void Overige::initializeRandom() {
  if (!geinitialiseerd) {
    seed = time(0);
    srand(seed);
    geinitialiseerd = true;
  }
}

int Overige::randomGetal(int max) {
  if (!geinitialiseerd) {
    initializeRandom();
  }

  seed = (221 * seed + 1) % 1000;
  int resultaat = seed % max;

  if (resultaat < 0) {
    resultaat = -resultaat;
  }

  return resultaat;
}

void Overige::schermSchoonmaken() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void Overige::wacht(int seconden) { sleep(seconden); }

int Overige::absoluut(int getal) { return getal < 0 ? -getal : getal; }