#include "solution_writer.h"



solution_writer::solution_writer()
{

}


solution_writer::~solution_writer()
{
}

void solution_writer::writeSolution(solution solution, string filename)
{
	instance_writer writer = instance_writer();
	writer.writeNewInstance(filename, solution.getInstance());

	fstream file;
	file.open(filename.c_str(), fstream::app);
	if (!file) {
		throw exception("Impossible d'ouvrir le fichier en écriture.");
		cerr << "ERREUR: Impossible d'ouvrir le fichier en écriture." << endl;
	}
	else
	{
		file << solution.getNbPoisSelected() << " " << solution.getDepartureTime() << " " << solution.getScore() << endl;
		if(solution.getPoisVector().size() == 0){
			for (int i = 0; i < solution.getNbPoisSelected(); i++) {
				file << solution.getPoisSelected()[0][i] << " " << solution.getPoisSelected()[1][i] << endl;
			}
		}
		else {
			for (int i = 0; i < solution.getPoisVector().size(); i++) {
				file << solution.getPoisVector().at(i).getId() << " " << 0 << endl;
			}
		}
		
	}
	file.close();
}
