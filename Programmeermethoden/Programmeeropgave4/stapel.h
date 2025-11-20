#ifndef STAPEL_H
#define STAPEL_H

class OthelloBord;
class Speler;

struct spelStand {
  OthelloBord *bord;
  int score1, score2;
  spelStand *volgende;
};

class Stapel {
private:
  spelStand *top = nullptr;

public:
  Stapel(OthelloBord *bord, int score1, int score2);
  ~Stapel();
  bool isLeeg();
  void push(OthelloBord *bord, int score1, int score2);
  void herstel(OthelloBord *huidigBord, Speler *speler1, Speler *speler2);
  spelStand *pop();
};

#endif