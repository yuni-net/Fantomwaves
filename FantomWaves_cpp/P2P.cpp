#include <fw_P2P.h>
#include <fw_NetWork.h>
#include <fw_cast.h>
#include <fw_zeromemory.h>
#include "fw_Bindata.h"


namespace fw
{
	void P2P::set_lifeline_ifneed(const NetSurfer & surfer) const
	{
		if (did_set_lifeline){ return; }
		lifeline = surfer;
		did_set_lifeline = true;
		fw::newthread(call_I_still_alive, fw::pointer_cast<void *>(const_cast<P2P *>(this)));
	}


	bool P2P::send(const NetSurfer & cliant_info, const Bindata & data) const
	{
		set_lifeline_ifneed(cliant_info);
		return P2P_base::send(cliant_info, data);
	}

	void P2P::disconnect_lifeline()
	{
		am_I_dying = true;
	}



	P2P::P2P()
	{
		did_set_lifeline = false;
		am_I_dying = false;
	}



	void P2P::call_I_still_alive(void * parameter)
	{
		static const unsigned int interval_mili_sec = 6000;
		while (true)
		{
			const P2P & self = *reinterpret_cast<P2P *>(parameter);
			if (self.am_I_dying)
			{
				return;
			}
			Bindata data;
			data.add(char(0));
			self.send(self.lifeline, data);
			Sleep(interval_mili_sec);
		}
	}

}