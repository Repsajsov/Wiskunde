#include "stapel.h"
#include "othelloBord.h"
#include "speler.h"
#include <iostream>

using namespace std;

Stapel::Stapel(OthelloBord *bord, int score1, int score2) {
  top = nullptr;
  push(bord, score1, score2);
}

Stapel::~Stapel() {
  while (!isLeeg()) {
    pop();
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
  for (int i = 0;
       i < huidigBord->krijgAantalRijen() * huidigBord->krijgAantalKolommen();
       i++) {
    huidigBord->krijgVakjes()[i]->teken = top->bord->krijgVakjes()[i]->teken;
  }
  speler1->zetScore(top->score1);
  speler2->zetScore(top->score2);
}

void Stapel::pop() {
  if (isLeeg())
    return;
  spelStand *temp = top;
  top = temp->volgende;
  delete temp->bord;
  delete temp;
}

void Stapel::undo(OthelloBord *bord, Speler *speler1, Speler *speler2) {
  if (top && top->volgende) {
    pop();
    pop();
    if (!isLeeg()) {
      herstel(bord, speler1, speler2);
    }
  }
}