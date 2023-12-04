#include <iostream>
#include <vector>
#include <string>
#include "../utils.h"

struct Card {
    std::vector<long> values;
    std::vector<long> winningValues;
    int points;
    long id;

    Card(const std::string& line) : points{ 0 }
    {
        std::vector<std::string> identifiantsEtNombres{ splitString(line, ':') };
        std::vector<std::string> identifiants{ splitString(identifiantsEtNombres[0], ' ') };
        id = parse(identifiants[identifiants.size() - 1]);
        std::vector<std::string> nombres{ splitString(identifiantsEtNombres[1], '|') };
        for (std::string& listeNombres : nombres)
        {
			listeNombres = trimString(listeNombres);
		}
        std::vector<std::string> nombresGagnants{ vectorStringSansVide(splitString(nombres[0], ' '))};
        for (std::string& nombreGagnant : nombresGagnants)
        {
			winningValues.push_back(parse(nombreGagnant));
		}
        std::vector<std::string> valeurs{ vectorStringSansVide(splitString(nombres[1], ' ')) };
        for (std::string& valeur : valeurs)
        {
            values.push_back(parse(valeur));
        }
        for (long valeur : values)
        {
            if (std::find(winningValues.begin(), winningValues.end(), valeur) != winningValues.end())
            {
				if (points == 0)
					points = 1;
				else
					points *= 2;
			}
		}
    }
};

int main()
{
    std::vector<std::string> lines{
        //"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53", "Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19", "Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1", "Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83", "Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36", "Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11"
        donneesFichier("donnees.txt")
    };
    std::vector<Card> cartes{};
    for (std::string& line : lines)
    {
		cartes.push_back(Card(line));
	}
    int sommePoints{ 0 };
    for (Card& carte : cartes)
    {
        sommePoints += carte.points;
    }
    std::cout << "La somme des cartes est de " << sommePoints <<'\n';
}