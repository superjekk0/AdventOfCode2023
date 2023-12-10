#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include "../utils.h"

using Donnees = std::vector<std::string>;

enum TypesTuyau {
	vertical,
	horizontal,
	nord_est,
	nord_ouest,
	sud_ouest,
	sud_est,
	debut,
	pas_tuyau
};

TypesTuyau recuperationTuyau(char tuyau)
{
	switch (tuyau)
	{
	case '|':
		return vertical;
		break;
	case '-':
		return horizontal;
		break;
	case 'L':
		return nord_est;
		break;
	case 'J':
		return nord_ouest;
	case '7':
		return sud_ouest;
		break;
	case 'F':
		return sud_est;
		break;
	case 'S':
		return debut;
		break;
	case '.':
		return pas_tuyau;
		break;
	default:
		assert(false && "How did you get here?");
		break;
	}
}

struct Tuyau {
	TypesTuyau type;
	size_t x;
	size_t y;

	Tuyau(char tuyau, size_t positionX, size_t positionY) : type{ recuperationTuyau(tuyau) }, x{ positionX }, y{ positionY } {}
};

std::vector<Tuyau*> premiersPas(const std::vector<Tuyau>& tuyaux, const Tuyau* const tuyauActuel)
{
	std::vector<Tuyau*> tuyauxAdjacentsDepart;
	auto tuyauAdjacent{ std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
		return tuyau.x == tuyauActuel->x - 1 && tuyau.y == tuyauActuel->y && tuyau.type != TypesTuyau::pas_tuyau;
	}) };

	if (tuyauAdjacent != tuyaux.end())
		tuyauxAdjacentsDepart.push_back(tuyauAdjacent._Ptr);

	tuyauAdjacent = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
		return tuyau.x == tuyauActuel->x + 1 && tuyau.y == tuyauActuel->y && tuyau.type != TypesTuyau::pas_tuyau;
		});

	if (tuyauAdjacent != tuyaux.end())
		tuyauxAdjacentsDepart.push_back(tuyauAdjacent._Ptr);

	tuyauAdjacent = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
		return tuyau.x == tuyauActuel->x && tuyau.y == tuyauActuel->y - 1 && tuyau.type != TypesTuyau::pas_tuyau;
		});

	if (tuyauAdjacent != tuyaux.end())
		tuyauxAdjacentsDepart.push_back(tuyauAdjacent._Ptr);

	tuyauAdjacent = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
		return tuyau.x == tuyauActuel->x && tuyau.y == tuyauActuel->y + 1 && tuyau.type != TypesTuyau::pas_tuyau;
		});

	if (tuyauAdjacent != tuyaux.end())
		tuyauxAdjacentsDepart.push_back(tuyauAdjacent._Ptr);

	return tuyauxAdjacentsDepart;
}

size_t chemin(std::vector<Tuyau>& tuyaux, const Tuyau* tuyauActuel, const Tuyau* tuyauDepart)
{
	size_t deplacements{ 1 };
	const Tuyau* tuyauPrecedent{ tuyauDepart };
	const Tuyau* temp{ nullptr };

	while (true)
	{
		switch (tuyauActuel->type)
		{
		case vertical:
			if (tuyauPrecedent->y < tuyauActuel->y)
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x && tuyau.y == tuyauActuel->y + 1 && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			else
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x && tuyau.y == tuyauActuel->y - 1 && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			break;
		case TypesTuyau::horizontal:
			if (tuyauPrecedent->x < tuyauActuel->x)
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x + 1 && tuyau.y == tuyauActuel->y && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			else
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x - 1 && tuyau.y == tuyauActuel->y && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			break;
		case TypesTuyau::nord_est:
			if (tuyauPrecedent->y < tuyauActuel->y)
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x + 1 && tuyau.y == tuyauActuel->y && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			else
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x && tuyau.y == tuyauActuel->y - 1 && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			break;
		case TypesTuyau::nord_ouest:
			if (tuyauPrecedent->x < tuyauActuel->x)
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x && tuyau.y == tuyauActuel->y - 1 && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			else
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x - 1 && tuyau.y == tuyauActuel->y && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			break;
		case TypesTuyau::sud_ouest:
			if (tuyauPrecedent->x < tuyauActuel->x)
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x && tuyau.y == tuyauActuel->y + 1 && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			else
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x - 1 && tuyau.y == tuyauActuel->y && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			break;
		case TypesTuyau::sud_est:
			if (tuyauPrecedent->x > tuyauActuel->x)
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x && tuyau.y == tuyauActuel->y + 1 && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			else
			{
				temp = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
					return tuyau.x == tuyauActuel->x + 1 && tuyau.y == tuyauActuel->y && tuyau.type != TypesTuyau::pas_tuyau;
					})._Ptr;
			}
			break;
		default:
			break;
		}
		if (temp && temp != tuyaux.end()._Ptr && temp != tuyauDepart)
		{
			++deplacements;
			tuyauPrecedent = tuyauActuel;
			tuyauActuel = temp;
		}
		else if (temp == tuyauDepart)
		{
			return deplacements / 2 + 1;
		}
	}

	return deplacements;
}

size_t nbDeplacements(std::vector<Tuyau>& tuyaux, Tuyau* tuyauActuel)
{
	if (tuyauActuel == tuyaux.end()._Ptr)
		return 0;
	std::vector<Tuyau*> tuyauxAdjacentsDepart{ premiersPas(tuyaux, tuyauActuel) };

	std::vector<size_t> deplacements;

	for (Tuyau* tuyau : tuyauxAdjacentsDepart)
	{
		deplacements.push_back(chemin(tuyaux, tuyau, tuyauActuel));
	}

	std::sort(deplacements.begin(), deplacements.end(), std::greater());

	return (deplacements.size() ? deplacements[0] : 0);
}

int main()
{
	Donnees donnees{
		//donneesFichier("exemple.txt")
		donneesFichier("donnees.txt")
	};

	std::vector<Tuyau> tuyaux;

	for (size_t y{ 0 }; y < donnees.size(); ++y)
	{
		for (size_t x{ 0 }; x < donnees[y].size(); ++x)
		{
			tuyaux.push_back(Tuyau(donnees[y][x], x, y));
		}
	}

	std::cout << nbDeplacements(tuyaux, std::find_if(tuyaux.begin(), tuyaux.end(),
		[](const Tuyau& tuyau)
		{
			return tuyau.type == debut;
		}
	)._Ptr);
}