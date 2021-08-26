#include "CGraphe.h"
#include <malloc.h>
using namespace std;

// Construit un CGraphe vide
CGraphe::CGraphe()
{
	this->iGRANbSommets = 0;
	this->GRAListeSommets = nullptr;
}

// Constructeur de recopie d'un CGraphe
CGraphe::CGraphe(CGraphe &graphe)
{
	this->iGRANbSommets = 0;
	this->GRAListeSommets = nullptr;

	// on parcourt tous les CSommets du CGraphe
	for (int iCompteurSommets = 0; iCompteurSommets < graphe.iGRANbSommets; iCompteurSommets++) {
		// on instancie un nouveau CSommet
		CSommet* sommet = new CSommet(*graphe.GRAListeSommets[iCompteurSommets]);
		// on l'ajoute au CGraphe
		this->GRAAjouterSommet(sommet);
	}
}

// Destructeur d'un CGraphe
CGraphe::~CGraphe()
{
	// on parcourt tous les CSommets du CGraphe
	for (int iCompteurSommets = 0; iCompteurSommets < this->iGRANbSommets; iCompteurSommets++) {
		// on supprime tous les CSommets
		delete this->GRAListeSommets[iCompteurSommets];
	}
	// on libere la zone memoire de la liste
	free(this->GRAListeSommets);
}

// Ajoute le CSommet sommet au CGraphe
void CGraphe::GRAAjouterSommet(CSommet* sommet)
{
	// on recupere le numero du CSommet
	int iNumero = sommet->SOMgetNumeroSommet();

	// si il y a un ou plusieurs CSommets
	if (this->iGRANbSommets != 0) {
		// on parcourt tous les CSommets
		for (int iCompteurSommets = 0; iCompteurSommets < this->iGRANbSommets; iCompteurSommets++) {
			// si un CSommet similaire existe deja
			if (this->GRAListeSommets[iCompteurSommets]->SOMgetNumeroSommet() == iNumero) {
				// On leve une CException
				throw CException(DoublonSommet, "Le sommet existe deja.");
			}
		}
	}

	// on incremente le nb de CSommets totaux
	this->iGRANbSommets++;

	// on agrandit la zone memoire de la liste des CSommets pour ajouter le nouveau CSommet
	this->GRAListeSommets = (CSommet**)realloc(this->GRAListeSommets, (sizeof(CSommet*) * this->iGRANbSommets));

	//On verifie les ereurs de reallocation en levant une CException
	if (this->GRAListeSommets == NULL) {
		throw CException(ErreurRealloc, "Il y a eu un probleme avec la reallocation.");
	}

	// on ajoute le nouveau CSommet a la liste
	this->GRAListeSommets[this->iGRANbSommets - 1] = sommet;
}

// Ajoute un CSommet au Cgraphe
CSommet* CGraphe::GRAAjouterSommet(int iNumero)
{
	// s'il a deja un ou plusieurs CSommets 
	if (iGRANbSommets != 0) {
		//on parcourt tous les CSommets existants
		for (int iCompteurSommets = 0; iCompteurSommets < this->iGRANbSommets; iCompteurSommets++) {
			// si l'un des CSommets existants a le meme numero que celui qu'on veut ajouter
			if (this->GRAListeSommets[iCompteurSommets]->SOMgetNumeroSommet() == iNumero) {
				// On leve une CException
				throw CException(DoublonSommet, "Le sommet existe deja.");
			}
		}
	}

	// on instancie un nouveau CSommet avec le numero passe en parametre
	CSommet* nouveauSommet = new CSommet(iNumero);
	// on incremente le nb de CSommets totaux
	this->iGRANbSommets++;
	// on agrandit la zone memoire de la liste des CSommets pour ajouter le nouveau CSommet
	this->GRAListeSommets = (CSommet**)realloc(this->GRAListeSommets, (sizeof(CSommet*) * this->iGRANbSommets));
	//On verifie les ereurs de reallocation en levant une CException
	if (this->GRAListeSommets == NULL) {
		throw CException(ErreurRealloc, "Il y a eu un probleme avec la reallocation.");
	}
	// on ajoute le nouveau CSommet a la liste
	this->GRAListeSommets[this->iGRANbSommets - 1] = nouveauSommet;
	// on renvoie le nouveau CSommet
	return nouveauSommet;

}

