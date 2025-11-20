#ifndef OTHELLOBORD_H
#define OTHELLOBORD_H

class Speler;

enum { NOORD = 0, NOORDOOST, OOST, ZUIDOOST, ZUID, ZUIDWEST, WEST, NOORDWEST };

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
  Speler *speler1;
  Speler *speler2;

public:
  OthelloBord(int m, int n, Speler *speler1, Speler *speler2);
  ~OthelloBord();
  OthelloBord *kopieer();

  void afdrukken();
  bool mensZet(Speler *speler);
  bool computerZet(Speler *speler);

  bool isKlaar();
  void bindVakjes();

  Speler *krijgTegenstander(Speler *speler);
  int krijgM();
  int krijgN();
  vak **krijgVakjes();

  bool flipVakken(vak *huidigVak, int richting, char symbool);
  bool isGeldig(vak *huidigVak, int richting, char symbool);
  int telFlips(vak *huidigVak, int richting, char symbool);
  mogelijkeZet *vindZet(vak *vakje);
  void voerZetUit(vak *vakje, int aantalFlips, Speler *speler);
  mogelijkeZet *kiesVak();

  void berekenValideZetten(Speler *speler);
};

#endif