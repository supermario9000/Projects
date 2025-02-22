#include <iostream>
#include <iomanip>

using namespace std;

void in(int& n, int& k, int& wid)//ivedimas
{
    cout << "Iveskite norima atsitiktinai sugeneruotu skaiciu kieki:";
    cin >> n;
    cout << endl;
    cout << "Iveskite norima sugeneruoto skaiciaus maksimalia verte:";//nezinau ar veiks, galbut reiks pasalinti
    cin >> k;
    cout << "\n" << endl;
    int temp = n;//sukuriu laikina n kintamaji, kuris pades suskaiciuot langeliu ploti
    wid = 0;
    while (temp > 0)
    {
        temp /= 10;
        wid++;//kintamaji naudosiu ekrano void funkcijoje nustatant langelio ploti
    }
    wid = max(wid, 2);
}

//atsitiktinai sugeneruoju reiksmes, ekrano parametrus darysiu pagal pasirenkama skaiciu diapazona
void ran(int n, int k, int A[])//atsitiktiniu sk. generavimas i A masyva
{
    unsigned int seed;//sukuriu trumpalaiki kintamaji, kurio - reiksmes perkeltos i pozityvias. naudosiu ji kaip atsitiktinumo pagrinda
    cout << "Iveskite bet kokia skaiciu kombinacija:";
    cin >> seed;
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        //trumpalaiki kintamaji vis keiciu cikle for
        seed = (seed * 1103515245 + 12345) & 0x7fffffff;//duoti skaiciai - daznai naudojamos konstantos atsitiktinumo algoritmuose
        //&-bitinis operatorius, pritaikantis gauta skaiciu prie 0x7ff..., kuris yra didziausias imanomas 31 bito int tipo kintamojo reiksmes
        int rand = 1 + seed % k;//salyga, kuri padaro, kad skaicius nebutu per didelis. 
        A[i] = rand;
    }
}

void ekranas(int n, int k, int A[], char E[], int wid)//sukuriame lentele
{
    cout << "Verte" << endl;
    for (int i = 0; i < k; i++)
    {
        cout << setw(wid) << k - i << " ";
        for (int j = 0; j < n; j++)
        {
            if (i == A[j] - 1) E[i * n + j] = 'O'; //elementas sutapo su duotais duomenimis, ekrane jo pozicijoje rodau O
            else E[i * n + j] = '-'; //kiekvienam tusciam lenteles elementui priskiriu -
            cout << setw(wid) << E[i * n + j] << " ";
        }
        cout << endl;
    }
    cout << "   ";
    for (int i = 1; i <= n; i++) cout << setw(wid) << i << " ";
    cout << " Eiles nr." << "\n\n" << endl;//pasidarau vietos, kad vizualiai atrodytu maloniau darant kitus veiksmus
}

void pasirinkimas(int n, int k, int A[], char E[], int wid)
{
    int veil, vst, aeil, ast;
    cout << "Is grafiko galite rinktis istraukti kvadrato formos duomenu lentele." << endl;
    cout << "PVZ: virsutinio tasko koordinates: eil=8, st=2; apatinio tasko koordinates: eil=3, st=4" << endl;
    cout << "\n" << "Iveskite norimu duomenu lenteles kairio virsutinio ir desinio apatinio kampu koordinates (eil,st):" << endl;
    cin >> veil >> vst >> aeil >> ast;
    //nusikopijuoju ekrano funkcija, tik sikart generuoju butent pasirinktu skaiciu kvadraciuka.

    cout << '\n' << "Verte" << endl;
    for (int i = veil; i >= aeil; i--)
    {
        cout << setw(wid) << i << " ";
        for (int j = vst; j <= ast; j++)
        {
            cout << setw(wid) << E[(k - i) * n + (j - 1)] << " ";//k-i grazina teisinga i kintamojo eiliskuma, j-1 padaro, kad jo indeksas prasidetu nuo 0
        }
        cout << endl;
    }
    cout << "   ";
    for (int i = vst; i <= ast; i++) cout << setw(wid) << i << " ";
    cout << " Eiles nr." << "\n\n" << endl;//pasidarau vietos, kad vizualiai atrodytu maloniau darant kitus veiksmus

    //lenteles dali darau cia, nes kitoje funkcijoje reiktu is naujo deklaruoti veil ir t.t.
    cout << "Lentele:" << '\n' << "Eil.Nr.   " << "Verte" << '\n';
    for (int i = veil; i >= aeil; i--)
    {
        for (int j = vst; j <= ast; j++)
        {
            if (E[(k - i) * n + (j - 1)] == 'O') cout << setw(2)<< j << setw(10) << i << endl;
        }
    }
}

int main()
{
    int n, k, wid;
    in(n, k, wid);
    char* E = new char[n * k];//apsirasau masyva, kuris nepriklauso nuo konstantu, kad galeciau jo apimti nustatyti pagal ivesti
    int* A = new int[n];//skiriu jam tiek atminties
    ran(n, k, A);
    ekranas(n, k, A, E, wid);
    char p;
    cout << "Ar noretumete pasirinkti tam tikrus duomenis is grafiko? (y/n):";
    cin >> p;
    cout << endl;
    if (p == 'n') cout << "Aciu, kad isbandete mano programa!" << endl;
    else pasirinkimas(n, k, A, E, wid);
    delete[] E;//istrinu ekrana is atminties, kad neuzimtu vietos
    delete[] A;
    char z;
    cout << "Ar patiko? (y/n):";
    cin >> z;
    return 0;
}

/*
Uzduotys:

Sukurti ekrana/lentele , kurioje butu pavaizduoti taskai. PADARYTA
Leisti pasirinkti tam tikrus duomenis PADARYTA
Suvesti viska i lentele, kurioje butu iskeltu tasku indeksai ir reiksmes PADARYTA
lentele PADARYTA

mastelis (sumazinti ekranus tokius, kurie netelpa i tvarkinga lentele/ padidinti masteli)
ideja del mastelio:
if(n/10>=10) x++;=wid
if(k/10>=10) y++;
idet i loopa is suskaiciuot kiek kartu galim sumazinti. tuomet 10x10 langeliu galesim paversti i 1x1.
NEPADARYTA
*/