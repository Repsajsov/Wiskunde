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

class OthelloBord {
private:
  vak *linksboven = nullptr;
  vak **vakjes;
  int m;
  int n;
  char karakterSpeler = 'W';
  char karakterTegenstander = 'Z';

public:
  OthelloBord(int m, int n);
  ~OthelloBord();

  void afdrukken();
  bool mensZet();
  bool computerZet();

  bool isKlaar();
  void bindVakjes();
  bool flipVakken(vak *huidigVak, int richting, char kleur);

  vak **berekenValideZetten();

  char leesOptie();
  int leesGetal(int max);
};

#endif