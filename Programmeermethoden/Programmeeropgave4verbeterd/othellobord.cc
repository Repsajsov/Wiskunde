#include "othellobord.h"
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

// Zodat we deze functies ook in mensZet kunnen gebruiken
extern int leesGetal(int maxWaarde);
extern char leesOptie();

BordVakje::BordVakje() {
  // Constructor Bordvakje
  kleur = '.';
  for (int i = 0; i < 8; i++) {
    buren[i] = nullptr;
  } // for
} // BordVakje::BordVakje

GeldigeZet::GeldigeZet() {
  // Constructor GeldigeZet vanuit het geldige vakje slaan we ook alle
  // richtingen op waar stenen omgeslagen moeten worden en ook de aantallen voor
  // het berekenen van de score
  vakje = nullptr;
  volgende = nullptr;
  for (int i = 0; i < 8; i++) {
    richtingen[i] = false;
  } // for
  aantalGeslagen = 0;
} // GeldigeZet::GeldigeZet

Speler::Speler(char kleur, bool isComputer) {
  // Constructor Speler
  this->kleur = kleur;
  this->isComputer = isComputer;
  score = 2;
} // Speler::Speler

Speler *OthelloBord::getTegenstander() {
  // Geeft de tegenstander dit verandert per beurt
  if (huidigeSpeler == speler1) {
    return speler2;
  } // if
  return speler1;
} // OthelloBord::getTegenstander

void OthelloBord::experiment(int aantalExperimenten) {
  // Laat het spel meerdere keren afspelen en slaat de data op in de files
  // "beurten.txt" en "scores.txt", tot slot geeft het ook nog aan welke speler
  // het meest gewonnen heeft
  std::ofstream uitvoerBeurten("beurten.txt", ios::out);
  std::ofstream uitvoerScores("scores.txt", ios::out);

  int speler1Gewonnen = 0;
  for (int i = 0; i < aantalExperimenten; i++) {
    spel();
    if (speler1->score > speler2->score) {
      speler1Gewonnen++;
    } // if

    uitvoerBeurten << i << " " << aantalBeurten << endl;
    uitvoerScores << i << " " << speler1->score << " " << speler2->score
                  << endl;

    resetBord();
    bouwBord();
    speler1->score = 2;
    speler2->score = 2;
    huidigeSpeler = speler1;
  } // for
  cout << "Aantal keren gewonnen:" << endl
       << "Speler 1: " << speler1Gewonnen
       << ", Speler 2: " << aantalExperimenten - speler1Gewonnen << endl;
  std::ofstream uitvoerWinnaars("winnaars.txt", ios::out);
  uitvoerWinnaars << 0 << " " << speler1Gewonnen << endl
                  << 1 << " " << aantalExperimenten - speler1Gewonnen << endl;

  uitvoerBeurten.close();
  uitvoerScores.close();
  uitvoerWinnaars.close();
} // OthelloBord::experiment

int OthelloBord::randomGetal(int maxWaarde) { return rand() % maxWaarde; }

GeldigeZet *OthelloBord::zoekGeldigeZet(BordVakje *vakje) {
  // Zoekt of het gekozen vak van een speler ook een geldige zet is
  GeldigeZet *huidig = geldigeZetten;
  while (huidig != nullptr) {
    if (huidig->vakje == vakje) {
      return huidig;
    } // if
    huidig = huidig->volgende;
  } // while
  return nullptr;
} // OthelloBord::zoekGeldigeZet

BordVakje *OthelloBord::vindVakje(int kolom, int rij) {
  // Vertaald de ingevoerde coördinaten naar het juiste vakje
  if (kolom < 0 || kolom >= n || rij < 0 || rij >= m) {
    return nullptr;
  } // if
  BordVakje *huidig = bordStart;
  for (int i = 0; i < rij; i++) {
    huidig = huidig->buren[4];
  } // for
  for (int i = 0; i < kolom; i++) {
    huidig = huidig->buren[2];
  } // for
  return huidig;
} // OthelloBord::vindVakje

void OthelloBord::voegVoor(GeldigeZet *&startZet, BordVakje *vakje,
                           int richting, int geslagen) {
  // Maakt linked list van geldige zetten, als een zet al bestaat update het de
  // richtingen en aantalGeslagen
  GeldigeZet *bestaandeZet = zoekGeldigeZet(vakje);
  if (bestaandeZet != nullptr) {
    bestaandeZet->richtingen[richting] = true;
    bestaandeZet->aantalGeslagen += geslagen;
    return;
  } // if

  GeldigeZet *nieuweZet = new GeldigeZet;
  nieuweZet->vakje = vakje;
  nieuweZet->richtingen[richting] = true;
  nieuweZet->aantalGeslagen = geslagen;
  nieuweZet->volgende = startZet;
  startZet = nieuweZet;
  aantalZetten++;
} // OthelloBord::voegVoor

