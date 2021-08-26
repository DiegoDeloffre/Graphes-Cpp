#pragma once
class CArc
{
private:
	int iARCDestination; // destination du CArc

public:
	// Construit un CArc de destination destination
	CArc(int destination);

	// Constructeur de recopie d'un CArc
	CArc(CArc& arc);

	// Recupere la destination d'un CArc
	int ARCgetDestination();

	// Modifie la destination d'un CArc en la remplacant par nouvelleDestination
	void ARCModifierDestination(int nouvelleDestination);

};