#pragma once
#include "point_of_interest.h"

///
///\class classic_instance
///\brief Classe de l'objet classic_instance
/// La classe permet de creer un objet correspondant a une instance classique de la litterature
///
class classic_instance
{
public:
	classic_instance();
	classic_instance(int tNbPOI, int tNbCategories, double tBudget, int tMaxPerCategories[], point_of_interest tStartingPoint, point_of_interest* tPOIs);
	~classic_instance();
	int getNbPoi();
	double getBudget();
	int getNbCategories();
	int* getMaxPerCategories();
	point_of_interest getStartingPoint();
	point_of_interest* getPois();

	void setNbPoi(int nbPoi);
	void setBudget(double budget);
	void setNbCategories(int nbCategories);
	void setMaxPerCategories(int* maxPerCategories);
	void setStartingPoint(point_of_interest startingPoint);
	void setPOIs(point_of_interest* POIs);
private:
	int nbPOI;
	double budget;
	int nbCategories;
	int* maxPerCategories;
	point_of_interest startingPoint;
	point_of_interest* POIs;
};

