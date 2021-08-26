#include "CArc.h"
#include <malloc.h>

// Construit un CArc de destination destination
CArc::CArc(int destination)
{
	this->iARCDestination = destination;
}

// Constructeur de recopie d'un CArc
CArc::CArc(CArc& arc)
{
	this->iARCDestination = arc.ARCgetDestination();
}

// Recupere la destination d'un CArc
int CArc::ARCgetDestination()
{
	return this->iARCDestination;
}

// Modifie la destination d'un CArc en la remplacant par nouvelleDestination
void CArc::ARCModifierDestination(int nouvelleDestination)
{
	this->iARCDestination = nouvelleDestination;
}
