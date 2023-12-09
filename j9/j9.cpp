#include <iostream>
#include <string>
#include <vector>
#include "../utils.h"

using Donnees = std::vector<std::string>;

struct DonneesOasis {
private:
	//bool nouvellesDonneesDonneZero()
	//{
	//	long somme{ 0 };
	//	for (auto& donnee : donneesGlobales)
	//	{
	//		somme += donnee[0];
	//	}

	//	return somme == 0l;
	//}

	void ajoutDonneesDebut()
	{
		//while (!nouvellesDonneesDonneZero())
		//{
		donneesGlobales[donneesGlobales.size() - 1].insert(donneesGlobales[donneesGlobales.size() - 1].begin(), 0l);
		for (size_t i{ donneesGlobales.size() - 1 }; i > 0; --i)
		{
			donneesGlobales[i - 1].insert(donneesGlobales[i - 1].begin(), donneesGlobales[i - 1][0] - donneesGlobales[i][0]);
		}
		//}
		std::cout << "Fin de cet objet\n";
	}
public:
	std::vector<std::vector<long>> donneesGlobales;
	//std::vector<long> donneesBase;
	//std::vector<long> differenceDonnees;

	DonneesOasis() = default;

	DonneesOasis(const std::string& donnees)
	{
		auto donneesStr = splitString(donnees, ' ');
		donneesGlobales.push_back(std::vector<long>());

		for (auto& str : donneesStr)
		{
			donneesGlobales[0].push_back(std::stol(str));
		}

		donneesGlobales.push_back(std::vector<long>());
		for (size_t i{ 0 }; i < donneesGlobales.size() - 1; ++i)
		{
			donneesGlobales[i + 1].reserve(donneesGlobales[i].size() - 1);
			for (size_t j{ 0 }; j < donneesGlobales[i].size() - 1; ++j)
			{
				donneesGlobales[i + 1].push_back(donneesGlobales[i][j + 1] - donneesGlobales[i][j]);
			}
			auto donneesDifferentesZero{ std::find_if(donneesGlobales[i + 1].begin(), donneesGlobales[i + 1].end(),
				[](long valeur)
				{
					return valeur != 0;
				}) };
			if (donneesDifferentesZero != donneesGlobales[i + 1].end())
			{
				donneesGlobales.push_back(std::vector<long>());
			}
		}

		donneesGlobales[donneesGlobales.size() - 1].push_back(0l);
		for (size_t i{ donneesGlobales.size() - 1 }; i > 0; --i)
		{
			donneesGlobales[i - 1].push_back(
				donneesGlobales[i][donneesGlobales[i].size() - 1] + donneesGlobales[i - 1][donneesGlobales[i - 1].size() - 1]);
		}

		ajoutDonneesDebut();
	}

	operator long() const
	{
		return donneesGlobales[0][donneesGlobales[0].size() - 1];
	}
};

std::vector<DonneesOasis> donneesOasis;

int main()
{
	Donnees donnees{
		"0 3 6 9 12 15", "1 3 6 10 15 21", "10 13 16 21 30 45"
		//donneesFichier("donnees.txt")
	};
	donneesOasis.reserve(donnees.size());
	for (auto& donnee : donnees)
	{
		donneesOasis.push_back(donnee);
	}
	long somme{ 0 };
	for (auto& donnee : donneesOasis)
	{
		somme += donnee;
	}
	std::cout << "Il la somme des dernieres interpolations est: " << somme;
}