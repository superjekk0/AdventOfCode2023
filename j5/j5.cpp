#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <cassert>
#include "../utils.h"

std::unordered_map<std::string, long> clesProprietes{
	{"seed", 0l},
	{"soil", 1l},
	{"fertilizer", 2l},
	{"water", 3l},
	{"light", 4l},
	{"temperature", 5l},
	{"humidity", 6l},
	{"location", 7l}
};

constexpr int DESTINATION = 0;
constexpr int SOURCE = 1;

struct Graine {
	long long idGraine{ -1l };
	long long idSol{ -1l };
	long long idFertilisant{ -1l };
	long long idEau{ -1 };
	long long idLumiere{ -1 };
	long long idTemperature{ -1 };
	long long idHumidite{ -1 };
	long long position{ -1l };

	Graine() = default;

	Graine(long long id) : idGraine{ id } {}

	Graine(long long source, long long destination, const std::vector<std::string> cles)
	{
		switch (clesProprietes[cles[SOURCE]])
		{
		case 0:
			idGraine = source;
			break;
		case 1:
			idSol = source;
			break;
		case 2:
			idFertilisant = source;
			break;
		case 3:
			idEau = source;
			break;
		case 4:
			idLumiere = source;
			break;
		case 5:
			idTemperature = source;
			break;
		case 6:
			idHumidite = source;
			break;
		case 7:
			position = source;
			break;
		default:
			break;
		}

		switch (clesProprietes[cles[DESTINATION]])
		{
		case 0:
			idGraine = destination;
			break;
		case 1:
			idSol = destination;
			break;
		case 2:
			idFertilisant = destination;
			break;
		case 3:
			idEau = destination;
			break;
		case 4:
			idLumiere = destination;
			break;
		case 5:
			idTemperature = destination;
			break;
		case 6:
			idHumidite = destination;
			break;
		case 7:
			position = destination;
			break;
		default:
			break;
		}
	}

	long long operator[](std::string_view cle) const
	{
		switch (clesProprietes[static_cast<std::string>(cle)])
		{
		case 0:
			return idGraine;
			break;
		case 1:
			return idSol;
			break;
		case 2:
			return idFertilisant;
			break;
		case 3:
			return idEau;
			break;
		case 4:
			return idLumiere;
			break;
		case 5:
			return idTemperature;
			break;
		case 6:
			return idHumidite;
			break;
		case 7:
			return position;
			break;
		default:
			break;
		}
		return -1l;
	}
	long long& operator[](std::string_view cle)
	{
		switch (clesProprietes[static_cast<std::string>(cle)])
		{
		case 0:
			return idGraine;
			break;
		case 1:
			return idSol;
			break;
		case 2:
			return idFertilisant;
			break;
		case 3:
			return idEau;
			break;
		case 4:
			return idLumiere;
			break;
		case 5:
			return idTemperature;
			break;
		case 6:
			return idHumidite;
			break;
		case 7:
			return position;
			break;
		default:
			assert(false && "You typed a wrong key!");
			break;
		}
	}
};

std::vector<Graine> graines;

void ajoutDonnees(const std::string& ligne, const std::vector<std::string>& origineDestination)
{
	std::vector<std::string> valeurs{ splitString(ligne, ' ') };
	long long source{ std::stoll(valeurs[SOURCE]) };
	long long destination{ std::stoll(valeurs[DESTINATION]) };
	long long portee{ std::stoll(valeurs[2]) };
	std::string_view sourceString{ origineDestination[SOURCE] };
	std::string_view destinationString{ origineDestination[DESTINATION] };

	for (Graine& graine : graines)
	{
		if (graine[sourceString] >= source && graine[sourceString] < source + portee)
		{
			graine[destinationString] = graine[sourceString] + (destination - source);
		}
	}
}

void remplissage(const std::vector<std::string>& cles)
{
	for (auto& graine : graines)
	{
		if (graine[cles[DESTINATION]] == -1l)
		{
			graine[cles[DESTINATION]] = graine[cles[SOURCE]];
		}
	}
}

void ajoutDonnees(const std::vector<std::string>& lignes)
{
	std::vector<std::string> origineDestination;
	for (int i{ 1 }; i < lignes.size(); ++i)
	{
		std::size_t indexSeparateur{ lignes[i].find(':') };
		if (indexSeparateur != std::string::npos)
		{
			if (origineDestination.size() == 2) remplissage(origineDestination);
			origineDestination = splitString(lignes[i].substr(0, lignes[i].find(' ')), "-to-");
			std::swap(origineDestination[0], origineDestination[1]);
		}
		else
		{
			ajoutDonnees(lignes[i], origineDestination);
		}
	}
	remplissage(origineDestination);

}

int main()
{
	std::vector<std::string> donnees{
		//"seeds: 79 14 55 13", "", "seed-to-soil map:", "50 98 2", "52 50 48", "",
		//"soil-to-fertilizer map:", "0 15 37", "37 52 2", "39 0 15", "", "fertilizer-to-water map:", "49 53 8",
		//"0 11 42", "42 0 7", "57 7 4", "", "water-to-light map:", "88 18 7", "18 25 70", "", "light-to-temperature map:",
		//"45 77 23", "81 45 19", "68 64 13", "", "temperature-to-humidity map:", "0 69 1", "1 0 69", "",
		//"humidity-to-location map:", "60 56 37", "56 93 4"
		donneesFichier("donnees.txt")
	};
	donnees = vectorStringSansVide(donnees);

	std::vector<long long> seeds;
	std::vector<std::string> chaineSeeds{ splitString(donnees[0], ':') };
	chaineSeeds[1] = trimString(chaineSeeds[1]);
	for (auto& seed : splitString(chaineSeeds[1], ' '))
		seeds.push_back(std::stoll(seed));

	for (auto seed : seeds)
	{
		graines.push_back(Graine{ seed });
	}

	ajoutDonnees(donnees);

	std::cout << "Graines selectionnees: " << std::endl;
	for (auto& graine : graines)
	{
		std::cout << graine.idGraine << ' ';
	}

	std::sort(graines.begin(), graines.end(), [](const Graine& graine1, const Graine& graine2) {
		return graine1.position < graine2.position;
		});
	std::cout << "Leurs localisations sont : \n";
	for (auto& graine : graines)
	{
		std::cout << "Graine " << graine.idGraine << " a la position " << graine.position << '\n';
	}

	std::cout << '\n' << graines[0].position << '\n';
}