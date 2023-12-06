#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "../utils.h"

/// <summary>
/// Le paramètre "a" a la valeur de -1
/// </summary>
struct Quadratique {
	long x1;
	long x2;
	long double k;
	long double h;

	Quadratique(long x1, long x2) : x1(x1), x2(x2)
	{
		h = (x1 + x2) / 2.l;
		k = this->operator()(h);
	}

	long nbAbcissesAuDessusValeur(long double valeur)
	{
		long double valeurAbcisse1{ -std::sqrtl(std::abs(valeur - k)) + h };
		long double difference{ std::abs(valeurAbcisse1 - h) };
		long double valeurAbcisse2{ valeurAbcisse1 + difference * 2 };

		long nbAbcisses{ 0 };
		for (long double i{ std::ceil(valeurAbcisse1) }; i <= std::floor(valeurAbcisse2); ++i)
		{
			if (i != valeurAbcisse1 && i != valeurAbcisse2)
				++nbAbcisses;
		}

		return nbAbcisses;
	}

	long double operator()(long double x) {
		return -(x - x1) * (x - x2);
	}
};

int main()
{
	std::vector<std::string> lines{
		//"Time:   7  15   30", "Distance:  9  40  200" 
		donneesFichier("donnees.txt")
	};
	std::vector<std::string> temps{ vectorStringSansVide(splitString(lines[0], ' ')) };
	std::vector<std::string> distances{ vectorStringSansVide(splitString(lines[1], ' ')) };
	std::vector<long> tempsLong{};
	for (int i{ 1 }; i < temps.size(); ++i) {
		tempsLong.push_back(std::stol(temps[i]));
	}
	std::vector<long> distancesLong{};
	for (int i{ 1 }; i < distances.size(); ++i) {
		distancesLong.push_back(std::stol(distances[i]));
	}
	std::vector<Quadratique> quadratiques{};
	for (int i{ 0 }; i < distancesLong.size(); ++i)
	{
		quadratiques.push_back(Quadratique(0l, tempsLong[i]));
	}
	long produitNombreGagnants{ 1 };
	for (int i{ 0 }; i < quadratiques.size(); ++i)
	{
		produitNombreGagnants *= quadratiques[i].nbAbcissesAuDessusValeur(distancesLong[i]);
	}
	std::cout << produitNombreGagnants;
}