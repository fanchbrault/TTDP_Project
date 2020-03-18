#pragma once
#include "new_instance.h"

class solution
{
public:
	solution();
	~solution();
	solution(double departureTime, new_instance instance, int nbPoisSelected, double** poisSelected, int score);
	solution(double departureTime, new_instance instance, int nbPoisSelected, vector<point_of_interest> poisVector, int score);
	double getDepartureTime();
	new_instance getInstance();
	int getNbPoisSelected();
	double** getPoisSelected();
	int getScore();
	vector<point_of_interest> getPoisVector();

	void setDepartureTime(double tDepartureTime);
	void setInstance(new_instance tInstance);
	void setNbPoisSelected(int tNbPois);
	void setPoisSelected(double** tPoisSelected);
	void setScore(int tScore);
	void setPoisVector(vector<point_of_interest> tPoisVector);

	int setNewScore(solution s);

private:
	double departureTime;
	new_instance instance;
	int nbPoisSelected;
	double** poisSelected;
	int score;
	vector<point_of_interest> poisVector;
};

