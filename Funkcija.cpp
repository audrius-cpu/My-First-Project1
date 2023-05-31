#include"Header.h"

void vidurkio_radimas(studentas & tmp)
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

    try {
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

                int pazymys;
                while (iss >> pazymys)
                {
                    student.pazymiai.push_back(pazymys);
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
            throw runtime_error("Nepavyko atidaryti failo: " + filename);
        }
    }
    catch (const exception& e) {
        cout << "Klaida: " << e.what() << endl;
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
