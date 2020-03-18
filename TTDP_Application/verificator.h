#pragma once
#include "solution.h"
#include "new_instance.h"
#include "point_of_interest.h"
#include <iostream>

using namespace std;

class verificator
{
public:
	verificator();
	~verificator();

	bool verifySolution(solution solution, double** traveltime);
	bool verifyWithoutOT(solution solution);
	bool verifyBudget(double budget, int nbPois, point_of_interest* pois);
	bool verifyMaxTime(solution s, double maxTime, point_of_interest startingPoint);
	bool verifyMandatory(int nbMandatory, int* mandatory, int nbPois, double** pois);
	bool verifyOpeningTime(int nbPois, point_of_interest* pois, solution solution);
	bool verifyPrecedence(int nbPois, point_of_interest* pois);
	bool verifyImplication(int nbPois, point_of_interest* pois);
	bool verifyExclusion(int nbPois, point_of_interest* pois);
	bool verifyCategories(int nbPois, point_of_interest* pois, int nbCategroies, int* maxPerCategories);
	bool findPoisInVector(vector<point_of_interest> pois, int id);
	bool findPoisInArray(int nbPois, point_of_interest * pois, int id);

	bool verifyBudgetV(solution sol, point_of_interest POI);
	bool verifyExclusionV(solution sol, point_of_interest POI);
	bool verifyCategoriesV(solution sol, point_of_interest POI);
	bool verifyOTV(solution sol, double** travelTime, double startX, double startY, double startCT);
	bool verifyPrecedenceV(solution sol, point_of_interest POI, int index);
	bool verifyMandatoryV(solution sol);
	int verifyImplicationV(solution sol);
};

