#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "new_instance.h"
#include "point_of_interest.h"
#include "solution.h"
#include "instance_writer.h"
using namespace std;

class solution_writer
{
public:
	solution_writer();
	~solution_writer();
	void writeSolution(solution solution, string filename);
};

