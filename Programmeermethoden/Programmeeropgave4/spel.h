#ifndef SPEL_H
#define SPEL_H

class OthelloBord;
class Speler;
class Stapel;

class Spel {
private:
  OthelloBord *bord;
  Speler *speler1;
  Speler *speler2;
  Speler *huidigeSpeler;
  Stapel *stapel;
  bool spelActief;
  int seed;

  void opstarten();
  void spelen();
  static char leesOptie();
  static int leesGetal(int max);
  void schermSchoonmaken();
  void wacht(int seconden);

public:
  Spel();
  ~Spel();
  void start();
  static int randomGetal(int max);
};

#endif