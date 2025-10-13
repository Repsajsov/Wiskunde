// Tweede programmeeropgave: Pincode
// Vincent van der Velden - s4494059 - Wiskunde 2024
// Jasper Vos             - s2911159-  Wiskunde 2025
// C++, 13/10/2025, g++.exe (Rev2, Built by MSYS2 project) 14.2.0

#include <climits>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void infoblokje() {
  cout << "Vincent van der Velden - s4494059 - Wiskunde 2024" << endl;
  cout << "Jasper Vos - s2911159 - Wiskunde 2025" << endl;
  cout << "Tweede programmeeropgave: Pincode 14/10/2025" << endl;
  cout << "We gaan een door u gekozen file kopieren naar" << endl;
  cout << "een ander bestand waarbij we de aantekeningen" << endl;
  cout << "weglaten en u mag kiezen hoeveel spaties een tab" << endl;
  cout << "is. Ook gaan we tellen hoe vaak een door u gekozen" << endl;
  cout << "drieletterwoord voorkomt in het bestand en" << endl;
  cout << "berekenen we de palindromen en de iteraties" << endl;
  cout << "van de getallen in het bestand." << endl;
} // infoblokje

int omgedraaidGetal(int getal) {
  // Draait het getal om vb: 1234 -> 4321
  int omGetal = 0;
  while (getal != 0) {
    omGetal = omGetal * 10 + getal % 10;
    getal /= 10;
  } // while
  return omGetal;
} // omgedraaid

int lychrel(int getal) {
  // Berekent het lychrel getal
  int teller = 0;
  int startGetal = getal;
  while (getal != omgedraaidGetal(getal)) {
    int omGetal = omgedraaidGetal(getal);
    if (getal > INT_MAX - omGetal) {
      cout << "Het getal: " << startGetal << ", is een potentieel lychrel getal"
           << endl;
      return teller + 1;
    } // if
    getal += omGetal;
    teller++;
  } // while
  return teller;
} // lychrel

int vindCijfer(int pincode, int pos) {
  // Geeft cijfer van een bepaalde positie pincode
  if (pos == 0)
    return (pincode / 1000) % 10;
  if (pos == 1)
    return (pincode / 100) % 10;
  if (pos == 2)
    return (pincode / 10) % 10;
  if (pos == 3)
    return (pincode / 1) % 10;
  return 0;
} // vindCijfer

bool isGetal(char kar) {
  // Controleert of karakter een getal is
  return (kar >= '0' && kar <= '9');
} // isGetal

int maakGetal(char kar, int getal) {
  // Bouwt een meercijferig getal
  getal = getal * 10 + (kar - '0');
  return getal;
} // maakGetal

void verwerkGetal(int &getal, char kar, char vkar, bool isKraken,
                  bool &veranderPincode) {
  // Standaard logica voor verwerken getallen voor 'coderen', 'decoderen' en
  // 'kraken'
  if (isGetal(kar)) {
    getal = maakGetal(kar, getal);
  } else if (!isGetal(kar) && isGetal(vkar)) {
    if (getal >= 0 && getal < 10000) {
      veranderPincode = true;
      if (!isKraken) {
        cout << lychrel(getal) << endl;
      } // if
    } // if
  } // else if
} // verwerk

void checkWoord(char &eersteLetter, char &tweedeLetter, char &derdeLetter,
                char kar, int &aantalWoorden) {
  // controleert of de voorgaande 3 karakters 'the' bevatten
  eersteLetter = tweedeLetter;
  tweedeLetter = derdeLetter;
  derdeLetter = kar;

  if ((eersteLetter == 't' || eersteLetter == 'T') &&
      (tweedeLetter == 'h' || tweedeLetter == 'H') &&
      (derdeLetter == 'e' || derdeLetter == 'E')) {
    aantalWoorden++;
  }; // if
} // checkWoord

void verwerkKarakter(char &kar, int &pos, int pincode, bool isCoderen) {
  if (kar >= ' ' && kar <= '~') {
    if (isCoderen) {
      kar = ((char(kar) - ' ' + vindCijfer(pincode, pos)) % 95);
    } else {
      kar = ((char(kar) - ' ' - vindCijfer(pincode, pos)) % 95);
    } // else
    if (kar < 0) {
      kar += 95;
    } // if
    kar += ' ';
    pos = (pos + 1) % 4;
  } else if (kar == '\n') {
    pos = 0;
  } // else if
} // verwerkKarakter

