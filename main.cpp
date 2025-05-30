#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#include <iostream>
#include <fstream>
#include <ctime>
#include <array>

#include "./headers/fonctions.h"

// Fonctions .csv
void ajoutsChampsCSV(const std::string& nomTri, std::vector<std::string>& champs);
void ajoutsDonneesCSV(unsigned int (*tri) (std::vector<int>), std::ofstream& fichier, const int tailleTab);

int main()
{
    // Pour l'encodage
    #ifdef _WIN32
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    #endif // _WIN32

    
    // Création du fichier
    std::ofstream out("fichierComparaison.csv");

    // Vérification de la création
    if (!out.is_open())
    {
        // std::cerr = console error
        std::cerr << "Problème d'ouverture du fichier \"fichierComparaison.csv\". \n";
        return 1;
    }

    // Pointeurs des fonctions de tri 
    const size_t nombreFonctionsTri = 6;

    unsigned int (*pTriSelection) (std::vector<int>) = triSelection;
    unsigned int (*pTriABulles) (std::vector<int>) = triABulles;
    unsigned int (*pTriABullesOpti) (std::vector<int>) = triABullesOpti;
    unsigned int (*pTriAPeigne) (std::vector<int>) = triAPeigne;
    unsigned int (*pTriAInsertion) (std::vector<int>) = triAInsertion;
    unsigned int (*pTriCocktail) (std::vector<int>) = triCocktail;
    
    void (*pTriRapide) (std::vector<int>&, int, int, unsigned int&) = triRapide;

    // Tableaux de fonctions de tri
    unsigned int (*tabFonctionsTri[nombreFonctionsTri]) (std::vector<int>) = {pTriSelection, pTriABulles, pTriABullesOpti, pTriAPeigne, pTriAInsertion, triCocktail};
    std::array<std::string, nombreFonctionsTri + 1> nomsFonctionsTri = {"Select.", "Bulles.", "Bulles Opti.", "Peigne.", "Insert.", "Cocktail.", "Rapide."};  // ! BIEN AJOUTER DANS LES DEUX LORS D'UN AJOUT D'UN TRI
    // ^^ nombreFonction +1 pour Tri Rapide

    // Tout les champs 
    std::vector<std::string> champs = {"N"};

    for (std::string nomTri : nomsFonctionsTri)
    {
        ajoutsChampsCSV(nomTri, champs);
    }

    // Ajout des champs dans le fichier
    for (std::string champ : champs)
    {
        if (champ == champs[champs.size() - 1])
        {
            out << champ << "\n";
            break;
        }

        out << champ << ",";
    }

    // Création de la graine
    std::srand(std::time(0));
	std::rand();

    const int range_max = 500;
    const int range_min = 0;    
    const int nombreDonnees = 300;
    
    // Ajouts des données
    for (int i = 1; i <= nombreDonnees; ++i)
    {
        // Ajout de chaque fonction (sauf Tri Rapide) dans le .csv
        for (unsigned int (*fonctionTri) (std::vector<int>) : tabFonctionsTri)
        {
            ajoutsDonneesCSV(fonctionTri, out, i);
        }
        
        // Tri Rapide
        unsigned int numComparaisonRapide;
        std::vector<int> tab = initTabAleat(i);
        triRapide(tab, 0, i - 1, numComparaisonRapide);
        
        out << i << ",";

        numComparaisonRapide = 0;
        tab = initTabPresqueTri(i);
        triRapide(tab, 0, i - 1, numComparaisonRapide);

        out << numComparaisonRapide << ",";

        numComparaisonRapide = 0;
        tab = initTabPresqueTriDeb(i);
        triRapide(tab, 0, i - 1, numComparaisonRapide);
        
        out << numComparaisonRapide << ",";

        numComparaisonRapide = 0;
        tab = initTabPresqueTriDebFin(i);
        triRapide(tab, 0, i - 1, numComparaisonRapide);
        
        out << numComparaisonRapide << ",";

        numComparaisonRapide = 0;
        tab = initTabPresqueTriFin(i);
        triRapide(tab, 0, i - 1, numComparaisonRapide);
        
        out << numComparaisonRapide << "\n";
    }

    return 0;
}

// ------------------------------- Fonctions liés au .csv -------------------------------
void ajoutsChampsCSV(const std::string& nomTri, std::vector<std::string>& champs)
{
    champs.push_back("Aléat " + nomTri);
    champs.push_back("PresqueTri " + nomTri);
    champs.push_back("PresqueTriDeb " + nomTri);
    champs.push_back("PresqueTriDebFin " + nomTri);
    champs.push_back("PresqueTriFin " + nomTri);
}

void ajoutsDonneesCSV(unsigned int (*tri) (std::vector<int>), std::ofstream& fichier, const int tailleTab)
{
    fichier << tailleTab << "," << tri(initTabAleat(tailleTab)) << "," << tri(initTabPresqueTri(tailleTab)) << "," << tri(initTabPresqueTriDeb(tailleTab)) << "," << tri(initTabPresqueTriDebFin(tailleTab)) << "," << tri(initTabPresqueTriFin(tailleTab)) << ",";
}