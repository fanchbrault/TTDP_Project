#include "new_instance.h"


new_instance::new_instance()
{
}

new_instance::new_instance(int tNbPOI, int tNbCategories, double tBudget, int tMaxPerCategories[], point_of_interest tStartingPoint, point_of_interest* tPOIs, int tNbMandatory, int tMandatory[]) : classic_instance(tNbPOI, tNbCategories, tBudget, tMaxPerCategories, tStartingPoint, tPOIs)
{
	nbMandatory = tNbMandatory;
	mandatory = new int[nbMandatory];
	for (int i = 0; i < nbMandatory; i++) {
		mandatory[i] = tMandatory[i];
	}
}

new_instance::~new_instance()
{
}

int new_instance::getNbMandatory()
{
	return nbMandatory;
}

int * new_instance::getMandatory()
{
	return mandatory;
}

int new_instance::getNbConstraints()
{
	return nbConstraints;
}


void new_instance::setNbMandatory(int tNbMandatory)
{
	nbMandatory = tNbMandatory;
}

void new_instance::setMandatory(int * tMandatory)
{
	mandatory = tMandatory;
}

void new_instance::setNbConstraints(int tNbConstraints)
{
	nbConstraints = tNbConstraints;
}


double ** new_instance::setTravelTime()
{
	/* Travel time computing */

	double** travelTime = new double*[getNbPoi()];
	for (int i = 0; i < getNbPoi(); i++) {
		travelTime[i] = new double[getNbPoi()];
	}

	for (int i = 0; i < getNbPoi(); i++) {
		for (int j = i + 1; j < getNbPoi(); j++) {
			point_of_interest poiI = getPois()[i];
			point_of_interest poiJ = getPois()[j];
			double d = sqrt((poiI.getX() - poiJ.getX())*(poiI.getX() - poiJ.getX()) + (poiI.getY() - poiJ.getY())*(poiI.getY() - poiJ.getY()));
			travelTime[i][j] = d;
			travelTime[j][i] = d;
		}
	}

	return travelTime;
}
