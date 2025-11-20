#ifndef OVERIGE_H
#define OVERIGE_H

class Overige {
private:
  static int seed;
  static bool geinitialiseerd;

public:
  static void initializeRandom();
  static int randomGetal(int max);

  static void schermSchoonmaken();
  static void wacht(int seconden);

  static int absoluut(int getal);
};

#endif