#include "speler.h"
#include <iostream>

Speler::Speler(char symbool, bool isComputer) {
  this->symbool = symbool;
  this->score = 2;
  this->isComputer = isComputer;
}

char Speler::krijgSymbool() { return symbool; }

int Speler::krijgScore() { return score; }

bool Speler::isComputerSpeler() { return isComputer; }

void Speler::veranderScore(int punten) { score += punten; }

void Speler::zetScore(int nieuweScore) { score = nieuweScore; }