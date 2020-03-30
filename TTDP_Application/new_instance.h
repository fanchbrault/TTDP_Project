#pragma once
#include "classic_instance.h"
#include <math.h>

using namespace std;

///
///\class new_instance
///\brief Classe de l'objet new_instance
/// La classe permet de creer un objet correspondant a une nouvelle instance
///
class new_instance : public classic_instance
{
public:
	new_instance();
	new_instance(int tNbPOI, int tNbCategories, double tBudget, int tMaxPerCategories[], point_of_interest tStartingPoint, point_of_interest* tPOIs, int tNbMandatory, int tMandatory[]);
	~new_instance();
	int getNbMandatory();
	int* getMandatory();
	int getNbConstraints();

	void setNbMandatory(int tNbMandatory);
	void setMandatory(int* tMandatory);
	void setNbConstraints(int tNbConstraints);

	double** setTravelTime();
private:
	int nbMandatory;
	int* mandatory;
	int nbConstraints;
};

