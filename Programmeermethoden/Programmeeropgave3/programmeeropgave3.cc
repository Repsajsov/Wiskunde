#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace std;

void infoblok() {
  cout << "-----------------------------------------------------" << endl
       << "|                     LightsOut                     |" << endl
       << "-----------------------------------------------------" << endl
       << endl
       << "Vincent van der Velden - s4494059 - Wiskunde 2024" << endl
       << "Jasper Vos - s2911159 - Wiskunde 2025" << endl
       << "Programmeeropgave 3 - 10/11/2025" << endl
       << endl
       << "-----------------------------------------------------" << endl
       << "Functies:" << endl
       << "- Speel LightsOut! Met of zonder torus modus." << endl
       << "- Genereer oplosbare puzzels." << endl
       << "- Teken modus met pen functie." << endl
       << "- Speel oplossingen af met animaties!" << endl
       << "-----------------------------------------------------" << endl;
}

void wissel(int &x, int &y) {
  // Verwisseld twee variabelen
  int temp = x;
  x = y;
  y = temp;
}

char leesOptie() {
  // Leest input van gebruiker per karakter
  char resultaat;
  do {
    cin.get(resultaat);
  } while (resultaat == '\n');
  if (resultaat >= 'a' && resultaat <= 'z') {
    resultaat = (resultaat - 'a') + 'A';
  }
  return resultaat;
}

int leesGetal(int max) {
  // Controleert of de input een getal is
  char resultaat = 0;
  char karakter = leesOptie();
  if (karakter >= '0' && karakter <= '9') {
    resultaat = karakter - '0';
  }
  while (cin.get(karakter) && karakter != '\n') {
    if (karakter >= '0' && karakter <= '9') {
      resultaat = resultaat * 10 + (karakter - '0');
      if (resultaat >= max)
        resultaat = max;
    }
  }
  return resultaat;
}

class Puzzel {
private:
  // Constante variabelen
  const static int MAX_HOOGTE = 20;
  const static int MAX_BREEDTE = 20;
  const static int MAX_PROPORTIE = 100;
  // States voor het scheiden van inputs en overige functies
  enum State {
    HOOFDMENU,
    PARAMETER,
    TEKEN,
    TOGGLE,
    PUZZEL,
    SPELEN,
  };
  // Parameters
  int hoogte = 5;
  int breedte = 5;
  int proportieLampenAan = 50;
  int pen = 0;
  char karakterLampAan = '0';
  char karakterLampUit = '.';
  bool isTorus = false;
  bool isAnimatie = false;
  // Nodig voor de random getallen
  long seed = time(0);
  // Om bij te houden waar de cursor is
  int posX = 0;
  int posY = 0;
  // Arrays die nodig zijn voor de puzzel
  bool lampen[MAX_HOOGTE][MAX_BREEDTE];
  bool lampenStart[MAX_HOOGTE][MAX_BREEDTE];
  bool oplossing[MAX_HOOGTE][MAX_BREEDTE];
  // Overige
  bool startProgramma = true;
  bool eindigSpel = false;
  State state = HOOFDMENU;

public:
  Puzzel() { genereerBord(); }
  // Starten van het programma
  void start();
  // Menu's
  void inputHandler(char input);
  void inputHoofdmenu(char input);
  void inputParameterMenu(char input);
  void inputPuzzelMenu(char input);
  void inputTekenMenu(char input);
  // Parameter menu
  void veranderParameter(string naam, int &variabele, int max);
  void veranderParameter(string naam, char &variabele);
  void veranderParameter(string naam, bool &variabele);
  // Teken menu
  void maakSchoon();
  void randomBord();
  void toggle(char input);
  void genereerBord();
  // Puzzel menu
  void volg();
  void losOp();
  void speelOplossing();
  void spelen(char input);
  // Overige hulp functies
  void randomArray(int grootte, int array[]);
  void kopieArray(bool array1[MAX_HOOGTE][MAX_BREEDTE],
                  bool array2[MAX_HOOGTE][MAX_BREEDTE]);
  int randomGetal();
  void bordTekenen();
  void updateScherm();
  void beweeg(int dx, int dy);
  void klik(int x, int y);
  void flipLamp(int x, int y);
  void menuText();
  void setState(State newState) { state = newState; }
};

