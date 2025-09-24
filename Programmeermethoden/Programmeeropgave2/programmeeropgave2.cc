#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int power(int getal, int exponent)
{
    if (exponent == 0)
        return 1;
    return getal *= power(getal, exponent - 1);
}

void codeer(string &invoerFilepad, string &uitvoerFilepad, int pincode)
{
    ifstream invoer(invoerFilepad, ios::in);
    ofstream uitvoer(uitvoerFilepad, ios::out);

    char letter;
    int caesar;
    int exponent;
    int count = 0;
    while (!invoer.eof())
    {
        letter = invoer.get();
        exponent = 3 - (count % 4);
        caesar = pincode / power(10, exponent) % 10;
        cout << caesar << endl;

        if (letter != '\n' && letter != '\r' && letter != '\t')
        {
            letter = ((letter - 32 + caesar) % 95) + 32;
        }
        else if (letter == '\n')
        {
            count = 0;
            cout << "VERAndert!";
            continue;
        }
        uitvoer.put(letter);
        count++;
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

    // int pincode;
    // cout << "Geef pincode: ";
    // cin >> pincode;
    // if (pincode < 0 || pincode > 9999)
    // {
    //     return 0;
    // }

    int pincode = 1234;

    // Lezen van invoerfile

    string orgineleFile = "simpel2025.txt";
    string gecodeerdeFile = "simpel2025gecodeerd.txt";
    string gedecoreerdeFile = "simpel2025gedecoreerd.txt";

    codeer(orgineleFile, gecodeerdeFile, pincode);
    // decodeer(gecodeerdeFile, gedecoreerdeFile, 2);

    return 0;
}