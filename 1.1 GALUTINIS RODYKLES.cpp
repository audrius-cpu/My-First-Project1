#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

struct studentas
{
    string vardas, pavarde;
    int* pazymiai;
    int pazymiu_kiekis;
    int egzaminas;
    double vidurkis, mediana;
};

void pazymiu_nuskaitymas(studentas& tmp)
{
    string ivestis;
    cout << "Pasirinkite pazymiu ivedimo metoda ('R' - ranka, 'A' - automatiskai): ";
    cin >> ivestis;

    if (ivestis == "R" || ivestis == "r")
    {
        int paz;
        string nutraukimas;

        tmp.pazymiai = new int[1];
        tmp.pazymiu_kiekis = 0;
        int talpa = 1;

        do
        {
            cout << "Iveskite studento pazymi[1-10]: ";
            while (!(cin >> paz) || paz > 10 || paz < 1)
            {
                cin.clear();
                cin.ignore();
                cout << "Jusu ivestas skaicius turi buti [1-10]. Bandykite dar karta: ";
            }

            if (tmp.pazymiu_kiekis == talpa)
            {
                talpa *= 2;
                int* nauji_pazymiai = new int[talpa];
                for (int i = 0; i < tmp.pazymiu_kiekis; i++)
                    nauji_pazymiai[i] = tmp.pazymiai[i];
                delete[] tmp.pazymiai;
                tmp.pazymiai = nauji_pazymiai;
            }

            tmp.pazymiai[tmp.pazymiu_kiekis] = paz;
            tmp.pazymiu_kiekis++;

            cout << "Pazymiu vedimo nutraukimas 'N', Tesimas 'Betkoks simbolis': ";
            cin >> nutraukimas;
        } while (nutraukimas != "N" && nutraukimas != "n");
    }
    else if (ivestis == "A" || ivestis == "a")
    {
        int rand_kiekis;
        cout << "Iveskite pazymiu skaiciu, kuris bus sugeneruotas atsitiktinai: ";
        cin >> rand_kiekis;

        tmp.pazymiai = new int[rand_kiekis];
        tmp.pazymiu_kiekis = rand_kiekis;

        for (int i = 0; i < rand_kiekis; i++)
        {
            int paz = rand() % 10 + 1;
            cout << paz << " ";
            tmp.pazymiai[i] = paz;
        }
        cout << endl;
    }
}

void vidurkio_radimas(studentas& tmp)
{
    double sum = 0;

    for (int i = 0; i < tmp.pazymiu_kiekis; i++)
    {
        sum += tmp.pazymiai[i];
    }

    tmp.vidurkis = sum / tmp.pazymiu_kiekis;
}

void medianos_radimas(studentas& tmp)
{
    sort(tmp.pazymiai, tmp.pazymiai + tmp.pazymiu_kiekis);

    int vidurinis = tmp.pazymiu_kiekis / 2;
    if (tmp.pazymiu_kiekis % 2 == 0)
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
    delete[] tmp.pazymiai;
    tmp.pazymiai = nullptr;
    cout << "Iveskite egzamino rezultata: ";

    while (!(cin >> egz_paz) || egz_paz > 10 || egz_paz < 1)
    {
        cin.clear();
        cin.ignore();
        cout << "Jusu ivestas skaicius turi buti [1-10]. Bandykite dar karta: ";
    }

    tmp.egzaminas = egz_paz;
}

void studento_spausdinimas(studentas* tmp, int kiekis)
{
    cout << setw(15) << left << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Gal.vid" << setw(10) << "Gal.med" << endl;
    for (int a = 0; a < 55; a++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < kiekis; i++)
    {
        cout << setw(15) << left << tmp[i].vardas << setw(20) << tmp[i].pavarde << setw(10) << fixed << setprecision(2) << 0.4 * tmp[i].vidurkis + 0.6 * tmp[i].egzaminas << setw(10) << setprecision(2) << 0.4 * tmp[i].mediana + 0.6 * tmp[i].egzaminas << endl;
    }
}

int main()
{
    string ivestis;
    int kiekis = 0;
    studentas* stud = nullptr;
    srand(time(NULL));

    do
    {
        studentas dab_stud;
        studento_nuskaitymas(dab_stud);
        kiekis++;

        studentas* naujas_stud = new studentas[kiekis];
        for (int i = 0; i < kiekis - 1; i++)
            naujas_stud[i] = stud[i];
        naujas_stud[kiekis - 1] = dab_stud;
        delete[] stud;
        stud = naujas_stud;

        cout << "Studentu vedimo nutraukimas 'N', Tesimas 'Betkoks simbolis': ";
        cin >> ivestis;

    } while (ivestis != "n" && ivestis != "N");

    studento_spausdinimas(stud, kiekis);

    delete[] stud;
    return 0;
}
