/**
 * \file fonctions.cpp
 * 
 * Définition des fonctions fournies.
 */
#include "./headers/fonctions.h"
#include <iostream>

/**
 * Crée un tableau d'entiers dont tous les éléments sont choisis aléatoirement.
 * 
 * Un tel tableau peut par exemple être 30968 28073 31177 2882 6140 17999 13828 20039 2310 24865.
 * 
 * \param[in] N taille du tableau
 * \return le tableau initialisé
 */

std::vector<int> initTabAleat(size_t N)
{
	std::vector<int> tab(N);

	for (auto& val : tab)
		val = rand();

	return tab;
}

/**
 * Crée un tableau d'entiers presque triés. Chaque élément est quasiment à sa place définitive, échangé éventuellement d'une place.
 * 
 * Un tel tableau peut par exemple être 1 3 2 4 6 5 8 7 9 10.
 *
 * \param[in] N taille du tableau
 * \return le tableau initialisé
 */
std::vector<int> initTabPresqueTri(size_t N)
{
	std::vector<int> tab(N);

	for (int i = 0; i < N; i++)
		tab[i] = i;

	for (int i = 0; i < N-1; i++)
	{
		if (rand() % 2 == 0)
		{
			std::swap(tab[i], tab[i + 1]);
			++i;
		}
	}

	return tab;
}

/**
 * Crée un tableau d'entiers presque triés. Seuls le premier et le deuxième élément sont échangés.
 *
 * Un tel tableau peut par exemple être 2 1 3 4 5 6 7 8 9 10.
 *
 * \param[in] N taille du tableau
 * \return le tableau initialisé
 */

std::vector<int> initTabPresqueTriDeb(size_t N)
{
	std::vector<int> tab(N);
	for (int i = 0; i < N; i++)
		tab[i] = i;
	std::swap(tab[0], tab[1]);
	return tab;
}

/**
 * Crée un tableau d'entiers presque triés. Seuls le dernier et l'avant dernier élément sont échangés.
 *
 * Un tel tableau peut par exemple être 1 2 3 4 5 6 7 8 10 9.
 *
 * \param[in] N taille du tableau
 * \return le tableau initialisé
 */

std::vector<int> initTabPresqueTriFin(size_t N)
{
	std::vector<int> tab(N);
	for (int i = 0; i < N; i++)
		tab[i] = i;
	std::swap(tab[N - 1], tab[N - 2]);
	return tab;
}

/**
 * Crée un tableau d'entiers presque triés. Seuls le premier et le dernier élément sont échangés.
 *
 * Un tel tableau peut par exemple être 10 2 3 4 5 6 7 8 9 1.
 *
 * \param[in] N taille du tableau
 * \return le tableau initialisé
 */
std::vector<int> initTabPresqueTriDebFin(size_t N)
{
	std::vector<int> tab(N);
	for (int i = 0; i < N; i++)
		tab[i] = i;
	std::swap(tab[N - 1], tab[0]);
	return tab;
}

/**
 * Vérifie qu'un tableau est correctement trié. Si le tableau est mal trié, un message d'erreur est
 * affiché sur le flux d'erreur et le programme est terminé.
 * 
 * \param[in] tab Le tableau à vérifier
 * \param[in] algoName Le nom de l'algorithme de tri qui a été utilisé. Ce paramètre est optionnel.
 */

void verifTri(const std::vector<int>& tab, const std::string& algoName)
{
	const size_t taille = tab.size();

	for (size_t i = 1; i < taille; i++)
	{
		if (tab[i - 1] > tab[i])
		{
			std::cerr << "Erreur dans le tri " << algoName << (algoName.empty() ? "!" : " !") << '\n';
			exit(EXIT_FAILURE);
		}
	}
}

