#ifndef OTHELLOBORD_H
#define OTHELLOBORD_H

enum {
  NOORD = 0,
  NOORDOOST = 1,
  OOST = 2,
  ZUIDOOST = 3,
  ZUID = 4,
  ZUIDWEST = 5,
  WEST = 6,
  NOORDWEST = 7
};

struct vak {
  char teken = '.';
  vak *buren[8] = {nullptr};
};

struct mogelijkeZet {
  vak *vakje = nullptr;
  int aantalFlips = 0;
};

class OthelloBord {
private:
  vak *linksboven = nullptr;
  vak **vakjes;
  mogelijkeZet *valideZetten;
  int aantalMogelijkeZetten = 0;
  int m;
  int n;
  char mensSymbool = 'W';
  char computerSymbool = 'Z';
  int mensScore = 2;
  int computerScore = 2;
  int seed;

public:
  OthelloBord(int m, int n);
  ~OthelloBord();

  void afdrukken();
  bool mensZet();
  bool computerZet();

  bool isKlaar();
  void bindVakjes();

  bool flipVakken(vak *huidigVak, int richting, char symbool);
  bool isGeldig(vak *huidigVak, int richting, char symbool);
  int telFlips(vak *huidigVak, int richting, char symbool);

  void berekenValideZetten(char symbool);

  int randomGetal();
  char leesOptie();
  int leesGetal(int max);
};

#endif