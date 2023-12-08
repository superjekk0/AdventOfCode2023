#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <numeric>
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

bool noeudTermine(Noeud* const noeud, const std::string& noeudArrivee)
{
	return noeud->noeudActuel.find_last_of('Z') == noeud->noeudActuel.size() - 1;
}

bool noeudsFinis(const std::vector<Noeud*>& noeuds, const std::vector<std::string>& noeudsArrivee)
{
	for (int i{ 0 }; i < noeuds.size(); ++i)
	{
		if (!noeudTermine(noeuds[i], noeudsArrivee[i]))
			return false;
	}
	return true;
}

void majNoeuds(std::vector<Noeud*>& noeudsAChanger, const std::vector<std::string>& prochainsNoeuds)
{
	for (int i{ 0 }; i < noeudsAChanger.size(); ++i)
		noeudsAChanger[i] = &noeuds[indexNoeuds[prochainsNoeuds[i]]];
}

std::size_t ppcm(std::size_t nbDeplacementIndividuel, std::vector<std::size_t> nbAutresDeplacements)
{
	if (nbAutresDeplacements.size() == 1)
		return std::lcm( nbAutresDeplacements[nbAutresDeplacements.size() - 1], nbDeplacementIndividuel);
	else
	{
		std::size_t donnee{ nbAutresDeplacements[nbAutresDeplacements.size() - 1] };
		nbAutresDeplacements.pop_back();
		return std::lcm(nbDeplacementIndividuel, ppcm(donnee, nbAutresDeplacements));
	}
}

std::size_t ppcm(const std::vector<std::size_t>& nbDeplacements)
{
	std::size_t produitDeplacements{ std::accumulate(nbDeplacements.begin(), nbDeplacements.end(), 1ull, std::multiplies()) };
	std::vector<std::size_t> ppcmPaires{nbDeplacements};

	std::sort(ppcmPaires.begin(), ppcmPaires.end(), std::greater());

	std::size_t donnee { ppcmPaires[ppcmPaires.size() - 1]};
	ppcmPaires.pop_back();
	return ppcm(donnee, ppcmPaires);
}

int main()
{
	std::vector<std::string> donnees{
		//"RL", "", "AAA = (BBB, CCC)", "BBB = (DDD, EEE)", "CCC = (ZZZ, GGG)", "DDD = (DDD, DDD)", "EEE = (EEE, EEE)", "GGG = (GGG, GGG)", "ZZZ = (ZZZ, ZZZ)"
		//"LLR", "", "AAA = (BBB, BBB)", "BBB = (AAA, ZZZ)", "ZZZ = (ZZZ, ZZZ)"
		//"LR", "", "11A = (11B, XXX)", "11B = (XXX, 11Z)", "11Z = (11B, XXX)", "22A = (22B, XXX)", "22B = (22C, 22C)", "22C = (22Z, 22Z)", "22Z = (22B, 22B)", "XXX = (XXX, XXX)"
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
	std::vector<Noeud*> noeudsDepart{  };
	for (auto& noeud : noeuds)
	{
		if (noeud.noeudActuel.find_last_of('A') == noeud.noeudActuel.size() - 1)
			noeudsDepart.push_back(&noeud);
	}
	std::vector<std::size_t> indexsZ{};
	for (auto& noeud : noeuds)
	{
		if (noeud.noeudActuel.find_last_of('Z') == noeud.noeudActuel.size() - 1)
			indexsZ.push_back(indexNoeuds[noeud.noeudActuel]);
	}

	std::vector<std::size_t> nbDeplacementsParNoeud{};

	for (Noeud* noeud : noeudsDepart)
	{
		std::string prochainNoeud{ ordreGaucheDroite[0] ? noeud->noeudDroite : noeud->noeudGauche };
		for (nbDeplacements = 0ll; std::find(indexsZ.begin(), indexsZ.end(), indexNoeuds[noeud->noeudActuel]) == indexsZ.end();
			noeud = &noeuds[indexNoeuds[prochainNoeud]])
		{
			prochainNoeud = (ordreGaucheDroite[nbDeplacements % ordreGaucheDroite.size()] ? noeud->noeudDroite : noeud->noeudGauche);
			++nbDeplacements;
		}
		nbDeplacementsParNoeud.push_back(nbDeplacements);
	}

	for (std::size_t deplacement : nbDeplacementsParNoeud)
		std::cout << deplacement << std::endl;
	std::cout << "Il y a eu " << ppcm(nbDeplacementsParNoeud) << " deplacements";
}