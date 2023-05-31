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

class human {
protected:
    string vardas;
    string pavarde;

public:
    human(const string& vardas, const string& pavarde)
        : vardas(vardas), pavarde(pavarde) {}

    virtual void saySomething() const = 0; 

    string vardo_nuskaitymas() const { return vardas; }
    string pavardes_nuskaitymas() const { return pavarde; }

    void vardo_nustatymas(const string& vardas) { this->vardas = vardas; }
    void pavardes_nustatymas(const string& pavarde) { this->pavarde = pavarde; }
};

class studentas : public human {
private:
    int egzaminas;
    double vidurkis, mediana;

public:
    vector<int> pazymiai;
    studentas() : human("", ""), egzaminas(0), vidurkis(0), mediana(0) {}

    void saySomething() const override {
        cout << "I am a student named " << vardas << " " << pavarde << endl;
    }

    int egzamino_nuskaitymas() const { return egzaminas; }
    double vidurkio_nuskaitymas() const { return vidurkis; }
    double medianos_nuskaitymas() const { return mediana; }
    const vector<int> pazymiu_nuskaitymas() const { return pazymiai; }

    void vidurkio_nustatymas(double vidurkis) { this->vidurkis = vidurkis; }
    void medianos_nustatymas(double mediana) { this->mediana = mediana; }
    void egzamino_nustatymas(int egzaminas) { this->egzaminas = egzaminas; }
    void pazymiu_nustatymas(const vector<int>& pazymiai) { this->pazymiai = pazymiai; }
    void sortGrades() { sort(pazymiai.begin(), pazymiai.end()); }
    
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
