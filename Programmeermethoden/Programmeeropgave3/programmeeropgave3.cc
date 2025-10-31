#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>

using namespace std;

void wissel(int &x, int &y) {
  int temp = x;
  x = y;
  y = temp;
}

char leesOptie() {
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
  const static int MAX_HOOGTE = 20;
  const static int MAX_BREEDTE = 20;
  enum State {
    HOOFDMENU,
    PARAMETER,
    TEKEN,
    TOGGLE,
    PUZZEL,
    SPELEN,
  };
  long seed = time(0);
  int breedte = 5;
  int hoogte = 5;
  int proportieLampenAan = 50;
  int posX = 0;
  int posY = 0;
  int pen = 0;
  bool isTorus = false;
  char karakterLampAan = '0';
  char karakterLampUit = '.';
  bool lampen[MAX_HOOGTE][MAX_BREEDTE];
  bool lampenStart[MAX_HOOGTE][MAX_BREEDTE];
  bool oplossing[MAX_HOOGTE][MAX_BREEDTE];

  bool eindigSpel = false;
  State state = HOOFDMENU;

public:
  Puzzel();
  void randomArray(int grootte, int array[]);
  void kopieArray(bool array1[MAX_HOOGTE][MAX_BREEDTE],
                  bool array2[MAX_HOOGTE][MAX_BREEDTE]);
  void resetPos();
  int randomGetal();
  void start();
  void bordTekenen();
  void maakSchoon();
  void updateScherm();
  void beweeg(int dx, int dy);
  void klik(int x, int y);
  void flipLamp(int x, int y);
  // input
  void inputHandler(char input);
  void inputHoofdmenu(char input);
  void inputParameterMenu(char input);
  void inputPuzzelMenu(char input);
  void inputTekenMenu(char input);

  void toggle(char input);
  void spelen(char input);
  void volg();
  void losOp();

  void randomBord();
  void genereerBord();
  void speelOplossing();

  void menuText();
  // setters
  void setState(State newState) { state = newState; }
  // void setState(GameState newState) { state = newState; }
  void setHoogte(int nieuweHoogte);
  void setBreedte(int nieuweBreedte);
  void setProportieLampenAan(int nieuweProportie);
  void setKarakterLampAan(char nieuweKarakter);
  void setKarakterLampUit(char nieuweKarakter);
  // getters
  State getState() { return state; }
  // Parameter-menu methods
  void vraagHoogte();
  void vraagBreedte();
  void vraagProportie();
  void veranderKarakterAan();
  void veranderKarakterUit();
  void vraagPenModus();
};

void Puzzel::setKarakterLampUit(char nieuweKarakter) {
  karakterLampUit = nieuweKarakter;
}

void Puzzel::resetPos() {
  posX = 0;
  posY = 0;
}

void Puzzel::start() {
  system("clear");
  bordTekenen();
  char input = '\0';

  while (!eindigSpel) {
    input = leesOptie();

    inputHandler(input);
    updateScherm();
  }
}
void Puzzel::setKarakterLampAan(char nieuweKarakter) {
  karakterLampAan = nieuweKarakter;
}

int Puzzel::randomGetal() {
  seed = (221 * seed + 1) % 1000;
  return seed;
}

void Puzzel::randomArray(int grootte, int array[]) {
  for (int i = 0; i < grootte; i++) {
    int r = i + randomGetal() % (grootte - i);
    wissel(array[i], array[r]);
  }
}

void Puzzel::randomBord() {
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
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      array1[i][j] = array2[i][j];
    }
  }
}

void Puzzel::speelOplossing() {
  kopieArray(lampen, lampenStart);
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      if (oplossing[i][j]) {
        klik(j, i);
        sleep(1);
        updateScherm();
      }
    }
  }
}

void Puzzel::genereerBord() {
  maakSchoon();
  int aantalLampen = breedte * hoogte;
  int getallen[aantalLampen];
  for (int i = 0; i < aantalLampen; i++) {
    getallen[i] = i;
  }
  randomArray(aantalLampen, getallen);
  cout << "Moeilijksheidsgraad (1-" << aantalLampen << ") :";
  int moeilijkheidsgraad = leesGetal(aantalLampen);

  for (int i = 0; i < moeilijkheidsgraad; i++) {
    int rij = getallen[i] / breedte;
    int kolom = getallen[i] % breedte;
    oplossing[rij][kolom] = true;
    klik(kolom, rij);
  }
  kopieArray(lampenStart, lampen);
}

