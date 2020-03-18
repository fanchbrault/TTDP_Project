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
	int populationSize = 50;
	clock_t t1, t2;
	t1 = clock();
	double timer = 0;
	vector<vector<int>> population;
	int bestScore = 0;
	vector<int> bestList;
	double** travelTime = instance.setTravelTime();
	srand(time(NULL));

	for (int i = 0; i < populationSize; i++) {
		int seed = rand();
		vector<int> newList = generateList(instance);
		population.push_back(newList);
	}
	vector<int> scores;
	for (int i = 0; i < populationSize; i++) {
		solution s = decode(population.at(i), instance, travelTime);
		scores.push_back(s.getScore());
		if (s.getScore() > bestScore) {
			bestScore = s.getScore();
			bestList = population.at(i);
		}
	}
	
	t2 = clock();
	timer = double(t2 - t1) / CLOCKS_PER_SEC;
	qDebug() << "Temps pour la premiere gen : " << timer << endl;
	int generationNumber = 1;
	while (timer < 100) {
		generationNumber++;
		vector<vector<int>> newPopulation;
		vector<int> newScores;
		for (int i = 0; i < populationSize/2; i++) {
			int breedPoint1 = rand() % 5;
			int breedPoint2 = rand() % (population.at(0).size()-5) + 5;
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
			child1 = mutation(child1);
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
				if (score1 > bestScore) {
					bestScore = score1;
					bestList = list1;
				}
			}
			else {
				population.push_back(list2);
				scores.push_back(score2);
				if (score2 > bestScore) {
					bestScore = score2;
					bestList = list2;
				}
			}
		}
		t2 = clock();
		timer = double(t2 - t1) / CLOCKS_PER_SEC;
		qDebug() << "Temps pour la gen " << generationNumber << " : " << timer << endl;
		qDebug() << "Best Solution : " << bestScore << endl;
	}
	return decode(bestList, instance, travelTime);
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

solution Genetique::deleteImplication(solution s, point_of_interest POI)
{
	return s;
}

vector<int> Genetique::crossBreed(vector<int> list1, vector<int> list2, int point1, int point2)
{

	vector<int> child(list1.size(), -1);
	for (int i = point1; i < point2; i++) {
		child.erase(child.begin() + i);
		child.insert(child.begin() + i, list1.at(i));
	}
	for (int i = point1; i < point2; i++) {
		pair<bool, int> e = findInVector(child, point1, point2, list2.at(i));
		if (!e.first) {
			child = insertInChild(child, list1, list2, point1, point2, list2.at(i));
		}
	}

	for (int i = 0; i < point1; i++) {
		if (child.at(i) == -1) {
			child.erase(child.begin() + i);
			child.insert(child.begin() + i, list2.at(i));
		}
	}
	for (int i = point2; i < child.size(); i++) {
		if (child.at(i) == -1) {
			child.erase(child.begin() + i);
			child.insert(child.begin() + i, list2.at(i));
		}
	}
	return child;
}

pair<bool, int> Genetique::findInVector(vector<int> v, int point1, int point2, int element)
{
	pair<bool, int> result;

	vector<int>::iterator it = find(v.begin() + point1, v.begin() + point2, element);
	
	if (it != v.begin() + point2) {
		result.first = true;
		result.second = distance(v.begin(), it);
	}
	else {
		result.first = false;
		result.second = -1;
	}
	return result;
}

vector<int> Genetique::insertInChild(vector<int> child, vector<int> list1, vector<int> list2, int point1, int point2, int element)
{
	int index = getIndex(list1, list2, point1, point2, element);
	child.erase(child.begin() + index);
	child.insert(child.begin() + index, element);
	return child;
}

int Genetique::getIndex(vector<int> list1, vector<int> list2, int point1, int point2, int element)
{
	pair<bool, int> p = findInVector(list1, 0, list1.size(), element);
	int index;
	if (p.second < point1 || p.second >= point2) {
		index = p.second;
	}
	else {
		index = getIndex(list1, list2, point1, point2, list2.at(p.second));
	}
	return index;
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


