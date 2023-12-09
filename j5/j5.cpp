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
	long idGraine{ -1l };
	long idSol{ -1l };
	long position{ -1l };
	long idFertilisant{ -1l };
	long idEau{ -1 };
	long idLumiere{ -1 };
	long idTemperature{ -1 };
	long idHumidite{ -1 };
	//std::unordered_map<std::string, long> infos;

	Graine() = default;

	Graine(long source, long destination, const std::vector<std::string> cles)
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

	long operator[](std::string_view cle) const
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
	long& operator[](std::string_view cle)
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
	long source{ std::stol(valeurs[SOURCE]) };
	long destination{ std::stol(valeurs[DESTINATION]) };
	long portee{ std::stol(valeurs[2]) };
	std::string_view sourceString{ origineDestination[SOURCE] };
	std::string_view destinationString{ origineDestination[DESTINATION] };

	for (long i{ 0 }; i < portee; ++i)
	{
		auto graineExistante = std::find_if(graines.begin(), graines.end(),
			[source, sourceString, i](const Graine& graine)
			{
				return graine[sourceString] == source + i;
			});
		if (graineExistante == graines.end())
		{
			graines.push_back(Graine{ source + i, destination + i, origineDestination });
		}
		else
		{
			(*graineExistante)[destinationString] = destination + i;
		}
	}
}

void verificationGraines(const std::vector<std::string>& cles)
{
	if (graines.empty())
		return;
	auto copieGraines{ graines };
	std::sort(copieGraines.begin(), copieGraines.end(), [cles](const Graine& graine1, const Graine& graine2) {
		return graine1[cles[DESTINATION]] > graine2[cles[DESTINATION]];
		});

	// Ne devrait s'activer qu'une fois: lors du premier appel de la fonction
	if (copieGraines.size() < copieGraines[0][cles[DESTINATION]])
	{
		for (long i{ 0 }; i < copieGraines[0][cles[DESTINATION]]; ++i)
		{
			if (std::find_if(copieGraines.begin(), copieGraines.end(), [i, cles](const Graine& graine) {
				return graine[cles[DESTINATION]] == i;
				}) == copieGraines.end())
			{
				copieGraines.push_back(Graine{ i, i, cles });
			}
		}
		graines = copieGraines;
		return;
	}

	for (auto& graine : copieGraines)
	{
		if (graine[cles[SOURCE]] == -1)
		{
			graine[cles[SOURCE]] = graine[cles[DESTINATION]];
		}
	}

	graines = copieGraines;
}

int main()
{
	std::vector<std::string> donnees{
		"seeds: 79 14 55 13", "", "seed-to-soil map:", "50 98 2", "52 50 48", "",
		"soil-to-fertilizer map:", "0 15 37", "37 52 2", "39 0 15", "", "fertilizer-to-water map:", "49 53 8",
		"0 11 42", "42 0 7", "57 7 4", "", "water-to-light map:", "88 18 7", "18 25 70", "", "light-to-temperature map:",
		"45 77 23", "81 45 19", "68 64 13", "", "temperature-to-humidity map:", "0 69 1", "1 0 69", "",
		"humidity-to-location map:", "60 56 37", "56 93 4"
	};
	donnees = vectorStringSansVide(donnees);

	std::vector<long> seeds;
	std::vector<std::string> chaineSeeds{ splitString(donnees[0], ':') };
	chaineSeeds[1] = trimString(chaineSeeds[1]);
	for (auto& seed : splitString(chaineSeeds[1], ' '))
		seeds.push_back(parse(seed));

	std::vector<std::string> origineDestination;
	for (int i{ 1 }; i < donnees.size(); ++i)
	{
		std::size_t indexSeparateur{ donnees[i].find(':') };
		if (indexSeparateur != std::string::npos)
		{
			verificationGraines(origineDestination);
			origineDestination = splitString(donnees[i].substr(0, donnees[i].find(' ')), "-to-");
			std::swap(origineDestination[0], origineDestination[1]);
			//cles[cle] = cles.size();
		}
		else
		{
			ajoutDonnees(donnees[i], origineDestination);
			//map[cle].push_back(donnees[i]);
			//ajoutDonnees(donnees[i], cle);
		}
	}

	std::vector<Graine> grainesSelectionnees{};
	for (auto& graine : graines)
	{
		if (std::find(seeds.begin(), seeds.end(), graine.idGraine) != seeds.end())
		{
			grainesSelectionnees.push_back(graine);
		}
	}

	std::cout << "Graines selectionnees: " << std::endl;
	for (auto& graine : grainesSelectionnees)
	{
		std::cout << graine.idGraine << ' ';
	}

	std::cout << "La plus petite localisation est: ";
	std::sort(grainesSelectionnees.begin(), grainesSelectionnees.end(), [](const Graine& graine1, const Graine& graine2) {
		return graine1.position < graine2.position;
		});
	std::cout << grainesSelectionnees[0].position << '\n';

	//std::sort(graines.begin(), graines.end(), [](const Graine& graine1, const Graine& graine2) {
	//	return graine1.position < graine2.position;
	//	});
	//Graine plusGrosIndex{ graines[graines.size() - 1] };

	//for (long i{ 0 }; i < plusGrosIndex.id; ++i)
	//{
	//	auto graineExistante = std::find_if(graines.begin(), graines.end(), [i](const Graine& graine) {
	//		return graine.id == i;
	//		});
	//	if (graineExistante == graines.end())
	//	{
	//		graines.push_back(Graine{ i , i });
	//	}
	//}


}