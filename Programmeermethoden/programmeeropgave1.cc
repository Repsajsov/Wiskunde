// Programmeeropgave I

// Auteur: Jasper Vos
// Studentnr: s2911159
// Compilerversie: g++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0

#include <iostream>
#include <ctime>
using namespace std;

int main()
{
  // Voor de coefficienten bij de ABC-formule
  srand(time(0));
  const int maandenInJaar = 12;
  const int huidigJaar = 2025;
  const int huidigeMaand = 9;
  const int huidigeDag = 22;

  int geboortejaar;
  int geboortemaand;
  int geboortedag;

  // Leeftijd invullen
  cout << "Wat is uw geboortejaar:" << endl;
  cin >> geboortejaar;
  // Ruwe leeftijdscontrole
  if (huidigJaar - geboortejaar > 100 || huidigJaar - geboortejaar < 10)
    return 1;
  cout << "Wat is uw geboortemaand:" << endl;
  cin >> geboortemaand;
  cout << "Wat is uw geboortedag:" << endl;
  cin >> geboortedag;

  // Leeftijd berekenen
  int maandenOud = (maandenInJaar - geboortemaand) +
                   ((huidigJaar - (geboortejaar + 1)) * 12) +
                   huidigeMaand;
  cout << maandenOud << endl;
  if (huidigeDag < geboortedag)
    maandenOud--;

  int jarenOud = maandenOud / maandenInJaar;
  float jarenOudDecimaal = maandenOud / 12.f;

  cout << jarenOud << " jaar en " << maandenOud % 12 << " maanden oud" << endl;
  cout << maandenOud << " maanden oud" << endl;

  // Eventuele feestdagen
  if (huidigeDag == geboortedag ||
      ((huidigeMaand == geboortemaand) && (huidigeDag == geboortedag)))
  {
    if (jarenOudDecimaal >= 30)
      cout << "Gefeliciteerd met uw ver(maand)jaardag!" << endl;
    else
      cout << "Gefeliciteerd met je ver(maand)jaardag!" << endl;
  }

  // Leeftijdscontrole
  if (jarenOudDecimaal > 100)
  {
    cout << "Sorry maar u bent iets te oud voor deze opleiding." << endl;
    return 1;
  }
  else if (jarenOudDecimaal < 10)
  {
    cout << "Sorry maar je bent niet geschikt voor de opleiding." << endl;
    return 1;
  }

  // Bereken het aantal dagen tussen 01-01-1901 tot het geboortejaar
  int aantalSchrikkeljaren = (((geboortejaar - 1) / 4) * 4 - 1904) / 4;
  int aantalDagen =
      (geboortejaar - 1901) * 365 + aantalSchrikkeljaren;

  if (geboortemaand == 1)
    aantalDagen += geboortedag;
  else if (geboortemaand == 2)
    aantalDagen += 31 + geboortedag;
  else if (geboortemaand == 3)
    aantalDagen += 59 + geboortedag;
  else if (geboortemaand == 4)
    aantalDagen += 90 + geboortedag;
  else if (geboortemaand == 5)
    aantalDagen += 120 + geboortedag;
  else if (geboortemaand == 6)
    aantalDagen += 151 + geboortedag;
  else if (geboortemaand == 7)
    aantalDagen += 181 + geboortedag;
  else if (geboortemaand == 8)
    aantalDagen += 212 + geboortedag;
  else if (geboortemaand == 9)
    aantalDagen += 243 + geboortedag;
  else if (geboortemaand == 10)
    aantalDagen += 273 + geboortedag;
  else if (geboortemaand == 11)
    aantalDagen += 304 + geboortedag;
  else if (geboortemaand == 12)
    aantalDagen += 334 + geboortedag;

  if (((geboortejaar % 4 == 0 && geboortejaar % 100 != 0) || geboortejaar % 400 == 0) && geboortemaand > 2)
    aantalDagen++;

  // Controleer de weekdag van de geboortedag
  char eersteLetter;
  char tweedeLetter = 'x';
  if (jarenOudDecimaal >= 30)
    cout << "Op welke weekdag bent u geboren? (m, di, w, do, v, za, zo):" << endl;
  else
    cout << "Welke weekdag bent je geboren!? (m, di, w, do, v, za, zo):" << endl;
  cout << "Eerste letter:" << endl;
  cin >> eersteLetter;
  if (eersteLetter != 'm' && eersteLetter != 'w' && eersteLetter != 'v')
  {
    cout << "Tweede letter:" << endl;
    cin >> tweedeLetter;
  }
  int weekdag = aantalDagen % 7;
  if ((eersteLetter == 'm' && tweedeLetter == 'x' && weekdag != 6) ||
      (eersteLetter == 'd' && tweedeLetter == 'i' && weekdag != 0) ||
      (eersteLetter == 'w' && tweedeLetter == 'x' && weekdag != 1) ||
      (eersteLetter == 'd' && tweedeLetter == 'o' && weekdag != 2) ||
      (eersteLetter == 'v' && tweedeLetter == 'x' && weekdag != 3) ||
      (eersteLetter == 'z' && tweedeLetter == 'z' && weekdag != 4) ||
      (eersteLetter == 'z' && tweedeLetter == 'o' && weekdag != 5))
    return 1;

  // Vraag voor toelating beta studie
  int antwoordBetaGebruiker;
  int antwoordBeta;

  double coefA = (rand() % 1000000) + 1;
  double coefB = (rand() % 1000000);
  double coefC = (rand() % 1000000);
  if (rand() % 2 == 1)
    coefB = -1 * coefB;
  if (rand() % 2 == 1)
    coefC = -1 * coefC;

  double discriminant = (coefB * coefB - 4 * coefA * coefC);
  cout << coefA << "x^2";
  if (coefB < 0)
    cout << coefB << "x";
  else
    cout << "+" << coefB << "x";
  if (coefC < 0)
    cout << coefC << endl;
  else
    cout << "+" << coefC << endl;

  cout << discriminant << endl;
  if (discriminant > 0)
    antwoordBeta = 2;
  else if (discriminant < 0)
    antwoordBeta = 0;
  else
    antwoordBeta = 1;

  cout << "Hoeveel oplossingen zijn er? (0, 1, 2)";
  cin >> antwoordBetaGebruiker;

  if (antwoordBetaGebruiker == antwoordBeta)
  {
    if (jarenOudDecimaal >= 30)
      cout << "Correct! U bent aangenomen voor de studie! Gefeliciteerd!!!" << endl;
    else
      cout << "Goed gedaan... Je bent aangenomen..." << endl;
    return 0;
  }
  else
  {
    if (jarenOudDecimaal >= 30)
      cout << "U heeft een incorrect antwoord gegeven." << endl;
    else
      cout << "Onjuist! Haha!!" << endl;
  }

  // Vraag voor toelating alpha studie
  char antwoordAlpha;
  if (jarenOudDecimaal >= 30)
  {
    cout << "Heeft u enig idee welke bekende schilder de nachtwacht heeft geschilderd?" << endl;
    cout << "A) Rembrandt" << endl;
    cout << "B) Van Gogh" << endl;
    cout << "C) Rubens" << endl;
    cout << "Vul in: (A, B, of C)" << endl;
    cin >> antwoordAlpha;
    cout << "Het juiste antwoord was A: Rembrandt." << endl;
    if (antwoordAlpha == 'A' || antwoordAlpha == 'a')
    {
      cout << "U heeft het correcte antwoord gegeven! U bent dus aangenomen voor een willekeurige alpha studie!" << endl;
      return 0;
    }
    cout << "U heeft het jammer genoeg incorrect en komt niet in aanmerking voor een universitaire studie." << endl;
    return 1;
  }
  else
  {
    cout << "Legolas speelt in welke filmreeks?" << endl;
    cout << "A) Lord of the Rings" << endl;
    cout << "B) Harry Potter" << endl;
    cout << "C) Game of Thrones" << endl;
    cout << "Vul in: (A, B, of C)" << endl;
    cin >> antwoordAlpha;
    cout << "Het juiste antwoord was A: Lord of the Rings." << endl;
    if (antwoordAlpha == 'A' || antwoordAlpha == 'a')
    {
      cout << "Goed gedaan! je kunt nu een alpha studie doen... " << endl;
      return 0;
    }
    cout << "Ga maar in de werken want de universiteit is niks voor jou." << endl;
    return 1;
  }

  return 0;
}
