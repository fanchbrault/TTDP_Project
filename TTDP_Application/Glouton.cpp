#include "Glouton.h"


struct {
	bool operator()(point_of_interest a, point_of_interest b) const
	{
		return a.getScore() < b.getScore();
	}
} sortByScore;

Glouton::Glouton()
{
}


Glouton::~Glouton()
{
}

/* Le principe de cet alogrithme est simple, on inclue tout d'abord les POIs obligtoires,
ensuite on parcourt les POIs restant en prenant celui avec le plus haut score, on essaye
de l'inclure à la suite avec toutes les contraintes liées à ce POIs*/
solution Glouton::searchSolution(new_instance instance)
{
	clock_t t1, t2;
	verificator v = verificator();
	double ** travelTime = instance.setTravelTime();
	vector<int> poisSelected;
	int score = 0;
	for (int i = 0; i < instance.getNbMandatory(); i++) {
		int id = instance.getMandatory()[i];
		poisSelected.push_back(id);
		score += instance.getPois()[id - 2].getScore();
		if (instance.getPois()[id - 2].getImplication().size() > 0) {
			for (int j = 0; j < instance.getPois()[id - 2].getImplication().size(); j++) {
				int idImp = instance.getPois()[id - 2].getImplication().at(j);
				if (!findIdInSol(idImp, poisSelected)) {
					poisSelected.push_back(idImp);
					score += instance.getPois()[idImp - 2].getScore();
				}	
			}
		}
	}

	int nbPois = poisSelected.size();
	double ** poisInSol = new double*[2];
	poisInSol[0] = new double[nbPois];
	poisInSol[1] = new double[nbPois];
	for (int i = 0; i < nbPois; i++) {
		poisInSol[0][i] = poisSelected.at(i);
	}
	solution firstSolution = solution(0.0, instance, nbPois, poisInSol, score);
	if (!v.verifyWithoutOT(firstSolution)) {
		cout << "Solution irrealisable, contrainte Mandatory incompatible avec d'autres contraintes" << endl;
		return firstSolution;
	}
	/*On tri le reste des POIs par ordre décroissant de score*/
	vector<point_of_interest> remainingPOI;
	for (int i = 0; i < instance.getNbPoi(); i++) {
		bool isMand = false;
		for (int j = 0; j < poisSelected.size(); j++) {
			if (instance.getPois()[i].getId() == poisSelected.at(j)) {
				isMand = true;
			}
		}
		if (!isMand) {
			remainingPOI.push_back(instance.getPois()[i]);
		}
	}
	sort(remainingPOI.begin(), remainingPOI.end(), sortByScore);
	reverse(remainingPOI.begin(), remainingPOI.end());
	for (int i = 0; i < remainingPOI.size(); i++) {
		firstSolution = tryToIncludePoi(firstSolution, remainingPOI[i], travelTime);
	}
	qDebug() << "Score : " << firstSolution.getScore() << endl;
	return firstSolution;

}

solution Glouton::tryToIncludePoi(solution s, point_of_interest poi, double** travelTime)
{
	int nbPois = s.getNbPoisSelected() + 1;
	double ** poisInSol = new double*[2];
	poisInSol[0] = new double[nbPois];
	poisInSol[1] = new double[nbPois];
	for (int i = 0; i < s.getNbPoisSelected(); i++) {
		poisInSol[0][i] = s.getPoisSelected()[0][i];
		poisInSol[1][i] = s.getPoisSelected()[1][i];
	}
	poisInSol[0][nbPois-1] = poi.getId();
	poisInSol[1][nbPois-1] = 0;
	solution copy = solution(0.0, s.getInstance(), nbPois, poisInSol, s.getScore()+poi.getScore());
	verificator v = verificator();
	if (v.verifyWithoutOT(copy)) {
		poisInSol = getDurationForAll(copy.getPoisSelected(), travelTime, copy.getNbPoisSelected(), s.getInstance());
		copy = solution(0.0, s.getInstance(), nbPois, poisInSol, s.getScore() + poi.getScore());
		if (v.verifySolution(copy, travelTime)) {
			return copy;
		}
	}
	return s;
}



solution Glouton::determineDepartureTime(solution s)
{
	return s;
}




double ** Glouton::getDurationForAll(double ** poisInSol, double ** travelTime, int nbPois, new_instance instance)
{
	if (nbPois == 1) {
		int firstId = poisInSol[0][0];
		double firstOT = instance.getPois()[firstId - 2].getOpeningTimeWindow()[0];
		double firstDuration = sqrt((instance.getStartingPoint().getX() - instance.getPois()[firstId - 2].getX())*(instance.getStartingPoint().getX() - instance.getPois()[firstId - 2].getX()) + (instance.getStartingPoint().getY() - instance.getPois()[firstId - 2].getY())*(instance.getStartingPoint().getY() - instance.getPois()[firstId - 2].getY()));
		poisInSol[1][0] = firstDuration < firstOT ? firstOT : firstDuration;
	}
	else {
		for (int i = 1; i < nbPois; i++) {
				int currentId = poisInSol[0][i];
				int previousId = poisInSol[0][i - 1];
				double duration = instance.getPois()[previousId - 2].getDuration();
				double travel = travelTime[currentId - 2][previousId - 2];
				double OP = instance.getPois()[currentId - 2].getOpeningTimeWindow()[0];
				poisInSol[1][i] = poisInSol[1][i - 1] + travel + duration < OP ? OP : poisInSol[1][i - 1] + travel + duration;
			}
	}
	
	return poisInSol;
}

bool Glouton::findIdInSol(int id, vector<int> pois)
{
	for (int i = 0; i < pois.size(); i++) {
		if (id == pois.at(i)) {
			return true;
		}
	}
	return false;
}
