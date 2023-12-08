#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "../utils.h"

struct Noeud;

std::vector<Noeud> noeuds;
std::unordered_map<std::string, std::size_t> indexNoeuds;

struct Noeud {
    std::string noeudActuel;
    std::string noeudGauche;
    std::string noeudDroite;

    Noeud() = default;

    Noeud(const std::string& ligne)
    {
        std::vector<std::string> donnees{ splitString(ligne, '=') };
        noeudActuel = trimString(donnees[0]);
        std::vector<std::string> noeudsGaucheDroite{ splitString(donnees[1], ',') };
        noeudGauche = trimString(noeudsGaucheDroite[0]).substr(1);
        noeudDroite = trimString(noeudsGaucheDroite[1]).substr(0, noeudsGaucheDroite[1].size() - 2);
    }
};

int main()
{
    std::vector<std::string> donnees{
        //"RL", "", "AAA = (BBB, CCC)", "BBB = (DDD, EEE)", "CCC = (ZZZ, GGG)", "DDD = (DDD, DDD)", "EEE = (EEE, EEE)", "GGG = (GGG, GGG)", "ZZZ = (ZZZ, ZZZ)"
        //"LLR", "", "AAA = (BBB, BBB)", "BBB = (AAA, ZZZ)", "ZZZ = (ZZZ, ZZZ)"
        donneesFichier("donnees.txt")
    };

    donnees = vectorStringSansVide(donnees);

    // Si c'est vrai, on va à droite, sinon à gauche
    std::vector<bool> ordreGaucheDroite{};
    for (char lettre : donnees[0])
		ordreGaucheDroite.push_back(lettre == 'R');

    for (int i{ 1 }; i < donnees.size(); ++i)
    {
        indexNoeuds[trimString(splitString(donnees[i], '=')[0])] = noeuds.size();
        noeuds.push_back(Noeud(donnees[i]));
    }

    std::size_t nbDeplacements{ 0 };
    Noeud* noeudActuel{ &noeuds[indexNoeuds["AAA"]]};
    std::size_t indexZZZ { indexNoeuds["ZZZ"] };
    std::string prochainNoeud{ordreGaucheDroite[0] ? noeudActuel->noeudDroite : noeudActuel->noeudGauche};
    for (; noeudActuel != &noeuds[indexZZZ]; noeudActuel = &noeuds[indexNoeuds[prochainNoeud]])
    {
        prochainNoeud = (ordreGaucheDroite[nbDeplacements % ordreGaucheDroite.size()] ? noeudActuel->noeudDroite : noeudActuel->noeudGauche);
        ++nbDeplacements;
    }

    std::cout << "Il y a eu " << nbDeplacements << " deplacements";
}