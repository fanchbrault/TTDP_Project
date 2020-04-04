
#pragma once
#include "solution.h"
#include "new_instance.h"
#include "point_of_interest.h"
#include <iostream>

using namespace std;

///
///\class verificator
///\brief Classe de verification de solution
/// La classe permet de verifier la faisabilité d'une solution dans son entierte ou juste verifier si une ou plusieurs contraintes sont respectees
/// Pour chaques verifications il y a deux versions, une pour la verification avec la liste de POIs selectiones dans un tableau et une autre 
///pour la verification avec la liste de POIs selectionnes dans un vecteur
///
class verificator
{
public:
	///
	///\brief Constructeur
	///
	verificator();
	///
	///\brief Destructeur
	///
	~verificator();

	///
	///\brief Methode de verification generale d'une solution
	///\param solution : objet solution a verifier
	///\param traveltime : tableau correspondant aux distances entre tous les POIs
	///\return true si la solution est faisable false sinon
	///
	bool verifySolution(solution solution, double** traveltime);
	///
	///\brief Methode de verification d'une solution sans les contraintes liees au temps
	///\param solution : objet solution a verifier
	///\return true si l'ensemble des contraintes sont respectees false sinon
	///
	bool verifyWithoutOT(solution solution);
	///
	///\brief Methode de verification de la contrainte de budget
	///\param budget : le budget maximum
	///\param nbPois : le nombre de POIs dans la solution
	///\param pois : tableau representant les POIs de la solution
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyBudget(double budget, int nbPois, point_of_interest* pois);
	///
	///\brief Methode de verification de la contrainte de temps maximum
	///\param s : objet solution
	///\param maxTime : temps maximum
	///\param startingpoint : objet point_of_interest representant le point de depart
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyMaxTime(solution s, double maxTime, point_of_interest startingPoint);
	///
	///\brief Methode de verification de la contrainte de POIs obligatoire
	///\param nbMandatory : nombre de POIs oblgatoire
	///\param mandatory : tableau des IDs des POIs obligatoires
	///\param nbPois : le nombre de POIs dans la solution
	///\param pois : tableau representant les POIs de la solution
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyMandatory(int nbMandatory, int* mandatory, int nbPois, double** pois);
	///
	///\brief Methode de verification de la contrainte de fenetre de temps
	///\param nbPois : le nombre de POIs dans la solution
	///\param pois : tableau representant les POIs de la solution
	///\param solution : objet solution
	///\param traveltime : tableau correspondant aux distances entre tous les POIs
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyOpeningTime(int nbPois, point_of_interest* pois, solution solution, double** travelTime);
	///
	///\brief Methode de verification de la contrainte de precedence
	///\param nbPois : le nombre de POIs dans la solution
	///\param pois : tableau representant les POIs de la solution
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyPrecedence(int nbPois, point_of_interest* pois);
	///
	///\brief Methode de verification de la contrainte d'implication
	///\param nbPois : le nombre de POIs dans la solution
	///\param pois : tableau representant les POIs de la solution
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyImplication(int nbPois, point_of_interest* pois);
	///
	///\brief Methode de verification de la contrainte d'exclusion
	///\param nbPois : le nombre de POIs dans la solution
	///\param pois : tableau representant les POIs de la solution
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyExclusion(int nbPois, point_of_interest* pois);
	///
	///\brief Methode de verification de la contrainte de categorie
	///\param nbPois : le nombre de POIs dans la solution
	///\param pois : tableau representant les POIs de la solution
	///\param nbCategories : nombre de categories
	///\param maxPerCategories : tableau representant le nombre de POIs par categories
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyCategories(int nbPois, point_of_interest* pois, int nbCategroies, int* maxPerCategories);
	///
	///\brief Methode permettant de rechercher si un POIs est dans un vecteur
	///\param pois : vecteur d'objet point_of_interest, liste ou l'on veut faire la recherche
	///\param id : l'id du POIs a recherche
	///\return true si le POIs recherche est dans la solution
	///
	bool findPoisInVector(vector<point_of_interest> pois, int id);
	///
	///\brief Methode permettant de rechercher si un POIs est dans un tableau
	///\param nbPois : le nombre de POIs dans la solution
	///\param pois : tableau representant les POIs de la solution
	///\param id : l'id du POIs a recherche
	///\return true si le POIs recherche est dans la solution
	///
	bool findPoisInArray(int nbPois, point_of_interest * pois, int id);

	///
	///\brief Methode de verification de la contrainte de budget
	///\param sol : objet solution
	///\param POI : objet point_of_interest que l'on veut inclure dans la solution
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyBudgetV(solution sol, point_of_interest POI);
	///
	///\brief Methode de verification de la contrainte d'exclusion
	///\param sol : objet solution
	///\param POI : objet point_of_interest que l'on veut inclure dans la solution
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyExclusionV(solution sol, point_of_interest POI);
	///
	///\brief Methode de verification de la contrainte de categorie
	///\param sol : objet solution
	///\param POI : objet point_of_interest que l'on veut inclure dans la solution
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyCategoriesV(solution sol, point_of_interest POI);
	///
	///\brief Methode de verification de la contrainte de fenetre de temps
	///\param sol : objet solution
	///\param travetime : : tableau correspondant aux distances entre tous les POIs
	///\param startX : composante X du point de départ
	///\param startY : composante Y du point de départ
	///\param startCT : heure maximale que l'on peut atteindre
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyOTV(solution sol, double** travelTime, double startX, double startY, double startCT);
	///
	///\brief Methode de verification de la contrainte de precedence
	///\param sol : objet solution
	///\param POI : objet point_of_interest que l'on veut inclure dans la solution
	///\param index : indice de l'endroit ou l'on veut inclure le POI
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyPrecedenceV(solution sol, point_of_interest POI, int index);
	///
	///\brief Methode de verification de la contrainte de POIs obligatoires
	///\param sol : objet solution
	///\return true si la contrainte est respectee false sinon
	///
	bool verifyMandatoryV(solution sol);
	///
	///\brief Methode de verification de la contrainte d'implication
	///\param sol : objet solution
	///\return le nombre d'implication qui ne sont pas respectee
	///
	int verifyImplicationV(solution sol);
};

