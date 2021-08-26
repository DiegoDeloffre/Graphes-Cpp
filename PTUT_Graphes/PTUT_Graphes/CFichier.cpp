#include "CFichier.h"

//Lit le nombre de sommets du graphe dans le fichier et le stocke dans l'attribut de classe
void CFichier::FIClirenbSommets()
{
	//on indique la chaine a chercher dans le fichier
	const char* pchaineAChercher = "NBSommets\0";

	//on alloue une zone memoire pour la chaine a recuperer
	char* pchaineTrouvee = (char*)malloc(sizeof(char) * 10);

	//on parcourt tout le fichier
	for (int icurseurFichier = 0; icurseurFichier < iFICtailleFichier; icurseurFichier++) {
		int icurseurRecherche = 0;

		//on saute la chaine a chercher (la valeur qui nous interesse est juste apres)
		while (pchaineAChercher[icurseurRecherche] == FICcontenuFichier[icurseurFichier + icurseurRecherche]) {
			icurseurRecherche++;
		}
		//si il y a un caractere
		if (pchaineAChercher[icurseurRecherche] == '\0') {
			icurseurFichier += icurseurRecherche + 1;
			int icurseurTrouve = 0;
			//tant que l'on est pas a la fin de la ligne
			while (FICcontenuFichier[icurseurFichier] != '\n') {
				//on enregistre la chaine a recuperer caracteres par caracteres
				pchaineTrouvee[icurseurTrouve] = FICcontenuFichier[icurseurFichier];
				icurseurFichier++;
				icurseurTrouve++;
			}
			//on transforme la chaine de caracteres recuperee en entier et on l'associe a l'attribut de la classe
			this->iFICnbSommets = atoi(pchaineTrouvee);

			// on alloue la zone memoire pour stocker la liste des numeros des CSommets
			FICListeNumerosSommets = (char**)malloc(iFICnbSommets * sizeof(char*));

			//on libere la zone memoire allouee pour la chaine a recuperer
			free(pchaineTrouvee);
			//on quitte le programme
			return;
		}
	}
	//si on arrive ici c'est que la chaine n'a pas pu etre lue
	//on libere la zone memoire allouee pour la chaine a recuperer
	free(pchaineTrouvee);
	//on indique l'erreur
	std::cout << "Le nombre de sommets n'a pas pu etre lu. Le fichier ne respecte surement pas les conventions d'ecritures.";
	exit(-1);
}

//Lit le nombre d'arcs du graphe dans le fichier et le stocke dans l'attribut de classe
void CFichier::FIClirenbArcs()
{
	//on indique la chaine a chercher dans le fichier
	const char* pchaineAChercher = "NBArcs\0";

	//on alloue une zone memoire pour la chaine a recuperer
	char* pchaineTrouvee = (char*)malloc(sizeof(char) * 10);

	//on parcourt tout le fichier
	for (int icurseurFichier = 0; icurseurFichier < iFICtailleFichier; icurseurFichier++) {
		int icurseurRecherche = 0;

		//on saute la chaine a chercher (la valeur qui nous interesse est juste apres)
		while (pchaineAChercher[icurseurRecherche] == FICcontenuFichier[icurseurFichier + icurseurRecherche]) {
			icurseurRecherche++;
		}
		//si il y a un caractere
		if (pchaineAChercher[icurseurRecherche] == '\0') {
			icurseurFichier += icurseurRecherche + 1;
			int icurseurTrouve = 0;
			//tant que l'on est pas a la fin de la ligne
			while (FICcontenuFichier[icurseurFichier] != '\n') {
				//on enregistre la chaine a recuperer caracteres par caracteres
				pchaineTrouvee[icurseurTrouve] = FICcontenuFichier[icurseurFichier];
				icurseurFichier++;
				icurseurTrouve++;
			}
			//on transforme la chaine de caracteres recuperee en entier et on l'associe a l'attribut de la classe
			this->iFICnbArcs = atoi(pchaineTrouvee);

			// on alloue la zone memoire pour stocker la liste des numeros des CArcs partants et arrivants
			this->FICListeNumerosDebuts = (char**)malloc(iFICnbArcs * sizeof(char*));
			this->FICListeNumerosFins = (char**)malloc(iFICnbArcs * sizeof(char*));

			//on libere la zone memoire allouee pour la chaine a recuperer
			free(pchaineTrouvee);
			//on quitte le programme
			return;
		}
	}
	//si on arrive ici c'est que la chaine n'a pas pu etre lue
	//on libere la zone memoire allouee pour la chaine a recuperer
	free(pchaineTrouvee);
	//on indique l'erreur
	std::cout << "Le nombre de CArcs n'a pas pu etre lu. Le fichier ne respecte surement pas les conventions d'ecritures.";
	exit(-1);
}

