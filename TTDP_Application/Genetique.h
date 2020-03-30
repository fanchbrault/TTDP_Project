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
#include <math.h>
#include <QDebug>

using namespace std;
///
///\class Genetique
///\brief Classe de l'algorithme genetique
/// La classe permet de trouver une solution a partir d'une instance en suivant un algorithme genetique
///
class Genetique
{
public:
	///
	///\brief Constructeur
	///
	Genetique();
	///
	///\brief Destructeur
	///
	~Genetique();
	///
	///\brief Methode principale permettant de calculer la solution
	///\param instance : objet instance ou l'on veut calculer une solution
	///\return un objet solution
	///
	solution searchSolution(new_instance instance);
	///
	///\brief Methode permettant de generer une liste aleatoire representant un individu
	///\param instance : objet instance 
	///\return une liste d'entiers representant tous les POIs dans un ordre aleatoire
	///
	vector<int> generateList(new_instance instance);
	///
	///\brief Methode permettant d'avoir une solution valide a partir d'une liste representant un individu
	///\param list : liste d'entiers que l'on veut decoder
	///\param instance : objet instance 
	///\param traveltime : tableau correspondant aux distances entre tous les POIs
	///\return un object solution
	///
	solution decode(vector<int> list, new_instance instance, double** traveltime);
	///
	///\brief Methode permettant d'avoir une solution valide a partir d'une liste representant un individu
	///\param list : liste d'entiers que l'on veut decoder
	///\param instance : objet instance 
	///\param traveltime : tableau correspondant aux distances entre tous les POIs
	///\return un object solution
	///
	solution insertPOI(solution s, point_of_interest POI, double** traveltime);
	solution deleteImplication(solution s, point_of_interest POI);
	vector<int> crossBreed(vector<int> list1, vector<int> list2, int point1, int point2);
	vector<int> mutation(vector<int> list);
	solution getDurationForAll(solution s, double** traveltime);

private:
	solution bestSolution;
	verificator v;
};

