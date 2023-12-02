#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cassert>

struct ValeurTrouve {
    std::size_t index;
    char valeur;

    ValeurTrouve(std::size_t emplacement, char caractere)
    {
        index = emplacement;
        valeur = caractere;
    }
};

const static std::unordered_map<std::string, char> chiffres{
    {"one", '1'},
    { "two", '2' },
    { "three", '3' },
    { "four", '4' },
    { "five", '5' },
    { "six", '6' },
    { "seven", '7' },
    { "eight", '8' },
    { "nine", '9' },
    { "1", '1' },
    { "2", '2' },
    { "3", '3' },
    { "4", '4' },
    { "5", '5' },
    { "6", '6' },
    { "7", '7' },
    { "8", '8' },
    { "9", '9' }
};

int parse(const std::string& ligne)
{
    std::stringstream conversion {ligne};
    int retour;
    if (!(conversion >> retour))
        retour = 0;
    return retour;
}

std::string valeursSelonLigne(const std::string& ligne)
{
    std::string valeurs;
    std::vector<ValeurTrouve> valeursTrouvees;
    for (auto& chiffre : chiffres)
    {
        for (std::size_t i{ ligne.find(chiffre.first)}; i != chiffre.first.npos; i = ligne.find(chiffre.first, i + 1))
        {
            valeursTrouvees.push_back(ValeurTrouve(i, chiffre.second));
        }
    }
    std::sort(valeursTrouvees.begin(), valeursTrouvees.end(),
        [](const ValeurTrouve& a, const ValeurTrouve& b)
        {
            return a.index < b.index; 
        });
    valeurs.reserve(valeursTrouvees.size());
    for (auto& valeur : valeursTrouvees)
    {
		valeurs.push_back(valeur.valeur);
	}
   
    return valeurs;
}

int main()
{
    std::fstream fichier {"donnees.txt"};
    std::vector<std::string> exemple;
    while (fichier)
    {
        std::string ligne;
        fichier >> ligne;
        exemple.push_back(ligne);
    }
    
    std::vector<int> valeursExemple;
    for (auto& ligne : exemple)
    {
        std::string valeurLigne = valeursSelonLigne(ligne);
        std::string total;
        if (!valeurLigne.empty())
        {
            total += valeurLigne[0];
            total += valeurLigne[valeurLigne.size() - 1];
        }
        valeursExemple.push_back(parse(total));
    }
    int resultat{0};
    for (int valeur : valeursExemple)
    {
        resultat += valeur;
    }
    std::cout << "Le resultat est de " << resultat;
}