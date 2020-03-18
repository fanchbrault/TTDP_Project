#pragma once
#include <vector>

using namespace std;
class point_of_interest
{
public:
	point_of_interest();
	//point_of_interest(int nbCategories, int tId, double tX, double tY, double tDuration, double tScore, double tEntranceFee, int* tCategories, double* tOpeningTimeWindow);
	point_of_interest(int nbCategories, int tId, double tX, double tY, double tDuration, double tScore, double tEntranceFee, int* tCategories, double* tOpeningTimeWindow, vector<int> tPrecedence, vector<int> tImplication, vector<int>tExclusion);
	~point_of_interest();
	int getId();
	double getX();
	double getY();
	double getDuration();
	double getScore();
	double getEntranceFee();
	int* getCategories();
	double* getOpeningTimeWindow();
	vector<int> getPrecedence();
	vector<int> getImplication();
	vector<int> getExclusion();

	void setPrecedence(vector<int> tPrecedence);
	void setImplication(vector<int> tImplication);
	void setExclusion(vector<int> tExclusion);

private:
	int id;
	double x;
	double y;
	double duration;
	double score;
	double entranceFee;
	int* categories;
	double* openingTimeWindow;
	vector<int> precedence;
	vector<int> implication;
	vector<int> exclusion;
};

