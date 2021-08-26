#include "CSommet.h"
#include <malloc.h>

// Construit un CSommet sans numero
CSommet::CSommet()
{
	this->iSOMNumero = -1;
	this->iSOMNbArcsArrivants = 0;
	this->SOMListeArcsArrivants = nullptr;
	this->iSOMNbArcsPartants = 0;
	this->SOMListeArcsPartants = nullptr;
}

// Construit un CSommmet de numero iNumero
CSommet::CSommet(int iNumero)
{
	this->iSOMNumero = iNumero;
	this->iSOMNbArcsArrivants = 0;
	this->SOMListeArcsArrivants = nullptr;
	this->iSOMNbArcsPartants = 0;
	this->SOMListeArcsPartants = nullptr;
}

// Constructeur de recopie d'un CSommet
CSommet::CSommet(CSommet& sommet)
{
	// on recupere le numero du CSommet passe en parametre
	this->iSOMNumero = sommet.SOMgetNumeroSommet();

	// on parcourt tous les CArcs arrivants du CSommet passe en parametre
	for (int iCompteurArcsArrivants = 0; iCompteurArcsArrivants < sommet.SOMgetNbArcsArrivants(); iCompteurArcsArrivants++) {
		// on les ajoute au nouveau CSommet recopie
		this->SOMAjouterArcArrivant(sommet.SOMListeArcsArrivants[iCompteurArcsArrivants]);
	}

	// on parcourt tous les CArcs partants du CSommet passe en parametre
	for (int iCompteurArcsPartants = 0; iCompteurArcsPartants < sommet.SOMgetNbArcsPartants(); iCompteurArcsPartants++) {
		// on les ajoute au nouveau CSommet recopie
		this->SOMAjouterArcPartant(sommet.SOMListeArcsPartants[iCompteurArcsPartants]);
	}
}

// Destructeur d'un CSommet
CSommet::~CSommet()
{
	// on parcourt tous les CArcs arrivants du CSommet
	for (int iCompteurArcsArrivants = 0; iCompteurArcsArrivants < this->iSOMNbArcsArrivants; iCompteurArcsArrivants++) {
		// on supprime les CArcs de la liste
		delete this->SOMListeArcsArrivants[iCompteurArcsArrivants];
	}

	// on parcourt tous les CArcs partants du CSommet
	for (int iCompteurArcsPartants = 0; iCompteurArcsPartants < this->iSOMNbArcsPartants; iCompteurArcsPartants++) {
		// on supprime les CArcs de la liste
		delete this->SOMListeArcsPartants[iCompteurArcsPartants];
	}

	// on libere les zones memoires des listes
	free(this->SOMListeArcsArrivants);
	free(this->SOMListeArcsPartants);
}

// Modifie le numero d'un CSommet avec le nouveau numero iNumero
void CSommet::SOMModifierNumeroSommet(int iNumero)
{
	this->iSOMNumero = iNumero;
}

// Renvoie le numero d'un sommet
int CSommet::SOMgetNumeroSommet()
{
	return this->iSOMNumero;
}

// Renvoie le nombre de CArcs arrivants d'un CSommet
int CSommet::SOMgetNbArcsArrivants()
{
	return this->iSOMNbArcsArrivants;
}

// Renvoie le nombre de CArcs partants d'un CSommet
int CSommet::SOMgetNbArcsPartants()
{
	return this->iSOMNbArcsPartants;
}

// Renvoie la liste des CArcs arrivants d'un CSommet
CArc** CSommet::SOMgetListeArcsArrivants()
{
	return this->SOMListeArcsArrivants;
}

// Renvoie la liste des CArcs partants d'un CSommet
CArc** CSommet::SOMgetListeArcsPartants()
{
	return this->SOMListeArcsPartants;
}

