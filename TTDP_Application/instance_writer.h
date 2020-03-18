#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "new_instance.h"
#include "point_of_interest.h"

using namespace std;

class instance_writer
{
public:
	instance_writer();
	~instance_writer();
	void writeNewInstance(string filename, new_instance newInstance);
};

