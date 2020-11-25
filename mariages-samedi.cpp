#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/** Calcule et affiche le nombre de mariages un samedi entre 2010 et 2015 **/
int main()
{
    ifstream registre;
    registre.open("statistiques-des-jours-des-mariages.txt");
    if (registre.is_open()) {
        int year;
        string day;
        int wedding;
        int total;
        while (registre >> year and registre >> day and registre >> wedding)
            if (day=="Samedi")
                total += wedding;
        cout << total << endl;
        registre.close();
    } else {
        throw runtime_error("Erreur à l'ouverture du fichier");
    }
}