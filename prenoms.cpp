#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

/** Calcule et affiche le prénom le plus utilisé une année donnée
 * ainsi que le nombre de naissances cette année là **/
int main()
{
    ifstream registre;
    registre.open("liste_des_prenoms.txt");
    if (registre.is_open()) {
        string sex;
        int year;
        string name;
        int birth;
        int user_year;
        int total_birth;
        int most_birth=0;
        string most_given_name;
        cout << "Entrez une année entre 2004 et 2019 : ";
        cin >> user_year;
        while (registre >> sex and registre >> year and registre >> name and registre >> birth) {
            if (user_year == year) {
                total_birth += birth;
                if (most_birth < birth) {
                    most_birth = birth;
                    most_given_name = name;
                }
            }
        }
        cout << "En " << user_year << ", il y a eu " << total_birth << " naissances" << endl;
        cout << "Le prénom le plus donné a été : " << most_given_name << " (donné " << most_birth << " fois)" << endl;
        registre.close();
    } else {
        throw runtime_error("Erreur à l'ouverture du fichier");
    }
}