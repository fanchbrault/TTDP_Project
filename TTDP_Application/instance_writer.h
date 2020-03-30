#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "new_instance.h"
#include "point_of_interest.h"

using namespace std;
///
///\class instance_writer
///\brief Classe d'ecriture de fichier d'instance
/// La classe permet d'ecrire les fichiers .txt representant une nouvelle instance
///
class instance_writer
{
public:
	///
	///\brief Constructeur
	///
	instance_writer();
	///
	///\brief Destructeur
	///
	~instance_writer();
	///
	///\brief Methode de d'ecriture d'un fichier representant une nouvelle instance
	///\param filename : String du chemin d'acces au fichier a ecrire
	///\param newInstance : objet new_instance 
	///
	void writeNewInstance(string filename, new_instance newInstance);
};