void Puzzel::start() {
  // Start het programma
  system("clear");
  bordTekenen();
  char input = '\0';

  while (!eindigSpel) {
    input = leesOptie();

    inputHandler(input);
    updateScherm();
  }
}
void Puzzel::veranderParameter(string naam, int &variabele, int max) {
  // Functie nodig voor het veranderen van de parameters, merk op dat we 3
  // varianten hebben gemaakt zodat elke soort type variabele compatibel is.
  cout << "Geef nieuwe " << naam << ": ";
  variabele = leesGetal(max);
  maakSchoon();
}

void Puzzel::veranderParameter(string naam, char &variabele) {
  cout << "Geef nieuwe " << naam << ": ";
  variabele = leesOptie();
  maakSchoon();
}

void Puzzel::veranderParameter(string naam, bool &variabele) {
  cout << naam << "modus (j/n): ";
  char keuze = leesOptie();
  if (keuze == 'J') {
    variabele = true;
  } else if (keuze == 'N') {
    variabele = false;
  }
  maakSchoon();
}

int Puzzel::randomGetal() {
  // Geeft een random getal
  seed = (221 * seed + 1) % 1000;
  return seed;
}

void Puzzel::randomArray(int grootte, int array[]) {
  // Maakt een random array met unieke getallen
  for (int i = 0; i < grootte; i++) {
    int r = i + randomGetal() % (grootte - i);
    wissel(array[i], array[r]);
  }
}

void Puzzel::randomBord() {
  // Maak een bord door random lampen aan te zetten. Let op dat deze puzzels
  // onoplosbaar kunnen zijn.
  maakSchoon();
  int aantalLampen = breedte * hoogte;
  int getallen[aantalLampen];
  for (int i = 0; i < aantalLampen; i++) {
    getallen[i] = i;
  }
  int aantalLampenAan = (aantalLampen * proportieLampenAan) / 100;
  randomArray(aantalLampen, getallen);

  for (int i = 0; i < aantalLampenAan; i++) {
    int rij = getallen[i] / breedte;
    int kolom = getallen[i] % breedte;
    lampen[rij][kolom] = true;
    lampenStart[rij][kolom] = true;
  }
}

void Puzzel::kopieArray(bool array1[MAX_HOOGTE][MAX_BREEDTE],
                        bool array2[MAX_HOOGTE][MAX_BREEDTE]) {
  // Maakt een kopie van een array
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      array1[i][j] = array2[i][j];
    }
  }
}

void Puzzel::speelOplossing() {
  // Lost puzzel op met de opgeslagen oplossing van genereerBord()
  kopieArray(lampen, lampenStart);
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      if (oplossing[i][j]) {
        klik(j, i);
        if (isAnimatie) {
          sleep(1);
          updateScherm();
        }
      }
    }
  }
}

void Puzzel::genereerBord() {
  // Maakt een bord door zetten te zetten. Deze puzzels zijn altijd oplosbaar.
  maakSchoon();
  int aantalLampen = breedte * hoogte;
  int getallen[MAX_BREEDTE * MAX_HOOGTE];
  int moeilijkheidsgraad = randomGetal() % aantalLampen;
  for (int i = 0; i < aantalLampen; i++) {
    getallen[i] = i;
  }
  randomArray(aantalLampen, getallen);
  if (startProgramma) {
    startProgramma = false;
  } else {
    cout << "Moeilijksheidsgraad (1-" << aantalLampen << ") :";
    moeilijkheidsgraad = leesGetal(aantalLampen);
  }

  for (int i = 0; i < moeilijkheidsgraad; i++) {
    int rij = getallen[i] / breedte;
    int kolom = getallen[i] % breedte;
    oplossing[rij][kolom] = true;
    klik(kolom, rij);
  }
  kopieArray(lampenStart, lampen);
}

