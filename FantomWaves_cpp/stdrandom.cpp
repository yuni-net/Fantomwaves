#include <fw_stdrandom.h>

namespace fw
{
	int stdrandom(int min, int max)
	{
		return min + int(double(rand()) * (1.0 + max - min) / (1.0 + RAND_MAX));
	}
	int stdrandom_(int min, int max)
	{
		if (min > max) return stdrandom(max, min);
		return stdrandom(min, max);
	}
	int stdrandom(int max)
	{
		return stdrandom(0, max);
	}

	uint restdrandom(uint value)
	{
		srand(value);
		return value;
	}
	uint restdrandom()
	{
		return restdrandom(uint(time(NULL)));
	}

}