// file othellobord.h
class BordVakje {
public:
  char kleur;          //     7 0 1
  BordVakje *buren[8]; //     6   2
  BordVakje();         //     5 4 3
}; // BordVakje

class GeldigeZet {
public:
  BordVakje *vakje;
  GeldigeZet *volgende;
  int aantalGeslagen;
  bool richtingen[8];
  GeldigeZet();
};

class Speler {
public:
  int score;
  char kleur;
  bool isComputer;
  Speler(char kleur, bool isComputer);
  void setScore(int nieuweScore);
  void verhoogScore(int punten);
};

class OthelloBord {
private:
  BordVakje *bordStart;
  GeldigeZet *geldigeZetten;

  Speler *speler1;
  Speler *speler2;
  Speler *huidigeSpeler;

  void voegVoor(BordVakje *&startVakje);
  void voegVoor(GeldigeZet *&startZet, BordVakje *vakje, int richting,
                int geslagen);
  BordVakje *maakRij();
  void ritsen(BordVakje *bovenRijVakje, BordVakje *onderRijVakje);
  void bouwBord();
  void zetBeginStenen();
  GeldigeZet *zoekGeldigeZet(BordVakje *vakje);
  bool berekenGeldigeZetten();
  void controleerZet(BordVakje *huidigVakje);
  void resetGeldigeZetten();
  void swap(char &a, char &b);
  void verwisselSpelers();

  bool mensZet();
  bool speelZet();
  void groottebord();
  int m = 8;
  int n = 8;
  void spelteller();
  int aantalspellen;
  int leesGetal(int maxWaarde);
  char leesOptie();
  BordVakje *vindVakje(int kolom, int rij);
  void flipVakken(BordVakje *vakje, GeldigeZet *geldig);
  // TODO
public:
  OthelloBord();
  ~OthelloBord();
  Speler *getTegenstander();
  bool computerzet();
  void spel();
  void bordAfdrukken();
}; // othellobord
