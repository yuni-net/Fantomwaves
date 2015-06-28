#define _CRT_SECURE_NO_DEPRECATE

#pragma once

namespace fw
{

	template<typename X>
	void trade(X & one, X & another)
	{
		X other = one;
		one = another;
		another = other;
	}

}