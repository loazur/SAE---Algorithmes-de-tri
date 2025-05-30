/**
 * \file fonctions.h
 *
 * Déclaration des fonctions fournies.
 */
#pragma once
#include <vector>
#include <string>

//!\brief Crée un tableau aléatoire
std::vector<int> initTabAleat(size_t N);

//!\brief Crée un tableau presque trié
std::vector<int> initTabPresqueTri(size_t N);

//!\brief Crée un tableau presque trié au début
std::vector<int> initTabPresqueTriDeb(size_t N);

//!\brief Crée un tableau presque trié à la fin
std::vector<int> initTabPresqueTriFin(size_t N);

//!\brief Crée un tableau presque trié entre le début et la fin
std::vector<int> initTabPresqueTriDebFin(size_t N);

//!\brief Vérifie qu'un tableau est correctement trié
void verifTri(const std::vector<int>& tab, const std::string& algoName = {});

//-----------------------------------------------------------------------------------------------------------------------------|

// Tri Sélection - Nombre de comparaison réalisé (en sortie)
unsigned int triSelection(std::vector<int> tab);

// Tri à bulles - Nombre de comparaison réalisé (en sortie)
unsigned int triABulles(std::vector<int> tab);
unsigned int triABullesOpti(std::vector<int> tab);

// Tri à peigne - Nombre de comparaison réalisé (en sortie)
unsigned int triAPeigne(std::vector<int> tab);

// Tri insertion - Nombre de comparaison réalisé (en sortie)
unsigned int triAInsertion(std::vector<int> tab);

// Tri rapide - Nombre de comparaison en référence 
int partition(std::vector<int>& tab, int debut, int fin, unsigned int& nbComparaison);
void triRapide(std::vector<int>& tab, int debut, int fin, unsigned int& nbComparaison);

// Tri cocktail - Nombre de comparaison en référence 
unsigned int triCocktail(std::vector<int> tab);