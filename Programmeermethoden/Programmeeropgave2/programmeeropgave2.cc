#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int power(int getal, int exponent)
{
    if (exponent == 0)
        return 1;
    return getal * power(getal, exponent - 1);
}

void codeer(string &invoerFile, string &uitvoerFile, int pincode)
{
    ifstream invoer(invoerFile, ios::in);
    ofstream uitvoer(uitvoerFile, ios::out);

    char karakter;
    int caesar;
    int exponent;
    int count = 0;
    while (!invoer.eof())
    {
        karakter = invoer.get();
        if (karakter == '\n')
        {
            count = -1;
        }
        else if (karakter != '\r' && karakter != '\t')
        {
            exponent = 3 - (count % 4);
            caesar = pincode / power(10, exponent) % 10;
            karakter = ((karakter - 32 + caesar) % 95) + 32;
        }
        uitvoer.put(karakter);
        count++;
    }
    invoer.close();
    uitvoer.close();
}
void decodeer(string &invoerFile, string &uitvoerFile, int pincode)
{
    ifstream invoer(invoerFile, ios::in);
    ofstream uitvoer(uitvoerFile, ios::out);

    char karakter;
    int caesar;
    int exponent;
    int count = 0;
    while (!invoer.eof())
    {
        karakter = invoer.get();
        if (karakter == '\n')
        {
            count = -1;
        }
        else if (karakter != '\r' && karakter != '\t')
        {
            exponent = 3 - (count % 4);
            caesar = pincode / power(10, exponent) % 10;
            karakter = ((karakter - 32 - caesar) % 95) + 32;
        }
        else if (karakter)
        {
        }
        uitvoer.put(karakter);
        count++;
    }
    invoer.close();
    uitvoer.close();
}

int main()
{

    int pincode;
    cout << "Geef pincode: ";
    cin >> pincode;
    if (pincode < 0 || pincode > 9999)
    {
        return 0;
    }

    // int pincode = 34;

    // Lezen van invoerfile

    string orgineleFile = "simpel2025.txt";
    string gecodeerdeFile = "simpel2025gecodeerd.txt";
    string gedecoreerdeFile = "simpel2025gedecoreerd.txt";

    codeer(orgineleFile, gecodeerdeFile, pincode);
    // decodeer(gecodeerdeFile, gedecoreerdeFile, 2);

    return 0;
}