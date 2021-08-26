#pragma once
#include "CSommet.h"

class CGraphe
{
private:
	int iGRANbSommets; // Nombre de CSommets du CGraphe
	CSommet** GRAListeSommets; // Liste des CSommets du CGraphe

public:
	// Construit un CGraphe vide
	CGraphe();
	// Constructeur de recopie d'un CGraphe
	CGraphe(CGraphe& graphe);
	// Destructeur d'un CGraphe
	~CGraphe();

	// Ajoute un CSommet au Cgraphe
	CSommet* GRAAjouterSommet(int iNumero);
	// Ajoute le CSommet sommet au CGraphe
	void GRAAjouterSommet(CSommet* sommet);
	// Supprime un CSommet du graphe
	void GRASuprimmerSommet(int iNumero);
	// Modifie un CSommet en remplacant son iAncienNumero par un iNouveauNumero
	void GRAModifierSommet(int iAncienNumero, int iNouveauNumero);

	// Ajoute un CArc au CGraphe
	void GRAAjouterArc(int iDepart, int iArrivee);
	// Supprime un CArc du CGraphe
	void GRASupprimerArc(int iDepart, int iArrivee);
	// Modifie un CArc du CGraphe en modifiant ses CSommets de depart et d'arrive
	void GRAModifierArc(int iAncienDepart, int iNouveauDepart, int iAncienneArrivee, int iNouvelleArrivee);

	// Recherche un CSommet dans le CGraphe en fonction de son iNumeroSommet
	CSommet* GRARechercherSommet(int iNumeroSommet);

	// Inverse un CGraphe en intervertissant les CSommets d'arrivees et de departs de tous les CArcs
	void GRAInverserGraphe();

	// Affiche un CGraphe
	void GRAAfficherGraphe();


};

