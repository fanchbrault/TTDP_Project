#include "classic_instance.h"

using namespace std;

classic_instance::classic_instance()
{
}

classic_instance::classic_instance(int tNbPOI, int tNbCategories, double tBudget, int tMaxPerCategories[], point_of_interest tStartingPoint, point_of_interest* tPOIs)
{
	nbPOI = tNbPOI;
	budget = tBudget;
	nbCategories = tNbCategories;
	maxPerCategories = new int[nbCategories];
	for (int i = 0; i < nbCategories; i++) {
		maxPerCategories[i] = tMaxPerCategories[i];
	}
	startingPoint = tStartingPoint;
	POIs = new point_of_interest[nbPOI];
	for (int i = 0; i < nbPOI; i++) {
		POIs[i] = tPOIs[i];
	}
}


classic_instance::~classic_instance()
{
}

/************************************/
/********Getters and Setters*********/
/**********************************/
int classic_instance::getNbPoi()
{
	return nbPOI;
}

double classic_instance::getBudget()
{
	return budget;
}

int classic_instance::getNbCategories()
{
	return nbCategories;
}

int * classic_instance::getMaxPerCategories()
{
	return maxPerCategories;
}

point_of_interest classic_instance::getStartingPoint()
{
	return startingPoint;
}

point_of_interest * classic_instance::getPois()
{
	return POIs;
}

void classic_instance::setNbPoi(int tNbPoi)
{
	nbPOI = tNbPoi;
}

void classic_instance::setBudget(double tBudget)
{
	budget = tBudget;
}

void classic_instance::setNbCategories(int tNbCategories)
{
	nbCategories = tNbCategories;
}

void classic_instance::setMaxPerCategories(int * tMaxPerCategories)
{
	maxPerCategories = tMaxPerCategories;
}

void classic_instance::setStartingPoint(point_of_interest tStartingPoint)
{
	startingPoint = tStartingPoint;
}

void classic_instance::setPOIs(point_of_interest * tPOIs)
{
	POIs = tPOIs;
}