// Supprime un CSommet du graphe
void CGraphe::GRASuprimmerSommet(int iNumero)
{
	// on initialise les valeurs
	CSommet* sommet = nullptr;
	bool sommetExiste = false;
	int iIndexSommet = -1;

	// on recherche le CSommet parmis les CSommets existants
	for (int iCompteurSommets = 0; iCompteurSommets < this->iGRANbSommets; iCompteurSommets++) {
		if (this->GRAListeSommets[iCompteurSommets]->SOMgetNumeroSommet() == iNumero) {
			// si on le trouve on le recupere
			sommet = this->GRAListeSommets[iCompteurSommets];
			// on indique que le CSommet a ete trouve
			sommetExiste = true;
			// on recupere l'index auquel il a ete trouve
			iIndexSommet = iCompteurSommets;
		}
	}

	// si le CSommet n'a pas ete trouve
	if (!sommetExiste) {
		// On leve une CException
		throw CException(SommetManquant, "Le sommet n'a pas ete trouve.");
		
	}

	// on parcourt tous les CSommets
	for (int iCompteurSommets = 0; iCompteurSommets < this->iGRANbSommets; iCompteurSommets++) {
		// on recupere le CSommet courant avec la liste de tous ses CArcs partants et arrivants
		CSommet* sommetCourant = this->GRAListeSommets[iCompteurSommets];
		CArc** arcsPartantsCourant = sommetCourant->SOMgetListeArcsPartants();
		CArc** arcsArrivantsCourant = sommetCourant->SOMgetListeArcsArrivants();

		// on parcourt tous les CArcs arrivants
		for (int iCompteurArcsArrivants = 0; iCompteurArcsArrivants < sommetCourant->SOMgetNbArcsArrivants(); iCompteurArcsArrivants++) {
			// si l'un des CArcs arrivants a pour origine le CSommet a supprimer
			if (arcsArrivantsCourant[iCompteurArcsArrivants]->ARCgetDestination() == iNumero) {
				// on le supprime
				try
				{
					sommetCourant->SOMSupprimerArcArrivant(iNumero);
				}
				catch (CException EXCobj)
				{
					std::cout << EXCobj.EXCgetMessage() << endl;
					exit(EXCobj.EXCgetNumero());
				}
			}
		}

		// on parourt tous ses CArcs partants
		for (int iCompteurArcsPartants = 0; iCompteurArcsPartants < sommetCourant->SOMgetNbArcsPartants(); iCompteurArcsPartants++) {
			// si l'un des CArcs partants a pour destination le CSommet a supprimer
			if (arcsPartantsCourant[iCompteurArcsPartants]->ARCgetDestination() == iNumero) {
				// on le supprime
				try
				{
					sommetCourant->SOMSupprimerArcPartant(iNumero);
				}
				catch (CException EXCobj)
				{
					std::cout << EXCobj.EXCgetMessage() << endl;
					exit(EXCobj.EXCgetNumero());
				}
				
			}
		}
	}

	// on supprime le CSommet a supprimer
	delete sommet;

	// on parcourt les CSommets de la liste apres le CSommet supprime
	for (int iCompteurSommets = iIndexSommet; iCompteurSommets < iGRANbSommets - 1; iCompteurSommets++) {
		// on les decale
		this->GRAListeSommets[iCompteurSommets] = this->GRAListeSommets[iCompteurSommets + 1];
	}
	// on decremente le nombre de CSommets
	this->iGRANbSommets--;

	// on realloue la zone memoire avec un CSommet de moins
	this->GRAListeSommets = (CSommet**)realloc(this->GRAListeSommets, sizeof(CSommet*) * this->iGRANbSommets);
	
	//On verifie les ereurs de reallocation en levant une CException
	if (this->GRAListeSommets == NULL) {
		throw CException(ErreurRealloc, "Il y a eu un probleme avec la reallocation.");
	}
}

