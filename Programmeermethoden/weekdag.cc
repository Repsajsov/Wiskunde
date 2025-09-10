#include <iostream>
using namespace std;

int main() {
  const int januariCumulatief = 31;
  const int februariCumulatief = 59;
  const int maartCumulatief = 90;
  const int aprilCumulatief = 120;
  const int meiCumulatief = 151;
  const int juniCumulatief = 181;
  const int juliCumulatief = 212;
  const int augustusCumulatief = 243;
  const int septemberCumulatief = 273;
  const int oktoberCumulatief = 304;
  const int novemberCumulatief = 334;
  const int decemberCumulatief = 365;

  // Array met test cases: {jaar, maand, dag, verwachte_weekdag}
  int testCases[][4] = {
      // 1901 - 1 januari was een dinsdag (0)
      {1901, 1, 1, 0},   // Dinsdag
      {1901, 1, 2, 1},   // Woensdag
      {1901, 1, 7, 6},   // Maandag
      {1901, 12, 31, 1}, // Woensdag

      // 1904 - schrikkeljaar
      {1904, 2, 28, 6}, // Maandag
      {1904, 2, 29, 0}, // Dinsdag (schrikkeldag)
      {1904, 3, 1, 1},  // Woensdag

      // 1900 - geen schrikkeljaar (deelbaar door 100)
      {1900, 2, 28, 2}, // Donderdag
      {1900, 3, 1, 3},  // Vrijdag

      // 2000 - wel schrikkeljaar (deelbaar door 400)
      {2000, 2, 28, 6}, // Maandag
      {2000, 2, 29, 0}, // Dinsdag
      {2000, 3, 1, 1},  // Woensdag
      {2000, 1, 1, 5},  // Zaterdag

      // Andere jaren
      {1950, 1, 1, 6},  // Maandag
      {1980, 1, 1, 0},  // Dinsdag
      {2020, 1, 1, 1},  // Woensdag
      {2020, 2, 29, 5}, // Zaterdag (schrikkeldag)
      {2024, 1, 1, 6},  // Maandag

      // Bekende data
      {1969, 7, 20, 6}, // Maandag (maanlanding)
      {2001, 9, 11, 0}, // Dinsdag
  };

  int numTests = sizeof(testCases) / sizeof(testCases[0]);
  string weekdagen[] = {"Dinsdag",  "Woensdag", "Donderdag", "Vrijdag",
                        "Zaterdag", "Zondag",   "Maandag"};

  for (int i = 0; i < numTests; i++) {
    int geboortejaar = testCases[i][0];
    int geboortemaand = testCases[i][1];
    int geboortedag = testCases[i][2];
    int verwachteWeekdag = testCases[i][3];

    cout << "\n=== Test " << (i + 1) << ": " << geboortedag << "/"
         << geboortemaand << "/" << geboortejaar << " ===" << endl;
    cout << "Verwacht: " << verwachteWeekdag << " ("
         << weekdagen[verwachteWeekdag] << ")" << endl;

    // Je originele code hieronder:
    // We tellen vanaf 1904 (Het eerste schrikkeljaar) we voegen +1 toe omdat we
    // 1904 niet meetellen
    int dagenVanaf1901 =
        (geboortejaar - 1901) * 365 + (((geboortejaar)-1904) + 1) / 4;
    cout << "Aantal schrikkeljaren: " << (((geboortejaar)-1904) / 4) << endl;
    bool isSchrikkeljaar =
        ((geboortejaar % 4 == 0 && geboortejaar % 100 != 0) ||
         geboortejaar % 400 == 0);
    // Correctie aangezien 2100 geen schrikkeljaar is
    if (geboortejaar >= 2100)
      dagenVanaf1901--;
    if (geboortemaand == 1) {
      dagenVanaf1901 += geboortedag;
      if (isSchrikkeljaar)
        dagenVanaf1901--;
    } else if (geboortemaand == 2) {
      dagenVanaf1901 += januariCumulatief + geboortedag;
      if (isSchrikkeljaar && geboortedag < 29)
        dagenVanaf1901--;
    } else if (geboortemaand == 3)
      dagenVanaf1901 += februariCumulatief + geboortedag;
    else if (geboortemaand == 4)
      dagenVanaf1901 += maartCumulatief + geboortedag;
    else if (geboortemaand == 5)
      dagenVanaf1901 += aprilCumulatief + geboortedag;
    else if (geboortemaand == 6)
      dagenVanaf1901 += meiCumulatief + geboortedag;
    else if (geboortemaand == 7)
      dagenVanaf1901 += juniCumulatief + geboortedag;
    else if (geboortemaand == 8)
      dagenVanaf1901 += juliCumulatief + geboortedag;
    else if (geboortemaand == 9)
      dagenVanaf1901 += augustusCumulatief + geboortedag;
    else if (geboortemaand == 10)
      dagenVanaf1901 += septemberCumulatief + geboortedag;
    else if (geboortemaand == 11)
      dagenVanaf1901 += oktoberCumulatief + geboortedag;
    else if (geboortemaand == 12)
      dagenVanaf1901 += novemberCumulatief + geboortedag;
    // Correctie aangezien we altijd op 1 januari eindigen en cumalatief het dus
    // 1 dag teveel optelt
    dagenVanaf1901--;

    int berekendWeekdag = dagenVanaf1901 % 7;
    cout << "Berekend: " << berekendWeekdag << " ("
         << weekdagen[berekendWeekdag] << ")" << endl;
    cout << "CORRECT: " << (berekendWeekdag == verwachteWeekdag ? "JA" : "NEE")
         << endl;
  }

  return 0;
}