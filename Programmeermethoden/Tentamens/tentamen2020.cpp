#include <iostream>

// Extra
void afdrukken(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
}

// Vraag 1.a
bool gem(int A[], int n)
{
    int teller = 0;
    for (int i = 1; i < n - 1; i++)
    {
        float getal = A[i];
        float gemiddelde = (A[i - 1] + A[i + 1]) / 2.0;
        if (getal == gemiddelde)
        {
            teller++;
        }
    }
    if (teller == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Vraag 1.b
int stijg(int A[], int &b, int n)
{
    int teller = 1;
    int maxLengte = -1;
    int lengte = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (A[i] > A[i + 1])
        {
            lengte = teller;
            if (lengte > maxLengte)
            {
                b = i - (lengte - 1);
                maxLengte = lengte;
            }
            teller = 1;
        }
        else
        {
            teller++;
        }
    }
    return maxLengte;
}

// Vraag 1.c
int kl(int A[], int n)
{
    int b = 0;
    int kleinste1 = A[0];
    int lengte = stijg(A, b, n);
    int kleinste2 = A[b + lengte];
    if (kleinste1 < kleinste2)
    {
        return kleinste1;
    }
    else
    {
        return kleinste2;
    }
}

// Vraag 1.d
void bu(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (A[j] < A[j + 1])
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                swapped = true;
            }
        }
        afdrukken(A, n);
        if (!swapped)
        {
            return;
        }
    }
}

// Vraag 1.e
/*

Als de array al gesorteerd is doet het n-1 aantal keer controleren of A[i] < A[i+1], n-1 is dus het minimum.
Als de array omgedraaid gesorteed is doet het n aantal vergelijkingen bij de eerste iteratie dan de tweede iteratie n-1 etc.
Ofwel

n-1 + n-2 + n-3 + ... + 1 = aantal vergelijkingen.


min = n-1, max = n(n-1)/2

*/

// Vraag 2.a
/*

formele parameters zijn concept variabelen wat je moet invullen om de functie aan te roepen.

actuele parameters zijn de variabelen die in een functie aanroep gestopt worden.

call by value zijn betekent dat de waarden die je een functie meegeeft gekopieerd worden en waarvan
de gekopieerde variant alleen in de functiescope bestaat

call by reference maakt geen kopie van de doorgegeven variabele en
als deze variabel gewijzigd wordt in de functie dan verandert deze waarde dus.

lokale variabelen zijn variabelen die alleen in zijn scope bestaan bijv als er een functie wordt aangeroepen
en daar worden variabelen gemaakt dan verdwijnen deze variabelen als de functie is beeindigd

globala variabelen zijn variabelen die overal gebruikt kunnen worden

*/

// Vraag 2.b

int michael(int &a, int &b, int &c)
{
    int temp = a;
    a = b;
    b = c;
    c = temp;
    return 2;
}

int peter(int u, int v, int w)
{
    int j, a = 0;
    u++;
    for (j = 1; j <= 1010; j++)
    {
        a += michael(u, v, w);
    }
    std::cout << j << "," << u << "," << v << "," << w << std::endl;
    return a;
    u++;
}

int main()
{
    int x = 1;
    int y = 4;
    int z = 8;
    std::cout << peter(x, y, z) << ",";
    std::cout << x << "," << y << "," << z << std::endl;

    return 0;
}