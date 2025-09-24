#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int power(int getal, int exponent)
{
    if (exponent == 0)
    {
        return 1;
    }
    return getal * power(getal, exponent - 1);
}
bool isCijfer(char karakter)
{
    if (karakter >= 48 && karakter <= 57)
    {
        return true;
    }
    return false;
}

void codeer(string &invoerFile, string &uitvoerFile, int pincode)
{
    ifstream invoer(invoerFile, ios::in);
    ofstream uitvoer(uitvoerFile, ios::out);

    char karakter, vorigKarakter, karakterUitvoer;
    int caesar;
    int getal = 0;
    int exponent;
    int count = 0;
    bool veranderPincode = false;
    while (!invoer.eof())
    {
        vorigKarakter = karakter;
        karakter = invoer.get();
        if (karakter == '\n')
        {
            uitvoer.put(karakter);
            count = -1;
        }
        else if (karakter == '\t' || karakter == 'r')
        {
            uitvoer.put(karakter);
        }
        else
        {
            exponent = 3 - (count % 4);
            caesar = pincode / power(10, exponent) % 10;
            karakterUitvoer = ((karakter - 32 + caesar) % 95) + 32;
            uitvoer.put(karakterUitvoer);
        }
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
        else
        {
            if (isCijfer(vorigKarakter))
            {
                if (getal >= 0 && getal <= 10000)
                {
                    veranderPincode = true;
                }
                cout << getal << endl;
            }
        }

        count++;
        if (veranderPincode)
        {
            pincode = getal;
            getal = 0;
            veranderPincode = false;
        }
    }
    invoer.close();
    uitvoer.close();
    cout << getal;
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

    string orgineleFile = "voorbeeld2025.txt";
    string gecodeerdeFile = "voorbeeld2025gecodeerd.txt";
    string gedecoreerdeFile = "voorbeeld2025gedecoreerd.txt";

    codeer(orgineleFile, gecodeerdeFile, pincode);
    decodeer(gecodeerdeFile, gedecoreerdeFile, pincode);

    return 0;
}