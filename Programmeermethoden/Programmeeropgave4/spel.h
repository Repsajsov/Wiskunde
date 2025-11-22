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
  static int seed;
  bool isExperiment;
  int aantalSpellen;

  void opstarten();
  void spelen();
  void speelZonderStapel();
  void resultaat();
  static char leesOptie();
  static int leesGetal(int max);
  void schermSchoonmaken();
  void wacht(int seconden);
  void experiment();

public:
  Spel();
  ~Spel();
  void start();
  static int randomGetal(int max);
};

#endif