// Ajoute un nouveau CArc arrivant arc a un CSommet
void CSommet::SOMAjouterArcArrivant(CArc *arc)
{
	// on parcourt tous les CArcs arrivants du CSommet
	for (int iCompteurArcsArrivants = 0; iCompteurArcsArrivants < this->iSOMNbArcsArrivants; iCompteurArcsArrivants++) {
		// si un CArc similaire existe
		if (this->SOMListeArcsArrivants[iCompteurArcsArrivants]->ARCgetDestination() == arc->ARCgetDestination()) {
			// On leve une CException
			throw CException(DoublonArc, "L'arc existe deja.");
		}
	}
	
	// si aucun CArc similaire n'a ete trouve
	// on incremente le nombre de CArc du CSommet
	this->iSOMNbArcsArrivants++;
	
	// on realloue la zone memoire avec un CArc de plus
	this->SOMListeArcsArrivants = (CArc**)realloc(this->SOMListeArcsArrivants, (sizeof(CArc*) * this->iSOMNbArcsArrivants));
	
	//On verifie les ereurs de reallocation en levant une CException
	if (this->SOMListeArcsArrivants == NULL) {
		// On leve une CException
		throw CException(ErreurRealloc, "Il y a eu un probleme avec la reallocation.");
	}

	// on ajoute le nouveau CArc a la liste
	this->SOMListeArcsArrivants[this->iSOMNbArcsArrivants-1] = new CArc(*arc);
}

// Ajoute un nouveau CArc partant arc a un CSommet
void CSommet::SOMAjouterArcPartant(CArc *arc)
{
	// on parcourt tous les CArcs partants du CSommet
	for (int iCompteurArcsPartants = 0; iCompteurArcsPartants < this->iSOMNbArcsPartants; iCompteurArcsPartants++) {
		// si un CArc similaire existe
		if (this->SOMListeArcsPartants[iCompteurArcsPartants]->ARCgetDestination() == arc->ARCgetDestination()) {
			// On leve une CException
			throw CException(DoublonArc, "L'arc existe deja.");
		}
	}

	// si aucun CArc similaire n'a ete trouve
	// on incremente le nombre de CArc du CSommet
	this->iSOMNbArcsPartants++;
	
	// on realloue la zone memoire avec un CArc de plus
	this->SOMListeArcsPartants = (CArc**)realloc(this->SOMListeArcsPartants, (sizeof(CArc*) * this->iSOMNbArcsPartants));
	
	//On verifie les ereurs de reallocation en levant une CException
	if (this->SOMListeArcsPartants == NULL) {
		throw CException(ErreurRealloc, "Il y a eu un probleme avec la reallocation.");
	}

	// on ajoute le nouveau CArc a la liste
	this->SOMListeArcsPartants[this->iSOMNbArcsPartants-1] = new CArc(*arc);
}

// Supprime un CArc arrivant de la destination iSommetDepart
void CSommet::SOMSupprimerArcArrivant(int iSommetDepart)
{
	bool arcTrouve = false;

	// on parcourt tous les Carcs arrivants du CSommet
	for (int iCompteurArcsArrivants = 0; iCompteurArcsArrivants < this->iSOMNbArcsArrivants; iCompteurArcsArrivants++) {
		// si le CArc recherche existe
		if (this->SOMListeArcsArrivants[iCompteurArcsArrivants]->ARCgetDestination() == iSommetDepart) {
			// on indique qu'ila ete trouve
			arcTrouve = true;
			// on le supprime
			delete(this->SOMListeArcsArrivants[iCompteurArcsArrivants]);
		}

		// si le CArc a ete trouve et que ce n'est pas le dernier de la liste
		if (arcTrouve && iCompteurArcsArrivants <= this->iSOMNbArcsArrivants) {
			// on decale les CArcs se situant après dans la liste
			this->SOMListeArcsArrivants[iCompteurArcsArrivants] = this->SOMListeArcsArrivants[iCompteurArcsArrivants + 1];
		}
	}

	// si le CArc n'a pas ete trouve
	if (!arcTrouve) {
		// On leve une CException
		throw CException(ArcManquant, "L'arc n'a pas ete trouve");
	}
	// Si le CArc a ete trouve
	else {
		// on decremente le nombre de CArcs dans la liste
		this->iSOMNbArcsArrivants--;

		// si la liste est vide
		if (this->iSOMNbArcsArrivants == 0) {
			// on lui affecte un pointeur null
			this->SOMListeArcsArrivants = nullptr;
		}
		// s'il reste des CArcs dans la liste
		else {
			// on realloue la zone memoire de la liste avec un CArc de moins
			this->SOMListeArcsArrivants = (CArc**)realloc(this->SOMListeArcsArrivants, (sizeof(CArc*) * this->iSOMNbArcsArrivants));

			//On verifie les ereurs de reallocation en levant une CException
			if (this->SOMListeArcsArrivants == NULL) {
				throw CException(ErreurRealloc, "Il y a eu un probleme avec la reallocation.");
			}
		}
	}
}

