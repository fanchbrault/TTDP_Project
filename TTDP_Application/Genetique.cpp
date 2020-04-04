#include "Genetique.h"



Genetique::Genetique()
{
	v = verificator();
}


Genetique::~Genetique()
{
}

solution Genetique::searchSolution(new_instance instance)
{
	string logFile = "C:/Users/fanch/Desktop/log.txt";
	ofstream log;
	log.open(logFile.c_str());
	log << "num gen \t min \t max \t moy" << endl;
	int generationOfBS = 1;

	int populationSize = 50;
	clock_t t1, t2;
	t1 = clock();
	double timer = 0;
	vector<vector<int>> population;
	int bestScore = -999999;
	vector<int> bestList;
	double** travelTime = instance.setTravelTime();
	srand(time(NULL));

	for (int i = 0; i < populationSize; i++) {
		int seed = rand();
		vector<int> newList = generateList(instance);
		population.push_back(newList);
	}
	vector<int> scores;
	int sumScore = 0;
	for (int i = 0; i < populationSize; i++) {
		solution s = decode(population.at(i), instance, travelTime);
		scores.push_back(s.getScore());
		sumScore += s.getScore();
		if (s.getScore() > bestScore) {
			bestScore = s.getScore();
			bestList = population.at(i);
		}
	}
	int max = *max_element(scores.begin(), scores.end());
	int min = *min_element(scores.begin(), scores.end());
	double moy = sumScore / populationSize;
	log << "1 \t " << min << "\t " << max << "\t" << moy << endl;
	t2 = clock();
	timer = double(t2 - t1) / CLOCKS_PER_SEC;
	qDebug() << "Temps pour la premiere gen : " << timer << endl;
	int generationNumber = 1;
	while (timer < 15) {
		generationNumber++;
		sumScore = 0;
		vector<vector<int>> newPopulation;
		vector<int> newScores;
		for (int i = 0; i < populationSize/2; i++) {
			int breedPoint1 = rand() % population.at(0).size();
			int breedPoint2 = rand() % population.at(0).size();
			if (breedPoint1 > breedPoint2) {
				int tmp = breedPoint1;
				breedPoint1 = breedPoint2;
				breedPoint2 = tmp;
			}
			int idParent1 = rand() % population.size();
			vector<int> parent1 = population.at(idParent1);
			population.erase(population.begin() + idParent1);
			newPopulation.push_back(parent1);
			int idParent2 = rand() % population.size();
			vector<int> parent2 = population.at(idParent2);
			population.erase(population.begin() + idParent2);
			newPopulation.push_back(parent2);

			newScores.push_back(scores.at(idParent1));
			scores.erase(scores.begin() + idParent1);
			newScores.push_back(scores.at(idParent2));
			scores.erase(scores.begin() + idParent2);

			vector<int> child1 = crossBreed(parent1, parent2, breedPoint1, breedPoint2);
			vector<int> child2 = crossBreed(parent2, parent1, breedPoint1, breedPoint2);
			child1 = mutation(child1);
			child2 = mutation(child2);
			newPopulation.push_back(child1);
			newPopulation.push_back(child2);
			solution solChild1 = decode(child1, instance, travelTime);
			solution solChild2 = decode(child2, instance, travelTime);
			newScores.push_back(solChild1.getScore());
			newScores.push_back(solChild2.getScore());
		}
		
		for (int i = 0; i < populationSize; i++) {
			int idList1 = rand() % newPopulation.size();
			vector<int> list1 = newPopulation.at(idList1);
			int score1 = newScores.at(idList1);
			newPopulation.erase(newPopulation.begin() + idList1);
			newScores.erase(newScores.begin() + idList1);
			int idList2 = rand() % newPopulation.size();
			vector<int> list2 = newPopulation.at(idList2);
			int score2 = newScores.at(idList2);
			newPopulation.erase(newPopulation.begin() + idList2);
			newScores.erase(newScores.begin() + idList2);

			if (score1 > score2) {
				population.push_back(list1);
				scores.push_back(score1);
				sumScore += score1;
				if (score1 > bestScore) {
					generationOfBS = generationNumber;
					bestScore = score1;
					bestList = list1;
				}
			}
			else {
				population.push_back(list2);
				scores.push_back(score2);
				sumScore += score2;
				if (score2 > bestScore) {
					generationOfBS = generationNumber;
					bestScore = score2;
					bestList = list2;
				}
			}
		}
		int max = *max_element(scores.begin(), scores.end());
		int min = *min_element(scores.begin(), scores.end());
		double moy = sumScore / populationSize;
		log << generationNumber << "\t " << min << "\t " << max << "\t" << moy << endl;
		t2 = clock();
		timer = double(t2 - t1) / CLOCKS_PER_SEC;
		qDebug() << "Temps pour la gen " << generationNumber << " : " << timer << endl;
		qDebug() << "Best Solution : " << bestScore << endl;
	}
	solution bestSolution = decode(bestList, instance, travelTime);
	bestSolution = getDurationForAll(bestSolution, travelTime);
	log << "Generation of the best solution : " << generationOfBS;
	return bestSolution;
}

