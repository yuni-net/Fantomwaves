#include <fw_popup.h>

namespace fw
{
	void popup(const std::string & message)
	{
		MessageBox(NULL, message.c_str(), "ÅI", MB_OK);
	}

	void popup(const std::string & message, const std::string & title)
	{
		MessageBox(NULL, message.c_str(), title.c_str(), MB_OK);
	}

}