// ------------------------------------------------------------------------
// Tri Séléction
unsigned int triSelection(std::vector<int> tab)
{
	unsigned int numComparaison = 0;
	const int tailleTab = tab.size();

	for (int i = 0; i < tailleTab - 1; ++i)
	{
		int min = i;

		for (int j = i + 1; j < tailleTab; ++j)
		{
			if (tab[j] < tab[min])
			{
				min = j;
				++numComparaison;
			}

		}

		if (min != i)
		{
			const int varTemp = tab[i];
			tab[i] = tab[min];
			tab[min] = varTemp;
			numComparaison++;
		}
	}

	return numComparaison;
}

// Tri à bulles
unsigned int triABulles(std::vector<int> tab)
{
    unsigned int numComparaisons = 0;
    for (size_t i = tab.size(); i > 1; --i)
    {
        for (size_t j = 0; j < i - 1; ++j)
        {
            numComparaisons++;
            if (tab[j] > tab[j + 1])
            {
                std::swap(tab[j], tab[j + 1]);
            }
        }
    }
    return numComparaisons;
}

// Version optimisée
unsigned int triABullesOpti(std::vector<int> tab)
{
    unsigned int numComparaisons = 0;
    for (size_t i = tab.size(); i > 1; --i)
    {
        bool tableauTrie = true;
        for (size_t j = 0; j < i - 1; ++j)
        {
            numComparaisons++;
            if (tab[j] > tab[j + 1])
            {
                std::swap(tab[j], tab[j + 1]);
                tableauTrie = false;
            }
        }
        if (tableauTrie)
        {
            break;
        }
    }
    return numComparaisons;
}

// Tri à peigne
unsigned int triAPeigne(std::vector<int> tab)
{
	unsigned int numComparaison = 0;

	int intervalle = tab.size();
	bool echange = false;

	while (intervalle > 1 || echange == true)
	{
		intervalle = int(intervalle / 1.3);

		if (intervalle < 1)
		{
			intervalle = 1;
			numComparaison++;
		}

		int i = 0;
		echange = false;

		while (i < tab.size() - intervalle)
		{
			if (tab[i] > tab[i + intervalle])
			{
				int varTemp = tab[i];
				tab[i] = tab[i + intervalle];
				tab[i + intervalle] = varTemp;

				echange = true;
				++numComparaison;
			}

			++i;
		}
	}

	return numComparaison;
}

// Tri insertion
unsigned int triAInsertion(std::vector<int> tab)
{
    unsigned int numComparaison = 0;

    for (int i = 1; i < tab.size(); ++i)
    {
        numComparaison++;

        int x = tab[i];

        int j = i;
        while (j > 0 && tab[j - 1] > x)
        {
            tab[j] = tab[j - 1];

            j--;
            numComparaison++;
        }

        tab[j] = x;
    }

    return numComparaison;
}

// Tri Rapide
int partition(std::vector<int>& tab, int debut, int fin, unsigned int& nbComparaison)
{
	int pivot = tab[fin];
	int i = debut - 1;

	for (int j = debut; j < fin; ++j)
	{
		nbComparaison++;

		if (tab[j] < pivot)
		{
			i++;
			std::swap(tab[i], tab[j]);
		}
	}

	std::swap(tab[i + 1], tab[fin]);
	return i + 1;
}

void triRapide(std::vector<int>& tab, int debut, int fin, unsigned int& nbComparaison)
{
	if (debut < fin)
	{
		int pivotIndex = partition(tab, debut, fin, nbComparaison);
		triRapide(tab, debut, pivotIndex - 1, nbComparaison);
		triRapide(tab, pivotIndex + 1, fin, nbComparaison);
	}
}

// Tri cocktail
unsigned int triCocktail(std::vector<int> tab)
{
    unsigned int numComparaison = 0;
    bool echanger = true;

    while (echanger)
    {
        echanger = false;

        for (int i = 0; i < tab.size() - 1; ++i)
        {
            if (tab[i] > tab[i + 1])
            {
                int tmp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = tmp;
                echanger = true;
                numComparaison++;
            }
        }

        for (int i = tab.size() - 2; i >= 0; --i)
        {
            if (tab[i] > tab[i + 1])
            {
                int tmp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = tmp;
                echanger = true;
                numComparaison++;
            }
        }
    }

    return numComparaison;
}