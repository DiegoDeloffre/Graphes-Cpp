#pragma once
#include "CArc.h"
#include "CException.h"
#include <iostream>
class CSommet
{
private:
	int iSOMNumero; // numero du sommet

	int iSOMNbArcsArrivants; // nombre d'arcs arrivant au sommet
	CArc ** SOMListeArcsArrivants; // liste des arcs arrivant au sommet

	int iSOMNbArcsPartants; // nombre d'arcs partants du sommet
	CArc ** SOMListeArcsPartants; // liste des arcs partants du sommet

public:
	// Construit un CSommet sans numero
	CSommet();

	// Construit un CSommmet de numero iNumero
	CSommet(int iNumero);

	// Constructeur de recopie d'un CSommet
	CSommet(CSommet &sommet);

	// Destructeur d'un CSommet
	~CSommet();

	// Modifie le numero d'un CSommet avec le nouveau numero iNumero
	void SOMModifierNumeroSommet(int iNumero);
	// Renvoie le numero d'un sommet
	int SOMgetNumeroSommet();
	// Renvoie le nombre de CArcs arrivants d'un CSommet
	int SOMgetNbArcsArrivants();
	// Renvoie le nombre de CArcs partants d'un CSommet
	int SOMgetNbArcsPartants();

	// Renvoie la liste des CArcs arrivants d'un CSommet
	CArc** SOMgetListeArcsArrivants();
	// Renvoie la liste des CArcs partants d'un CSommet
	CArc** SOMgetListeArcsPartants();

	// Ajoute un nouveau CArc arrivant arc a un CSommet
	void SOMAjouterArcArrivant(CArc *arc);
	// Ajoute un nouveau CArc partant arc a un CSommet
	void SOMAjouterArcPartant(CArc *arc);

	// Supprime un CArc arrivant de la destination iSommetDepart
	void SOMSupprimerArcArrivant(int iSommetDepart);
	// Supprime un CArc partant vers la destination iSommetArrivee
	void SOMSupprimerArcPartant(int iSommetArrivee);
	// Supprime tous les CArcs d'un CSommet
	void SOMSupprimerArcs();

};