void OthelloBord::controleerZet(BordVakje *huidigVakje) {
  // Controleert of een vakje geldige zetten bevat, als dat zo is maakt het een
  // GeldigeZet object en voegt het toe aan de linked list
  Speler *tegenstander = getTegenstander();
  for (int i = 0; i < 8; i++) {
    if (huidigVakje->buren[i] != nullptr) {
      if (huidigVakje->buren[i]->kleur == tegenstander->kleur) {
        BordVakje *hulp = huidigVakje->buren[i];
        int aantalGeslagen = 0;
        while (hulp != nullptr && hulp->kleur != '.') {
          if (hulp->kleur == huidigeSpeler->kleur) {
            voegVoor(geldigeZetten, huidigVakje, i, aantalGeslagen);
            break;
          } // if
          aantalGeslagen++;
          hulp = hulp->buren[i];
        } // while
      } // if
    } // if
  } // for
} // OthelloBord::controleerZet

bool OthelloBord::berekenGeldigeZetten() {
  // Gaat door het hele bord en zoekt naar geldige zetten
  resetGeldigeZetten();
  BordVakje *rij = bordStart;
  while (rij != nullptr) {
    BordVakje *huidigVakje = rij;
    while (huidigVakje != nullptr) {
      if (huidigVakje->kleur == '.') {
        controleerZet(huidigVakje);
      } // if
      huidigVakje = huidigVakje->buren[2];
    } // while
    rij = rij->buren[4];
  } // while
  if (geldigeZetten != nullptr) {
    return true;
  } // if
  return false;
} // OthelloBord::berekenGeldigeZetten

bool OthelloBord::computerZet() {
  // Pakt een random geldige zet
  if (!berekenGeldigeZetten()) {
    return false;
  } // if

  int a = randomGetal(aantalZetten);
  GeldigeZet *hulp = geldigeZetten;
  cout << "Zetten: " << aantalZetten << ", Gekozen: " << a << endl; // ✓

  for (int i = 0; i < a && hulp->volgende != nullptr; i++) {
    hulp = hulp->volgende;
  } // for

  flipVakken(hulp->vakje, hulp);
  return true;
} // OthelloBord::computerZet

void OthelloBord::flipVakken(BordVakje *startVakje, GeldigeZet *zet) {
  // Vanuit het gekozen vak worden alle stenen omgeslagen
  startVakje->kleur = huidigeSpeler->kleur;
  Speler *tegenstander = getTegenstander();

  for (int i = 0; i < 8; i++) {
    if (zet->richtingen[i]) {
      BordVakje *hulp = startVakje->buren[i];
      while (hulp != nullptr && hulp->kleur == tegenstander->kleur) {
        hulp->kleur = huidigeSpeler->kleur;
        hulp = hulp->buren[i];
      } // while
    } // if
  } // for
  huidigeSpeler->score += zet->aantalGeslagen + 1;
  tegenstander->score -= zet->aantalGeslagen;
} // OthelloBord::flipVakken

bool OthelloBord::speelZet() {
  // Bekijkt of speler computer of mens is en bepaald welke soort zet
  if (huidigeSpeler->isComputer) {
    return computerZet();
  } // if
  return mensZet();
} // OthelloBord::speelZet

bool OthelloBord::mensZet() {
  // Laat de gebruiker een zet kiezen
  berekenGeldigeZetten();
  if (geldigeZetten == nullptr) {
    cout << "Geen mogelijke zetten!" << endl;
    return false;
  } // if
  bool isGeldigeZet = false;
  while (!isGeldigeZet) {
    cout << "Geef Coordinaat (A1, B2, ...): ";
    int kolom = int(leesOptie() - 'A');
    int rij = leesGetal(m);
    if (kolom < 0 || kolom >= n || rij < 1 || rij > m) {
      cout << "Deze coordinaten liggen buiten het bord!" << endl;
    } else {
      BordVakje *gekozenVakje = vindVakje(kolom, rij - 1);
      GeldigeZet *gekozenZet = zoekGeldigeZet(gekozenVakje);
      if (gekozenZet == nullptr) {
        cout << "Ongeldige zet!" << endl;
      } else {
        flipVakken(gekozenVakje, gekozenZet);
        isGeldigeZet = true;
      }
    }
  } // while
  return true;
} // OthelloBord::mensZet

void OthelloBord::voegVoor(BordVakje *&startVakje) {
  // Voegt een vakje toe aan de linked list
  BordVakje *hulp = new BordVakje;
  hulp->buren[2] = startVakje;
  if (startVakje != nullptr) {
    startVakje->buren[6] = hulp;
  } // if
  startVakje = hulp;
} // OthelloBord::voegVoor

BordVakje *OthelloBord::maakRij() {
  // Maakt een rij van vakjes
  BordVakje *rijStart = nullptr;
  for (int i = 0; i < n; i++) {
    voegVoor(rijStart);
  } // for
  return rijStart;
} // OthelloBord::maakRij

