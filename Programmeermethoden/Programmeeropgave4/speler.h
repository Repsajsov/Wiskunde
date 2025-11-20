#ifndef SPELER_H
#define SPELER_H

class Speler {
private:
  char symbool;
  int score;
  bool isComputer;

public:
  Speler(char symbool, bool isComputer);
  char krijgSymbool();
  int krijgScore();
  bool isComputerSpeler();
  void veranderScore(int punten);
  void zetScore(int nieuweScore);
};

#endif