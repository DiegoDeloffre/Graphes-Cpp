#include "CGraphe.h"
#include <iostream>
#include "CFichier.h"
using namespace std;

int main(int argc, char** argv)
{
	// si aucun fichier n'est passe en parametre
	if (argc == 1) {
		// on declare un CGraphe
		CGraphe graphe;

		// on cree et on ajoute tous les CSommets au CGraphe
		CSommet* sommet1 = graphe.GRAAjouterSommet(1);
		CSommet* sommet2 = graphe.GRAAjouterSommet(2);
		CSommet* sommet3 = graphe.GRAAjouterSommet(3);
		CSommet* sommet4 = graphe.GRAAjouterSommet(4);
		CSommet* sommet5 = graphe.GRAAjouterSommet(5);

		// on ajoute tous les CArcs au CGraphe
		graphe.GRAAjouterArc(1, 2);
		graphe.GRAAjouterArc(1, 4);
		graphe.GRAAjouterArc(1, 3);

		graphe.GRAAjouterArc(2, 3);
		graphe.GRAAjouterArc(2, 4);
		
		graphe.GRAAjouterArc(3, 1);
		graphe.GRAAjouterArc(3, 2);
		graphe.GRAAjouterArc(3, 4);

		graphe.GRAAjouterArc(4, 5);
		graphe.GRAAjouterArc(4, 1);

		graphe.GRAAjouterArc(5, 1);
		graphe.GRAAjouterArc(5, 3);

		// on affiche le CGraphe
		cout << "Graphe 1" << endl;
		graphe.GRAAfficherGraphe();

		// on inverse le CGraphe
		CGraphe *grapheInverse = new CGraphe(graphe);
		grapheInverse->GRAInverserGraphe();
		// on affiche le CGraphe inverse
		cout << "Graphe inverse" << endl;
		grapheInverse->GRAAfficherGraphe();

		// on re-affiche le premier CGraphe
		cout << "Graphe 1" << endl;
		graphe.GRAAfficherGraphe();

		// on modifie un CArc
		graphe.GRAModifierArc(1, 2, 2, 1);

		// on affiche le CGraphe modifie
		cout << "Graphe 1 modifie" << endl;
		graphe.GRAAfficherGraphe();

		delete grapheInverse;
	}
	// si au moins un fichier est passe en parametre
	else {
		// on recupere le nombre de fichiers passes en parametre
		const int inbFichiers = argc - 1;

		// on declare un CGraphe
		CGraphe graphe;

		// on parcourt tous les fichiers
		for (int iCompteur = 0; iCompteur < inbFichiers; iCompteur++) {
			//on initialise le fichier courant
			CFichier FICfichier = CFichier(argv[iCompteur + 1]);

			// on parcourt tous les CSommets lus dans le fichier
			for (int iCompteurLignes = 0; iCompteurLignes < FICfichier.FICgetNBSommets(); iCompteurLignes++) {
				// on ajoute les CSommets au CGraphe
				CSommet* sommet = graphe.GRAAjouterSommet(atoi(FICfichier.FICgetSommets()[iCompteurLignes]));
			}

			// on parcourt tous les CArcs lus dans le fichier
			for (int iCompteurLignes = 0; iCompteurLignes < FICfichier.FICgetNBArcs(); iCompteurLignes++) {
				// on ajoute les CArcs au CGraphe
				graphe.GRAAjouterArc(atoi(FICfichier.FICgetDebuts()[iCompteurLignes]), atoi(FICfichier.FICgetFins()[iCompteurLignes]));
			}

			// on affiche le CGraphe
			cout << "Graphe 1" << endl;
			graphe.GRAAfficherGraphe();

			// on inverse le CGraphe
			CGraphe *grapheInverse = new CGraphe(graphe);
			grapheInverse->GRAInverserGraphe();

			// on affiche le CGraphe inverse
			cout << "Graphe inverse" << endl;
			grapheInverse->GRAAfficherGraphe();

			// on re-affiche le premier CGraphe
			graphe.GRAAfficherGraphe();

			delete grapheInverse;
		}
	}
}


