#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "../utils.h"

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
    }
};

std::unordered_map<std::string, std::vector<Portee>> map;

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
    std::vector<std::string> chaineSeeds { splitString(donnees[0], ':') };
    chaineSeeds[1] = trimString(chaineSeeds[1]);
    for (auto& seed : splitString(chaineSeeds[1], ' '))
		seeds.push_back(parse(seed));

    std::string cle;

    for (int i{ 1 }; i < donnees.size(); ++i)
    {
        std::size_t indexSeparateur{ donnees[i].find(':') };
        if (indexSeparateur != std::string::npos)
        {
            cle = donnees[i].substr(0, indexSeparateur);
        }
        else
        {
			map[cle].push_back(donnees[i]);
		}
    }

    std::cout << "Hello World!\n";
}