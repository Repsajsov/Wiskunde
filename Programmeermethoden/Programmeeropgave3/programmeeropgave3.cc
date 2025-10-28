#include <cstdlib>
#include <iostream>

using namespace std;

char leesOptie() {
  char resultaat;
  do {
    cin.get(resultaat);
  } while (resultaat == '\n');
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
      if (resultaat > max)
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
    HOOFDMENU_STATE,
    PARAMETER_STATE,
    TEKEN_STATE,
    TOGGLE_STATE,
    PUZZEL_STATE,
    SPEEL_STATE
  };
  int breedte = 5;
  int hoogte = 5;
  int proportieLampenAan = 50;
  int posX = 0;
  int posY = 0;
  char karakterLampAan = 'o';
  char karakterLampUit = 'x';
  bool lampen[MAX_HOOGTE][MAX_BREEDTE];
  State state = HOOFDMENU_STATE;

public:
  Puzzel();
  void bordTekenen();
  void maakSchoon();
  void updateScherm();
  void beweeg(int dx, int dy);
  void klik();
  void flipLamp(int x, int y);
  void inputHandler(char input);
  void speel(char input);
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
};

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

void Puzzel::setBreedte(int nieuweBreedte) {
  if (nieuweBreedte <= MAX_BREEDTE && nieuweBreedte >= 0) {
    breedte = nieuweBreedte;
  }
  maakSchoon();
}

void Puzzel::menuText() {
  switch (state) {
  case HOOFDMENU_STATE:
    cout << "[P]arameters | p[U]zzelmenu | [T]ekenmenu | [S]toppen" << endl;
    break;
  case PUZZEL_STATE:
    cout << "[V]olg | [L]os 5x5 | [S]peel oplossing | S[p]elen | [T]erug"
         << endl;
    break;
  case SPEEL_STATE:
    cout << "[W]omhoog | [A]links | [S]omlaag | [D]rechts |[E]klik | [T]erug"
         << endl;
    break;
  case PARAMETER_STATE:
    cout << "[H]oogte | [B]reedte | [R]andom | [A]an | [U]it | [T]orus | [P]en "
            "| [T]erug"
         << endl;
    break;
  default:
    cout << "NIKS." << endl;
    break;
  }
}

void Puzzel::inputHandler(char input) {
  switch (state) {
  case HOOFDMENU_STATE: {
    switch (input) {
    case 'p':
    case 'P':
      setState(PARAMETER_STATE);
      break;
    case 't':
    case 'T':
      setState(TEKEN_STATE);
      break;
    case 'u':
    case 'U':
      setState(PUZZEL_STATE);
      break;
    }
    break;
  }
  case PARAMETER_STATE: {
    switch (input) {
    case 'h':
    case 'H':
      vraagHoogte();
      break;
    case 'b':
    case 'B':
      vraagBreedte();
      break;

    default:
      break;
    }
    break;
  }
  case PUZZEL_STATE: {
    switch (input) {
    case 'p':
    case 'P':
      setState(SPEEL_STATE);
      break;
    }
  } break;
  case SPEEL_STATE: {
    speel(input);
  }
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
      if (posX == j && posY == i && state == SPEEL_STATE) {

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

void Puzzel::speel(char input) {
  switch (input) {
  case 'd':
    beweeg(1, 0);
    break;
  case 'a':
    beweeg(-1, 0);
    break;
  case 'w':
    beweeg(0, -1);
    break;
  case 's':
    beweeg(0, 1);
    break;
  case 'e':
    klik();
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

  Puzzel game;
  game.bordTekenen();
  bool stoppen = false;
  char input = '\0';

  while (!stoppen) {
    input = leesOptie();

    game.inputHandler(input);
    game.updateScherm();
    // cout << game.getState();
  }

  return 0;
}