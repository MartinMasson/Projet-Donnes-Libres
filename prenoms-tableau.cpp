#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/** Infrastructure minimale de test **/
#define ASSERT(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

vector<vector<string>> tableauTest = {
    { "M", "2011", "Bubulle", "3"},
    { "F", "2012", "Bichette", "4"},
    { "F", "2011", "Babouche", "7"},
    { "F", "2011", "Ziboulette", "1"}
};

/** Affiche le contenu d'un tableau de chaînes à deux dimensions
 * @param tableau un tableau à deux dimensions
 **/
void afficheTableau(vector<vector<string>> tableau)
{
    for(size_t i=0; i<tableau.size(); i++) {
        for(size_t j=0; j<tableau[i].size(); j++) {
            cout << tableau[i][j] << " ";
        }
        cout << endl;
    }
}

void testAfficheTableau() {
    afficheTableau(tableauTest);
}


/** Construction d'un tableau 2D de chaines de caractères lu depuis un fichier
 * @param fichier le nom d'un fichier contenant un nombre fixe
 * de colonnes séparées par des espaces
 * @param nb_colonnes le nombre de colonnes du fichier
 * @return un tableau de chaines de caractères à deux dimensions
 **/
vector<vector<string>> litTableau(string nom_fichier, int nb_colonnes)
{
    ifstream registre;
    registre.open(nom_fichier);
    if (registre.is_open()) {
        vector<vector<string>> TAB = {};
        string data;
        vector<string> tab(nb_colonnes);
        while(registre) {
            for(size_t i=0; i<nb_colonnes; i++) {
                registre >> data;
                tab[i]=data;
            }
            TAB.push_back(tab);
        }
        registre.close();
        TAB.pop_back();
        return TAB;
    } else {
        throw runtime_error("Erreur à l'ouverture du fichier");
    }
}

/** Test de la fonction litTableau **/
void testLitTableau() {
    ASSERT(litTableau("donnees-test.txt", 4) == tableauTest);
    vector<vector<string>> t = litTableau("liste_des_prenoms.txt", 4);
   ASSERT(t.size() == 20453);
    ASSERT(t[0][0] == "M");
    ASSERT(t[5][2] == "Aboubacar");
    ASSERT(t[6][3] == "7");
}

/** Extraction d'une colonne d'un tableau de données
 * @param t un tableau 2D de chaines de caractères
 * @param j un numéro de colonne
 * @return la colonne j, représentée par un vecteur de chaines de caractères
 **/
vector<string> colonne(vector<vector<string>> t, int j)
{
    vector<string> column(t.size());
    for(size_t i=0; i<t.size(); i++) {
        column[i]=t[i][j];
    }
    return column;
}

/** Test de la fonction colonne **/
void testColonne() {
    ASSERT(colonne(tableauTest, 0) == vector<string>({"M","F","F","F"}));
    ASSERT(colonne(tableauTest, 1) == vector<string>({"2011","2012","2011","2011"}));
    ASSERT(colonne(tableauTest, 2) == vector<string>({"Bubulle","Bichette","Babouche","Ziboulette"}));
    ASSERT(colonne(tableauTest, 3) == vector<string>({"3","4","7","1"}));
}

/** Convertit un tableau de chaines de caractères en un tableau d'entiers
 * @param t, un vecteur de chaines de caractères
 * @return un vecteur d'entiers
 **/
vector<int> conversionInt(vector<string> t) {
    vector<int> resultat = vector<int>(t.size());
    for(int i =0; i < t.size(); i++) {
        istringstream(t[i]) >> resultat[i];
    }
    return resultat;
}

void testConversionInt() {
    ASSERT(conversionInt({}) == vector<int>({}));
    ASSERT(conversionInt({"1","2","3"}) == vector<int>({1,2,3}));
}

/** copier la fonction somme déjà écrite **/
int somme(vector<int> t)
{
    int total=0;
    for(size_t i=0; i<t.size(); i++)
        total+=t[i];
    return total;
}

/** copier la fonction moyenne déjà écrite **/
int moyenne(vector<int> t)
{
    int average;
    for(size_t i=0; i<t.size(); i++)
        average=somme(t)/t.size();
    return average;
}

