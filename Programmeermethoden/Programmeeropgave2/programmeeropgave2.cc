#include <iostream>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

int draaiGetal(int getal)
{
    int result = 0;
    while (getal > 0)
    {
        result *= 10;
        result += getal % 10;
        getal /= 10;
    }
    return result;
}
int lychrel(int getal)
{
    int omgekeerdGetal;
    int iteraties = 0;
    while (getal < 1000000)
    {
        omgekeerdGetal = draaiGetal(getal);
        if (getal == omgekeerdGetal)
        {
            return iteraties;
        }

        getal += omgekeerdGetal;
        iteraties++;
    }
    return -1;
}
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
    int resultaat = (karakter - 32 + verschuiving) % 95;
    if (resultaat < 0)
    {
        resultaat += 95;
    }
    return resultaat + 32;
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
        cout << "Getal: " << getal << "\nIteraties lychrel: " << lychrel(getal) << endl;
        getal = 0;
    }
}
char ontsleutelKarakter(char karakter, char vorigVersleuteldKarakter, int &pincode, int &index, int &getal)
{
    int verschuiving = krijgPincodeCijfer(pincode, index);
    char versleuteldKarakter = verschuifKarakter(karakter, -verschuiving);
    verwerkGetal(versleuteldKarakter, vorigVersleuteldKarakter, pincode, getal);
    if (karakter == '\n')
    {
        index = 0;
        return karakter;
    }
    else if (karakter == '\t' || karakter == '\r')
    {
        return karakter;
    }
    index++;
    return versleuteldKarakter;
}
char versleutelKarakter(char karakter, char vorigKarakter, int &pincode, int &index, int &getal)
{
    int verschuiving;
    verwerkGetal(karakter, vorigKarakter, pincode, getal);
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

        verschuiving = krijgPincodeCijfer(pincode, index);
        index++;
        return verschuifKarakter(karakter, verschuiving);
    }
}
void versleutel(bool isVersleuteld, string invoerFile, string uitvoerFile, int pincode)
{
    ifstream invoer(invoerFile, ios::in);
    ofstream uitvoer(uitvoerFile, ios::out);

    char karakter;
    char vorigKarakter = '\0';
    char vorigVersleuteldKarakter = '\0';
    char resultaat;
    int getal = 0;
    int index = 0;

    karakter = invoer.get();
    while (!invoer.eof())
    {
        if (isVersleuteld)
        {
            resultaat = ontsleutelKarakter(karakter, vorigVersleuteldKarakter, pincode, index, getal);
            vorigVersleuteldKarakter = resultaat;
        }
        else
        {
            resultaat = versleutelKarakter(karakter, vorigKarakter, pincode, index, getal);
        }
        uitvoer.put(resultaat);
        vorigKarakter = karakter;
        karakter = invoer.get();
    }
    invoer.close();
    uitvoer.close();
}

int main()
{
    int pincode = 1234;

    // Test
    string orgineleFile = "test.txt";
    string gecodeerdeFile = "testCod.txt";
    string gedecoreerdeFile = "testDecod.txt";

    // Voorbeeld
    // string orgineleFile = "voorbeeld2025.txt";
    // string gecodeerdeFile = "voorbeeld2025gecodeerd.txt";
    // string gedecoreerdeFile = "voorbeeld2025gedecodeerd.txt";

    versleutel(false, orgineleFile, gecodeerdeFile, pincode);
    versleutel(true, gecodeerdeFile, gedecoreerdeFile, pincode);

    return 0;
}