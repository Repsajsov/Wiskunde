#include <cstdlib>
#include <iostream>

using namespace std;

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
  int breedte = 5;
  int hoogte = 5;
  int proportieLampenAan = 50;
  int posX = 0;
  int posY = 0;
  bool isTorus = false;
  char karakterLampAan = 'o';
  char karakterLampUit = 'x';
  bool lampen[MAX_HOOGTE][MAX_BREEDTE];
  bool eindigSpel = false;
  State state = HOOFDMENU;

public:
  Puzzel();
  void start();
  void bordTekenen();
  void maakSchoon();
  void updateScherm();
  void beweeg(int dx, int dy);
  void klik();
  void flipLamp(int x, int y);
  // input
  void inputHandler(char input);
  void inputHoofdmenu(char input);
  void inputParameterMenu(char input);
  void inputPuzzelMenu(char input);

  void spelen(char input);
  void volg();
  void losOp();
  void pen();

  void menuText();
  // setters
  void setState(State newState) { state = newState; }
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
};
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
void Puzzel::pen() {};
void Puzzel::setKarakterLampAan(char nieuweKarakter) {
  karakterLampAan = nieuweKarakter;
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
  case PUZZEL:
    cout << "[V]olg | [L]os 5x5 | [S]peel oplossing | S[P]elen | [T]erug"
         << endl;
    break;
  case SPELEN:
    cout << "[W]omhoog | [A]links | [S]omlaag | [D]rechts |[E]klik | [T]erug"
         << endl;
    break;
  case PARAMETER:
    cout << "[H]oogte | [B]reedte | [R]andom | [A]an | [U]it | T[O]rus | [P]en "
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
    pen();
  case 'T':
    setState(HOOFDMENU);
    break;
  }
}

void Puzzel::volg() {
  for (int i = 1; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      if (lampen[i - 1][j]) {
        klik();
      }
    }
  }
}
void Puzzel::losOp() { return; }

void Puzzel::inputPuzzelMenu(char input) {
  switch (input) {
  case 'V':
    volg();
    break;
  case 'S':
    losOp();
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
  case SPELEN:
    spelen(input);
  }
}

Puzzel::Puzzel() {
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      lampen[i][j] = false;
    }
  }
}

void Puzzel::bordTekenen() {
  char karakter = '\0';
  for (int i = 0; i < hoogte; i++) {
    for (int j = 0; j < breedte; j++) {
      if (lampen[i][j]) {
        karakter = karakterLampAan;
      } else {
        karakter = karakterLampUit;
      }
      if (posX == j && posY == i && state == SPELEN) {

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
    }
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
    klik();
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

void Puzzel::klik() {
  flipLamp(posX, posY);
  flipLamp(posX - 1, posY);
  flipLamp(posX + 1, posY);
  flipLamp(posX, posY - 1);
  flipLamp(posX, posY + 1);
}

int main() {
  Puzzel game = Puzzel();
  game.start();

  return 0;
}