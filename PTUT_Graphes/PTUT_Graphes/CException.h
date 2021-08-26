#pragma once
#define ErreurRealloc 1
#define DoublonArc 2
#define ArcManquant 3
#define DoublonSommet 4
#define SommetManquant 5

class CException
{
private:
	int iEXCnumero;				//Numéro de l'erreur
	const char* pcEXCphrase;	//Description de l'erreur
public:
	// Cree une CException comprenant un numero et un message d'erreur
	CException(int iNumero, const char* pPhrase);

	// Destructeur d'une CException
	~CException();
	
	// Renvoie le code de la CException levee
	int EXCgetNumero();

	//Renvoie le message de la CException levee
	const char* EXCgetMessage();
};