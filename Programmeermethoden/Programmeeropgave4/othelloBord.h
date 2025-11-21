#ifndef OTHELLOBORD_H
#define OTHELLOBORD_H

class Speler;

enum Richting {
  NOORD = 0,
  NOORDOOST,
  OOST,
  ZUIDOOST,
  ZUID,
  ZUIDWEST,
  WEST,
  NOORDWEST
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
  int aantalRijen;
  int aantalKolommen;
  int oppervlakte;
  Speler *speler1;
  Speler *speler2;

public:
  OthelloBord(int aantalRijen, int aantalKolommen, Speler *speler1,
              Speler *speler2);
  ~OthelloBord();
  OthelloBord *kopieer();

  void afdrukken();
  bool mensZet(Speler *speler, mogelijkeZet *gekozenZet);
  bool computerZet(Speler *speler);
  void voerZetUit(vak *vakje, int aantalFlips, Speler *speler);

  void bindVakjes();
  bool geenMogelijkeZetten();

  Speler *krijgTegenstander(Speler *speler);
  int krijgAantalRijen();
  int krijgAantalKolommen();
  int krijgAantalMogelijkeZetten();
  vak **krijgVakjes();

  bool flipVakken(vak *huidigVak, int richting, char symbool);
  bool isGeldig(vak *huidigVak, int richting, char symbool);
  int telFlips(vak *huidigVak, int richting, char symbool);
  mogelijkeZet *vindZet(vak *vakje);
  mogelijkeZet *vindZet(int rij, int kolom);

  void berekenValideZetten(Speler *speler);
};

#endif