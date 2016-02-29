#include "fw_typedef.h"
#include "fw_ArrayPOD.h"

namespace fw
{
	class Bindata
	{
	public:
		void set_size(const uint bytes);
		char * buffer();
		const char * buffer() const;
		uint bytes() const;
		bool operator!=(const Bindata & another) const;

		/**
		 @brief ������f�[�^��ǉ�����B
		 @detail �Ō�̃k���������܂߂Ēǉ������B
		 */
		void add(const std::string & text);

		/**
		@brief Bindata�̃o�C�i���f�[�^��ǉ�����B
		*/
		void add(const Bindata & data);

		/**
		@brief �C�ӂ̃o�C�i���f�[�^��ǉ�����B
		*/
		template<typename T> void add(const T & data)
		{
			mybuffer.add(reinterpret_cast<const char *>(&data), sizeof(T));
		}


		/**]
		 @brief �f�[�^���e��W���o�͂ɏo�͂���B
		 @detail 
		    �W���o�͂��R�}���h�v�����v�g�ɂȂ��Ă��邱�Ƃ��O��B
			�����R�[�h����������(n�o�C�g�ڂ̐��l)
			��L�̂悤�ȃt�H�[�}�b�g�őS�f�[�^�o�͂����B
		 */
		void show_cmd() const;

		Bindata & operator>>(std::string & text);
		template<typename T> Bindata & operator>>(T & data)
		{
			return pop(data);
		}

		Bindata & pop(std::string & text);
		template<typename T> Bindata & pop(T & data)
		{
			return pop(&data, 1);
		}
		template<typename T> Bindata & pop(T * buffer, unsigned int size)
		{
			copy(buffer, size);
			proceed(sizeof(T)*size);
			return *this;
		}

		Bindata & copy(std::string & text);
		template<typename T> Bindata & copy(T & data)
		{
			return pop(&data, 1);
		}
		template<typename T> Bindata & copy(T * buffer, unsigned int size)
		{
			memcpy(buffer, mybuffer.address(read_beg), sizeof(T)*size);
			return *this;
		}

		Bindata & proceed(unsigned int bytes);
		Bindata & seek_head();




		Bindata();
	private:
		ArrayPOD<char> mybuffer;
		unsigned int read_beg;
	};
}