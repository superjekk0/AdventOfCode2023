#include <string>
#include <sstream>
#include <vector>
#include <fstream>

inline long parse(const std::string& ligne)
{
    std::stringstream conversion {ligne};
    int retour;
    if (!(conversion >> retour))
        retour = 0;
    return retour;
}

inline std::string trimString(const std::string& str)
{
	std::string strTrimmed{ str };
	while (strTrimmed[0] == ' ')
		strTrimmed = strTrimmed.substr(1, strTrimmed.size() - 1);
	while (strTrimmed[strTrimmed.size() - 1] == ' ')
		strTrimmed = strTrimmed.substr(0, strTrimmed.size() - 1);
	return strTrimmed;
}

inline std::vector<std::string> splitString(std::string str, const char separator)
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

inline std::vector<std::string> donneesFichier(const std::string& nomFichier)
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