void Puzzel::inputTekenMenu(char input) {
  // Switch voor alle verschillen opties
  switch (input) {
  case 'S':
    maakSchoon();
    break;
  case 'R':
    randomBord();
    break;
  case 'O':
    setState(TOGGLE);
    break;
  case 'G':
    genereerBord();
    break;
  case 'T':
    setState(HOOFDMENU);
    break;
  }
}

void Puzzel::menuText() {
  // Alle verschillende soorten menu's
  switch (state) {
  case HOOFDMENU:
    cout << "[P]arameters | p[U]zzelmenu | [T]ekenmenu | [S]toppen" << endl;
    break;
  case TEKEN:
    cout << "[S]choon | [R]andom | T[O]ggle | [G]enereer | [T]erug" << endl;
    break;
  case PUZZEL:
    cout << "[V]olg | [L]os 5x5 | [S]peel oplossing | S[P]elen | [T]erug"
         << endl;
    break;
  case SPELEN:
    cout << "[W]omhoog | [A]links | [S]omlaag | [D]rechts |[E]klik | [T]erug"
         << endl;
    break;
  case TOGGLE:
    cout << "[W]omhoog | [A]links | [S]omlaag | [D]rechts |[E]klik | [T]erug"
         << endl;
    break;
  case PARAMETER:
    cout << "[H]oogte | [B]reedte | [R]andom | [A]an | [U]it | T[O]rus | [P]en "
            "| A[N]imatie | [T]erug"
         << endl;
    break;
  }
}

void Puzzel::inputHoofdmenu(char input) {
  // Switch van alle opties in het hoofdmenu
  switch (input) {
  case 'P':
    setState(PARAMETER);
    break;
  case 'U':
    setState(PUZZEL);
    break;
  case 'T':
    setState(TEKEN);
    break;
  case 'S':
    eindigSpel = true;
    break;
  }
}

void Puzzel::inputParameterMenu(char input) {
  // Switch van alle opties in het parameter menu
  switch (input) {
  case 'H':
    veranderParameter("hoogte", hoogte, MAX_HOOGTE);
    break;
  case 'B':
    veranderParameter("breedte", breedte, MAX_BREEDTE);
    break;
  case 'R':
    veranderParameter("proportie", proportieLampenAan, MAX_PROPORTIE);
    break;
  case 'A':
    veranderParameter("karakter", karakterLampAan);
    break;
  case 'U':
    veranderParameter("karakter", karakterLampUit);
    break;
  case 'O':
    veranderParameter("Torus ", isTorus);
    break;
  case 'N':
    veranderParameter("Animatie ", isAnimatie);
    break;
  case 'P':
    veranderParameter("pen modus(0 := uit, 1 := alles aan, 2 := alles uit)",
                      pen, 2);
    break;
  case 'T':
    setState(HOOFDMENU);
    break;
  }
}

void Puzzel::volg() {
  // Lost alleen de laatste rij niet op
  for (int i = 1; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      if (lampen[i - 1][j]) {
        klik(j, i);
        if (isAnimatie) {
          updateScherm();
          sleep(1);
        }
      }
    }
  }
}

void Puzzel::losOp() {
  // Gebruikt volg en als er geen oplossing is proberen we verschillende
  // combinaties van lampen in de bovenste rij aan te zetten, volg() wordt dan
  // opnieuw aangeroepen en dit proces blijft herhalen tot alle rijen leeg zijn.
  if (hoogte != 5 || breedte != 5) {
    return;
  }
  bool isLeeg = true;
  for (int p = 0; p < 32; p++) {
    for (int j = 0; j < breedte; j++) {
      if (p & (1 << j)) {
        klik(j, 0);
      }
    }
    volg();
    isLeeg = true;
    for (int j = 0; j < breedte; j++) {
      if (lampen[hoogte - 1][j] == true) {
        isLeeg = false;
        break;
      }
    }
    if (isLeeg) {
      return;
    } else {
      for (int i = 0; i < hoogte; i++) {
        for (int j = 0; j < breedte; j++) {
          lampen[i][j] = lampenStart[i][j];
        }
      }
    }
  }
}