vector<int> Genetique::generateList(new_instance instance)
{
	int nbPoi = instance.getNbPoi();
	point_of_interest* pois = instance.getPois();
	vector<int> list;
	vector<int> remainingList;
	for (int i = 0; i < nbPoi; i++) {
		remainingList.push_back(pois[i].getId());
	}
	for (int i = 0; i < nbPoi; i++) {
		int randomId = rand() % remainingList.size();
		list.push_back(remainingList.at(randomId));
		remainingList.erase(remainingList.begin() + randomId);
	}
	return list;
}

solution Genetique::decode(vector<int> list, new_instance instance, double** travelTime)
{
	int alpha = 200; 
	int beta = 100;
	vector<int> mandatoryList;
	vector<int> remainingList;
	vector<point_of_interest> poisSelected;


	solution newSol = solution(0, instance, 0, poisSelected, 0);
	for (int i = 0; i < list.size(); i++) {
		bool isMand = false;
		for (int j = 0; j < instance.getNbMandatory(); j++) {
			if (list.at(i) == instance.getMandatory()[j]) {
				isMand = true;
			}
		}
		if (isMand) {
			mandatoryList.push_back(list.at(i));
		}
		else {
			remainingList.push_back(list.at(i));
		}

	}
	
	for (int i = 0; i < mandatoryList.size(); i++) {
		int id = mandatoryList.at(i);
		point_of_interest currentPOI = instance.getPois()[id - 2];
		newSol = insertPOI(newSol, currentPOI, travelTime);
	}

	if (!v.verifyMandatoryV(newSol)) {
		int dif = instance.getNbMandatory() - newSol.getPoisVector().size();
		newSol.setScore(newSol.getScore() - alpha * dif);
	}

	for (int i = 0; i < remainingList.size(); i++) {
		int id = remainingList.at(i);
		point_of_interest currentPOI = instance.getPois()[id - 2];
		newSol = insertPOI(newSol, currentPOI, travelTime);
	}
	
	
	int nbMissImp = v.verifyImplicationV(newSol);
	if (nbMissImp > 0) {
		newSol.setScore(newSol.getScore() - beta * nbMissImp);
	}
	
	return newSol;
}

solution Genetique::insertPOI(solution s, point_of_interest POI, double** travelTime)
{
	solution copy = s;
	vector<point_of_interest> poisVector = copy.getPoisVector();
	if (!v.verifyBudgetV(copy, POI)) {
		return s;
	}
	if (!v.verifyExclusionV(copy, POI)) {
		return s;
	}
	if (!v.verifyCategoriesV(copy, POI)) {
		return s;
	}

	double Xstart = s.getInstance().getStartingPoint().getX();
	double Ystart = s.getInstance().getStartingPoint().getY();
	double startCT = s.getInstance().getStartingPoint().getOpeningTimeWindow()[4];
	for (int i = 0; i < poisVector.size() + 1; i++) {
		poisVector.insert(poisVector.begin() + i, POI);
		copy.setPoisVector(poisVector);
		if (v.verifyPrecedenceV(copy, POI, i)) {
			if (v.verifyOTV(copy, travelTime, Xstart, Ystart, startCT)) {
				copy.setNbPoisSelected(copy.getNbPoisSelected() + 1);
				copy.setScore(copy.getScore() + POI.getScore());
				return copy;
			}
			else {
				poisVector.erase(poisVector.begin() + i);
			}

		}
		else {
			poisVector.erase(poisVector.begin() + i);
		}
	}
	return s;
}

