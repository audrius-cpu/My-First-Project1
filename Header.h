#include <iostream>
#include <iomanip>
#include <string>
#include <deque>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

struct studentas
{
    string vardas, pavarde;
    deque<int> pazymiai;
    int egzaminas;
    double vidurkis, mediana;
};

void generuoti_faila_duomenis(int studentu_skaicius, int pazymiu_skaicius, const string& filename);
void spausdinti_i_faila(const deque<studentas>& tmp, const string& filename);
void vidurkio_radimas(studentas& tmp);
deque<studentas> failo_nuskaitymass(const string& filename);
void medianos_radimas(studentas& tmp);
void pazymiu_nuskaitymas(studentas& tmp);
void studento_nuskaitymas(studentas& tmp);
deque<studentas> failo_nuskaitymas(const string& filename);
void studento_spausdinimas(const deque<studentas>& tmp);
bool studentu_rikiavimas(const studentas& student1, const studentas& student2);