void Puzzel::inputTekenMenu(char input) {
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

void Puzzel::setHoogte(int nieuweHoogte) {
  if (nieuweHoogte <= MAX_HOOGTE && nieuweHoogte >= 0) {
    hoogte = nieuweHoogte;
  }
  maakSchoon();
}

void Puzzel::setProportieLampenAan(int nieuweProportie) {
  if (nieuweProportie <= 100 && nieuweProportie >= 0) {
    proportieLampenAan = nieuweProportie;
  }
}

void Puzzel::vraagProportie() {
  int temp;
  cout << "Geef nieuwe proportie: ";
  temp = leesGetal(100);
  setProportieLampenAan(temp);
}

void Puzzel::vraagHoogte() {
  int temp;
  cout << "Geef nieuwe hoogte: ";
  temp = leesGetal(10000);
  setHoogte(temp);
}
void Puzzel::vraagBreedte() {
  int temp;
  cout << "Geef nieuwe breedte: ";
  temp = leesGetal(10000);
  setBreedte(temp);
}

void Puzzel::veranderKarakterAan() {
  char temp;
  cout << "Karakter voor lamp aan: ";
  temp = leesOptie();
  setKarakterLampAan(temp);
}

void Puzzel::setBreedte(int nieuweBreedte) {
  if (nieuweBreedte <= MAX_BREEDTE && nieuweBreedte >= 0) {
    breedte = nieuweBreedte;
  }
  maakSchoon();
}

void Puzzel::menuText() {
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
    cout << "[H]oogte | [B]reedte | [R]andom | [A]an | [U]it | T[O]rus | "
            "[P]en "
            "| [T]erug"
         << endl;
    break;
  }
}

void Puzzel::inputHoofdmenu(char input) {
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

void Puzzel::veranderKarakterUit() {
  char temp;
  cout << "Karakter voor lamp uit: ";
  temp = leesOptie();
  setKarakterLampUit(temp);
}
void Puzzel::vraagPenModus() {
  int temp;
  cout << "Verander Pen modus\n-0 geen pen modus\n-1 alle lampen aan\n-2 alle "
          "lampen uit\n\nGeef Pen modus: ";
  temp = leesGetal(3);
  pen = temp;
}

void Puzzel::inputParameterMenu(char input) {
  switch (input) {
  case 'H':
    vraagHoogte();
    break;
  case 'B':
    vraagBreedte();
    break;
  case 'R':
    vraagProportie();
    break;
  case 'A':
    veranderKarakterAan();
    break;
  case 'U':
    veranderKarakterUit();
    break;
  case 'O':
    isTorus = !isTorus;
    break;
  case 'P':
    vraagPenModus();
    break;
  case 'T':
    setState(HOOFDMENU);
    break;
  }
}

void Puzzel::volg() {
  for (int i = 1; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      if (lampen[i - 1][j]) {
        klik(j, i);
        updateScherm();
        sleep(1);
      }
    }
  }
}
void Puzzel::losOp() {
  if (hoogte != 5 || breedte != 5) {
    return;
  }
  bool isLeeg = true;
  for (int p = 0; p < 32; p++) {
    for (int j = 0; j < breedte; j++) {
      if (p & (1 << j)) {
        klik(0, j);
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
  resetPos();
}

void Puzzel::inputPuzzelMenu(char input) {
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

Puzzel::Puzzel() { maakSchoon(); }

void Puzzel::bordTekenen() {
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
  for (int i = 0; i < MAX_HOOGTE; i++) {
    for (int j = 0; j < MAX_BREEDTE; j++) {
      lampen[i][j] = false;
      lampenStart[i][j] = false;
      oplossing[i][j] = false;
    }
  }
}

void Puzzel::toggle(char input) {
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
  system("clear");
  bordTekenen();
}

void Puzzel::beweeg(int dx, int dy) {
  posX = (posX + dx + breedte) % breedte;
  posY = (posY + dy + hoogte) % hoogte;
}

void Puzzel::flipLamp(int x, int y) {
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
  flipLamp(x, y);
  flipLamp(x - 1, y);
  flipLamp(x + 1, y);
  flipLamp(x, y - 1);
  flipLamp(x, y + 1);
}

int main() {
  Puzzel game = Puzzel();
  game.start();

  return 0;
}