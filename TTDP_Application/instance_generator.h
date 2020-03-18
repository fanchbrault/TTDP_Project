#pragma once
#include "classic_instance.h"
#include "new_instance.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

class instance_generator
{
public:
	instance_generator();
	~instance_generator();

	new_instance generateNewInstance(classic_instance instance);
};