//Lit les numeros des sommets du graphe dans le fichier et la stocke dans l'attribut de classe
void CFichier::FIClireSommets()
{
	//on indique la chaine a chercher dans le fichier
	const char* pchaineAChercher = "Numero\0";
	int iCurseurListeSommets = -1;
	char* pchaineTrouvee;

	//on parcourt tout le fichier
	for (int icurseurFichier = 0; icurseurFichier < iFICtailleFichier; icurseurFichier++) {
		int icurseurRecherche = 0;

		//on saute la chaine a chercher (la valeur qui nous interesse est juste apres)
		while (pchaineAChercher[icurseurRecherche] == FICcontenuFichier[icurseurFichier + icurseurRecherche]) {
			icurseurRecherche++;
		}

		//si il y a un caractere
		if (pchaineAChercher[icurseurRecherche] == '\0') {
			//on alloue une zone memoire pour la chaine a recuperer
			pchaineTrouvee = (char*)malloc(sizeof(char) * 10);
			iCurseurListeSommets++;

			icurseurFichier += icurseurRecherche + 1;
			int icurseurTrouve = 0;
			//tant que l'on est pas a la fin de la ligne
			while (FICcontenuFichier[icurseurFichier] != '\n') {
				//on enregistre la chaine a recuperer caracteres par caracteres
				pchaineTrouvee[icurseurTrouve] = FICcontenuFichier[icurseurFichier];
				icurseurFichier++;
				icurseurTrouve++;
			}
			//on ajoute le caractere de fin a la chaine que l'on vient de recuperer
			pchaineTrouvee[icurseurTrouve] = '\0';

			//on stocke la chaine recuperee dans l'attribut de classe
			this->FICListeNumerosSommets[iCurseurListeSommets] = pchaineTrouvee;
		}
	}
	//free(pchaineTrouvee);
	//on quitte le programme
	return;
	//si on arrive ici c'est que la chaine n'a pas pu etre lue
	//on libere la zone memoire allouee pour la chaine a recuperer

	//on indique l'erreur
	std::cout << "Les numeros des CSommets n'ont pas pu etre lus correctement. Le fichier ne respecte surement pas les conventions d'ecritures.";
	exit(-1);
}

//Lit les numeros des arrivees des arcs du graphe dans le fichier et la stocke dans l'attribut de classe
void CFichier::FIClireDebuts()
{
	//on indique la chaine a chercher dans le fichier
	const char* pchaineAChercher = "Debut\0";
	int iCurseurListeNumerosDebut = -1;
	char* pchaineTrouvee;

	//on parcourt tout le fichier
	for (int icurseurFichier = 0; icurseurFichier < iFICtailleFichier; icurseurFichier++) {
		int icurseurRecherche = 0;

		//on saute la chaine a chercher (la valeur qui nous interesse est juste apres)
		while (pchaineAChercher[icurseurRecherche] == FICcontenuFichier[icurseurFichier + icurseurRecherche]) {
			icurseurRecherche++;
		}
		//si il y a un caractere
		if (pchaineAChercher[icurseurRecherche] == '\0') {
			//on alloue une zone memoire pour la chaine a recuperer
			pchaineTrouvee = (char*)malloc(sizeof(char) * 10);
			iCurseurListeNumerosDebut++;

			icurseurFichier += icurseurRecherche + 1;
			int icurseurTrouve = 0;
			//tant que l'on est pas a la fin de la ligne
			while (FICcontenuFichier[icurseurFichier] != '\n') {
				//on enregistre la chaine a recuperer caracteres par caracteres
				pchaineTrouvee[icurseurTrouve] = FICcontenuFichier[icurseurFichier];
				icurseurFichier++;
				icurseurTrouve++;
			}
			//on ajoute le caractere de fin a la chaine que l'on vient de recuperer
			pchaineTrouvee[icurseurTrouve] = '\0';

			//on stocke la chaine recuperee dans l'attribut de classe
			this->FICListeNumerosDebuts[iCurseurListeNumerosDebut] = pchaineTrouvee;

		}
	}
	//on libere la zone memoire allouee pour la chaine a recuperer
	//free(pchaineTrouvee);

	//on quitte le programme
	return;
	//si on arrive ici c'est que la chaine n'a pas pu etre lue

	//on indique l'erreur
	std::cout << "Les numeros de CSommet de depart des CArcs n'ont pas pu etre lus correctement. Le fichier ne respecte surement pas les conventions d'ecritures.";
	exit(-1);
}

