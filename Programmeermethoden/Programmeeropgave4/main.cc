#include <iostream>

enum {
  NOORD = 0,
  NOORDOOST = 1,
  OOST = 2,
  ZUIDOOST = 3,
  ZUID = 4,
  ZUIDWEST = 5,
  WEST = 6,
  NOORDWEST = 7
};

struct vak {
  char teken = '.';
  vak *buren[8] = {nullptr};
};

class Bord {
  vak *linksboven = nullptr;
  int m;
  int n;
  vak **indices;

  Bord(int m, int n) {
    indices = new vak *[m * n];
    for (int i = 0; i < m * n; i++) {
      indices[i] = new vak;
    }
    linksboven = indices[0];

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        int index = i * n + j;
        if (i > 0) {
          indices[index]->buren[NOORD] = indices[(i - 1) * n + j];
        }
        if (i > 0 && j < n - 1) {
          indices[index]->buren[NOORDOOST] = indices[(i - 1) * n + (j + 1)];
        }
        if (j < n - 1) {
          indices[index]->buren[OOST] = indices[i * n + (j + 1)];
        }
        if (j < n - 1 && i < m - 1) {
          indices[index]->buren[ZUIDOOST] = indices[(i + 1) * n + (j + 1)];
        }
        if (i < m - 1) {
          indices[index]->buren[ZUID] = indices[(i + 1) * n + j];
        }
        if (j > 0) {
          indices[index]->buren[WEST] = indices[i * n + (j - 1)];
        }
      }
    }
  }
};

int main() { return 0; }