void Puzzel::inputPuzzelMenu(char input) {
  // Switch van alle opties in het puzzel menu
  switch (input) {
  case 'V':
    volg();
    break;
  case 'L':
    losOp();
    break;
  case 'S':
    speelOplossing();
    break;
  case 'P':
    setState(SPELEN);
    break;
  case 'T':
    setState(HOOFDMENU);
    break;
  }
}
void Puzzel::inputHandler(char input) {
  // Stuurt de input naar de goede state
  switch (state) {
  case HOOFDMENU:
    inputHoofdmenu(input);
    break;
  case PARAMETER:
    inputParameterMenu(input);
    break;
  case PUZZEL:
    inputPuzzelMenu(input);
    break;
  case TEKEN:
    inputTekenMenu(input);
    break;
  case SPELEN:
    spelen(input);
    break;
  case TOGGLE:
    toggle(input);
    break;
  }
}

void Puzzel::bordTekenen() {
  // Tekent het bord en menu
  infoblok();
  char karakter = '\0';
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      if (lampen[i][j]) {
        karakter = karakterLampAan;
      } else {
        karakter = karakterLampUit;
      }
      if (posX == j && posY == i && (state == SPELEN || state == TOGGLE)) {

        cout << " [" << karakter << "] ";
      } else {
        cout << "  " << karakter << "  ";
      }
    }
    cout << "\n";
  }
  menuText();
}

void Puzzel::maakSchoon() {
  // Zet alle elementen in de arrays naar "false"
  for (int i = 0; i < MAX_HOOGTE; i++) {
    for (int j = 0; j < MAX_BREEDTE; j++) {
      lampen[i][j] = false;
      lampenStart[i][j] = false;
      oplossing[i][j] = false;
    }
  }
}

void Puzzel::toggle(char input) {
  // Toggle modus waarbij we lampen kunnen aan/uit zetten
  switch (input) {
  case 'D':
    beweeg(1, 0);
    break;
  case 'A':
    beweeg(-1, 0);
    break;
  case 'W':
    beweeg(0, -1);
    break;
  case 'S':
    beweeg(0, 1);
    break;
  case 'E':
    if (pen == 0) {
      lampen[posY][posX] = !lampen[posY][posX];
    }
    break;
  case 'T':
    setState(TEKEN);
    break;
  }
  if (pen == 1) {
    lampen[posY][posX] = true;
  } else if (pen == 2) {
    lampen[posY][posX] = false;
  }
}

void Puzzel::spelen(char input) {
  // Het spel spelen
  switch (input) {
  case 'D':
    beweeg(1, 0);
    break;
  case 'A':
    beweeg(-1, 0);
    break;
  case 'W':
    beweeg(0, -1);
    break;
  case 'S':
    beweeg(0, 1);
    break;
  case 'E':
    klik(posX, posY);
    break;
  case 'T':
    setState(PUZZEL);
    break;
  }
}

void Puzzel::updateScherm() {
  // Maakt de terminal schoon, en tekent het bord
  system("clear");
  bordTekenen();
}

void Puzzel::beweeg(int x, int y) {
  // Berekent juiste positie
  posX = (posX + x + breedte) % breedte;
  posY = (posY + y + hoogte) % hoogte;
}

void Puzzel::flipLamp(int x, int y) {
  // Flipt de desbetreffende lamp
  if (isTorus) {
    if (x < 0) {
      x = (x + breedte) % breedte;
    }
    if (y < 0) {
      y = (y + hoogte) % hoogte;
    }
  }
  if (y >= 0 && y < hoogte && x >= 0 && x < breedte) {
    lampen[y][x] = !lampen[y][x];
  }
}

void Puzzel::klik(int x, int y) {
  // Flipt de lamp en de buren
  flipLamp(x, y);
  flipLamp(x - 1, y);
  flipLamp(x + 1, y);
  flipLamp(x, y - 1);
  flipLamp(x, y + 1);
}

int main() {
  Puzzel puzzel = Puzzel();
  puzzel.start();
  return 0;
}