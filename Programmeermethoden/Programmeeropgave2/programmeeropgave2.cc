#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void codeer(string &invoerFilepad, string &uitvoerFilepad, int caesar)
{
    ifstream invoer(invoerFilepad, ios::in);
    ofstream uitvoer(uitvoerFilepad, ios::out);

    char letter;
    while (!invoer.eof())
    {
        letter = invoer.get();
        if (letter != '\n' && letter != '\r' && letter != '\t')
        {
            letter = ((letter - 32 + caesar) % 95) + 32;
            cout << "\nASCII-waarde: " << int(letter) << "\nLetter: " << letter << endl;
        }
        uitvoer.put(letter);
    }
    invoer.close();
    uitvoer.close();
}
void decodeer(string &invoerFilepad, string &uitvoerFilepad, int caesar)
{
    ifstream invoer(invoerFilepad, ios::in);
    ofstream uitvoer(uitvoerFilepad, ios::out);

    char letter;
    while (!invoer.eof())
    {
        letter = invoer.get();
        cout << letter;
        if (letter != '\n' && letter != '\r' && letter != '\t')
        {
            letter = ((letter - 32 - caesar) % 95) + 32;
        }
        uitvoer.put(letter);
    }
    invoer.close();
    uitvoer.close();
}

int main()
{

    // Lezen van invoerfile
    string orgineleFile = "simpel2025.txt";
    string gecodeerdeFile = "simpel2025gecodeerd.txt";
    string gedecoreerdeFile = "simpel2025gedecoreerd.txt";

    codeer(orgineleFile, gecodeerdeFile, 2);
    decodeer(gecodeerdeFile, gedecoreerdeFile, 2);

    return 0;
}