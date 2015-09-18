#pragma once

#include "fw_includes.h"

namespace fw
{
	struct NetSurfer
	{
		sockaddr_in addr;

		bool operator==(const NetSurfer & another) const;
		bool operator!=(const NetSurfer & another) const;
	};
}