/** copier la fonction indiceMax déjà écrite **/
int indiceMax(vector<int> t)
{
    if(t.size()!=0) {
        int max_value=0;
        int max_value_index=0;
        for(size_t i=0; i<t.size(); i++) {
            if(max_value<t[i]) {
                max_value=t[i];
                max_value_index=i;
            }
        }
        return max_value_index;
    } else {
        return -1;
    }
}

/** Sélection des lignes d'un tableau de données
 * Sélectionne un ensemble de lignes en fonction d'un critère donné
 * @param t, un tableau contenant des lignes de données
 * @param j, l'indice de la colonne à vérifier
 * @param valeur, une chaine de caractères correspondant au critère
 * @return un tableau de données ne contenant que les lignes de t telles
 *  que la colonne j ait la valeur correspondant au critère
 **/
vector<vector<string>> selectLignes(vector<vector<string>> t, int j, string valeur)
{
    vector<vector<string>> lines = {};
    vector<string> column_index = colonne(t, j);
    for(size_t i=0; i<column_index.size(); i++) {
        if(column_index[i]==valeur) {
            lines.push_back(t[i]);
        }
    }
    return lines;
}

/** Test de la fonction selectLignes **/
void testSelectLignes() {
    ASSERT(selectLignes(tableauTest, 0, "M") == vector<vector<string>>({{ "M", "2011", "Bubulle", "3"}}));
    ASSERT(selectLignes(tableauTest, 1, "2011") == vector<vector<string>>({{ "M", "2011", "Bubulle", "3"}, { "F", "2011", "Babouche", "7"}, { "F", "2011", "Ziboulette", "1"}}));
}

/** Lance les tests de litTableau, selectLignes et colonne puis
 * affiche le nombre total de naissances puis
 * demande à l'utilisateur un prénom et calcule et affiche
 * - le nombre de garçons et filles à qui l'on a donné ce prénom
 * - la meilleure année pour ce prénom pour les garçons et filles
 **/
int main()
{
    testLitTableau();
    testColonne();
    testSelectLignes();
    string user_name;
    int total_birth = somme(conversionInt(colonne(litTableau("liste_des_prenoms.txt", 4), 3)));
    cout << "Nombre total de naissances : " << total_birth << endl
    << "Choisissez un prénom : ";
    cin >> user_name;
    vector<vector<string>> birth_M_tab = selectLignes(selectLignes(litTableau("liste_des_prenoms.txt", 4), 2, user_name), 0, "M");
    vector<vector<string>> birth_F_tab = selectLignes(selectLignes(litTableau("liste_des_prenoms.txt", 4), 2, user_name), 0, "F");
    if (somme(conversionInt(colonne(birth_M_tab, 3)))==0) {
        cout << "Le prénom " << user_name << " n'a été donné à aucun garçon entre 2004 et 2019" << endl;
    } else {
        cout << "Le prénom " << user_name << " a été donné à " << somme(conversionInt(colonne(birth_M_tab, 3))) << " garçons entre 2004 et 2019" << endl
        << "L'année la plus forte est " << colonne(birth_M_tab, 1)[indiceMax(conversionInt(colonne(birth_M_tab, 3)))] << " avec "
        << colonne(birth_M_tab, 3)[indiceMax(conversionInt(colonne(birth_M_tab, 3)))] << " enfants" << endl;
    }
    if (somme(conversionInt(colonne(birth_F_tab, 3)))==0) {
        cout << "Le prénom " << user_name << " n'a été donné à aucune fille entre 2004 et 2019" << endl;
    } else {
        cout << "Le prénom " << user_name << " a été donné à " << somme(conversionInt(colonne(birth_F_tab, 3))) << " filles entre 2004 et 2019" << endl
        << "L'année la plus forte est " << colonne(birth_F_tab, 1)[indiceMax(conversionInt(colonne(birth_F_tab, 3)))] << " avec "
        << colonne(birth_F_tab, 3)[indiceMax(conversionInt(colonne(birth_F_tab, 3)))] << " enfants" << endl;
    }
}
