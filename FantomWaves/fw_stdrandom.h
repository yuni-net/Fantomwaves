#pragma once

#include "fw_includes.h"
#include "fw_typedef.h"

namespace fw
{

	int stdrandom(int min, int max);
	int stdrandom_(int min, int max);
	int stdrandom(int max);

	uint restdrandom(uint value);
	uint restdrandom();

}