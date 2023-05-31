#include "Header.h"

int main()
{
    vector<studentas> stud;
    srand(time(NULL));
    studentas dab_stud;

    string ivestis;
    bool tinkama_ivestis = false;

    while (!tinkama_ivestis)
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

            tinkama_ivestis = true;
        }
        else if (ivestis == "F" || ivestis == "f")
        {
            string file_name;

            cout << "Iveskite failo pavadinima: ";
            cin >> file_name;

            stud = failo_nuskaitymas(file_name);

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

    studento_spausdinimas(stud);

    return 0;
}
