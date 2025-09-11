#include <iostream>
using namespace std;

int main()
{
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
  cout << "Wat is uw geboortemaand:" << endl;
  cin >> geboortemaand;
  cout << "Wat is uw geboortedag:" << endl;
  cin >> geboortedag;

  // Leeftijd berekenen
  int maandenOud = (maandenInJaar - geboortemaand) +
                   ((huidigJaar - (geboortejaar + 1)) * 12) + huidigeMaand;
  if (huidigeDag < geboortedag)
  {
    maandenOud--;
  }
  int jarenOud = maandenOud / maandenInJaar;
  float jarenOudDecimaal = maandenOud / 12.f;

  cout << jarenOud << " jaar en " << maandenOud % 12 << " maanden oud" << endl;
  cout << maandenOud << " maanden oud" << endl;

  // Eventuele feestdagen
  if (huidigeDag == geboortedag ||
      (huidigeMaand == geboortemaand) && (huidigeDag == geboortedag))
  {
    if (jarenOudDecimaal >= 30)
    {
      cout << "Gefeliciteerd met uw ver(maand)jaardag!" << endl;
    }
    else
    {
      cout << "Gefeliciteerd met je ver(maand)dag!" << endl;
    }
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

  // Aantal schrikkeljaren tussen 1901 en het geboortejaar
  int aantalSchrikkeljaren = (((geboortejaar - 1) / 4) * 4 - 1904) / 4;
  int aantalDagen =
      (geboortejaar - 1901) * 365 + aantalSchrikkeljaren;

  // cout << "Aantal schrikkeljaren: " << aantalSchrikkeljaren << endl;

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

  // Geboorteweekdag controle
  char eersteLetter;
  char tweedeLetter;
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
  // cout << "Weekdag: " << aantalDagen % 7 << endl;

  // Check of de weekdag overeenkomt

  // Beta vraag
  int antwoordBetaGebruiker;
  int antwoordBeta;

  const int coefA = (rand() % 10) + 1;
  const int coefB = (rand() % 10) + 1;
  const int coefC = (rand() % 10) + 1;

  int discriminant = (coefB * coefB - 4 * coefA * coefC);
  cout << coefA << "x^2 + " << coefB << "x + " << coefC << endl;

  cout << discriminant << endl;
  if (discriminant > 0)
  {
    antwoordBeta = 2;
  }
  else if (discriminant < 0)
  {
    antwoordBeta = 0;
  }
  else
    antwoordBeta = 1;

  cout << "Hoeveel oplossingen zijn er? (0, 1, 2)";
  cin >> antwoordBetaGebruiker;

  if (antwoordBetaGebruiker == antwoordBeta)
  {
    cout << "Correct!" << endl;
  }
  else
  {
    cout << "Fout!" << endl;
    return 1;
  }

  // Alpha vraag
  if (jarenOudDecimaal > 30)
  {
    cout << "Heeft u enig idee welke artiest de nachtwacht heeft geschilderd?" << endl;
  }
  else
  {
    cout << "Wie heeft de nachtwacht geschilderd!?" << endl;
  }
  cout << "A) Rembrandt" << endl;
  cout << "B) Van Gogh" << endl;
  cout << "C) Rubens" << endl;
  cout << "Vul in (A, B, of C)" << endl;

  char antwoordAlphaGebruiker;
  char antwoordAlpha = 'A';
  cin >> antwoordAlphaGebruiker;

  if (antwoordAlpha == antwoordAlphaGebruiker)
  {
    cout << "Correct!" << endl;
  }
  else
  {
    cout << "Fout!" << endl;
    return 1;
  }

  return 0;
}
