#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "solution.h"
#include "instance_reader.h"

///
///\class solution_reader
///\brief Classe de lecture de fichier de solution
/// La classe permet de lire les fichiers .txt representant une solution
///
class solution_reader
{
public:
	///
	///\brief Constructeur
	///
	solution_reader();
	///
	///\brief Destructeur
	///
	~solution_reader();
	///
	///\brief Methode de lecture d'un fichier representant une solution
	///\param filename : String du chemin d'acces au fichier a lire
	///\return un objet solution
	///
	solution readSolutionFile(string filename);
};

