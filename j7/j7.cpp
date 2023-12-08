#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include "../utils.h"

enum Valeurs {
	deux = 2,
	trois = 3,
	quatre,
	cinq,
	six,
	sept,
	huit,
	neuf,
	dix,
	valet = 1,
	dame = 12,
	roi,
	as
};

enum TypeJeu {
	highCard,
	paire,
	doublePaire,
	brelan,
	full,
	carre,
	quinte
};

Valeurs valeurCarte(char carte)
{
	switch (carte)
	{
	case '2':
		return Valeurs::deux;
	case '3':
		return Valeurs::trois;
	case '4':
		return Valeurs::quatre;
	case '5':
		return Valeurs::cinq;
	case '6':
		return Valeurs::six;
	case '7':
		return Valeurs::sept;
	case '8':
		return Valeurs::huit;
	case '9':
		return Valeurs::neuf;
	case 'T':
		return Valeurs::dix;
	case 'J':
		return Valeurs::valet;
	case 'Q':
		return Valeurs::dame;
	case 'K':
		return Valeurs::roi;
	case 'A':
		return Valeurs::as;
	default:
		assert(false && "How did you get here?");
		break;
	}
}

struct Jeu {
	std::string jeu;
	long nb;
	TypeJeu typeJeu;

	Jeu(const std::string& ligne)
	{
		std::vector<std::string> donnees = splitString(ligne, ' ');
		jeu = donnees[0];
		nb = std::stol(donnees[1]);

		std::unordered_map<char, int> occurencesCarte;
		for (char c : jeu)
		{
			occurencesCarte[c]++;
		}
		int totalNbCartes = 0;
		auto occurenceJoker = occurencesCarte.find('J');

		switch (occurencesCarte.size())
		{
		case 1:
			typeJeu = TypeJeu::quinte;
		case 2:
			if (occurencesCarte.find('J') != occurencesCarte.end())
			{
				typeJeu = TypeJeu::quinte;
				break;
			}
			for (auto& cle : occurencesCarte)
			{
				if (cle.second == 4 || cle.second == 1)
				{
					typeJeu = TypeJeu::carre;
				}
				else if (cle.second == 3 || cle.second == 2)
				{
					typeJeu = TypeJeu::full;
				}
			}
			break;
		case 3:
			for (auto& cle : occurencesCarte)
			{
				if (occurenceJoker != occurencesCarte.end() && cle != *occurenceJoker)
				{
					switch (occurenceJoker->second)
					{
					case 1:
						switch (cle.second)
						{
						case 1:
							typeJeu = TypeJeu::carre;
							break;
						case 2:
							typeJeu = TypeJeu::full;
							break;
						case 3:
							typeJeu = TypeJeu::carre;
							break;
						default:
							break;
						}
						break;
					case 2:
						typeJeu = TypeJeu::carre;
						break;
					case 3:
						typeJeu = TypeJeu::carre;
						break;
					default:
						break;
					}
					break;
				}
				if (cle.second == 1)
				{
					if (totalNbCartes == 3 || totalNbCartes == 1)
					{
						typeJeu = TypeJeu::brelan;
						break;
					}
					else if (totalNbCartes == 4 || totalNbCartes == 2)
					{
						typeJeu = TypeJeu::doublePaire;
						break;
					}
					else
					{
						totalNbCartes += cle.second;
					}
					if (occurenceJoker != occurencesCarte.end() && cle != *occurenceJoker)
					{
						if (occurenceJoker->second == 1)
						{
							typeJeu = TypeJeu::carre;
						}
						else if (occurenceJoker->second == 2)
						{
							typeJeu = (totalNbCartes == 2 ? TypeJeu::full : TypeJeu::carre);
						}
						else
						{
							typeJeu = TypeJeu::carre;
						}
						break;
					}
				}
				else if (cle.second == 2)
				{
					if (totalNbCartes == 2 || totalNbCartes == 1)
					{
						typeJeu = TypeJeu::doublePaire;
						break;
					}
					else
					{
						totalNbCartes += cle.second;
					}
				}
				else if (cle.second == 3)
				{
					if (occurenceJoker != occurencesCarte.end() && cle != *occurenceJoker)
					{
						typeJeu = TypeJeu::carre;
						break;
					}
					typeJeu = TypeJeu::brelan;
					break;
				}
			}
			break;
		case 4:
			if (occurencesCarte.find('J') != occurencesCarte.end())
			{
				typeJeu = TypeJeu::brelan;
				break;
			}
			typeJeu = TypeJeu::paire;
			break;
		case 5:
			if (occurencesCarte.find('J') != occurencesCarte.end())
			{
				typeJeu = TypeJeu::paire;
				break;
			}
			typeJeu = TypeJeu::highCard;

		}
	}
};

bool cartePlusFaible(const Jeu& a, const Jeu& b)
{
	if (a.typeJeu != b.typeJeu)
	{
		return a.typeJeu < b.typeJeu;
	}
	else
	{
		for (int i{ 0 }; i < a.jeu.size(); ++i)
		{
			if (valeurCarte(a.jeu[i]) != valeurCarte(b.jeu[i]))
			{
				return valeurCarte(a.jeu[i]) < valeurCarte(b.jeu[i]);
			}
		}
	}
}

int main()
{
	std::vector<std::string> donnees{
		//"32T3K 765","T55J5 684","KK677 28","KTJJT 220","QQQJA 483"
		donneesFichier("donnees.txt")
	};
	std::vector<Jeu> jeux;
	for (const std::string& ligne : donnees)
	{
		jeux.push_back(Jeu(ligne));
	}

	std::sort(jeux.begin(), jeux.end(), cartePlusFaible);
	long long total{ 0 };
	for (long long i{ 0 }; i < jeux.size(); ++i)
	{
		total += jeux[i].nb * (i + 1);
	}
	std::cout << "Le total est de " << total;
}