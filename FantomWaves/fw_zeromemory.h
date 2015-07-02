#pragma once

namespace fw
{

	template<typename T>
	void zeromemory(T * req)
	{
		ZeroMemory(req, sizeof(T));
	}

}