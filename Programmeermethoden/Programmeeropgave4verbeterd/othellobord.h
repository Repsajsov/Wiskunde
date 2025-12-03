// file othellobord.h
class bordvakje {
public:
  char kleur;          //     7 0 1
  bordvakje *buren[8]; //     6   2
  bordvakje();         //     5 4 3
}; // bordvakje

class geldigvakje {
public:
  bordvakje *vakje;
  geldigvakje *volgende;
  int aantalgeslagen;
  bool richtingen[8];
  geldigvakje();

private:
};
class othellobord {
private:
  bordvakje *ingang;
  geldigvakje *inganggeldig;

  void voegvoor(bordvakje *&ingangpointer);
  void voegvoor(geldigvakje *&ingangpointer, bordvakje *vakje, int richting);
  bordvakje *maakrij();
  void ritsen(bordvakje *boven, bordvakje *onder);
  void bouwbord();
  void zetBeginStenen();
  const char wit = 'W';
  const char zwart = 'Z';
  char gettegenstander(char huidigespeler);
  geldigvakje *zoekGeldigVakje(bordvakje *vakje);
  bool geldigzet();
  bool isgeldig(char huidigespeler);
  void controleerzet(bordvakje *huidigvakje, char tegenstander,
                     char huidigespeler);
  void maakGeldigLijstLeeg();
  void swap(char &a, char &b);

  bool menszet(char huidigspeler, char tegenstander);
  int mogelijkezetten;
  void mensofpc();
  void groottebord();
  int m = 8;
  int n = 8;
  char zmensofpc;
  char wmensofpc;
  void spelteller();
  int aantalspellen;
  int leesgetal(int maxwaarde);
  char leesoptie();
  bordvakje *vindVakje(int kolom, int rij);
  void doeZet(bordvakje *vakje, geldigvakje *geldig, char speler);
  // TODO
public:
  othellobord();
  ~othellobord();
  bool computerzet(char huidigspeler, char tegenstander);
  void spel();
  void drukaf();
  // TODO
  };// othellobord
