#include <UDP_server.h>

namespace fw
{
	bool UDP_server::start_server(const unsigned short port)
	{
		// todo
	}

	/**
	@return
	true: �܂����o����Ă��Ȃ��f�[�^������B
	false: �S�Ẵf�[�^�͊��Ɏ��o����Ă���B
	*/
	bool UDP_server::are_there_any_left_datas() const
	{
		// todo
	}

	/**
	@brief �����o���̎�M�f�[�^����ł��Â����̂����o���B
	@param ���o�����f�[�^���i�[����Bindata�^�ϐ����w�肷��B
	@return
	true: �f�[�^�����o�����B
	false: �f�[�^�����o���Ȃ������B(�����o���f�[�^����������)
	*/
	bool UDP_server::pop_received_data(Bindata & buffer, NetSurfer & cliant_info)
	{
		// todo
	}

	void UDP_server::add_cliant(const NetSurfer & cliant_info)
	{
		// todo
	}
	void UDP_server::remove_cliant(const NetSurfer & cliant_info)
	{
		// todo
	}

	bool UDP_server::send_a_cliant(const Bindata & data, const NetSurfer & cliant_info) const
	{
		// todo
	}
	bool UDP_server::send_a_cliant(const Bindata & data) const
	{
		// todo
	}
	bool UDP_server::send_all(const Bindata & data) const
	{
		// todo
	}

	void UDP_server::begin_enum_cliants()
	{
		// todo
	}
	bool UDP_server::did_finish_enum() const
	{
		// todo
	}
	void UDP_server::goto_next_cliant()
	{
		// todo
	}



	UDP_server::UDP_server()
	{
		did_create_socket = false;
	}
	UDP_server::~UDP_server()
	{
		if (did_create_socket)
		{
			closesocket(sock);
		}
	}

}