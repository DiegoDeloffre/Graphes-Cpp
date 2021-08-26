#include "CException.h"

// Cree une CException comprenant un numero et un message d'erreur
CException::CException(int iNumero, const char * pPhrase)
{
	this->iEXCnumero = iNumero;
	this->pcEXCphrase = pPhrase;
}

// Destructeur d'une CException
CException::~CException()
{}

// Renvoie le code de la CException levee
int CException::EXCgetNumero()
{
	return this->iEXCnumero;
}

//Renvoie le message de la CException levee
const char* CException::EXCgetMessage()
{
	return this->pcEXCphrase;
}