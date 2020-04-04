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
	///
	///\brief Constructeur
	///
	Glouton();
	///
	///\brief Destructeur
	///
	~Glouton();
	///
	///\brief Methode principale permettant de calculer la solution
	///\param instance : objet instance ou l'on veut calculer une solution
	///\return un objet solution
	///
	solution searchSolution(new_instance instance);
	///
	///\brief Methode permettant d'inclure un POI a une solution
	///\param s : objet solution
	///\param poi : objet point_of_interest que l'on veut inclure dans s
	///\param traveltime : tableau correspondant aux distances entre tous les POIs
	///\return un objet solution
	///
	solution tryToIncludePoi(solution s, point_of_interest poi, double** travelTime);
	///
	///\brief Methode permettant de determiner l'heure de départ
	///\param s : objet solution
	///\return un objet solution
	///
	solution determineDepartureTime(solution s);
	///
	///\brief Methode permettant d'obtenir toutes les heures d'arrivee pour tout les pois
	///\param poisInSol : tableau répsentant l'id d'un poi dans la solution ainsi son heure d'arrivee dans le circuit
	///\param nbPois : nombre de POIs dans la solution
	///\param traveltime : tableau correspondant aux distances entre tous les POIs
	///\param instance : objet param
	///\return la tableau des IDs des POIs avec les bonnes heures d'arrivee
	///
	double ** getDurationForAll(double ** poisInSol, double ** travelTime, int nbPois, new_instance instance);
	///
	///\brief Methode permettant de savoir si un POI est dans une liste de POIs
	///\param id : ID du POI a rechercher
	///\param pois : liste d'IDs de POIs
	///\return true si l'ID du POI recherche est dans la liste false sinon
	///
	bool findIdInSol(int id, vector<int> pois);
};

