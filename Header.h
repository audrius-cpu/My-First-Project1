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
};

void vidurkio_radimas(studentas& tmp);
void medianos_radimas(studentas& tmp);
void pazymiu_nuskaitymas(studentas& tmp);
void studento_nuskaitymas(studentas& tmp);
vector<studentas> failo_nuskaitymas(const string& filename);
void studento_spausdinimas(const vector<studentas>& tmp);

