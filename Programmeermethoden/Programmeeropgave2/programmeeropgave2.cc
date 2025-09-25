#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isCijfer(char karakter)
{
    if (karakter >= 48 && karakter <= 57)
    {
        return true;
    }
    return false;
}
int krijgPincodeCijfer(int pincode, int index)
{
    switch (index % 4)
    {
    case 0:
        return (pincode / 1000) % 10;
    case 1:
        return (pincode / 100) % 10;
    case 2:
        return (pincode / 10) % 10;
    case 3:
        return pincode % 10;
    default:
        return 0;
    }
}
char verschuifKarakter(char karakter, int verschuiving)
{
    return (((karakter - 32) + verschuiving) % 95) + 32;
}
void verwerkGetal(char karakter, char vorigKarakter, int &pincode, int &getal)
{

    if (isCijfer(karakter))
    {
        if (isCijfer(vorigKarakter))
        {
            getal = (getal * 10) + (karakter - '0');
        }
        else
        {
            getal = karakter - '0';
        }
    }
    else if (isCijfer(vorigKarakter) && (getal > 0 && getal < 10000))
    {
        pincode = getal;
        getal = 0;
    }
}
char verwerkKarakter(char karakter, char vorigKarakter, int &pincode, int &index, int &getal)
{
    int verschuiving;
    if (karakter == '\n')
    {
        index = 0;
        return karakter;
    }
    else if (karakter == '\t' || karakter == '\r')
    {
        return karakter;
    }
    else
    {
        verwerkGetal(karakter, vorigKarakter, pincode, getal);

        verschuiving = krijgPincodeCijfer(pincode, index);
        index++;
        return verschuifKarakter(karakter, verschuiving);
    }
}

void codeer(string &invoerFile, string &uitvoerFile, int pincode)
{
    ifstream invoer(invoerFile, ios::in);
    ofstream uitvoer(uitvoerFile, ios::out);

    char karakter;
    char vorigKarakter = '\0';
    int getal = 0;
    int index = 0;

    karakter = invoer.get();
    while (!invoer.eof())
    {
        uitvoer.put(verwerkKarakter(karakter, vorigKarakter, pincode, index, getal));
        vorigKarakter = karakter;
        karakter = invoer.get();
    }
    invoer.close();
    uitvoer.close();
}

int main()
{
    int pincode = 1234;

    string orgineleFile = "test.txt";
    string gecodeerdeFile = "testCod.txt";
    string gedecoreerdeFile = "testDecod.txt";

    codeer(orgineleFile, gecodeerdeFile, pincode);

    return 0;
}