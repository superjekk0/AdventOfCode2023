#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include "../utils.h"

struct Graine {
	long id;
	long position;
	long idFertilisant;
	long idEau;
	long idLumiere;
	long idTemperature;
	long idHumidite;

	Graine(long graineId, long graineIndex) : id{ graineId }, position{ graineIndex } {}
};



std::vector<Graine> graines;

struct Portee {
	long destination;
	long source;
	long portee;

	Portee(const std::string& ligne)
	{
		std::vector<std::string> valeurs{ splitString(ligne, ' ') };
		destination = parse(valeurs[0]);
		source = parse(valeurs[1]);
		portee = parse(valeurs[2]);

		for (int i{ 0 }; i < portee; ++i)
		{
			graines.push_back(Graine{ destination + i, source + i });
		}
	}
};

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

	std::string cle;

	for (int i{ 1 }; i < donnees.size(); ++i)
	{
		std::size_t indexSeparateur{ donnees[i].find(':') };
		if (indexSeparateur != std::string::npos)
		{
			cle = donnees[i].substr(0, donnees[i].find(' '));
			std::vector<std::string> destinations{ splitString(cle, "-to-") };
			//cles[cle] = cles.size();
		}
		else
		{
			//map[cle].push_back(donnees[i]);
			//ajoutDonnees(donnees[i], cle);
		}
	}

	std::sort(graines.begin(), graines.end(), [](const Graine& graine1, const Graine& graine2) {
		return graine1.position < graine2.position;
		});
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

	//std::sort(graines.begin(), graines.end(), [](const Graine& graine1, const Graine& graine2) {
	//	return graine1.position < graine2.position;
	//	});

	//std::vector<std::vector<Graine>::iterator> grainesParSeed{};
	//for (long seed : seeds)
	//{
	//	auto graineExistante = std::find_if(graines.begin(), graines.end(), [seed](const Graine& graine) {
	//		return graine.id == seed;
	//		});
	//	if (graineExistante != graines.end())
	//	{
	//		grainesParSeed.push_back(graineExistante);
	//	}
	//}

	//std::sort(grainesParSeed.begin(), grainesParSeed.end(), [](const auto& graine1, const auto& graine2) {
	//	return graine1->index < graine2->index;
	//	});

	long localisation{ 100000l };
	for (long graineRecherchee : seeds)
	{
		auto minimum = std::find_if(graines.begin(), graines.end(), [graineRecherchee](const Graine& graine) {
			return graine.id == graineRecherchee;
			});
		if (minimum != graines.end() && minimum->position < localisation)
		{
			localisation = minimum->position;
		}
	}

	std::cout << "Le minimum est de " << localisation << "!\n";
}