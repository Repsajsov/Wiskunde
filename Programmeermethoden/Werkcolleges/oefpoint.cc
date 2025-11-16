
//
// Programmeermethoden 2025
//
// http://www.liacs.leidenuniv.nl/~visjk/pm/bestanden/oefpoint.cc
// C++-programma om te oefenen in het gebruik van pointers.
// Er moet eerst een enkelverbonden pointerlijst gefabriceerd worden,
// waarbij de "vakjes" die met elkaar verbonden worden bestaan uit
//   1. Een int(eger)
//   2. Een pointer naar een int(eger) (of nullptr)
//   3. Een pointer naar het volgende vakje (of nullptr)
// Schrijf de functies Afdrukken, Toevoegen en Verwijderen
// --- in deze volgorde.
// Er is ook een uitwerking van dit programma beschikbaar:
//   http://www.liacs.leidenuniv.nl/~visjk/pm/pointer.cc
//
// Doe hierna
//   http://www.liacs.leidenuniv.nl/~visjk/pm/dubbel.cc
//
// Compiler: GNU g++
// Datum: 10 november 2025
// Auteur: Jonathan Vis, Informatica Universiteit Leiden
//         e-mail pm@liacs.leidenuniv.nl
//

#include <iostream>
using namespace std;

// het soort vakje waar het om draait:
class vakje { // een struct mag ook
public:
  int info;
  int *andere;
  vakje *volgende;
}; // vakje

//
//   +-----+        +----+----+-----+        +----+----+-----+
//   |   --+------> | 34 |  | |   --+------> | 56 |  | | null|ptr
//   +-----+        +----+--+-+-----+        +----+--+-+-----+
//  ingang                  |                        |
//                          V                        V
//                       +----+                   +----+
//                       | 23 |                   | 18 |
//                       +----+                   +----+
//
// ingang wijst dus een vakje uit een lijst vakjes aan
// waarbij ieder vakje informatie bevat (het info-veld),
// een pointer naar een int(eger) (het andere-veld),
// en een pointer naar het volgende vakje; om zulke
// structuurtjes te maken is doorgaans in totaal steeds
// twee maal new nodig, voor het voorbeeld hierboven in totaal vier
// Een voorbeeld: het getal 34 (in het eerste vakje)
// wordt afgedrukt via:
//   cout << ingang->info << endl;
// En het getal 18 (toegankelijk door het tweede vakje) via:
//   cout << *(ingang->volgende->andere) << endl;
// En een pointer hulp (vakje* hulp) gaat naar het vakje
// met onder andere 56 erin wijzen via:
//   hulp = ingang->volgende;
//

// ************************************************************************

void Afdrukken(vakje *ingang) {
  // druk lijst met ingang als ingang af
  cout << "Lijst afdrukken ..." << endl;

  for (; ingang; ingang = ingang->volgende) {

    cout << ingang->info << " " << *ingang->andere << endl;
  }

} // Afdrukken

void Toevoegen(vakje *&ingang, int een, int twee) {
  vakje *nieuw = new vakje;
  nieuw->info = een;
  nieuw->andere = new int;
  *(nieuw->andere) = twee;

  nieuw->volgende = ingang;
  ingang = nieuw;
} // Toevoegen

void Verwijderen(vakje *&ingang) {} // Verwijderen

void LeesInGetallen(int &een, int &twee) {
  // lees integers een en twee in
  cout << "Eerste getal svp .. ";
  cin >> een;
  cout << "Tweede getal svp .. ";
  cin >> twee;
} // LeesInGetallen

int main() {

  vakje *ingang = nullptr;

  Toevoegen(ingang, 10, 20);
  Toevoegen(ingang, 12, 22);
  Afdrukken(ingang);

  return 0;

} // main
