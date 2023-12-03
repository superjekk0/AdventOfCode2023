#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "..\utils.h"

std::vector<std::string> lignes{
	//"467..114..", "...*......", "..35..633.", "......#...", "617*......", ".....+.58.", "..592.....", "......755.", "...$.*....", ".664.598.."
	donneesFichier("./donnees.txt")
};

struct Chiffre {
	std::size_t x;
	std::size_t y;
	char chiffre;

	Chiffre(std::size_t x, std::size_t y, char chiffre) : x{ x }, y{ y }, chiffre{ chiffre } {}
};

bool pasNombreActuel(int y, const Chiffre& chiffre)
{
	return y != chiffre.y;

}

bool chiffresAdjacents(const std::vector<Chiffre>& chiffres)
{
	for (auto& chiffre : chiffres)
	{
		for (int i{ (chiffre.x == 0 ? 0 : -1) }; i < (chiffre.x == lignes[chiffre.y].size() - 1 ? 1 : 2); ++i)
		{
			for (int j{ (chiffre.y == 0 ? 0 : -1) }; j < (chiffre.y == lignes.size() - 1 ? 1 : 2); ++j)
			{
				char c {lignes[chiffre.y + j][chiffre.x + i]};
				if (std::isdigit(c) && pasNombreActuel(chiffre.y + j, chiffre))
					return true;
				else if (c != '.' && !std::isdigit(c))
					return true;
			}
		}
	}
	return false;
}

std::vector<std::string> scanLignes(const std::vector<std::string>& lignes)
{
	std::vector<std::string> chiffresValides{};
	std::vector<Chiffre> indexChiffres{};
	for (std::size_t i{ 0 }; i < lignes.size(); ++i)
	{
		for (char c{ '0' }; c <= '9'; ++c)
		{
			for (std::size_t positionChiffre{ lignes[i].find(c) }; positionChiffre != std::string::npos; positionChiffre = lignes[i].find(c, positionChiffre + 1))
			{
				indexChiffres.push_back(Chiffre(positionChiffre, i, c));
			}
		}
	}

	std::sort(indexChiffres.begin(), indexChiffres.end(), [](const Chiffre& a, const Chiffre& b)
		{
			if (a.y < b.y)
				return true;
			else if (a.y > b.y)
				return false;
			else
				return a.x < b.x;
		});

	std::string nombre;
	std::vector<Chiffre> chiffresConsecutifs{};
	for (int i{ 0 }; i < indexChiffres.size(); ++i)
	{
		if (i < indexChiffres.size() - 1)
		{
			chiffresConsecutifs.push_back(indexChiffres[i]);
			if (indexChiffres[i].y != indexChiffres[i + 1].y)
			{
				for (const Chiffre& chiffre : chiffresConsecutifs)
				{
					nombre += chiffre.chiffre;
				}
				if (chiffresAdjacents(chiffresConsecutifs))
					chiffresValides.push_back(nombre);
				nombre.clear();
				chiffresConsecutifs.clear();
			}
			else if (indexChiffres[i].x + 1 != indexChiffres[i + 1].x)
			{

				for (const Chiffre& chiffre : chiffresConsecutifs)
				{
					nombre += chiffre.chiffre;
				}
				if (chiffresAdjacents(chiffresConsecutifs))
					chiffresValides.push_back(nombre);
				nombre.clear();
				chiffresConsecutifs.clear();
			}
			//else
			//{
			//	chiffresConsecutifs.push_back(indexChiffres[i]);
			//}
		}
		else
		{
			chiffresConsecutifs.push_back(indexChiffres[i]);
			for (const Chiffre& chiffre : chiffresConsecutifs)
			{
				nombre += chiffre.chiffre;
			}
			if (chiffresAdjacents(chiffresConsecutifs))
				chiffresValides.push_back(nombre);
		}
	}

	return chiffresValides;
}

int main()
{
	std::vector<std::string> chiffresValides{ scanLignes(lignes) };
	std::vector<long> chiffres;
	for (auto& nombreValide : chiffresValides)
	{
		chiffres.push_back(parse(nombreValide));
	}
	int somme{ 0 };
	for (auto& chiffre : chiffres)
	{
		somme += chiffre;
	}
	std::cout << "La somme est de " << somme << ".\n";
	return 0;
}