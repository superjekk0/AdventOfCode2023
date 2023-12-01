// jour1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_map>
#include <algorithm>

struct ValeurTrouve {
    std::size_t index;
    char aTrouver;

    ValeurTrouve(std::size_t emplacement, char caractere)
    {
        index = emplacement;
        aTrouver = caractere;
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
    { "nine", '9' }
};

bool contientDebutChiffre(const std::string& chaine)
{
    if (chaine[0] == 'o' && chaine.size() < 4)
        return true;
    else if (chaine[0] == 't' && chaine.size() < 6)
        return true;
    else if (chaine[0] == 'f' && chaine.size() < 5)
        return true;
    else if (chaine[0] == 's' && chaine.size() < 6)
        return true;
    else if (chaine[0] == 'e' && chaine.size() < 6)
        return true;
    else if (chaine[0] == 'n' && chaine.size() < 5)
        return true;
    else
        return false;
}

std::vector<ValeurTrouve> valeurDebutChiffreLettre(const std::string& chaine, int debutScan)
{
    std::vector<ValeurTrouve> valeurs;

    valeurs.push_back(ValeurTrouve(chaine.find('o', debutScan), 'o'));
    valeurs.push_back(ValeurTrouve(chaine.find('t', debutScan), 't'));
    valeurs.push_back(ValeurTrouve(chaine.find('f', debutScan), 'f'));
    valeurs.push_back(ValeurTrouve(chaine.find('s', debutScan), 's'));
    valeurs.push_back(ValeurTrouve(chaine.find('e', debutScan), 'e'));
    valeurs.push_back(ValeurTrouve(chaine.find('n', debutScan), 'n'));
    
    return valeurs;
}

int parse(const std::string& ligne)
{
    std::stringstream conversion {ligne};
    int retour;
    if (!(conversion >> retour))
        retour = 0;
    return retour;
}

int parse(char lettre)
{
    std::stringstream conversion {lettre};
    int valeurRetour;
    if (!(conversion >> valeurRetour))
        valeurRetour = 0;
    return valeurRetour;
}

char chiffreEnLettre(std::string& texte)
{
    if (!chiffres.contains(texte))
        return '0';
    switch (chiffres.at(texte))
    {
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return chiffres.at(texte);
    default:
        return '0';
        break;
    }
}

std::vector<char> valeursSelonLigne(const std::string& ligne)
{
    std::vector<char> valeurs;
    std::string valeurComplexe {""};
    for (int i{ 0 }; i < ligne.size(); ++i)
    {
        if (std::isdigit(ligne[i]))
        {
            valeurs.push_back(ligne[i]);
            valeurComplexe = "";
        }
        else
        { 
            valeurComplexe += ligne[i];
            std::vector<ValeurTrouve> indexProchainsDebut {valeurDebutChiffreLettre(ligne, i)};
            std::sort(indexProchainsDebut.begin(), indexProchainsDebut.end(), [&] (ValeurTrouve index1, ValeurTrouve index2){
                return index1.index < index2.index;
                });
            if (!contientDebutChiffre(valeurComplexe))
            {
                valeurComplexe = "";
                if (indexProchainsDebut[0].index > i && indexProchainsDebut[0].index != std::string::npos)
                    i = indexProchainsDebut[0].index;
            }
            char resultat{ chiffreEnLettre(valeurComplexe) };
            if (resultat != '0')
            {
                valeurs.push_back(resultat);
                valeurComplexe = "";
            }
            else if (resultat == '0' && valeurComplexe.size() > 6)
            {
                valeurComplexe = "";
            }
        }
    }
    return valeurs;
}

int main()
{
    std::fstream fichier {"donnees.txt"};
    std::vector<std::string> exemple{"two1nine", "eightwothree", "abcone2threexyz", "xtwone3four", "4nineeightseven2", "zoneight234", "7pqrstsixteen" };
    //while (fichier)
    //{
    //    std::string ligne;
    //    fichier >> ligne;
    //    exemple.push_back(ligne);
    //}
    
    std::vector<int> valeursExemple;
    for (auto& ligne : exemple)
    {
        std::vector<char> valeurLigne = valeursSelonLigne(ligne);
        std::string total;
        if (!valeurLigne.empty())
        {
            total += valeurLigne[0];
            total += valeurLigne[valeurLigne.size() - 1];
        }
        valeursExemple.push_back(parse(total));
    }
    int resultat{};
    for (int valeur : valeursExemple)
    {
        resultat += valeur;
    }
    std::cout << "Le resultat est de " << resultat;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
