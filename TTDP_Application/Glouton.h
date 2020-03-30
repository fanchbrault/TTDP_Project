#pragma once
#include "new_instance.h"
#include "solution.h"
#include "verificator.h"
#include "point_of_interest.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <time.h>
#include <QDebug>


using namespace std;
///
///\class Glouton
///\brief Classe de l'algorithme glouton
/// La classe permet de trouver une solution a partir d'une instance en suivant un algorithme glouton
///
class Glouton
{
public:
	Glouton();
	~Glouton();
	solution searchSolution(new_instance instance);
	solution tryToIncludePoi(solution s, point_of_interest poi, double** travelTime);
	solution determineDepartureTime(solution s);
	double ** getDurationForAll(double ** poisInSol, double ** travelTime, int nbPois, new_instance instance);
	bool findIdInSol(int id, vector<int> pois);
	void displaySolution(solution solution);
};

