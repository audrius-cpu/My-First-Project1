#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

struct studentas
{
    string vardas, pavarde;
    vector<int> pazymiai;
    int egzaminas;
    double vidurkis, mediana;
} dab_stud;

void pazymiu_nuskaitymas(studentas& tmp)
{
    string ivesties_metodas;
    cout << "Pasirinkite pazymiu ivedimo metoda ('R' - ranka, 'A' - automatiskai): ";
    cin >> ivesties_metodas;

    if (ivesties_metodas == "R" || ivesties_metodas == "r")
    {
        int paz;
        string nutraukimas;

        do
        {
            cout << "Iveskite studento pazymi[1-10]: ";
            while (!(cin >> paz) || paz > 10 || paz < 1)
            {
                cin.clear();
                cin.ignore();
                cout << "Jusu ivestas skaicius turi buti [1-10]. Bandykite dar karta: ";
            }

            tmp.pazymiai.push_back(paz);

            cout << "Pazymiu vedimo nutraukimas 'N', Tesimas 'Betkoks simbolis': ";
            cin >> nutraukimas;
        } while (nutraukimas != "N" && nutraukimas != "n");
    }
    else if (ivesties_metodas == "A" || ivesties_metodas == "a")
    {
        int rand_kiek;
        cout << "Iveskite pazymiu skaiciu, kuris bus sugeneruotas atsitiktinai: ";
        cin >> rand_kiek;

        for (int i = 0; i < rand_kiek; i++)
        {
            int paz = rand() % 10 + 1;
            cout << paz << " ";
            tmp.pazymiai.push_back(paz);
        }
        cout << endl;
    }
}

void vidurkio_radimas(studentas& tmp)
{
    double sum = 0;

    for (int i = 0; i < tmp.pazymiai.size(); i++)
    {
        sum += tmp.pazymiai[i];
    }

    tmp.vidurkis = sum / tmp.pazymiai.size();
}

void medianos_radimas(studentas& tmp)
{
    sort(tmp.pazymiai.begin(), tmp.pazymiai.end());

    int vidurinis = tmp.pazymiai.size() / 2;
    if (tmp.pazymiai.size() % 2 == 0)
        tmp.mediana = (tmp.pazymiai[vidurinis - 1] + tmp.pazymiai[vidurinis]) / 2.0;
    else
        tmp.mediana = tmp.pazymiai[vidurinis];
}

void studento_nuskaitymas(studentas& tmp)
{
    int egz_paz;

    cout << "Iveskite studento varda ir pavarde: ";
    cin >> tmp.vardas >> tmp.pavarde;
    pazymiu_nuskaitymas(tmp);
    vidurkio_radimas(tmp);
    medianos_radimas(tmp);
    tmp.pazymiai.clear();
    cout << "Iveskite egzamino rezultata: ";

    while (!(cin >> egz_paz) || egz_paz > 10 || egz_paz < 1)
    {
        cin.clear();
        cin.ignore();
        cout << "Jusu ivestas skaicius turi buti [1-10]. Bandykite dar karta: ";
    }

    tmp.egzaminas = egz_paz;
}

void studento_spausdinimas(vector<studentas> tmp)
{
    cout << setw(15) << left << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Gal.vid" << setw(10) << "Gal.med" << endl;
    for (int a = 0; a < 55; a++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < tmp.size(); i++)
    {
        cout << setw(15) << left << tmp[i].vardas << setw(20) << tmp[i].pavarde << setw(10) << fixed << setprecision(2) << 0.4 * tmp[i].vidurkis + 0.6 * tmp[i].egzaminas << setw(10) << setprecision(2) << 0.4 * tmp[i].mediana + 0.6 * tmp[i].egzaminas << endl;
    }
}

int main()
{
    string ivestis;
    vector<studentas> stud;
    srand(time(NULL));

    do
    {
        studento_nuskaitymas(dab_stud);
        stud.push_back(dab_stud);

        cout << "Studentu vedimo nutraukimas 'N', Tesimas 'Betkoks simbolis': ";
        cin >> ivestis;

    } while (ivestis != "n" && ivestis != "N");

    studento_spausdinimas(stud);

    return 0;
}