// Modifie un CSommet en remplacant son iAncienNumero par un iNouveauNumero
void CGraphe::GRAModifierSommet(int iAncienNumero, int iNouveauNumero)
{
	// Si le numero de nouveau CSommet existe deja dans la liste
	if (this->GRARechercherSommet(iNouveauNumero) != nullptr) {
		// On leve une CException
		throw CException(DoublonSommet, "Le sommet existe deja.");
	}

	// on ajoute le nouveau CSommet
	CSommet* nouveauSommet = GRAAjouterSommet(iNouveauNumero);
	// on recupere l'ancien CSommet
	CSommet* sommet = this->GRARechercherSommet(iAncienNumero);

	// on parcourt tous les CArcs partants de l'ancien CSommet
	for (int iCompteurArcsPartants = 0; iCompteurArcsPartants < sommet->SOMgetNbArcsPartants(); iCompteurArcsPartants++) {
		// on les modifie pour remplacer l'ancien CSommet par le nouveau
		this->GRAModifierArc(iAncienNumero, iNouveauNumero, sommet->SOMgetListeArcsPartants()[iCompteurArcsPartants]->ARCgetDestination(), sommet->SOMgetListeArcsPartants()[iCompteurArcsPartants]->ARCgetDestination());
	}

	// on parcourt tous les CArcs partants de l'ancien CSommet
	for (int iCompteurArcsArrivants = 0; iCompteurArcsArrivants < sommet->SOMgetNbArcsArrivants(); iCompteurArcsArrivants++) {
		// on les modifie pour remplacer l'ancien CSommet par le nouveau
		this->GRAModifierArc(sommet->SOMgetListeArcsArrivants()[iCompteurArcsArrivants]->ARCgetDestination(), sommet->SOMgetListeArcsArrivants()[iCompteurArcsArrivants]->ARCgetDestination(), iAncienNumero, iNouveauNumero);
	}

	// on supprime l'anien CSommet
	this->GRASuprimmerSommet(iAncienNumero);
}

// Ajoute un CArc au CGraphe
void CGraphe::GRAAjouterArc(int iDepart, int iArrivee)
{
	// on recupere le CSommet de depart
	CSommet* sommetDepart = this->GRARechercherSommet(iDepart);

	// si ce CSommet a des CArcs partants
	if (sommetDepart->SOMgetListeArcsPartants() != 0) {
		// on recupere la liste de ses CArcs partants
		CArc** ArcsPartantsSommetDepart = sommetDepart->SOMgetListeArcsPartants();
		// on les parcourt
		for (int iCompteurArcsPartantsSommetDepart = 0; iCompteurArcsPartantsSommetDepart < sommetDepart->SOMgetNbArcsPartants(); iCompteurArcsPartantsSommetDepart++) {
			// si un CArc similaire existe deja
			if (ArcsPartantsSommetDepart[iCompteurArcsPartantsSommetDepart]->ARCgetDestination() == iDepart) {
				// On leve une CException
				throw CException(DoublonArc, "L'arc existe deja.");
			}
		}
	}

	// on recupere le CSommet d'arrivee
	CSommet* sommetArrivee = this->GRARechercherSommet(iArrivee);
	// si ce CSommet a des CArcs arrivants
	if (sommetArrivee->SOMgetNbArcsArrivants() != 0) {
		// on recupere la liste de ses CArcs arrivants
		CArc** ArcsArrivantsSommetArrivee = sommetArrivee->SOMgetListeArcsArrivants();
		// on les parcourt
		for (int iCompteurArcsArrivantsSommetArrivee = 0; iCompteurArcsArrivantsSommetArrivee < sommetArrivee->SOMgetNbArcsArrivants(); iCompteurArcsArrivantsSommetArrivee++) {
			// si un CArc similaire existe deja
			if (ArcsArrivantsSommetArrivee[iCompteurArcsArrivantsSommetArrivee]->ARCgetDestination() == iArrivee) {
				// On leve une CException
				throw CException(DoublonArc, "L'arc existe deja.");
			}
		}
	}

	// on cree les nouveaux CArcs 
	CArc* nouvelArcDepart = new CArc(iDepart);
	CArc* nouvelArcArrivee = new CArc(iArrivee);

	try
	{
		// on les ajoute
		sommetDepart->SOMAjouterArcPartant(nouvelArcArrivee);
		sommetArrivee->SOMAjouterArcArrivant(nouvelArcDepart);
	}
	catch (CException EXCobj)
	{
		std::cout << EXCobj.EXCgetMessage() << "\n";
		exit(EXCobj.EXCgetNumero());
	}
	
}

// Supprime un CArc du CGraphe
void CGraphe::GRASupprimerArc(int iDepart, int iArrivee)
{
	try
	{
		// on supprime le CArc partant du CSommet de depart
		this->GRARechercherSommet(iDepart)->SOMSupprimerArcPartant(iArrivee);

		// on supprime le CArc arrivant du CSommet d'arrivee
		this->GRARechercherSommet(iArrivee)->SOMSupprimerArcArrivant(iDepart);
	}
	catch (CException EXCobj)
	{
		std::cout << EXCobj.EXCgetMessage() << "\n";
		exit(EXCobj.EXCgetNumero());
	}
	
}

