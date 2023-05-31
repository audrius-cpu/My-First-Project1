#include"Header.h"

bool studentu_rikiavimas(const studentas& student1, const studentas& student2) {
    if (student1.vardas != student2.vardas) {
        return student1.vardas < student2.vardas;
    }
    return student1.pavarde < student2.pavarde;
}

void generuoti_faila_duomenis(int studentu_skaicius, int pazymiu_skaicius, const string& filename) {

    ofstream file(filename);

    if (file.is_open()) {
        file << setw(15) << left << "Vardas" << setw(15) << left << "Pavarde";
        for (int i = 1; i <= pazymiu_skaicius; i++) {
            file << setw(10) << left << "Pazymys" + to_string(i);
        }
        file << setw(10) << left << "Egzaminas" << endl;

        for (int i = 1; i <= studentu_skaicius; i++) {
            file << setw(15) << left << "Vardas" + to_string(i) << setw(15) << left << "Pavarde" + to_string(i);
            for (int j = 1; j <= pazymiu_skaicius; j++) {
                file << setw(10) << left << to_string(rand() % 10 + 1);
            }
            file << setw(10) << left << to_string(rand() % 10 + 1) << endl;
        }

        file.close();
        cout << "Failas su duomenimis sugeneruotas: " << filename << endl;
    }
    else {
        cout << "Nepavyko atidaryti failo: " << filename << endl;
    }

}


void spausdinti_i_faila(const std::list<studentas>& tmp, const string& filename)
{
    ofstream file(filename);

    if (file.is_open())
    {
        file << setw(15) << left << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Gal.vid" << setw(10) << "Gal.med" << endl;
        for (int a = 0; a < 55; a++)
            file << "-";
        file << endl;

        for (const auto& student : tmp)
        {
            file << setw(15) << left << student.vardas << setw(20) << student.pavarde << setw(10) << fixed << setprecision(2) << 0.4 * student.vidurkis + 0.6 * student.egzaminas << setw(10) << setprecision(2) << 0.4 * student.mediana + 0.6 * student.egzaminas << endl;
        }

        file.close();
        cout << "Duomenys issaugoti faile: " << filename << endl;
    }
    else
    {
        cout << "Nepavyko atidaryti failo: " << filename << endl;
    }
}

void vidurkio_radimas(studentas& tmp)
{
    double sum = 0;

    if (tmp.pazymiai.empty())
    {
        tmp.vidurkis = 0;
        return;
    }

    for (const auto& pazymys : tmp.pazymiai)
    {
        sum += pazymys;
    }

    tmp.vidurkis = sum / tmp.pazymiai.size();
}

std::list<studentas> failo_nuskaitymass(const string& filename)
{
    std::list<studentas> students;
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
                    student.pazymiai.emplace_back(pazymys);
                }

                if (!student.pazymiai.empty()) {
                    student.egzaminas = student.pazymiai.back();
                    student.pazymiai.pop_back();
                }

                vidurkio_radimas(student);
                medianos_radimas(student);
                students.emplace_back(student);
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

void medianos_radimas(studentas& tmp)
{
    if (tmp.pazymiai.empty())
    {
        tmp.mediana = 0;
        return;
    }

    tmp.pazymiai.sort();

    int vidurinis = tmp.pazymiai.size() / 2;
    auto it = tmp.pazymiai.begin();
    std::advance(it, vidurinis);

    if (tmp.pazymiai.size() % 2 == 0) {
        int pazymys1 = *std::prev(it);
        int pazymys2 = *it;
        tmp.mediana = (pazymys1 + pazymys2) / 2.0;
    }
    else {
        tmp.mediana = *it;
    }
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

            tmp.pazymiai.emplace_back(paz);

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
            tmp.pazymiai.emplace_back(paz);
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

list<studentas> failo_nuskaitymas(const string& filename)
{
    auto start = chrono::steady_clock::now();
    list<studentas> students;
    list<studentas> geri;
    list<studentas> blogi;
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
                    student.pazymiai.push_front(pazymys);
                }

                if (!student.pazymiai.empty()) {
                    student.egzaminas = student.pazymiai.front();
                    student.pazymiai.pop_front();
                }

                vidurkio_radimas(student);
                medianos_radimas(student);
                students.push_front(student);
            }

            auto endReading = chrono::steady_clock::now();
            auto durationReading = chrono::duration_cast<chrono::seconds>(endReading - start);
            cout << "Laikas nuo pradzios iki skaitymo pabaigos + vidurkis + mediana: " << durationReading.count() << " s" << endl;

            auto startSorting = std::chrono::steady_clock::now();
            students.sort(studentu_rikiavimas);
            auto endSorting = std::chrono::steady_clock::now();
            auto durationSorting = std::chrono::duration_cast<std::chrono::seconds>(endSorting - startSorting);
            std::cout << "Laikas vykdant studentu rikiavima: " << durationSorting.count() << " seconds" << std::endl;
            file.close();

            auto startGrouping = chrono::steady_clock::now();
            for (const auto& student : students) {
                if (0.4 * student.vidurkis + 0.6 * student.egzaminas < 5)
                    blogi.push_front(student);
                else if (0.4 * student.vidurkis + 0.6 * student.egzaminas >= 5)
                    geri.push_front(student);
            }
            auto endGrouping = chrono::steady_clock::now();
            auto durationGrouping = chrono::duration_cast<chrono::seconds>(endGrouping - startGrouping);
            cout << "Laikas vykdant studentu grupavima: " << durationGrouping.count() << " s" << endl;

            spausdinti_i_faila(geri, "angelai");
            spausdinti_i_faila(blogi, "demonai");
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

void studento_spausdinimas(const list<studentas>& tmp)
{
    cout << setw(15) << left << "Vardas" << setw(20) << "Pavarde" << setw(10) << "Gal.vid" << setw(10) << "Gal.med" << endl;
    for (int a = 0; a < 55; a++)
        cout << "-";
    cout << endl;

    for (const auto& student : tmp)
    {
        cout << setw(15) << left << student.vardas << setw(20) << student.pavarde << setw(10) << fixed << setprecision(2) << 0.4 * student.vidurkis + 0.6 * student.egzaminas << setw(10) << setprecision(2) << 0.4 * student.mediana + 0.6 * student.egzaminas << endl;
    }
}