// Supprime un CArc partant vers la destination iSommetArrivee
void CSommet::SOMSupprimerArcPartant(int iSommetArrivee)
{
	bool arcTrouve = false;
	// on parcourt tous les Carcs partants du CSommet
	for (int iCompteurArcsPartants = 0; iCompteurArcsPartants < this->iSOMNbArcsPartants; iCompteurArcsPartants++) {
		// si le CArc recherche existe
		if (this->SOMListeArcsPartants[iCompteurArcsPartants]->ARCgetDestination() == iSommetArrivee) {
			// on indique qu'ila ete trouve
			arcTrouve = true;
			// on le supprime
			delete(this->SOMListeArcsPartants[iCompteurArcsPartants]);
		}

		// si le CArc a ete trouve et que ce n'est pas le dernier de la liste
		if (arcTrouve && iCompteurArcsPartants <= this->iSOMNbArcsPartants) {
			// on decale les CArcs se situant après dans la liste
			this->SOMListeArcsPartants[iCompteurArcsPartants] = SOMListeArcsPartants[iCompteurArcsPartants + 1];
		}
	}
	// si le CArc n'a pas ete trouve
	if (!arcTrouve) {
		// On leve une CException
		throw CException(ArcManquant, "L'arc n'a pas ete trouve");
	}
	// Si le CArc a ete trouve
	else {
		// on decremente le nombre de CArcs dans la liste
		this->iSOMNbArcsPartants--;

		// si la liste est vide
		if (this->iSOMNbArcsPartants == 0) {
			// on lui affecte un pointeur null
			this->SOMListeArcsPartants = nullptr;
		}
		// s'il reste des CArcs dans la liste
		else {
			// on realloue la zone memoire de la liste avec un CArc de moins
			this->SOMListeArcsPartants = (CArc**)realloc(this->SOMListeArcsPartants, (sizeof(CArc*) * this->iSOMNbArcsPartants));

			//On verifie les ereurs de reallocation en levant une CException
			if (this->SOMListeArcsPartants == NULL) {
				throw CException(ErreurRealloc, "Il y a eu un probleme avec la reallocation.");
			}
		}
	}
}

// Supprime tous les CArcs d'un CSommet
void CSommet::SOMSupprimerArcs()
{
	// on parcourt tous les CArcs arrivants du CSommet
	for (int iCompteurArcsArrivants = 0; iCompteurArcsArrivants < this->iSOMNbArcsArrivants; iCompteurArcsArrivants++) {
		// on les supprimme
		delete this->SOMListeArcsArrivants[iCompteurArcsArrivants];
	}

	// on parcourt tous les CArcs partants du CSommet
	for (int iCompteurArcsPartants = 0; iCompteurArcsPartants < this->iSOMNbArcsPartants; iCompteurArcsPartants++) {
		// on les supprime
		delete this->SOMListeArcsPartants[iCompteurArcsPartants];
	}
	// on affecte des pointeurs null aux listes de CArcs partants et arrivants
	this->SOMListeArcsArrivants = nullptr;
	this->SOMListeArcsPartants = nullptr;

	// on que indique le nombre de CArs partants et arrivants est egal a 0
	this->iSOMNbArcsArrivants = 0;
	this->iSOMNbArcsPartants = 0;
}
