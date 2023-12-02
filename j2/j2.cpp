#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <array>
#include <sstream>
#include <fstream>

const std::unordered_map<std::string, int> maximumCubes{
	{"green", 13},
	{"red", 12},
	{"blue", 14}
};

const std::unordered_map<std::string, int> couleurCubes{
	{"green", 0},
	{"red", 1},
	{"blue", 2}
};

std::string trimString(const std::string& str)
{
	std::string strTrimmed{ str };
	while (strTrimmed[0] == ' ')
		strTrimmed = strTrimmed.substr(1, strTrimmed.size() - 1);
	while (strTrimmed[strTrimmed.size() - 1] == ' ')
		strTrimmed = strTrimmed.substr(0, strTrimmed.size() - 1);
	return strTrimmed;
}

std::vector<std::string> splitString(std::string str, const char separator)
{
	std::vector<std::string> listStrings{};
	listStrings.reserve(4);
	for (size_t indexSeparateur{ str.find(separator) }; indexSeparateur != str.npos; indexSeparateur = str.find(separator))
	{
		listStrings.push_back(str.substr(0, indexSeparateur));
		str = str.substr(indexSeparateur + 1, str.size() - indexSeparateur);
	}
	if (str != "")
		listStrings.push_back(str);
	return listStrings;
}

int parse(const std::string& ligne)
{
	std::stringstream conversion{ ligne };
	int retour;
	if (!(conversion >> retour))
		retour = 0;
	return retour;
}

struct Tirage {
	std::array<int, 3> cubes{0,0,0};
	Tirage(const std::string& tirage)
	{
		std::vector<std::string> cubes{ splitString(tirage, ',') };
		for (auto& cube : cubes)
		{
			std::vector<std::string> cubeTexte{ splitString(trimString(cube), ' ') };
			int nombre{ parse(cubeTexte[0]) };
			std::string couleur{ cubeTexte[1] };
			this->cubes[couleurCubes.at(couleur)] = nombre;
		}
	}
};

struct Jeu {
	int id;
	std::vector<Tirage> tirages;

	Jeu(const std::string& ligne)
	{
		std::vector<std::string> jeu{ splitString(ligne, ':') };
		id = parse(splitString(jeu[0], ' ')[1]);
		std::vector<std::string> tiragesTexte { splitString(jeu[1], ';') };
		std::vector<Tirage> tirages{};
		tirages.reserve(tiragesTexte.size());
		for (auto& tirage : tiragesTexte)
		{
			this->tirages.push_back(Tirage(tirage));
		}
	}

	bool tiragesValide() const
	{
		for (auto& couleurCube : couleurCubes)
		{
			for (auto& tirage : tirages)
			{
				if (tirage.cubes[couleurCubes.at(couleurCube.first)] > maximumCubes.at(couleurCube.first))
					return false;
			}
		}
		return true;
	}
};

std::vector<Jeu> verification(const std::vector<std::string>& lignes)
{
	std::vector<Jeu> jeux{};
	jeux.reserve(lignes.size());
	for (auto& ligne : lignes)
	{
		Jeu jeu { ligne };
		if (jeu.tiragesValide())
			jeux.push_back(jeu);
	}
	return jeux;
}

std::vector<std::string> donneesFichier(const std::string& nomFichier)
{
	std::ifstream fichier{ nomFichier };
	std::vector<std::string> lignes{};
	std::string ligne{};
	while (fichier)
	{
		std::getline(fichier, ligne);
		lignes.push_back(ligne);
	}
	if (lignes[lignes.size() - 1] == "")
		lignes.pop_back();

	return lignes;
}

int main()
{
	std::vector<std::string> lignes{
		//"Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green",
		//"Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue",
		//"Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red",
		//"Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red",
		//"Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"
			donneesFichier("donnees.txt")
	};
	std::vector<Jeu> jeuxValides{ verification(lignes) };
	int somme{ 0 };
	for (auto& jeu : jeuxValides)
	{
		somme += jeu.id;
	}
	std::cout << "Le total des ID de jeux valides est " << somme;
}