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
		 @brief 文字列データを追加する。
		 @detail 最後のヌル文字も含めて追加される。
		 */
		void add(const std::string & text);

		/**
		@brief Bindataのバイナリデータを追加する。
		*/
		void add(const Bindata & data);

		/**
		@brief 任意のバイナリデータを追加する。
		*/
		template<typename T> void add(const T & data)
		{
			mybuffer.add(reinterpret_cast<const char *>(&data), sizeof(T));
		}


		/**]
		 @brief データ内容を標準出力に出力する。
		 @detail 
		    標準出力がコマンドプロンプトになっていることが前提。
			文字コードが示す文字(nバイト目の数値)
			上記のようなフォーマットで全データ出力される。
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