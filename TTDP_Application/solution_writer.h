#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "new_instance.h"
#include "point_of_interest.h"
#include "solution.h"
#include "instance_writer.h"
using namespace std;

///
///\class solution_writer
///\brief Classe d'ecriture de fichier de solution
/// La classe permet d'ecrire les fichiers .txt representant une solution
///
class solution_writer
{
public:
	///
	///\brief Constructeur
	///
	solution_writer();
	///
	///\brief Destructeur
	///
	~solution_writer();
	///
	///\brief Methode d'ecriture d'un fichier representant une solution
	///\param filename : String du chemin d'acces au fichier a ecrire
	///\param solution : objet solution 
	///
	void writeSolution(solution solution, string filename);
};

