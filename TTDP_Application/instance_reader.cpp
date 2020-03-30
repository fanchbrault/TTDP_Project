#include "instance_reader.h"


instance_reader::instance_reader()
{
}


instance_reader::~instance_reader()
{
}

classic_instance instance_reader::readClassicFile(string filename)
{
	classic_instance instance = classic_instance();
	ifstream file(filename.c_str());

	if (!file) {
		throw exception("Impossible d'ouvrir le fichier en lecture.");
		cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}
	else {


		int nbTours;
		file >> nbTours;

		int nbPOI;
		file >> nbPOI;

		double budget;
		file >> budget;

		string categories;
		getline(file, categories);
		categories = categories.substr(1);
		int nbCategories;
		nbCategories = getNbCategories(categories);

		int* maxPerCategories;
		maxPerCategories = getMaxPerCategories(categories, nbCategories);

		string line;
		getline(file, line);
		point_of_interest startingPoint = getStartingPoint(line);

		int count = 0;
		point_of_interest* POIs = new point_of_interest[nbPOI];

		while (getline(file, line)) {
			point_of_interest newPOI = getPOI(line, nbCategories);
			POIs[count] = newPOI;
			count++;
		}

		instance = classic_instance(nbPOI, nbCategories, budget, maxPerCategories, startingPoint, POIs);
	}
	file.close();

	return instance;
}

new_instance instance_reader::readNewFile(string filename)
{
	new_instance instance = new_instance();
	ifstream file(filename.c_str());

	if (!file) {
		cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}
	else {
		int nbTours;
		file >> nbTours;

		int nbPOI;
		file >> nbPOI;

		double budget;
		file >> budget;

		string categories;
		getline(file, categories);
		categories = categories.substr(1);
		int nbCategories;
		nbCategories = getNbCategories(categories);

		int* maxPerCategories;
		maxPerCategories = getMaxPerCategories(categories, nbCategories);

		string line;
		getline(file, line);
		point_of_interest startingPoint = getStartingPoint(line);

		point_of_interest* POIs = new point_of_interest[nbPOI];
		for (int i = 0; i < nbPOI; i++) {
			getline(file, line);
			point_of_interest newPOI = getNewPOI(line, nbCategories);
			POIs[i] = newPOI;
		}

		int nbMandatory;
		file >> nbMandatory;
		int* mandatories = new int[nbMandatory];

		for (int i = 0; i < nbMandatory; i++) {
			int mandatory;
			file >> mandatory;
			mandatories[i] = mandatory;
		}

		instance = new_instance(nbPOI, nbCategories, budget, maxPerCategories, startingPoint, POIs, nbMandatory, mandatories);
	}

	file.close();
	return instance;
}


int instance_reader::getNbCategories(string categories)
{
	vector<string> splitedString = split(categories);
	return splitedString.size();
}

int * instance_reader::getMaxPerCategories(string categories, int nbCategories)
{
	vector<string> splitedString = split(categories);
	int* maxPerCategories = new int[nbCategories];
	for (int i = 0; i < nbCategories; i++) {
		maxPerCategories[i] = stoi(splitedString.at(i));
	}
	return maxPerCategories;
}

point_of_interest instance_reader::getStartingPoint(string startingPoint)
{
	vector<string> splitedString = split(startingPoint);
	int id = stoi(splitedString.at(0));
	double x = stod(splitedString.at(1));
	double y = stod(splitedString.at(2));
	double duration = stod(splitedString.at(3));
	double score = stod(splitedString.at(4));
	double openingTimeWindow[5];
	openingTimeWindow[0] = stod(splitedString.at(5));
	openingTimeWindow[1] = 0;
	openingTimeWindow[2] = 0;
	openingTimeWindow[3] = 0;
	openingTimeWindow[4] = stod(splitedString.at(6));
	int noCategories[1];
	noCategories[0] = 0;
	return point_of_interest(1, id, x, y, duration, score, 0, noCategories, openingTimeWindow, vector<int>(0), vector<int>(0), vector<int>(0));
}

point_of_interest instance_reader::getPOI(string POI, int nbCategories) {
	vector<string> splitedString = split(POI);
	int id = stoi(splitedString.at(0));
	double x = stod(splitedString.at(1));
	double y = stod(splitedString.at(2));
	double duration = stod(splitedString.at(3));
	double score = stod(splitedString.at(4));
	double openingTimeWindow[5];
	openingTimeWindow[0] = stod(splitedString.at(5));
	openingTimeWindow[1] = stod(splitedString.at(6));
	openingTimeWindow[2] = stod(splitedString.at(7));
	openingTimeWindow[3] = stod(splitedString.at(8));
	openingTimeWindow[4] = stod(splitedString.at(9));
	double entrenceFee = stod(splitedString.at(11));

	int* categories = new int[nbCategories];
	for (int i = 12; i < splitedString.size(); i++) {
		categories[i - 12] = stoi(splitedString.at(i));
	}
	return point_of_interest(nbCategories, id, x, y, duration, score, entrenceFee, categories, openingTimeWindow, vector<int>(0), vector<int>(0), vector<int>(0));
}

point_of_interest instance_reader::getNewPOI(string POI, int nbCategories)
{
	vector<string> splitedString = split(POI);
	int id = stoi(splitedString.at(0));
	double x = stod(splitedString.at(1));
	double y = stod(splitedString.at(2));
	double duration = stod(splitedString.at(3));
	double score = stod(splitedString.at(4));
	double openingTimeWindow[5];
	openingTimeWindow[0] = stod(splitedString.at(5));
	openingTimeWindow[1] = stod(splitedString.at(6));
	openingTimeWindow[2] = stod(splitedString.at(7));
	openingTimeWindow[3] = stod(splitedString.at(8));
	openingTimeWindow[4] = stod(splitedString.at(9));
	double entrenceFee = stod(splitedString.at(11));

	int* categories = new int[nbCategories];
	for (int i = 0; i < nbCategories; i++) {
		categories[i] = stoi(splitedString.at(i + 12));
	}
	vector<int> precedence;
	vector<int> implication;
	vector<int> exclusion;
	int count = 12 + nbCategories;
	while (splitedString.at(count) != "P")
		count++;
	count++;
	while (splitedString.at(count) != "I") {
		precedence.push_back(stoi(splitedString.at(count)));
		count++;
	}
	count++;
	while (splitedString.at(count) != "E") {
		implication.push_back(stoi(splitedString.at(count)));
		count++;
	}
	count++;
	while (count < splitedString.size()) {
		exclusion.push_back(stoi(splitedString.at(count)));
		count++;
	}
	return point_of_interest(nbCategories, id, x, y, duration, score, entrenceFee, categories, openingTimeWindow, precedence, implication, exclusion);
}

vector<string> instance_reader::split(string str)
{
	vector<string> split;
	size_t pos = 0;
	string token;
	while ((pos = str.find(' ')) != string::npos) {
		token = str.substr(0, pos);
		split.push_back(token);
		str.erase(0, pos + 1);
	}
	split.push_back(str);
	return split;
}



