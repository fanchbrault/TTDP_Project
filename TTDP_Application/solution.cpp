#include "solution.h"


solution::solution()
{
}


solution::~solution()
{
}

solution::solution(double tDepartureTime, new_instance tInstance, int tNbPoisSelected, double ** tPoisSelected, int tScore)
{
	departureTime = tDepartureTime;
	instance = tInstance;
	nbPoisSelected = tNbPoisSelected;
	poisSelected = tPoisSelected;
	score = tScore;
}

solution::solution(double tDepartureTime, new_instance tInstance, int tNbPoisSelected, vector<point_of_interest> tPoisVector, int tScore)
{
	departureTime = tDepartureTime;
	instance = tInstance;
	nbPoisSelected = tNbPoisSelected;
	poisVector = tPoisVector;
	score = tScore;
	poisSelected = nullptr;
}

double solution::getDepartureTime()
{
	return departureTime;
}

new_instance solution::getInstance()
{
	return instance;
}

int solution::getNbPoisSelected()
{
	return nbPoisSelected;
}

double ** solution::getPoisSelected()
{
	return poisSelected;
}

int solution::getScore()
{
	return score;
}

vector<point_of_interest> solution::getPoisVector()
{
	return poisVector;
}

void solution::setDepartureTime(double tDepartureTime)
{
	departureTime = tDepartureTime;
}

void solution::setInstance(new_instance tInstance)
{
	instance = tInstance;
}

void solution::setNbPoisSelected(int tNbPois)
{
	nbPoisSelected = tNbPois;
}

void solution::setPoisSelected(double ** tPoisSelected)
{
	poisSelected = tPoisSelected;
}

void solution::setScore(int tScore)
{
	score = tScore;
}

void solution::setPoisVector(vector<point_of_interest> tPoisVector)
{
	poisVector = tPoisVector;
}

int solution::setNewScore(solution s)
{
	int score = 0;
	for (int i = 0; i < s.getNbPoisSelected(); i++) {
		int id = s.getPoisSelected()[0][i] - 2;
		int newScore = s.getScore() + s.getInstance().getPois()[id].getScore();
		s.setScore(newScore);
	}
	return score;
}
