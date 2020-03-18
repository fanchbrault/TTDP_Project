#include "verificator.h"


verificator::verificator()
{
}


verificator::~verificator()
{
}

bool verificator::verifySolution(solution solution, double** travelTime)
{
	bool verif = true;
	new_instance instance = solution.getInstance();
	int nbPoisSelected = solution.getNbPoisSelected();
	point_of_interest* pois = new point_of_interest[nbPoisSelected];
	for (int i = 0; i < solution.getNbPoisSelected(); i++) { // On lit les POIs de la solution
		int idPoi = solution.getPoisSelected()[0][i];
		pois[i] = instance.getPois()[idPoi - 2];
	}


	/*Verifications*/

	/*Contrainte de temps*/
	verif = verifyMaxTime(solution, instance.getStartingPoint().getOpeningTimeWindow()[4], instance.getStartingPoint());
	if (!verif)
		return false;

	/*Contrainte de fenêtre de temps*/
	verif = verifyOpeningTime(nbPoisSelected, pois, solution);
	if (!verif)
		return false;

	/*Contrainte de Precedence*/
	verif = verifyPrecedence(nbPoisSelected, pois);
	if (!verif)
		return false;

	return true;
}

bool verificator::verifyWithoutOT(solution solution)
{
	bool verif = true;
	new_instance instance = solution.getInstance();
	int nbPoisSelected = solution.getNbPoisSelected();
	point_of_interest* pois = new point_of_interest[nbPoisSelected];
	for (int i = 0; i < solution.getNbPoisSelected(); i++) { // On lit les POIs de la solution
		int idPoi = solution.getPoisSelected()[0][i];
		pois[i] = instance.getPois()[idPoi - 2];
	}

	/*Verifications*/
	/*Contrainte de budget*/
	verif = verifyBudget(instance.getBudget(), nbPoisSelected, pois);
	if (!verif) {
		cout << "Contrainte de budget non respectee" << endl;
		return false;
	}


	/*Contrainte de POI obligatoire*/
	verif = verifyMandatory(instance.getNbMandatory(), instance.getMandatory(), nbPoisSelected, solution.getPoisSelected());
	if (!verif) {
		cout << "Contrainte de Mandatory non respectee" << endl;
		return false;
	}

	/*Contrainte d'Implication*/
	verif = verifyImplication(nbPoisSelected, pois);
	if (!verif) {
		cout << "Contrainte d'Implication non respectee" << endl;
		return false;
	}


	/*Contrainte d'Exclusion*/
	verif = verifyExclusion(nbPoisSelected, pois);
	if (!verif) {
		cout << "Contrainte d'Exclusion non respectee" << endl;
		return false;
	}


	/*Contrainte de categories*/
	verif = verifyCategories(nbPoisSelected, pois, instance.getNbCategories(), instance.getMaxPerCategories());
	if (!verif) {
		cout << "Contrainte de categorie non respectee" << endl;
		return false;
	}

	return true;
}

bool verificator::verifyBudget(double budget, int nbPois, point_of_interest * pois)
{
	double sumEntranceFees = 0;
	for (int i = 0; i < nbPois; i++) {
		sumEntranceFees += pois[i].getEntranceFee();
	}

	if (sumEntranceFees < budget)
		return true;
	else return false;
}

bool verificator::verifyMaxTime(solution s, double maxTime, point_of_interest startingPoint)
{
	double duration = 0;
	int id = s.getNbPoisSelected() - 1;
	duration = s.getPoisSelected()[1][id];
	int lastId = s.getPoisSelected()[0][id];
	point_of_interest lastPois = s.getInstance().getPois()[lastId - 2];
	duration += lastPois.getDuration();
	int d = sqrt((startingPoint.getX() - lastPois.getX())*(startingPoint.getX() - lastPois.getX()) + (startingPoint.getY() - lastPois.getY())*(startingPoint.getY() - lastPois.getY()));
	duration += d;
	if (duration > maxTime)
		return false;
	else return true;
}

