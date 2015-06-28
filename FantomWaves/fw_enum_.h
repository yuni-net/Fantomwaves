#pragma once

#define fw_enum_(type, target, name, value) \
	void name(){\
		target = value;\
		return *this;\
	}\
	bool ifname(){\
		return target==value;\
	}