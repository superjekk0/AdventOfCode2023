#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <cmath>
#include "../utils.h"

using Donnees = std::vector<std::string>;

struct Galaxie {
	long id;
	long x;
	long y;

	Galaxie(long id, long x, long y) : id{ id }, x{ x }, y{ y } {}
};

struct Colonne {
	std::vector<Galaxie*> galaxies;
	long idColonne;

	Colonne(long idColonne) : idColonne{ idColonne } {}
};

struct Ligne {
	std::vector<Galaxie*> galaxies;
	long idLigne;

	Ligne(long idLigne) : idLigne{ idLigne } {}
};

struct Univers {
	std::vector<Galaxie> galaxies;
	std::vector<Colonne> colonnes;
	std::vector<Ligne> lignes;

	Univers(Donnees donnees)
	{
		// Fonctionnel
		for (long i{ 1 }; i <= donnees.size(); ++i)
		{
			lignes.push_back(Ligne(static_cast<long>(lignes.size()) + 1));
			for (long j{ 1 }; j <= donnees[i - 1].size(); ++j)
			{
				if (std::find_if(colonnes.begin(), colonnes.end(), [j](Colonne c) { return c.idColonne == j; }) == colonnes.end())
					colonnes.push_back(Colonne{ static_cast<long>(colonnes.size()) + 1 });

				if (donnees[i - 1][j - 1] == '#')
				{
					galaxies.push_back(Galaxie{ static_cast<long>(galaxies.size()) + 1, j, i });
					lignes[i - 1].galaxies.push_back(&galaxies[galaxies.size() - 1]);
					colonnes[j - 1].galaxies.push_back(&galaxies[galaxies.size() - 1]);
				}
			}
		}

		// Fonctionnel
		for (int i{ 0 }; i < lignes.size(); ++i)
		{
			if (lignes[i].galaxies.empty())
			{
				lignes.insert(std::next(lignes.begin(), i), lignes[i]);
				++i;
				//lignes[i + 1].idLigne++;
				for (auto& galaxie : galaxies)
				{
					if (galaxie.y > i - 1)
					{
						galaxie.y++;
					}
				}

				for (int j{ i }; j < lignes.size(); ++j)
				{
					lignes[j].idLigne++;
				}

			}
		}

		for (int i{ 0 }; i < colonnes.size(); ++i)
		{
			if (colonnes[i].galaxies.empty())
			{
				colonnes.insert(std::next(colonnes.begin(), i), colonnes[i]);
				++i;
				//colonnes[i + 1].idColonne++;
				for (auto& galaxie : galaxies)
				{
					if (galaxie.x > i - 1)
					{
						galaxie.x++;
					}
				}

				for (int j{ i }; j < colonnes.size(); ++j)
				{
					colonnes[j].idColonne++;
				}

			}
		}
	}

private:
	bool paireDejaPresente(const std::vector<std::array<Galaxie*, 2>>& chemins, const Galaxie& galaxie1, const Galaxie& galaxie2)
	{
		for (auto& chemin : chemins)
		{
			if ((chemin[0] == &galaxie1 || chemin[1] == &galaxie1) && (chemin[0] == &galaxie2 || chemin[1] == &galaxie2))
				return true;
		}
		return false;
	}
public:

	std::vector<long> cheminsPlusCourts()
	{
		std::vector<std::array<Galaxie*, 2>> chemins{};
		std::vector<Galaxie>* refGalaxies{ &galaxies };


		// Fonctionnel
		for (int i{ 0 }; i < galaxies.size(); ++i)
		{
			for (int j{ i + 1 }; j < galaxies.size(); ++j)
			{
				if (chemins.empty())
				{
					chemins.push_back({ &galaxies[i], &galaxies[j] });
					continue;
				}

				//for (auto& paire : chemins)
				//{
				auto resultat = std::find_if(chemins.begin(), chemins.end(),
					[i, j, &refGalaxies](auto& galaxie)
					{
						return galaxie[0] == (&(refGalaxies->at(i))) || galaxie[1] == (&(refGalaxies->at(j)));
							});
						//auto resultat2 = std::find_if(chemins.begin(), chemins.end(), [i, j ,&refGalaxies](auto& galaxie) { return galaxie[0] == &refGalaxies[i] || galaxie[1] == &refGalaxies[j]; });
						if (resultat != chemins.end())
						{
							chemins.push_back({ &galaxies[i], &galaxies[j] });
						}
						//}
			}
		}

		std::vector<long> longueursChemins{};
		longueursChemins.reserve(chemins.size());

		for (auto& chemin : chemins)
		{
			longueursChemins.push_back(std::abs(chemin[0]->x - chemin[1]->x) +
				std::abs(chemin[0]->y - chemin[1]->y));

			//std::cout << "Eille";
		}

		return longueursChemins;
	}
};

int main()
{
	std::vector<std::string> donnees{ donneesFichier(
		"exemple.txt"
	) };

	Univers univers{ donnees };

	auto chemins{ univers.cheminsPlusCourts() };
	long somme{ 0 };
	for (auto& chemin : chemins)
	{
		somme += chemin;
	}
	std::cout << somme;
}