bool verificator::verifyMandatory(int nbMandatory, int* mandatory, int nbPois, double** pois)
{
	bool allMandIsInSol = true;
	for (int i = 0; i < nbMandatory; i++) {
		bool mandIsInSol = false;
		for (int j = 0; j < nbPois; j++) {
			if (mandatory[i] == pois[0][j])
				mandIsInSol = true;
		}
		if (!mandIsInSol)
			allMandIsInSol = false;
	}
	return allMandIsInSol;
}

bool verificator::verifyOpeningTime(int nbPois, point_of_interest * pois, solution solution)
{
	for (int i = 0; i < nbPois; i++) {
		if (solution.getPoisSelected()[1][i] < pois[i].getOpeningTimeWindow()[0] || solution.getPoisSelected()[1][i] + pois[i].getDuration() > pois[i].getOpeningTimeWindow()[4]) {
			return false;
		}
	}
	return true;
}

bool verificator::verifyPrecedence(int nbPois, point_of_interest* pois)
{
	bool checking = true;
	for (int i = 0; i < nbPois; i++) {
		for (int j = 0; j < pois[i].getPrecedence().size(); j++) {
			if (findPoisInArray(nbPois, pois, pois[i].getPrecedence().at(j))) {
				if (findPoisInArray(i, pois, pois[i].getPrecedence().at(j))) {
					return false;
				}
			}
		}
	}
	return checking;
}

bool verificator::verifyImplication(int nbPois, point_of_interest* pois)
{
	bool checking = true;
	for (int i = 0; i < nbPois; i++) {
		for (int j = 0; j < pois[i].getImplication().size(); j++) {
			if (!findPoisInArray(nbPois, pois, pois[i].getImplication().at(j))) {
				checking = false;
			}
		}
	}
	return checking;
}

bool verificator::verifyExclusion(int nbPois, point_of_interest* pois)
{
	bool checking = true;
	for (int i = 0; i < nbPois; i++) {
		for (int j = 0; j < pois[i].getExclusion().size(); j++) {
			if (findPoisInArray(nbPois, pois, pois[i].getExclusion().at(j))) {
				checking = false;
			}
		}
	}
	return checking;
}

bool verificator::verifyCategories(int nbPois, point_of_interest * pois, int nbCategroies, int * maxPerCategories)
{
	for (int i = 0; i < nbCategroies; i++) {
		int count = 0;
		for (int j = 0; j < nbPois; j++) {
			if (pois[j].getCategories()[i] == 1) {
				count++;
			}
		}
		if (count > maxPerCategories[i]) {
			return false;
		}
	}

	return true;
}

bool verificator::findPoisInVector(vector<point_of_interest> pois, int id)
{
	for (int i = 0; i < pois.size(); i++) {
		if (pois.at(i).getId() == id) {
			return true;
		}
	}
	return false;
}

bool verificator::findPoisInArray(int nbPois, point_of_interest * pois, int id)
{
	for (int i = 0; i < nbPois; i++) {
		if (pois[i].getId() == id) {
			return true;
		}
	}
	return false;
}

bool verificator::verifyBudgetV(solution sol, point_of_interest POI)
{
	int maxBudget = sol.getInstance().getBudget();
	int sumBudget = 0;
	vector<point_of_interest> pois = sol.getPoisVector();
	for (int i = 0; i < pois.size(); i++) {
		sumBudget = pois.at(i).getEntranceFee();
	}
	sumBudget += POI.getEntranceFee();
	if (sumBudget > maxBudget) {
		return false;
	}
	else return true;
}

bool verificator::verifyExclusionV(solution sol, point_of_interest POI)
{
	vector<int> exclusion = POI.getExclusion();
	vector<point_of_interest> pois = sol.getPoisVector();
	for (int i = 0; i < exclusion.size(); i++) {
		for (int j = 0; j < pois.size(); j++) {
			if (exclusion.at(i) == pois.at(j).getId()) {
				return false;
			}
		}
	}
	return true;
}

