#pragma once

namespace fw
{
	template<typename T> void inline exchange(const T & one, const T & ano)
	{
		T strage = one;
		one = ano;
		ano = strage;
	}
}