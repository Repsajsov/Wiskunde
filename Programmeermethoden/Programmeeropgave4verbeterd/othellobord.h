// file othellobord.h
class bordvakje {
public:
  char kleur;          //     7 0 1
  bordvakje *buren[8]; //     6   2
  bordvakje();         //     5 4 3
}; // bordvakje

class geldigeZet {
public:
  bordvakje *vakje;
  geldigeZet *volgende;
  int aantalGeslagen;
  bool richtingen[8];
  geldigeZet();

private:
};
class othellobord {
private:
  bordvakje *bordStart;
  geldigeZet *geldigeZetten;

  void voegVoor(bordvakje *&startVakje);
  void voegVoor(geldigeZet *&startGeldigeZet, bordvakje *vakje, int richting);
  bordvakje *maakRij();
  void ritsen(bordvakje *bovenRijVakje, bordvakje *onderRijVakje);
  void bouwBord();
  void zetBeginStenen();
  char getTegenstander(char speler);
  geldigeZet *zoekGeldigeZet(bordvakje *vakje);
  bool geldigzet();
  bool berekenGeldigeZetten(char speler);
  void controleerZet(bordvakje *huidigvakje, char tegenstander,
                     char huidigespeler);
  void resetGeldigeZetten();
  void swap(char &a, char &b);

  bool menszet(char huidigspeler, char tegenstander);
  void mensofpc();
  void groottebord();
  int m = 8;
  int n = 8;
  void spelteller();
  int aantalspellen;
  int leesGetal(int maxWaarde);
  char leesOptie();
  bordvakje *vindVakje(int kolom, int rij);
  void doeZet(bordvakje *vakje, geldigeZet *geldig, char speler);
  // TODO
public:
  othellobord();
  ~othellobord();
  bool computerzet(char huidigspeler, char tegenstander);
  void spel();
  void bordAfdrukken();
}; // othellobord