bool verificator::verifyCategoriesV(solution sol, point_of_interest POI)
{
	new_instance instance = sol.getInstance();
	int nbCat = instance.getNbCategories();
	for (int i = 0; i < nbCat; i++) {
		if (POI.getCategories()[i] == 1) {
			int c = 0;
			for (int j = 0; j < sol.getPoisVector().size(); j++) {
				if (sol.getPoisVector().at(j).getCategories()[i] == 1) {
					c++;
				}	
			}
			if (c > instance.getMaxPerCategories()[i]) {
				return false;
			}
		}
	}
	return true;
}

bool verificator::verifyOTV(solution sol, double ** travelTime, double Xstart, double Ystart, double startCT)
{
	point_of_interest startingPoint = sol.getInstance().getStartingPoint();
	vector<point_of_interest> pois = sol.getPoisVector();
	double Xfirst = pois.at(0).getX();
	double Yfirst = pois.at(0).getY();
	double Xlast = pois.at(pois.size() - 1).getX();
	double Ylast = pois.at(pois.size() - 1).getY();
	double SToFirst = sqrt((Xstart - Xfirst)*(Xstart - Xfirst) + (Ystart - Yfirst)*(Ystart - Yfirst));
	double LastToS = sqrt((Xstart - Xlast)*(Xstart - Xlast) + (Ystart - Ylast)*(Ystart - Ylast));
	double firstOT = pois.at(0).getOpeningTimeWindow()[0];
	double minArr = (firstOT > SToFirst ? firstOT : SToFirst);
	double lastCT = pois.at(pois.size() - 1).getOpeningTimeWindow()[4];
	double maxArr = 0.0;
	if ( lastCT + LastToS > startCT) {
		maxArr = startCT;
	}
	else {
		maxArr = lastCT + LastToS;
	}
	for (int i = 0; i < pois.size() - 1; i++) {
		minArr += pois.at(i).getDuration();
		int currentId = pois.at(i).getId();
		int nextId = pois.at(i+1).getId();
		if (pois.at(i + 1).getOpeningTimeWindow()[0] > minArr + (travelTime[currentId - 2][nextId - 2]))
		{
			minArr = pois.at(i + 1).getOpeningTimeWindow()[0];
		}
		else {
			minArr += (travelTime[currentId - 2][nextId - 2]);
		}
	}
	minArr += pois.at(pois.size() - 1).getDuration();
	minArr += LastToS;
	return minArr > maxArr ? false : true;
}

bool verificator::verifyPrecedenceV(solution sol, point_of_interest POI, int index)
{
	vector<int> precedence = POI.getPrecedence();
	vector<point_of_interest> vectorPOI = sol.getPoisVector();
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < precedence.size(); j++) {
			if (vectorPOI.at(i).getId() == precedence.at(j)) {
				return false;
			}
		}
	}
	for (int i = index + 1; i < vectorPOI.size(); i++) {
		vector<int> currentPrec = vectorPOI.at(i).getPrecedence();
		for (int j = 0; j < currentPrec.size(); j++) {
			if (currentPrec.at(j) == POI.getId()) {
				return false;
			}
		}
	}
	return true;
}

bool verificator::verifyMandatoryV(solution sol)
{
	bool allMandIsInSol = true;
	int nbMandatory = sol.getInstance().getNbMandatory();
	int* mand = sol.getInstance().getMandatory();
	for (int i = 0; i < nbMandatory; i++) {
		bool mandIsInSol = false;
		for (int j = 0; j < sol.getNbPoisSelected(); j++) {
			if (mand[i] == sol.getPoisVector().at(j).getId())
				mandIsInSol = true;
		}
		if (!mandIsInSol)
			allMandIsInSol = false;
	}
	return allMandIsInSol;
}

int verificator::verifyImplicationV(solution sol)
{
	int implicationMiss = 0;
	vector<point_of_interest> vectorPOI = sol.getPoisVector();
	for (int i = 0; i <vectorPOI.size(); i++) {
		point_of_interest currentPOI = vectorPOI.at(i);
		for (int j = 0; j < currentPOI.getImplication().size(); j++) {
			if (!findPoisInVector(vectorPOI, currentPOI.getImplication().at(j))) {
				implicationMiss++;
			}
		}
	}
	return implicationMiss;
}
