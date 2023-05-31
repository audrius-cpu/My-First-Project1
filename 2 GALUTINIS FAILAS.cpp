#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <sstream>

using namespace std;

struct studentas
{
    string vardas, pavarde;
    vector<int> pazymiai;
    int egzaminas;
    double vidurkis, mediana;
} dab_stud;

bool studentu_rikiavimas(const studentas& a, const studentas& b)
{
    return a.vardas < b.vardas;
}

void vidurkio_radimas(studentas& tmp)
{
    double sum = 0;

    if (tmp.pazymiai.empty())
    {
        tmp.vidurkis = 0;
        return;
    }

    for (int i = 0; i < tmp.pazymiai.size(); i++)
    {
        sum += tmp.pazymiai[i];
    }

    tmp.vidurkis = sum / tmp.pazymiai.size();
}

void medianos_radimas(studentas& tmp)
{
    if (tmp.pazymiai.empty())
    {
        tmp.mediana = 0;
        return;
    }

    sort(tmp.pazymiai.begin(), tmp.pazymiai.end());

    int vidurinis = tmp.pazymiai.size() / 2;
    if (tmp.pazymiai.size() % 2 == 0)
        tmp.mediana = (tmp.pazymiai[vidurinis - 1] + tmp.pazymiai[vidurinis]) / 2.0;
    else
        tmp.mediana = tmp.pazymiai[vidurinis];
}

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

vector<studentas> failo_nuskaitymas(const string& filename)
{
    vector<studentas> students;
    ifstream file(filename);

    if (file.is_open()) {
        string antraste;
        getline(file, antraste);

        string line;
        while (getline(file, line))
        {
            studentas student;
            istringstream iss(line);
            string vardas, pavarde;
            iss >> vardas >> pavarde;

            student.vardas = vardas;
            student.pavarde = pavarde;

            int grade;
            while (iss >> grade)
            {
                student.pazymiai.push_back(grade);
            }

            if (!student.pazymiai.empty()) {
                student.egzaminas = student.pazymiai.back();
                student.pazymiai.pop_back();
            }

            vidurkio_radimas(student);
            medianos_radimas(student);
            students.push_back(student);
        }

        file.close();
    }
    else {
        cout << "Nepavyko atidaryti failo : " << filename << endl;
    }

    return students;
}

void studento_spausdinimas(const vector<studentas>& tmp)
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
    vector<studentas> stud;
    srand(time(NULL));

    string ivestis;
    bool validInput = false;

    while (!validInput)
    {
        cout << "Pasirinkite pazymiu ivedimo metoda ('R' - ranka, 'F' - failas): ";
        cin >> ivestis;

        if (ivestis == "R" || ivestis == "r")
        {
            do
            {
                studento_nuskaitymas(dab_stud);
                stud.push_back(dab_stud);

                cout << "Studentu vedimo nutraukimas 'N', Tesimas 'Betkoks simbolis': ";
                cin >> ivestis;

            } while (ivestis != "n" && ivestis != "N");

            validInput = true;
        }
        else if (ivestis == "F" || ivestis == "f")
        {
            string file_name;

            cout << "Iveskite failo pavadinima: ";
            cin >> file_name;

            stud = failo_nuskaitymas(file_name);

            if (!stud.empty())
                validInput = true;
            else
                cout << "Failas neegzistuoja arba yra tuscias. Bandykite dar karta." << endl;
        }
        else
        {
            cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
        }
    }
    sort(stud.begin(), stud.end(), studentu_rikiavimas);

    studento_spausdinimas(stud);

    return 0;
}