void OthelloBord::ritsen(BordVakje *bovenRijVakje, BordVakje *onderRijVakje) {
  // Kan twee rijen aan elkaar vastbinden
  while (bovenRijVakje != nullptr && onderRijVakje != nullptr) {
    bovenRijVakje->buren[4] = onderRijVakje;
    onderRijVakje->buren[0] = bovenRijVakje;
    bovenRijVakje->buren[3] = onderRijVakje->buren[2];
    bovenRijVakje->buren[5] = onderRijVakje->buren[6];
    onderRijVakje->buren[1] = bovenRijVakje->buren[2];
    onderRijVakje->buren[7] = bovenRijVakje->buren[6];

    bovenRijVakje = bovenRijVakje->buren[2];
    onderRijVakje = onderRijVakje->buren[2];
  } // while
} // OthelloBord::ritsen

void OthelloBord::bouwBord() {
  // Maakt het volledige bord
  BordVakje *bovenRijVakje = maakRij();
  bordStart = bovenRijVakje;
  for (int i = 1; i < m; i++) {
    BordVakje *onderRijVakje = maakRij();
    ritsen(bovenRijVakje, onderRijVakje);
    bovenRijVakje = onderRijVakje;
  } // for
  zetBeginStenen();
} // OthelloBord::bouwBord

void OthelloBord::zetBeginStenen() {
  // Zet de begin stenen neer zodat het spel kan starten
  BordVakje *huidigVakje = bordStart;
  for (int i = 0; i < (n / 2) - 1; i++) {
    huidigVakje = huidigVakje->buren[2];
  } // for
  for (int j = 0; j < (m / 2) - 1; j++) {
    huidigVakje = huidigVakje->buren[4];
  } // for
  huidigVakje->kleur = 'W';
  huidigVakje->buren[2]->kleur = 'Z';
  huidigVakje->buren[4]->kleur = 'Z';
  huidigVakje->buren[3]->kleur = 'W';
} // OthelloBord::zetBeginStenen

void OthelloBord::verwisselSpelers() {
  // Na iedere beurt moeten de spelers gewisseld worden
  if (huidigeSpeler == speler1) {
    huidigeSpeler = speler2;
  } else {
    huidigeSpeler = speler1;
  }
} // OthelloBord::zetBeginStenen

void OthelloBord::spel() {
  // Spel logica, als twee beurten achterelkaar overgeslagen worden dan stopt
  // het spel
  int beurtenOvergeslagen = 0;
  aantalBeurten = 0;

  bordAfdrukken();
  while (beurtenOvergeslagen < 2) {
    if (!speelZet()) {
      beurtenOvergeslagen += 1;
    } else {
      beurtenOvergeslagen = 0;
      aantalBeurten++;
    }
    verwisselSpelers();
    bordAfdrukken();
  } // while
} // OthelloBord::spel

OthelloBord::OthelloBord(int aantalRijen, int aantalKolommen, bool isZComputer,
                         bool isWComputer) {
  // Constructor bord
  srand(time(NULL));
  m = aantalRijen;
  n = aantalKolommen;
  bouwBord();
  geldigeZetten = nullptr;
  speler1 = new Speler('Z', isZComputer);
  speler2 = new Speler('W', isWComputer);
  huidigeSpeler = speler1;
} // OthelloBord::OthelloBord

void OthelloBord::resetGeldigeZetten() {
  // Verwijdert alle geldige zetten van de vorige beurt
  while (geldigeZetten != nullptr) {
    GeldigeZet *oudeZet = geldigeZetten;
    geldigeZetten = geldigeZetten->volgende;
    delete oudeZet;
  } // while
  aantalZetten = 0;
} // OthelloBord::resetGeldigeZetten

OthelloBord::~OthelloBord() {
  // Destructor van het volledige spel
  delete speler1;
  delete speler2;
  resetGeldigeZetten();
  resetBord();
} // OthelloBord::~OthelloBord

void OthelloBord::resetBord() {
  // Verwijdert het volledige bord
  BordVakje *rij = bordStart;
  while (rij != nullptr) {
    BordVakje *huidigVakje = rij;
    rij = rij->buren[4];
    while (huidigVakje != nullptr) {
      BordVakje *oudVakje = huidigVakje;
      huidigVakje = huidigVakje->buren[2];
      delete oudVakje;
    } // while
  } // while
  bordStart = nullptr;
} // OthelloBord::resetBord

void OthelloBord::bordAfdrukken() {
  // Print het volledige bord zodat je het spel kan spelen
  BordVakje *rij = bordStart;
  cout << "Speler 1: " << speler1->score << ", Speler 2: " << speler2->score
       << endl
       << endl;
  ;
  cout << "  ";
  for (int i = 0; i < n; i++) {
    cout << char('A' + i) << " ";
  } // for
  cout << endl;
  int rijNummer = 1;
  while (rij != nullptr) {
    cout << rijNummer << " ";
    BordVakje *kolom = rij;
    while (kolom != nullptr) {
      cout << kolom->kleur << ' ';
      kolom = kolom->buren[2];
    } // while
    cout << endl;
    rij = rij->buren[4];
    rijNummer += 1;
  } // while
} // OthelloBord::bordAfdrukken