void updatePincode(bool &veranderPincode, int &pincode, int &getal, int &pos) {
  if (veranderPincode) {
    pincode = getal;
    getal = 0;
    pos = 0;
    veranderPincode = false;
  }
}

void coderen(string invoerFile, string uitvoerFile, int pincode) {
  char kar;
  char vkar = '\0';
  int getal = 0;
  int pos = 0;
  bool veranderPincode = false;
  ifstream invoer(invoerFile, ios::in);
  ofstream uitvoer(uitvoerFile, ios::out);
  while (invoer.get(kar)) {
    verwerkGetal(getal, kar, vkar, false, veranderPincode);
    vkar = kar;
    verwerkKarakter(kar, pos, pincode, true);
    updatePincode(veranderPincode, pincode, getal, pos);
    uitvoer.put(kar);
  } // while
  invoer.close();
  uitvoer.close();
  cout << "Bestand gekopieerd." << endl;
} // coderen

void decoderen(string invoerFile, string uitvoerFile, int pincode) {
  char kar;
  char vkar = '\0';
  int getal = 0;
  int pos = 0;
  bool veranderPincode = false;
  ifstream invoer(invoerFile, ios::in);
  ofstream uitvoer(uitvoerFile, ios::out);
  while (invoer.get(kar)) {
    verwerkKarakter(kar, pos, pincode, false);
    verwerkGetal(getal, kar, vkar, false, veranderPincode);
    updatePincode(veranderPincode, pincode, getal, pos);
    vkar = kar;
    uitvoer.put(kar);
  } // while
} // decoderen

void kraken(string invoerFile) {
  int maxAantalWoorden = 0, bestePincode = 0;

  for (int i = 0; i < 10000; i++) {
    int nieuwePincode = i;
    char eersteLetter = '\0', tweedeLetter = '\0', derdeLetter = '\0';
    int aantalWoorden = 0;
    char kar = '\0', vkar = '\0';
    int getal = 0;
    int pos = 0;
    bool veranderPincode = false;
    ifstream invoer(invoerFile, ios::in);

    while (invoer.get(kar)) {
      verwerkKarakter(kar, pos, nieuwePincode, false);
      checkWoord(eersteLetter, tweedeLetter, derdeLetter, kar, aantalWoorden);
      verwerkGetal(getal, kar, vkar, true, veranderPincode);
      updatePincode(veranderPincode, nieuwePincode, getal, pos);
      vkar = kar;
    } // while
    invoer.close();
    if (maxAantalWoorden < aantalWoorden) {
      maxAantalWoorden = aantalWoorden;
      bestePincode = i;
    } // if
    aantalWoorden = 0;
  } // for
  cout << "Beste pincode is: " << bestePincode << endl;
  cout << "Aantal keer 'the': " << maxAantalWoorden << endl;
} // kraken

void startProgramma() {
  string invoerFile;
  string uitvoerFile;
  char optie;  // coderen of decoderen;
  int pincode; // ingevoerde pincode;
  infoblokje();
  cout << "Wat is uw pincode?" << endl;
  while (pincode < -1 || pincode > 9999) {
    cout << "(0-9999) | (-1)" << endl;
    cin >> pincode;
  } // while
  cout << "Hoe heet het originele bestand?" << endl;
  cin >> invoerFile;
  if (pincode == -1) {
    kraken(invoerFile);
    return;
  } // if
  cout << "Wilt u coderen of decoderen?" << endl;
  while (optie != 'c' && optie != 'C' && optie != 'd' && optie != 'D') {
    cout << "[D]coderen | [C]oderen" << endl;
    cin >> optie;
  } // while
  cout << "Hoe heet het uitvoer bestand?" << endl;
  cin >> uitvoerFile;
  if (optie == 'c' || optie == 'C') {
    coderen(invoerFile, uitvoerFile, pincode);
  } else if (optie == 'd' || optie == 'D') {
    decoderen(invoerFile, uitvoerFile, pincode);
  } // else if
} // startProgramma

int main() {
  startProgramma();
  return 0;
} // main