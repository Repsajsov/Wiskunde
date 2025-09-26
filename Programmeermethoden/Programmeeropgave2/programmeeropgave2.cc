#include <climits>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int draaiGetal(int getal) {
  int resultaat = 0;
  while (getal != 0) {
    if ((INT_MAX / 10) < resultaat)
      return -1;
    else {
      resultaat *= 10;
    }
    if ((INT_MAX - getal) < resultaat) {
      return -1;
    } else {
      resultaat += getal % 10;
    }
    getal /= 10;
  }
  return resultaat;
}
int lychrel(int getal) {
  int omgekeerdGetal;
  int iteraties = 0;
  while (true) {
    iteraties++;
    omgekeerdGetal = draaiGetal(getal);
    if (getal == omgekeerdGetal || omgekeerdGetal == -1) {
      break;
    }
    if ((INT_MAX - omgekeerdGetal) < getal) {
      break;
    } else {
      getal += omgekeerdGetal;
    }
  }
  return iteraties;
}
bool isCijfer(char karakter) { return karakter >= '0' && karakter <= '9'; }
int krijgPincodeCijfer(int pincode, int index) {
  int indexRest = index % 4;
  if (indexRest == 0)
    return (pincode / 1000);
  else if (indexRest == 1)
    return (pincode / 100) % 10;
  else if (indexRest == 2)
    return (pincode / 10) % 10;
  else
    return pincode % 10;
}
char verschuifKarakter(char karakter, int verschuiving) {
  int resultaat = (karakter - 32 + verschuiving) % 95;
  if (resultaat < 0) {
    resultaat += 95;
  }
  return resultaat + 32;
}
void verwerkGetal(char karakter, char vorigKarakter, int &pincode, int &getal) {

  if (isCijfer(karakter)) {
    if (isCijfer(vorigKarakter)) {
      getal = (getal * 10) + (karakter - '0');
    } else {
      getal = karakter - '0';
    }
  } else if (isCijfer(vorigKarakter) && (getal > 0 && getal < 10000)) {
    pincode = getal;
    cout << "Getal: " << getal << "\nIteraties lychrel: " << lychrel(getal)
         << endl;
    getal = 0;
  }
}
char ontsleutelKarakter(char karakter, char vorigVersleuteldKarakter,
                        int &pincode, int &index, int &getal) {
  int verschuiving = krijgPincodeCijfer(pincode, index);
  char versleuteldKarakter = verschuifKarakter(karakter, -verschuiving);
  verwerkGetal(versleuteldKarakter, vorigVersleuteldKarakter, pincode, getal);
  if (karakter == '\n') {
    index = 0;
    return karakter;
  } else if (karakter == '\t' || karakter == '\r') {
    return karakter;
  }
  index++;
  return versleuteldKarakter;
}
char versleutelKarakter(char karakter, char vorigKarakter, int &pincode,
                        int &index, int &getal) {
  int verschuiving;
  verwerkGetal(karakter, vorigKarakter, pincode, getal);
  if (karakter == '\n') {
    index = 0;
    return karakter;
  } else if (karakter == '\t' || karakter == '\r') {
    return karakter;
  } else {

    verschuiving = krijgPincodeCijfer(pincode, index);
    index++;
    return verschuifKarakter(karakter, verschuiving);
  }
}
void telAantalThe(char nieuwKarakter, char &karakter1, char &karakter2,
                  char &karakter3, int &aantalThe) {
  karakter3 = karakter2;
  karakter2 = karakter1;
  karakter1 = nieuwKarakter;

  if ((karakter3 == 't' || karakter3 == 'T') &&
      (karakter2 == 'h' || karakter2 == 'H') &&
      (karakter1 == 'e' || karakter1 == 'E')) {
    aantalThe++;
  }
}
int versleutel(bool isVersleuteld, string invoerFile, string uitvoerFile,
               int pincode, bool schrijf) {
  ifstream invoer(invoerFile, ios::in);
  ofstream uitvoer(uitvoerFile, ios::out);

  char karakter;
  char vorigKarakter = '\0';
  char vorigVersleuteldKarakter = '\0';
  char resultaat;
  int getal = 0;
  int index = 0;
  int aantalThe = 0;
  char karakter1 = '\0', karakter2 = '\0', karakter3 = '\0';

  karakter = invoer.get();
  while (!invoer.eof()) {
    if (isVersleuteld) {
      resultaat = ontsleutelKarakter(karakter, vorigVersleuteldKarakter,
                                     pincode, index, getal);
      vorigVersleuteldKarakter = resultaat;
      if (!schrijf) {
        telAantalThe(resultaat, karakter1, karakter2, karakter3, aantalThe);
      }
    } else {
      resultaat =
          versleutelKarakter(karakter, vorigKarakter, pincode, index, getal);
    }
    if (schrijf) {
      uitvoer.put(resultaat);
    }
    vorigKarakter = karakter;
    karakter = invoer.get();
  }
  invoer.close();
  if (schrijf) {
    uitvoer.close();
  }
  if (schrijf) {
    return -1;
  } else
    return aantalThe;
}

int main() {

  // Voorbeeld
  string orgineleFile = "voorbeeld2025.txt";
  string gecodeerdeFile = "geheim2025.txt";
  string gedecoreerdeFile = "geheim2025antwoord.txt";

  //   versleutel(false, orgineleFile, gecodeerdeFile, pincode, true);
  int aantalThe = 0;
  int bestePincode = 0;
  int maxThe = INT_MIN;

  for (int i = 0; i < 10000; i++) {
    aantalThe = versleutel(true, gecodeerdeFile, gedecoreerdeFile, i, false);
    if (aantalThe >= maxThe) {
      maxThe = aantalThe;
      bestePincode = i;
    }
  }
  cout << "Beste pincode: " << bestePincode << ", Aantal the's: " << maxThe
       << endl;
  versleutel(true, gecodeerdeFile, gedecoreerdeFile, bestePincode, true);

  return 0;
}
