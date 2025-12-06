class BordVakje {
  // Vertegenwoordigd ieder vakje van het bord
public:
  char kleur;
  BordVakje *buren[8];
  BordVakje();
}; // BordVakje

class GeldigeZet {
  // Dit slaat per beurt op welke verschillende zetten er zijn en helpt met
  // bepalen score en richtingen waar sten omgeslagen moeten worden
public:
  BordVakje *vakje;
  GeldigeZet *volgende;
  int aantalGeslagen;
  bool richtingen[8];
  GeldigeZet();
}; // GeldigeZet

class Speler {
  // Dit maakt het wat makkelijker leesbaar omdat we dan geen scoreZ, scoreW
  // etc. hoeven te maken
public:
  int score;
  char kleur;
  bool isComputer;
  Speler(char kleur, bool isComputer);
}; // Speler

class OthelloBord {
  // Deze klasse bevat alle benodigdheden om het spel te spelen zoals het bord,
  // geldige zetten, welke spelers er zijn etc.
private:
  int m;
  int n;
  Speler *speler1;
  Speler *speler2;
  Speler *huidigeSpeler;
  BordVakje *bordStart;
  GeldigeZet *geldigeZetten;
  int aantalBeurten;
  int aantalZetten;

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
  void verwisselSpelers();
  bool mensZet();
  bool computerZet();
  bool speelZet();
  BordVakje *vindVakje(int kolom, int rij);
  void flipVakken(BordVakje *vakje, GeldigeZet *geldig);
  Speler *getTegenstander();
  void bordAfdrukken();
  int randomGetal(int maxWaarde);
  void resetGeldigeZetten();
  void resetBord();

public:
  OthelloBord(int rijen, int kolommen, bool zComputer, bool wCompute);
  ~OthelloBord();
  void spel();
  void experiment(int aantalExperimenten);
}; // OthelloBord
