#include <iostream>
using namespace std;
int main() {

  // const int maandenInJaar = 12;
  // const int huidigJaar = 2025;
  // const int huidigeMaand = 9;
  // const int huidigedag = 22;

  // int geboortejaar;
  // int geboortemaand;
  // int geboortedag;

  // // Leeftijd invullen
  // cout << "Wat is uw geboortejaar:" << endl;
  // cin >> geboortejaar;
  // cout << "Wat is uw geboortemaand:" << endl;
  // cin >> geboortemaand;
  // cout << "Wat is uw geboortedag:" << endl;
  // cin >> geboortedag;

  // // Leeftijd berekenen
  // int maandenOud = (maandenInJaar - geboortemaand) +
  //                  ((huidigJaar - (geboortejaar + 1)) * 12) + huidigeMaand;
  // if (huidigedag < geboortedag) {
  //   maandenOud--;
  // }

  // int jarenOud = maandenOud / maandenInJaar;
  // float jarenOudDecimaal = maandenOud / 12.f;

  //   cout << jarenOud << " jaar en " << maandenOud % 12 << " maanden oud" <<
  //   endl; cout << maandenOud << " maanden oud" << endl;

  // // Eventuele feestdagen
  // if (huidigedag == geboortedag ||
  //     (huidigeMaand == geboortemaand) && (huidigedag == geboortedag)) {
  //   cout << "Gefeliciteerd!" << endl;
  // }

  // // Leeftijdscontrole
  // if (jarenOudDecimaal < 10 || jarenOudDecimaal > 100) {
  //   cout << "Opdonderen!" << endl;
  // }

  // // Berekening op welke weekdag geboortedatum viel
  // // Jezus wat kut zonder hashmaps...
  // const int januariCumulatief = 31;
  // const int februariCumulatief = 59;
  // const int maartCumulatief = 90;
  // const int aprilCumulatief = 120;
  // const int meiCumulatief = 151;
  // const int juniCumulatief = 181;
  // const int juliCumulatief = 212;
  // const int augustusCumulatief = 243;
  // const int septemberCumulatief = 273;
  // const int oktoberCumulatief = 304;
  // const int novemberCumulatief = 334;
  // const int decemberCumulatief = 365;

  // // We tellen vanaf 1904 (Het eerste schrikkeljaar) we voegen +1 toe omdat we
  // // 1904 niet meetellen
  // int aantalSchrikkeljaren = (((geboortejaar-1)/4)*4 - 1904)/4;
  // int dagenVanaf1901 =
  //     (geboortejaar - 1901) * 365 + aantalSchrikkeljaren;

  // cout << "Aantal schrikkeljaren: " << aantalSchrikkeljaren << endl;

  // bool isSchrikkeljaar = ((geboortejaar % 4 == 0 && geboortejaar % 100 != 0) ||
  //                         geboortejaar % 400 == 0);

  // // Correctie aangezien 2100 geen schrikkeljaar is
  // if (geboortejaar >= 2100)
  //   dagenVanaf1901--;

  // if (geboortemaand == 1) {
  //   dagenVanaf1901 += geboortedag;
  //   if (isSchrikkeljaar)
  //     dagenVanaf1901--;
  // } else if (geboortemaand == 2) {
  //   dagenVanaf1901 += januariCumulatief + geboortedag;
  //   if (isSchrikkeljaar && geboortedag < 29)
  //     dagenVanaf1901--;
  // } else if (geboortemaand == 3)
  //   dagenVanaf1901 += februariCumulatief + geboortedag;
  // else if (geboortemaand == 4)
  //   dagenVanaf1901 += maartCumulatief + geboortedag;
  // else if (geboortemaand == 5)
  //   dagenVanaf1901 += aprilCumulatief + geboortedag;
  // else if (geboortemaand == 6)
  //   dagenVanaf1901 += meiCumulatief + geboortedag;
  // else if (geboortemaand == 7)
  //   dagenVanaf1901 += juniCumulatief + geboortedag;
  // else if (geboortemaand == 8)
  //   dagenVanaf1901 += juliCumulatief + geboortedag;
  // else if (geboortemaand == 9)
  //   dagenVanaf1901 += augustusCumulatief + geboortedag;
  // else if (geboortemaand == 10)
  //   dagenVanaf1901 += septemberCumulatief + geboortedag;
  // else if (geboortemaand == 11)
  //   dagenVanaf1901 += oktoberCumulatief + geboortedag;
  // else if (geboortemaand == 12)
  //   dagenVanaf1901 += novemberCumulatief + geboortedag;

  // // Correctie aangezien we altijd op 1 januari eindigen en cumalatief het dus 1
  // // dag teveel optelt
  // dagenVanaf1901--;

  // cout << "Weekdag: " << dagenVanaf1901 % 7 << endl;

  int antwoordBetaGebruiker;
  int antwoordBeta;
  int a, b, c;

  a = ((a*a)%10) + 1;
  b = ((b*b)%10) + 1;
  c = ((c*c)%10) + 1;

  int D = (b*b - 4*a*c);
  cout << a << "x^2 + " << b << "x + " << c <<endl;
  
  cout << D << endl;
  if (D > 0) {
    antwoordBeta = 2;
  } else if (D < 0) {
    antwoordBeta = 0;
  } else
    antwoordBeta = 1;

  cout << "Hoeveel oplossingen zijn er: (0?1?2)";
  cin >> antwoordBetaGebruiker;
  
  if (antwoordBetaGebruiker == antwoordBeta) {
    cout << "Correct!" << endl;
  } else {cout << "Fout!" << endl;
  return 1;
  
  }

  cout << "Welke artiest heeft de nachtwacht geschilderd?" << endl; 
  cout << "A) Rembrandt" << endl; 
  cout << "B) Van Gogh" << endl;
  cout << "C) Rubens" << endl;

  char antwoordAlphaGebruiker;
  char antwoordAlpha = 'A';
  cin >> antwoordAlphaGebruiker;

  if (antwoordAlpha == antwoordAlphaGebruiker) {
    cout << "Correct!" << endl;
  }
  else {
    cout << "Fout!" << endl;
    return 1;
  }

  



  return 0;
}
