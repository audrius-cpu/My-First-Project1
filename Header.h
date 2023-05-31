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
#include <chrono>

using namespace std;

class studentas
{
    private:

    string vardas, pavarde;
    int egzaminas;
    double vidurkis, mediana;

    public:

        vector<int> pazymiai;

        inline string vardo_nuskaitymas() const { return vardas; };
        inline string pavardes_nuskaitymas() const { return pavarde; };
        inline int egzamino_nuskaitymas() const { return egzaminas; };
        inline double vidurkio_nuskaitymas() const { return vidurkis; };
        inline double medianos_nuskaitymas() const { return mediana; };
        const vector<int> pazymiu_nuskaitymas() const { return pazymiai; };

        void vardo_nustatymas(string vardas) { this->vardas = vardas; };
        void pavardes_nustatymas(string pavarde) { this->pavarde = pavarde; };
        void vidurkio_nustatymas(double vidurkis) { this->vidurkis = vidurkis; };
        void medianos_nustatymas(double mediana) { this->mediana = mediana; };
        void egzamino_nustatymas(int egzaminas) { this->egzaminas = egzaminas; };
        void pazymiu_nustatymas(vector<int> pazymiai) { this->pazymiai = pazymiai; };
        void sortGrades() { sort(pazymiai.begin(), pazymiai.end()); };
};

void generuoti_faila_duomenis(int studentu_skaicius, int pazymiu_skaicius, const string& filename);
void spausdinti_i_faila(const vector<studentas>& tmp, const string& filename);
void vidurkio_radimas(studentas& tmp);
vector<studentas> failo_nuskaitymas1(const string& filename);
void medianos_radimas(studentas& tmp);
void pazymiu_nuskaitymas(studentas& tmp);
void studento_nuskaitymas(studentas& tmp);
vector<studentas> failo_nuskaitymas2(const string& filename);
void studento_spausdinimas(const vector<studentas>& tmp);
vector<studentas> failo_nuskaitymas3(const string& filename);
