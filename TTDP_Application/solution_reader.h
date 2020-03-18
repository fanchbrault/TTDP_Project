#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "solution.h"
#include "instance_reader.h"

class solution_reader
{
public:
	solution_reader();
	~solution_reader();
	solution readSolutionFile(string filename);
};

