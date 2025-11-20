#include "stapel.h"
#include "othelloBord.h"
#include "speler.h"
#include <iostream>

using namespace std;

Stapel::Stapel(OthelloBord *bord, int s1, int s2) {
  top = nullptr;
  push(bord, s1, s2);
}

Stapel::~Stapel() {
  while (!isLeeg()) {
    spelStand *temp = pop();
    delete temp->bord;
    delete temp;
  }
}

void Stapel::push(OthelloBord *bord, int s1, int s2) {
  spelStand *nieuw = new spelStand;
  nieuw->bord = bord->kopieer();
  nieuw->score1 = s1;
  nieuw->score2 = s2;
  nieuw->volgende = top;
  top = nieuw;
}

bool Stapel::isLeeg() { return (top == nullptr); }

void Stapel::herstel(OthelloBord *huidigBord, Speler *speler1,
                     Speler *speler2) {
  for (int i = 0; i < huidigBord->krijgM() * huidigBord->krijgN(); i++) {
    huidigBord->krijgVakjes()[i]->teken = top->bord->krijgVakjes()[i]->teken;
  }
  speler1->zetScore(top->score1);
  speler2->zetScore(top->score2);
}

spelStand *Stapel::pop() {
  if (isLeeg()) {
    return nullptr;
  }
  spelStand *laatsteStand = top;
  top = laatsteStand->volgende;
  laatsteStand->volgende = nullptr;
  return laatsteStand;
}
