#include "instance_writer.h"


instance_writer::instance_writer()
{
}


instance_writer::~instance_writer()
{
}

void instance_writer::writeNewInstance(string filename, new_instance newInstance)
{
	ofstream file;
	file.open(filename.c_str());
	if (!file) {
		cout << "ERREUR: Impossible d'ouvrir le fichier en écriture." << endl;
	}
	else
	{
		/************* Ecriture de la premiere ligne *************/
		file << "1 ";
		file << newInstance.getNbPoi() << " ";
		file << newInstance.getBudget() << " ";
		for (int i = 0; i < newInstance.getNbCategories() - 1; i++) {
			file << newInstance.getMaxPerCategories()[i] << " ";
		}
		file << newInstance.getMaxPerCategories()[newInstance.getNbCategories() - 1];
		file << endl;

		/************* Ecriture du point de depart *************/
		point_of_interest start = newInstance.getStartingPoint();
		file << "0 ";
		file << start.getX() << " " << start.getY() << " ";
		file << "0.0 0.0 0 " << start.getOpeningTimeWindow()[4] << endl;

		/************* Ecriture des POIs *************/
		point_of_interest* pois = new point_of_interest[newInstance.getNbPoi()];
		for (int i = 0; i < newInstance.getNbPoi(); i++) {
			pois[i] = newInstance.getPois()[i];
		}

		for (int i = 0; i < newInstance.getNbPoi(); i++) {
			file << pois[i].getId() << " " << pois[i].getX() << " " << pois[i].getY() << " " << pois[i].getDuration() << " " << pois[i].getScore() << " ";

			for (int j = 0; j < 5; j++) {
				file << pois[i].getOpeningTimeWindow()[j] << " ";
			}

			file << "1 " << pois[i].getEntranceFee() << " ";

			for (int j = 0; j < newInstance.getNbCategories(); j++) {
				file << pois[i].getCategories()[j] << " ";
			}
			file << "P";
			for (int j = 0; j < pois[i].getPrecedence().size(); j++) {
				file << " " << pois[i].getPrecedence().at(j);
			}
			file << " I";
			for (int j = 0; j < pois[i].getImplication().size(); j++) {
				file << " " << pois[i].getImplication().at(j);
			}
			file << " E";
			for (int j = 0; j < pois[i].getExclusion().size(); j++) {
				file << " " << pois[i].getExclusion().at(j);
			}

			file << endl;
		}

		/************* Ecriture des POIs obligatoire *************/
		file << newInstance.getNbMandatory() << " ";
		for (int i = 0; i < newInstance.getNbMandatory() - 1; i++) {
			file << newInstance.getMandatory()[i] << " ";
		}
		file << newInstance.getMandatory()[newInstance.getNbMandatory() - 1];
		file << endl;
		file.close();
	}
}
