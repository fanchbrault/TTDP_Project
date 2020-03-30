#include "solution_reader.h"



solution_reader::solution_reader()
{
}


solution_reader::~solution_reader()
{
}

solution solution_reader::readSolutionFile(string filename)
{
	solution s = solution();
	new_instance newInstance = new_instance();
	instance_reader instanceReader = instance_reader();
	newInstance = instanceReader.readNewFile(filename);

	ifstream file(filename.c_str());

	if (!file) {
		throw exception("Impossible d'ouvrir le fichier en lecture.");
		cerr << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}
	else {
		string line;
		getline(file, line); //lecture de la première ligne
		getline(file, line); //lecture de la deuxième ligne (starting point)
		for (int i = 0; i < newInstance.getNbPoi(); i++) {
			getline(file, line); //lecture de tout les POIs
		}
		getline(file, line); //lecture de la ligne des POIs obligatoires
		int nbPOIsSelected;
		file >> nbPOIsSelected;
		double departureTime;
		file >> departureTime;
		double globalScore;
		file >> globalScore;
		double ** poisSelected = new double*[2];
		poisSelected[0] = new double[nbPOIsSelected];
		poisSelected[1] = new double[nbPOIsSelected];
		for (int i = 0; i < nbPOIsSelected; i++) {
			file >> poisSelected[0][i];
			file >> poisSelected[1][i];
		}
		s = solution(departureTime, newInstance, nbPOIsSelected, poisSelected, globalScore);
	}
	file.close();
	return s;
}