vector<int> Genetique::crossBreed(vector<int> list1, vector<int> list2, int point1, int point2)
{
	int size = list1.size();
	vector<int> child(size, -1);

	for (int i = point1; i < point2; i++) {
		child.at(i) = list2.at(i);
	}

	for (int i = 0; i < point1; i++) {
			child.at(i) = list1.at(i);
	}
	for (int i = point2; i < size; i++) {
			child.at(i) = list1.at(i);
	}

	for (int i = 0; i < point1; i++) {
		if (find(child.begin() + point1, child.begin() + point2, child.at(i)) != child.begin() + point2) {
			child.at(i) = -1;
		}
	}
	for (int i = point2; i < size; i++) {
		if (find(child.begin() + point1, child.begin() + point2, child.at(i)) != child.begin() + point2) {
			child.at(i) = -1;
		}
	}
	vector<int> remainingPOIinParent1;
	for (int i = 0; i < size; i++) {
		if (find(child.begin(), child.end(), list1.at(i)) == child.end()) {
			remainingPOIinParent1.push_back(list1.at(i));
		}
	}
	for (int i = 0; i < size; i++) {
		if (child.at(i) == -1) {
			child.at(i) = remainingPOIinParent1.at(0);
			remainingPOIinParent1.erase(remainingPOIinParent1.begin());
		}
	}

	return child;
}


vector<int> Genetique::mutation(vector<int> list)
{
	double r = rand()%10;
	if (r > 7) {
		int randomSwap1 = rand() % list.size();
		int	randomSwap2 = rand() % list.size();
		swap(list.at(randomSwap1), list.at(randomSwap2));
	}
	
	return list;
}

solution Genetique::getDurationForAll(solution s, double ** traveltime)
{
	new_instance instance = s.getInstance();
	point_of_interest startingPoint = s.getInstance().getStartingPoint();
	vector<point_of_interest> pois = s.getPoisVector();
	int size = pois.size();
	double Xstart = startingPoint.getX();
	double Ystart = startingPoint.getY();
	double startCT = startingPoint.getOpeningTimeWindow()[4];
	double Xfirst = pois.at(0).getX();
	double Yfirst = pois.at(0).getY();
	double Xlast = pois.at(pois.size() - 1).getX();
	double Ylast = pois.at(pois.size() - 1).getY();
	double SToFirst = sqrt((Xstart - Xfirst)*(Xstart - Xfirst) + (Ystart - Yfirst)*(Ystart - Yfirst));
	double LastToS = sqrt((Xstart - Xlast)*(Xstart - Xlast) + (Ystart - Ylast)*(Ystart - Ylast));
	double lastCT = pois.at(pois.size() - 1).getOpeningTimeWindow()[4];
	double firstOT = pois.at(0).getOpeningTimeWindow()[0];

	double ** poisInSol = new double*[2];
	poisInSol[0] = new double[size];
	poisInSol[1] = new double[size];
	for (int i = 0; i < size; i++) {
		poisInSol[0][i] = pois.at(i).getId();
		poisInSol[1][i] = 0;
	}
	if (startCT < lastCT + LastToS) {
		poisInSol[1][size - 1] = startCT - LastToS - pois.at(size - 1).getDuration();
	}
	else {
		poisInSol[1][size - 1] = lastCT - pois.at(size - 1).getDuration();
	}
	for (int i = size - 1; i > 0; i--) {
		int currentId = poisInSol[0][i];
		int previousId = poisInSol[0][i - 1];
		double travel = traveltime[currentId - 2][previousId - 2];
		if (poisInSol[1][i] < pois.at(i - 1).getOpeningTimeWindow()[4] + travel) {
			poisInSol[1][i - 1] = poisInSol[1][i] - travel - pois.at(i - 1).getDuration();
		}
		else {
			poisInSol[1][i - 1] = pois.at(i - 1).getOpeningTimeWindow()[4] - pois.at(i - 1).getDuration();
		}
	}

	double departureTime = poisInSol[1][0] - SToFirst;
	solution sol = solution(departureTime, instance, pois.size(), poisInSol, s.getScore());
	return sol;
}


