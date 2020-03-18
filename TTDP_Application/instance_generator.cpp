#include "instance_generator.h"


instance_generator::instance_generator()
{
}


instance_generator::~instance_generator()
{
}

new_instance instance_generator::generateNewInstance(classic_instance instance)
{
	/* initialize random seed */
	srand(time(NULL));


	/* Mandatory constraint definition */
	int nbMandatory = rand() % 3 + 1;

	int* mandatory = new int[nbMandatory];
	for (int i = 0; i < nbMandatory; i++) {
		int newMandatory = rand() % (instance.getNbPoi() - 1) + 2; //We choose a number between 2 and nbPoi+1
		mandatory[i] = newMandatory;
	}

	int nbConstraint = 0.005*(instance.getNbPoi() * instance.getNbPoi()); // 0.5% of the number of possible constraints

	/* Precedence constraint definition */
	for (int i = 0; i < nbConstraint; i++) {
		int poi1 = rand() % (instance.getNbPoi() - 1) + 2;
		int poi2 = rand() % (instance.getNbPoi() - 1) + 2;
		vector<int> tempPrecedence = instance.getPois()[poi1 - 2].getPrecedence();
		tempPrecedence.push_back(poi2);
		instance.getPois()[poi1 - 2].setPrecedence(tempPrecedence);
	}

	/* Implication constraint definition */

	for (int i = 0; i < nbConstraint; i++) {
		int poi1 = rand() % (instance.getNbPoi() - 1) + 2;
		int poi2 = rand() % (instance.getNbPoi() - 1) + 2;
		vector<int> tempImplication = instance.getPois()[poi1 - 2].getImplication();
		tempImplication.push_back(poi2);
		instance.getPois()[poi1 - 2].setImplication(tempImplication);
	}

	/* Exclusion constraint definition */

	for (int i = 0; i < nbConstraint; i++) {
		int poi1 = rand() % (instance.getNbPoi() - 1) + 2;
		int poi2 = rand() % (instance.getNbPoi() - 1) + 2;
		vector<int> tempExclu1 = instance.getPois()[poi1 - 2].getExclusion();
		tempExclu1.push_back(poi2);
		instance.getPois()[poi1 - 2].setExclusion(tempExclu1);
		vector<int> tempExclu2 = instance.getPois()[poi2 - 2].getExclusion();
		tempExclu2.push_back(poi1);
		instance.getPois()[poi2 - 2].setExclusion(tempExclu2);
	}

	new_instance newInstance = new_instance(instance.getNbPoi(), instance.getNbCategories(), instance.getBudget(), instance.getMaxPerCategories(), instance.getStartingPoint(), instance.getPois(), nbMandatory, mandatory);
	return newInstance;
}
