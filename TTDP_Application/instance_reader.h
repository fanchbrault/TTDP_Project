#pragma once
#include "classic_instance.h"
#include "point_of_interest.h"
#include "new_instance.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class instance_reader
{
public:
	instance_reader();
	~instance_reader();
	classic_instance readClassicFile(string filename);
	new_instance readNewFile(string filename);
	int getNbCategories(string categories);
	int* getMaxPerCategories(string categories, int nbCategories);
	point_of_interest getStartingPoint(string startingPoint);
	point_of_interest getPOI(string POI, int nbCategories);
	point_of_interest getNewPOI(string POI, int nbCategories);
	vector<string> split(string str);
};