//Lit les numeros des arrivees des arcs du graphe dans le fichier et la stocke dans l'attribut de classe
void CFichier::FIClireFins()
{
	//on indique la chaine a chercher dans le fichier
	const char* pchaineAChercher = "Fin\0";
	int iCurseurListeNumerosFin = -1;
	char* pchaineTrouvee;

	//on parcourt tout le fichier
	for (int icurseurFichier = 0; icurseurFichier < iFICtailleFichier; icurseurFichier++) {
		int icurseurRecherche = 0;

		//on saute la chaine a chercher (la valeur qui nous interesse est juste apres)
		while (pchaineAChercher[icurseurRecherche] == FICcontenuFichier[icurseurFichier + icurseurRecherche]) {
			icurseurRecherche++;
		}

		//si il y a un caractere
		if (pchaineAChercher[icurseurRecherche] == '\0') {
			//on alloue une zone memoire pour la chaine a recuperer
			pchaineTrouvee = (char*)malloc(sizeof(char) * 10);
			iCurseurListeNumerosFin++;
			icurseurFichier += icurseurRecherche + 1;
			int icurseurTrouve = 0;
			//tant que l'on est pas a la fin de la ligne
			while (FICcontenuFichier[icurseurFichier] != '\n') {
				//on enregistre la chaine a recuperer caracteres par caracteres
				pchaineTrouvee[icurseurTrouve] = FICcontenuFichier[icurseurFichier];
				icurseurFichier++;
				icurseurTrouve++;
			}
			//on ajoute le caractere de fin a la chaine que l'on vient de recuperer
			pchaineTrouvee[icurseurTrouve] = '\0';

			//on stocke la chaine recuperee dans l'attribut de classe
			this->FICListeNumerosFins[iCurseurListeNumerosFin] = pchaineTrouvee;

		}
	}
	//on libere la zone memoire allouee pour la chaine a recuperer
	//free(pchaineTrouvee);
	//on quitte le programme
	return;
	//si on arrive ici c'est que la chaine n'a pas pu etre lue
	//on indique l'erreur
	std::cout << "Les numeros de CSommet d'arrivee des CArcs n'ont pas pu etre lus correctement.. Le fichier ne respecte surement pas les conventions d'ecritures.";
	exit(-1);
}

// Construit un CFichier a partir du nom de fichier pFICcheminFichier passe en parametre
CFichier::CFichier(const char * pFICcheminFichier)
{
	FILE *FFichier;
	errno_t bError;
	char cChar;
	int iCurseurFichier = 0;

	//on ouvre le fichier en gerant les erreurs d'ouvertures
	if (bError = fopen_s(&FFichier, pFICcheminFichier, "r") != 0) {
		std::cout << "Ouverture du fichier impossible\n";
		exit(-1);
	}
	else {
		//on recupere l'indice de fin de fichier
		fseek(FFichier, 0, SEEK_END);
		iFICtailleFichier = ftell(FFichier);
		fseek(FFichier, 0, SEEK_SET);

		//on alloue une zone memoire pour le contenu du fichier
		FICcontenuFichier = (char*)malloc(sizeof(char) * iFICtailleFichier);

		//tant que l'on est pas a la fin du fichier
		while ((cChar = fgetc(FFichier)) != EOF && iCurseurFichier < iFICtailleFichier)
		{
			//on recupere le contenu caratere par caractere
			FICcontenuFichier[iCurseurFichier] = cChar;
			iCurseurFichier++;
		}
		//on ajoute le caractere de fin de chaine
		FICcontenuFichier[iCurseurFichier] = '\0';

		//on ferme le fichier
		fclose(FFichier);

		//on recupere les attributs en utilisant les fonctions adequates
		FIClirenbArcs();
		FIClirenbSommets();
		FIClireSommets();
		FIClireDebuts();
		FIClireFins();
	}
}

// Renvoie le nombre de CSommets du CGraphe
int CFichier::FICgetNBSommets()
{
	return this->iFICnbSommets;
}

// Renvoie le nombre de CArcs du CGraphe
int CFichier::FICgetNBArcs()
{
	return this->iFICnbArcs;
}

// Renvoie la liste des CSommets du CGraphe
char ** CFichier::FICgetSommets()
{
	return this->FICListeNumerosSommets;
}

// Renvoie les numeros des departs des Carcs du CGraphe
char ** CFichier::FICgetDebuts()
{
	return this->FICListeNumerosDebuts;
}

// Renvoie les numeros des arrivees des Carcs du CGraphe
char ** CFichier::FICgetFins()
{
	return this->FICListeNumerosFins;
}
