#pragma once
#include "new_instance.h"
#include "solution.h"
#include "verificator.h"
#include "point_of_interest.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
#include <time.h>
#include <math.h>
#include <QDebug>

using namespace std;
class Genetique
{
public:
	Genetique();
	~Genetique();
	solution searchSolution(new_instance instance);
	vector<int> generateList(new_instance instance);
	solution decode(vector<int>, new_instance instance, double** traveltime);
	solution insertPOI(solution s, point_of_interest POI, double** traveltime);
	solution deleteImplication(solution s, point_of_interest POI);
	vector<int> crossBreed(vector<int> list1, vector<int> list2, int point1, int point2);
	pair<bool,int> findInVector(vector<int> v, int point1, int point2, int element);
	vector<int> insertInChild(vector<int> child, vector<int> list1, vector<int>list2, int point1, int point2, int element);
	int getIndex(vector<int> list1, vector<int> list2, int point1, int point2, int element);
	vector<int> mutation(vector<int> list);

private:
	solution bestSolution;
	verificator v;
};

