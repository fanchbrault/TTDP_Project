#pragma once
#include "classic_instance.h"
#include "point_of_interest.h"
#include "new_instance.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;
///
///\class instance_reader
///\brief Classe de lecture de fichier d'instance
/// La classe permet de lire les fichiers .txt representant n'importe quelle instance (instance classique ou nouvelle)
///
class instance_reader
{
public:
	///
	///\brief Constructeur
	///
	instance_reader();
	///
	///\brief Destructeur
	///
	~instance_reader();
	///
	///\brief Methode de lecture d'un fichier d'instance classique
	///\param filename : String du chemin d'accès au fichier a lire
	///\return un objet classic_instance
	///
	classic_instance readClassicFile(string filename);
	///
	///\brief Methode de lecture d'un fichier representant une nouvelle instance
	///\param filename : String du chemin d'acces au fichier a lire
	///\return un objet new_instance
	///
	new_instance readNewFile(string filename);
	///
	///\brief Méthode recuperant le nombre de categorie d'une instance
	///\param categories : String de la ligne du fichier ou il y a le nombre maximum de POIs par categorie
	///\return le nombre de catégorie d'une instance
	///
	int getNbCategories(string categories);
	///
	///\brief Méthode recuperant le nombre maximum de POIs par categories d'une instance
	///\param categories : String de la ligne du fichier ou il y a le nombre maximum de POIs par categorie
	///\param nbCategories : Entier du nombre de categorie
	///\return une liste d'entier qui correspond au nombre maximum de POIs par categories
	///
	int* getMaxPerCategories(string categories, int nbCategories);
	///
	///\brief Méthode recuperant le point de depart de l'instance
	///\param startingPoint : String de la ligne du fichier correspondant au point de depart
	///\return un objet point_of_interest
	///
	point_of_interest getStartingPoint(string startingPoint);
	///
	///\brief Méthode recuperant un POI d'une instance classique
	///\param POI : String de la ligne du fichier correspondant a un POI
	///\param nbCategories :  Entier du nombre de catégorie
	///\return un objet point_of_interest
	///
	point_of_interest getPOI(string POI, int nbCategories);
	///
	///\brief Méthode recuperant un POI d'une nouvelle instance
	///\param POI : String de la ligne du fichier correspondant a un POI
	///\param nbCategories :  Entier du nombre de categorie
	///\return un objet point_of_interest
	///
	point_of_interest getNewPOI(string POI, int nbCategories);
	///
	///\brief Methode de separer chaque element d'un String
	///\param str : String a séparer
	///\return une liste de string de chaque element du string
	///
	vector<string> split(string str);
};

