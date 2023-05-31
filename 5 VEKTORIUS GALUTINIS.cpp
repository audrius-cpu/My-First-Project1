#include "Header.h"

int main()
{
    vector<studentas> stud;
    vector<studentas> geri;
    vector<studentas> blogi;
    srand(time(NULL));
    studentas dab_stud;

    string ivestis;
    bool tinkama_ivestis = false;

    while (!tinkama_ivestis)
    {
        cout << "Pasirinkite pazymiu ivedimo metoda ('R' - ranka, 'F' - failas, 'G' - generavimas): ";
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
            studento_spausdinimas(stud);
            tinkama_ivestis = true;
        }
        if (ivestis == "G" || ivestis == "g")
        {
            int studentu_skaicius;
            int pazymiu_skaicius;
            string generuoto_failo_pavadinimas;

            cout << "Iveskite pavadinima, kuriame bus sugeneruoti duomenys: "; cin >> generuoto_failo_pavadinimas;
            cout << "Iveskite studentu skaiciu, kuris bus sugeneruotas: "; cin >> studentu_skaicius;
            cout << "Iveskite pazmymiu skaiciu, kuris bus sugeneruotas: "; cin >> pazymiu_skaicius;

            generuoti_faila_duomenis(studentu_skaicius, pazymiu_skaicius, generuoto_failo_pavadinimas);
            stud = failo_nuskaitymas(generuoto_failo_pavadinimas);
            tinkama_ivestis = true;
        }
        else if (ivestis == "F" || ivestis == "f")
        {
            string file_name;
            cout << "Iveskite failo pavadinima: ";
            cin >> file_name;

            stud = failo_nuskaitymass(file_name);
            studento_spausdinimas(stud);

            if (!stud.empty())
                tinkama_ivestis = true;
            else
                cout << "Failas neegzistuoja arba yra tuscias. Bandykite dar karta." << endl;
        }
        else
        {
            cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
        }
    }

    return 0;
}
