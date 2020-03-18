#include "point_of_interest.h"

point_of_interest::point_of_interest()
{
}

point_of_interest::point_of_interest(int nbCategories, int tId, double tX, double tY, double tDuration, double tScore, double tEntranceFee, int * tCategories, double * tOpeningTimeWindow, vector<int> tPrecedence, vector<int> tImplication, vector<int> tExclusion)
{
	id = tId;
	x = tX;
	y = tY;
	duration = tDuration;
	score = tScore;
	entranceFee = tEntranceFee;
	categories = new int[nbCategories];
	for (int i = 0; i < nbCategories; i++) {
		categories[i] = tCategories[i];
	}
	openingTimeWindow = new double[5];
	for (int i = 0; i < 5; i++) {
		openingTimeWindow[i] = tOpeningTimeWindow[i];
	}

	precedence = tPrecedence;
	implication = tImplication;
	exclusion = tExclusion;
}


point_of_interest::~point_of_interest()
{
}

int point_of_interest::getId()
{
	return id;
}

double point_of_interest::getX()
{
	return x;
}

double point_of_interest::getY()
{
	return y;
}

double point_of_interest::getDuration()
{
	return duration;
}

double point_of_interest::getScore()
{
	return score;
}

double point_of_interest::getEntranceFee()
{
	return entranceFee;
}

int * point_of_interest::getCategories()
{
	return categories;
}

double * point_of_interest::getOpeningTimeWindow()
{
	return openingTimeWindow;
}

vector<int> point_of_interest::getPrecedence()
{
	return precedence;
}

vector<int> point_of_interest::getImplication()
{
	return implication;
}

vector<int> point_of_interest::getExclusion()
{
	return exclusion;
}

void point_of_interest::setPrecedence(vector<int> tPrecedence)
{
	precedence = tPrecedence;
}

void point_of_interest::setImplication(vector<int> tImplication)
{
	implication = tImplication;
}

void point_of_interest::setExclusion(vector<int> tExclusion)
{
	exclusion = tExclusion;
}
