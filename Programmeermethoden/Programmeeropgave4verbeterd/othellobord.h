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

class OthelloBord {
private:
  BordVakje *bordStart;
  GeldigeZet *geldigeZetten;

  void voegVoor(BordVakje *&startVakje);
  void voegVoor(GeldigeZet *&startGeldigeZet, BordVakje *vakje, int richting);
  BordVakje *maakRij();
  void ritsen(BordVakje *bovenRijVakje, BordVakje *onderRijVakje);
  void bouwBord();
  void zetBeginStenen();
  char getTegenstander(char speler);
  GeldigeZet *zoekGeldigeZet(BordVakje *vakje);
  bool berekenGeldigeZetten(char speler);
  void controleerZet(BordVakje *huidigVakje, char tegenstander,
                     char speler);
  void resetGeldigeZetten();
  void swap(char &a, char &b);

  bool mensZet(char speler, char tegenstander);
  void groottebord();
  int m = 8;
  int n = 8;
  void spelteller();
  int aantalspellen;
  int leesGetal(int maxWaarde);
  char leesOptie();
  BordVakje *vindVakje(int kolom, int rij);
  void doeZet(BordVakje *vakje, GeldigeZet *geldig, char speler);
  // TODO
public:
  OthelloBord();
  ~OthelloBord();
  bool computerzet(char speler, char tegenstander);
  void spel();
  void bordAfdrukken();
}; // othellobord