// Modifie un CArc du CGraphe en modifiant ses CSommets de depart et d'arrive
void CGraphe::GRAModifierArc(int iAncienDepart, int iNouveauDepart, int iAncienneArrivee, int iNouvelleArrivee)
{
	// on supprimer l'ancien CArc
	this->GRASupprimerArc(iAncienDepart, iAncienneArrivee);

	// on ajoute un nouvel CArc avec les nouveaux CSommets d'arrivee et depart
	this->GRAAjouterArc(iNouveauDepart, iNouvelleArrivee);
}

// Recherche un CSommet dans le CGraphe en fonction de son iNumeroSommet
CSommet* CGraphe::GRARechercherSommet(int iNumeroSommet)
{
	// on parcourt tous les CSommets
	for (int iCompteurSommets = 0; iCompteurSommets < this->iGRANbSommets; iCompteurSommets++) {
		// si le numero du CSommet dans la liste est egal au iNumeroSommet passe en parametre
		if (this->GRAListeSommets[iCompteurSommets]->SOMgetNumeroSommet() == iNumeroSommet) {
			// on renvoie le CSommet
			return this->GRAListeSommets[iCompteurSommets];
		}
	}

	//si le CSommet n'a pas ete trouve on renvoie un pointeur null
	return nullptr;
}

// Inverse un CGraphe en intervertissant les CSommets d'arrivees et de departs de tous les CArcs
void CGraphe::GRAInverserGraphe()
{
	// on parcourt tous les CSommets du graphe
	for (int iCompteurSommets = 0; iCompteurSommets < this->iGRANbSommets; iCompteurSommets++) {
		// on recupere le CSommet courant avec la liste de tous ses CArcs partants et arrivants
		CSommet* sommetTemp = new CSommet(*this->GRAListeSommets[iCompteurSommets]);
		CArc** arcsArrivantsTemp = sommetTemp->SOMgetListeArcsArrivants();
		CArc** arcsPartantsTemp = sommetTemp->SOMgetListeArcsPartants();

		// on supprime tous les CArcs du graphe a inverser
		this->GRAListeSommets[iCompteurSommets]->SOMSupprimerArcs();

		//on parcourt tous les CArcs arrivants
		for (int iCompteurSommetsArrivants = 0; iCompteurSommetsArrivants < sommetTemp->SOMgetNbArcsArrivants(); iCompteurSommetsArrivants++) {
			try
			{
				// on affecte les nouveaux CArcs arrivants (ceux qui etaient partants avant)
				this->GRAListeSommets[iCompteurSommets]->SOMAjouterArcPartant(new CArc(arcsArrivantsTemp[iCompteurSommetsArrivants]->ARCgetDestination()));
			}
			catch (CException EXCobj)
			{
				std::cout << EXCobj.EXCgetMessage() << "\n";
				exit(EXCobj.EXCgetNumero());
			}
		}

		// on parcourt tous les CArcs partants
		for (int iCompteurSommetsPartants = 0; iCompteurSommetsPartants < sommetTemp->SOMgetNbArcsPartants(); iCompteurSommetsPartants++) {
			try
			{
				// on affecte les nouveaux CArcs partants (ceux qui etaient arrivants avant)
				this->GRAListeSommets[iCompteurSommets]->SOMAjouterArcArrivant(new CArc(arcsPartantsTemp[iCompteurSommetsPartants]->ARCgetDestination()));
			}
			catch (CException EXCobj)
			{
				std::cout << EXCobj.EXCgetMessage() << "\n";
				exit(EXCobj.EXCgetNumero());
			}
		}
		delete sommetTemp;
	}
}

// Affiche un CGraphe
void CGraphe::GRAAfficherGraphe()
{
	// on parcourt tous les CSommets
	for (int iCompteurNbSommets = 0; iCompteurNbSommets < iGRANbSommets; iCompteurNbSommets++) {
		// on affiche le numero du CSommet courant
		std::cout << "Sommet " << this->GRAListeSommets[iCompteurNbSommets]->SOMgetNumeroSommet() << " : ";

		// on parcourt tous les CArcs du sommet
		for (int iCompteurArcs = 0; iCompteurArcs < this->GRAListeSommets[iCompteurNbSommets]->SOMgetNbArcsPartants(); iCompteurArcs++) {
			// on affiche tous ses CArcs sous la forme "NumeroSommetDepart->NumeroSommetArrivee"
			std::cout << this->GRAListeSommets[iCompteurNbSommets]->SOMgetNumeroSommet() << "->" << this->GRAListeSommets[iCompteurNbSommets]->SOMgetListeArcsPartants()[iCompteurArcs]->ARCgetDestination() << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
