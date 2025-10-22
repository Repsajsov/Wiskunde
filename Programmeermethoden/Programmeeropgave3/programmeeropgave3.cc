#include <cstdlib>
#include <iostream>

using namespace std;

enum State { PUZZEL_STATE };

class Puzzel {
private:
  static const int BREEDTE = 20;
  static const int HOOGTE = 20;
  int posX = 0;
  int posY = 0;
  bool lampen[HOOGTE][BREEDTE];

public:
  Puzzel();
  void bordTekenen();
  void updateScherm();
  void beweeg(int dx, int dy);
  void klik();
  void flipLamp(int x, int y);
};

Puzzel::Puzzel() {
  for (int i = 0; i < HOOGTE; i++) {
    for (int j = 0; j < BREEDTE; j++) {
      lampen[i][j] = false;
    }
  }
}

void Puzzel::bordTekenen() {
  char teken = '\0';
  for (int i = 0; i < HOOGTE; i++) {
    for (int j = 0; j < BREEDTE; j++) {
      if (lampen[i][j]) {
        teken = 'o';
      } else {
        teken = 'x';
      }
      if (posX == j && posY == i) {
        cout << " [" << teken << "] ";
      } else {
        cout << "  " << teken << "  ";
      }
    }
    cout << "\n";
  }
}

void Puzzel::updateScherm() {
  system("clear");
  bordTekenen();
}

void Puzzel::beweeg(int dx, int dy) {
  posX = (posX + dx + BREEDTE) % BREEDTE;
  posY = (posY + dy + HOOGTE) % HOOGTE;
}

void Puzzel::flipLamp(int x, int y) {
  if (y >= 0 && y < HOOGTE && x >= 0 && x < BREEDTE) {
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

class Menu {};

class Spelen {};

int main() {

  Puzzel game;
  game.bordTekenen();
  bool stoppen = false;
  char actie = '\0';
  while (!stoppen) {
    cin.get(actie);

    if (actie == '\n')
      continue;
    if (actie == 'j') {
    } else if (actie == 'k') {
      stoppen = true;
    } else if (actie == 'd') {
      game.beweeg(1, 0);
    } else if (actie == 'a') {
      game.beweeg(-1, 0);
    } else if (actie == 'w') {
      game.beweeg(0, -1);
    } else if (actie == 's') {
      game.beweeg(0, 1);
    } else if (actie == 't') {
      game.klik();
    }

    game.updateScherm();
  }

  return 0;
}