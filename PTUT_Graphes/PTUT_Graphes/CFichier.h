#pragma once
#include <iostream>

class CFichier
{
private:
	char* FICcontenuFichier; // chaine de caracteres pour stocker le contenu du fichier
	int iFICtailleFichier; // longueur du fichier
	int iFICnbSommets; // nombre de sommets inscrits dans le fichier
	int iFICnbArcs; // nombre d'arcs inscrits dans le fichier
	char** FICListeNumerosSommets; // Liste des numeros des sommets inscrits dans le fichier
	char** FICListeNumerosDebuts; // Liste des numeros des departs des arcs inscrits dans le fichier
	char** FICListeNumerosFins; // Liste des numeros des arrivees des arcs inscrits dans le fichier

	//Lit le nombre de sommets du graphe dans le fichier et le stocke dans l'attribut de classe
	void FIClirenbSommets();
	//Lit le nombre d'arcs du graphe dans le fichier et le stocke dans l'attribut de classe
	void FIClirenbArcs();

	//Lit les numeros des sommets du graphe dans le fichier et la stocke dans l'attribut de classe
	void FIClireSommets();
	//Lit les numeros des arrivees des arcs du graphe dans le fichier et la stocke dans l'attribut de classe
	void FIClireDebuts();
	//Lit les numeros des arrivees des arcs du graphe dans le fichier et la stocke dans l'attribut de classe
	void FIClireFins();

public:
	// Construit un CFichier a partir du nom de fichier pFICcheminFichier passe en parametre
	CFichier(const char* pFICcheminFichier);

	// Renvoie le nombre de CSommets du CGraphe
	int FICgetNBSommets();
	// Renvoie le nombre de CArcs du CGraphe
	int FICgetNBArcs();

	// Renvoie la liste des CSommets du CGraphe
	char** FICgetSommets();
	// Renvoie les numeros des departs des Carcs du CGraphe
	char** FICgetDebuts();
	// Renvoie les numeros des arrivees des Carcs du CGraphe
	char** FICgetFins();
};