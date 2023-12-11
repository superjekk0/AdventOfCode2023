#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include "../utils.h"
#include <cmath>

using Donnees = std::vector<std::string>;

enum DansBoucle {
	indefini,
	non,
	oui
};

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
	DansBoucle dansBoucle{ indefini };
	size_t x;
	size_t y;
	TypesTuyau type;

	Tuyau(char tuyau, size_t positionX, size_t positionY) : type{ recuperationTuyau(tuyau) }, x{ positionX }, y{ positionY } {}
};

std::vector<Tuyau*> premiersPas(const std::vector<Tuyau>& tuyaux, const Tuyau* const tuyauActuel)
{
	std::vector<Tuyau*> tuyauxAdjacentsDepart;
	auto tuyauAdjacent{ std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
		return tuyau.x == tuyauActuel->x - 1 && tuyau.y == tuyauActuel->y && tuyau.type != TypesTuyau::pas_tuyau;
	}) };

	if (tuyauAdjacent != tuyaux.end())
	{
		switch (tuyauAdjacent->type)
		{
		case horizontal:
		case TypesTuyau::nord_est:
		case TypesTuyau::sud_est:
			tuyauxAdjacentsDepart.push_back(tuyauAdjacent._Ptr);
			break;
		default:
			break;
		}
	}

	tuyauAdjacent = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
		return tuyau.x == tuyauActuel->x + 1 && tuyau.y == tuyauActuel->y && tuyau.type != TypesTuyau::pas_tuyau;
		});

	if (tuyauAdjacent != tuyaux.end())
	{
		switch (tuyauAdjacent->type)
		{
		case horizontal:
		case TypesTuyau::nord_ouest:
		case TypesTuyau::sud_ouest:
			tuyauxAdjacentsDepart.push_back(tuyauAdjacent._Ptr);
			break;
		default:
			break;
		}
	}

	tuyauAdjacent = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
		return tuyau.x == tuyauActuel->x && tuyau.y == tuyauActuel->y - 1 && tuyau.type != TypesTuyau::pas_tuyau;
		});

	if (tuyauAdjacent != tuyaux.end())
	{
		switch (tuyauAdjacent->type)
		{
		case vertical:
		case TypesTuyau::sud_est:
		case TypesTuyau::sud_ouest:
			tuyauxAdjacentsDepart.push_back(tuyauAdjacent._Ptr);
			break;
		default:
			break;
		}
	}

	tuyauAdjacent = std::find_if(tuyaux.begin(), tuyaux.end(), [tuyauActuel](const Tuyau& tuyau) {
		return tuyau.x == tuyauActuel->x && tuyau.y == tuyauActuel->y + 1 && tuyau.type != TypesTuyau::pas_tuyau;
		});

	if (tuyauAdjacent != tuyaux.end())
	{
		switch (tuyauAdjacent->type)
		{
		case vertical:
		case TypesTuyau::nord_est:
		case TypesTuyau::nord_ouest:
			tuyauxAdjacentsDepart.push_back(tuyauAdjacent._Ptr);
			break;
		default:
			break;
		}
	}

	return tuyauxAdjacentsDepart;
}

size_t chemin(std::vector<Tuyau>& tuyaux, Tuyau* tuyauActuel, Tuyau* tuyauDepart)
{
	size_t deplacements{ 1 };
	Tuyau* tuyauPrecedent{ tuyauDepart };
	tuyauPrecedent->dansBoucle = DansBoucle::oui;
	Tuyau* temp{ nullptr };

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
			tuyauPrecedent->dansBoucle = DansBoucle::oui;
			tuyauActuel = temp;
			tuyauActuel->dansBoucle = DansBoucle::oui;
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

	//for (Tuyau* tuyau : tuyauxAdjacentsDepart)
	//{
	deplacements.push_back(chemin(tuyaux, tuyauxAdjacentsDepart[0], tuyauActuel));
	//}

	//std::sort(deplacements.begin(), deplacements.end(), std::greater());

	return (deplacements.size() ? deplacements[0] : 0);
}

long long aireTuyaux(const std::vector<Tuyau>& tuyaux)
{
	long long aire{ 0 };

	for (int i{ 0 }; i < tuyaux.size() - 1; ++i)
	{
		aire += tuyaux[i].x * tuyaux[i + 1].y;
		aire -= tuyaux[i].y * tuyaux[i + 1].x;
	}
	aire += tuyaux[tuyaux.size() - 1].x
		* tuyaux[0].y;
	aire -= tuyaux[tuyaux.size() - 1].y *
		tuyaux[0].x;

	return aire / 2;
}

long long nbInternes(const std::vector<Tuyau>& tuyaux)
{
	long long aire{ aireTuyaux(tuyaux) };

	aire++;

	aire = aire - tuyaux.size() / 2;

	return static_cast<long long>(aire);
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
	)._Ptr) << '\n';

	std::sort(tuyaux.begin(), tuyaux.end(), [](const Tuyau& tuyau1, const Tuyau& tuyau2) {
		if (tuyau1.y < tuyau2.y)
			return true;
		else if (tuyau1.y > tuyau2.y)
			return false;
		return tuyau1.x < tuyau2.x;
		});

	std::vector<Tuyau> tuyauxDansBoucle;
	for (auto& tuyau : tuyaux)
	{
		if (tuyau.dansBoucle == DansBoucle::oui)
			tuyauxDansBoucle.push_back(tuyau);
	}

	std::cout << "Il y a " << nbInternes(tuyauxDansBoucle) << " tuyaux internes.\n";

	//std::vector<Tuyau> tests{ {'.', 1, 6}, {'.', 3, 1}, {'.', 7, 2}, {'.', 4, 4}, {'.', 8, 5}};

	//std::cout << "Il y a " << aireTuyaux(tests) << " tuyaux internes.\n";

	return 0;
}