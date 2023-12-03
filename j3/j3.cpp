#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "..\utils.h"

std::vector<std::string> lignes{
	//"467..114..", "...*......", "..35..633.", "......#...", "617*......", ".....+.58.", "..592.....", "......755.", "...$.*....", ".664.598.."
	donneesFichier("./donnees.txt")
};

struct Nombre;
std::vector<Nombre> detectNumbers(std::size_t x, std::size_t y, const std::vector<Nombre>& nombres);

std::vector<Nombre> nombres{};

struct Gear {
	std::size_t x;
	std::size_t y;
	std::vector<Nombre> nombres;
	Gear(std::size_t x, std::size_t y, const std::vector<Nombre> tousNombres) : x{ x }, y{ y }, nombres{ detectNumbers(x, y, tousNombres) } {}
};

std::vector<Gear> gears{};

struct Chiffre {
	std::size_t x;
	std::size_t y;
	char chiffre;

	Chiffre(std::size_t x, std::size_t y, char chiffre) : x{ x }, y{ y }, chiffre{ chiffre } {}
};

struct Nombre {
	std::vector<Chiffre> chiffres;
	std::size_t debutX;
	std::size_t finX;
	std::size_t y;

	Nombre(const std::vector<Chiffre>& chiffres) : chiffres{ chiffres }, debutX{ chiffres[0].x }, finX{ chiffres[chiffres.size() - 1].x }, y{ chiffres[0].y }
	{

	}

	operator long()
	{
		std::string chaineNombre;
		for (const auto& chiffre : chiffres)
		{
			chaineNombre += chiffre.chiffre;
		}
		return parse(chaineNombre);
	}
};

std::vector<Nombre> detectNumbers(std::size_t x, std::size_t y, const std::vector<Nombre>& nombres)
{
	std::vector<Nombre> nombresDetectes{};
	for (const Nombre& nombre : nombres)
	{
		for (int i{ (x == 0 ? 0 : -1) }; i < (x == lignes[y].size() - 1 ? 1 : 2); ++i)
		{
			for (int j{ (y == 0 ? 0 : -1) }; j < (y == lignes.size() - 1 ? 1 : 2); ++j)
			{
				if (y + j == nombre.y && x + i >= nombre.debutX && x + i <= nombre.finX)
				{
					nombresDetectes.push_back(nombre);
					goto prochainNombre;
				}
			}
		}
	prochainNombre:;
	}
	return nombresDetectes;
}

bool pasNombreActuel(int y, const Chiffre& chiffre)
{
	return y != chiffre.y;
}

bool chiffresAdjacents(const Nombre& nombre)
{
	for (auto& chiffre : nombre.chiffres)
	{
		for (int i{ (chiffre.x == 0 ? 0 : -1) }; i < (chiffre.x == lignes[chiffre.y].size() - 1 ? 1 : 2); ++i)
		{
			for (int j{ (chiffre.y == 0 ? 0 : -1) }; j < (chiffre.y == lignes.size() - 1 ? 1 : 2); ++j)
			{
				char c{ lignes[chiffre.y + j][chiffre.x + i] };
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

	std::string chaineNombre;
	std::vector<Chiffre> chiffresConsecutifs{};
	for (int i{ 0 }; i < indexChiffres.size(); ++i)
	{
		if (i < indexChiffres.size() - 1)
		{
			chiffresConsecutifs.push_back(indexChiffres[i]);
			if (indexChiffres[i].y != indexChiffres[i + 1].y)
			{
				Nombre nombre{ chiffresConsecutifs };
				for (const Chiffre& chiffre : chiffresConsecutifs)
				{
					chaineNombre += chiffre.chiffre;
				}
				nombres.push_back(nombre);
				if (chiffresAdjacents(nombre))
					chiffresValides.push_back(chaineNombre);
				chaineNombre.clear();
				chiffresConsecutifs.clear();
			}
			else if (indexChiffres[i].x + 1 != indexChiffres[i + 1].x)
			{
				Nombre nombre{ chiffresConsecutifs };
				for (const Chiffre& chiffre : chiffresConsecutifs)
				{
					chaineNombre += chiffre.chiffre;
				}
				nombres.push_back(nombre);
				if (chiffresAdjacents(nombre))
				{
					chiffresValides.push_back(chaineNombre);
				}
				chaineNombre.clear();
				chiffresConsecutifs.clear();
			}
		}
		else
		{
			chiffresConsecutifs.push_back(indexChiffres[i]);
			Nombre nombre{ chiffresConsecutifs };
			for (const Chiffre& chiffre : chiffresConsecutifs)
			{
				chaineNombre += chiffre.chiffre;
			}
			nombres.push_back(nombre);
			if (chiffresAdjacents(nombre))
			{
				chiffresValides.push_back(chaineNombre);
			}
		}
	}

	for (std::size_t i{ 0 }; i < lignes.size(); ++i)
	{
		for (std::size_t positionChiffre{ lignes[i].find('*')}; positionChiffre != std::string::npos; positionChiffre = lignes[i].find('*', positionChiffre + 1))
		{
			gears.push_back(Gear(positionChiffre, i, nombres));	
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
	std::vector<Gear> gearsValides{};
	for (auto& gear : gears)
	{
		if (gear.nombres.size() == 2)
			gearsValides.push_back(gear);
	}
	long sommeGears{ 0 };
	for (auto& gear : gearsValides)
	{
		sommeGears += gear.nombres[0] * gear.nombres[1];
	}
	std::cout << "La somme des gears est de " << sommeGears << ".\n";
	return 0;
}