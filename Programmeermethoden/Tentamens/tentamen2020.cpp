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

/*

peter roept steeds michael aan die steeds u, v, en w opschuift. (we kunnen u, v, en w dus als een cykel zien)
De output van michael is altijd 2, en dus wordt a (in peter) uiteindelijk 1010 * 2 = 2020.
Na de for loop moeten u, v, en w dus 1010 mod 3 = 2 plaatsen zijn opgeschoven.
Dit betekent dat na de for loop u=8, v=2, w=4.

De console print dus uiteindelijk:

1011,8,2,4
2020,1,4,8

*/

// Vraag 2.c

int michaelB(int &a, int &b, int &c)
{
    int temp = a;
    a = b;
    b = c;
    c = temp;
    return 2;
}

int peterB(int &u, int &v, int &w)
{
    int j, a = 0;
    u++;
    for (j = 1; j <= u; j++)
    {
        a += michael(u, v, w);
    }
    std::cout << j << "," << u << "," << v << "," << w << std::endl;
    return a;
    u++;
}

/*

Voor de for loop gaat j niet verder dan 4 omdat dat de eerste keer is dat u > j en de for loop dus stopt.
Dit betekent dus dat er 3 rotaties zijn geweest en u=2, v=4, w=8.
Deze zijn gelijk aan x, y, en z omdat die als reference worden meegegeven.

De console print dus uiteindelijk:

4, 2, 4, 8
6, 2, 4, 8

*/

// Vraag 2.d

int michaelD(int &a, int &b, int &c)
{
    int temp = a;
    a = b;
    b = c;
    c = temp;
    return 2;
}

int peterD(int &u, int &v, int &w)
{
    int j, a = 0;
    u++;
    for (j = 1; j <= 124124; j++)
    {
        a += michael(u, v, w);
    }
    std::cout << j << "," << u << "," << v << "," << w << std::endl;
    return a;
    u++;
}

/*

Eerst berekenen we 124124 mod 3 = 2, dus 2 rotaties en we krijgen dus
u=1, v=2, 2=1. j = 124125 als we de forloop hebben doorlopen en a = 248248.
De uiteindelijke console output is dus:

124125,1,2,1
248248,1

 */

// Vraag 2.e

int peterE(int u, int v, int w);
int michaelE(int &a, int &b, int &c)
{
    int temp = a;
    a = peterE(a, a - 1, a - 2);
    b = c;
    c = temp;
    return 2;
}

int peterE(int u, int v, int w)
{
    int j, a = 0;
    u++;
    for (j = 1; j <= 1010; j++)
    {
        a += michaelE(u, v, w);
    }
    std::cout << j << "," << u << "," << v << "," << w << std::endl;
    return a;
    u++;
}

/*

Zonder "&" voor peter krijgen we steeds dat peter michael aanroept en michael roept steeds peter op.
Dit gaat oneindig door tot we een stack overflow hebben en dus compileert het programma wel maar crashed het.

Met "&" krijgen we een probleem in het aanroepen van peter,
omdat a-1 niet een variabele is en dus kan het niet worden overschreven.
De code compileert dus niet.

*/

// Vraag 3.a

// Schrijf op de toets "n" in plaats van "4".
int trip(const int P[][4], const int K[], int i, int &totaal)
{
    int min = __INT_MAX__;
    int kleinste = i;

    int kosten = 0;
    for (int j = 0; j < 4; j++)
    {
        if (j != i)
        {
            kosten = 2 * P[i][j] + K[j];
            if (kosten < min)
            {
                min = kosten;
                kleinste = j;
            }
        }
    }
    totaal = min;
    return kleinste;
}

// Vraag 3.b

bool driehoek(const int P[][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            int directeAfstand = P[i][j];
            for (int k = 0; k < 4; k++)
            {
                if (k != i && k != j)
                {
                    int indirecteAfstand = P[i][k] + P[k][j];
                    if (directeAfstand > indirecteAfstand)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Vraag 3.c

int ran()
{
    return rand() % 4;
}

int kosten(const int P[][4], const int K[4], int i)
{
    int totaal = 0;
    bool B[4];
    for (int k = 0; k < 4; k++)
    {
        B[k] = false;
    }
    int j = i;
    while (B[i] == false)
    {
        while (j == i)
        {
            j = ran();
        }
        totaal += P[i][j] + K[j];
        std::cout << "kosten reis: " << P[i][j] << ", kosten overnachting: " << K[j] << ", totaal kosten: " << totaal << std::endl;
        B[i] = true;
        i = j;
    }
    return totaal - K[j];
}

// Vraag 4.a

int main()
{
    srand(time(0));
    int P[][4] = {
        {0, 9, 1, 5},
        {9, 0, 2, 5},
        {1, 2, 0, 3},
        {5, 5, 3, 0}};

    int K[4] = {30, 10, 20, 15};

    int totaal;
    std::cout << kosten(P, K, 2);

    return 0;
}