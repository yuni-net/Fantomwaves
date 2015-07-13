#pragma once
#define _CRT_SECURE_NO_DEPRECATE

#include "fw_cnct.h"
#include "fw_includes.h"
#include "fw_typedef.h"
#include "fw_vtypedef.h"

namespace fw
{
	/***
	@brief �t�@�C�������݂��邩�ǂ������肵�܂��B
	@param �����Ɏw�肵���p�X�����݂��A���t�@�C���ł��邩�ǂ������肵�܂��B
	@return true...It's a file. false...It's a NOT file.
	*/
	bool iffile(const std::string & path);
	bool iffile(const vstring & path);

	/***
	@brief �f�B���N�g�������݂��邩�ǂ������肵�܂��B
	@param �����Ɏw�肵���p�X�����݂��A���f�B���N�g���ł��邩�ǂ������肵�܂��B
	@return true...It's a directory. false...It's a NOT directory.
	*/
	bool ifdire(const std::string & path);
	bool ifdire(const vstring & path);

	/***
	@brief ���[�g�p�X�𓾂�Ƃ��֗��ł��B
	@param �����Ɏw�肵���t�@�C���E�f�B���N�g���̃p�X�ւ̃��[�g�p�X�𓾂܂��B
	@detail �p�X�̍Ō�ɂ� / ���t���܂��B
	        ��1) C:/root/text.txt -> C:/root/
			��2) C:/root/directory -> C:/root/
			\ ���g�����\�L�͎g���܂���B
	@return ���[�g�p�X
	*/
	std::string root(const std::string & path);
	vstring root(const vstring & path);

	/***
	@brief ���[�g�f�B���N�g���𓾂�Ƃ��֗��ł��B
	@param �����Ɏw�肵���t�@�C���E�f�B���N�g���̃��[�g�f�B���N�g���𓾂܂��B
	@detail �p�X�̍Ō�� / �͕t���܂���B
		��1) C:/root/text.txt -> C:/root
		��2) C:/root/directory -> C:/root
		\ ���g�����\�L�͎g���܂���B
	@return ���[�g�f�B���N�g��
	*/
	std::string rootdire(const std::string & path);
	vstring rootdire(const vstring & Path);

	/***
	@brief �t�@�C���̊g���q�𓾂܂��B
	@detail �h�b�g�t���ł��B
	        ��) file.txt -> .txt
	@param �����Ɏw�肵���t�@�C���̊g���q�𓾂܂��B
	@return �g���q
	*/
	std::string extend(const std::string & filepath);	// file.txt -> .txt
	vstring extend(const vstring & filepath);

	/***
	@brief �t�@�C���̊g���q�𓾂܂��B
	@detail �h�b�g�͕t���܂���B
		��) file.txt -> txt
	@param �����Ɏw�肵���t�@�C���̊g���q�𓾂܂��B
	@return �g���q
	*/
	std::string onlyextend(const std::string & filepath);	// file.txt -> txt
	vstring onlyextend(const vstring & filepath);

	/***
	@brief �t�@�C�����𓾂܂��B
	@detail �g���q�t���ł��B
	        ��) C:/file.txt -> file.txt
	@param �����Ɏw�肵���t�@�C���̖��O�𓾂܂��B
	@return �t�@�C����
	*/
	std::string filename(const std::string & path);

	/***
	@brief �t�@�C������f�B���N�g�����𓾂܂��B
	@detail �t�@�C�����̏ꍇ�A�g���q�͕t���܂���B
		��1) C:/file.txt -> file
		��2) C:/dire -> dire
	@param �����Ɏw�肵���p�X�̖��O�𓾂܂��B
	@return �p�X
	*/
	std::string onlyname(const std::string & path);
	vstring onlyname(const vstring & path);

	/***
	@brief �p�X�̔z���n���ƁA���̒��Ńt�@�C���ւ̃p�X�������W�߂��z���Ԃ��܂��B
	@param �p�X�̔z��
	@return �t�@�C���p�X�̔z��
	*/
	vstring onlyfile(const vstring & path);

	/***
	@brief �p�X�̔z���n���ƁA���̒��Ńf�B���N�g���̃p�X�������W�߂��z���Ԃ��܂��B
	@param �p�X�̔z��
	@return �f�B���N�g���p�X�̔z��
	*/
	vstring onlydire(const vstring & path);

	/***
	@brief �g���q�̕�����ύX���܂��B
	@param
		filepath: �ύX�O�̃t�@�C���p�X���w�肵�܂��B
		extend: �ύX��̊g���q���w�肵�܂��B�h�b�g�͕t���Ă͂����܂���B
	@return �g���q���ύX���ꂽ��̃t�@�C���p�X
	*/
	std::string changextend(const std::string & filepath, const std::string & extend);
	vstring changextend(const vstring & filepath, const std::string & extend);

	/***
	@brief �g���q���������ǂ������肵�܂��B
	@param
		one: ���肵�����p�X�̈��
		ano: ���肵�����p�X�̂������
	@return true...���� false...�Ⴄ
	*/
	bool samextend(const std::string & one, const std::string & ano);

	/***
	@brief �g���q������̕����ǂ����`�F�b�N����B
	@param
		extend: ����̊g���q
		path: �����Ɏw�肵���p�X�̊g���q��extend�Ɠ������ǂ������`�F�b�N���܂��B
	@return true...���� false...�Ⴄ
	*/
	bool checkextend(const std::string & extend, const std::string & path);



	/*
	memo: deep�̂Ƃ����C���h�J�[�h��ݒ肵�Ă��܂��ƃt�H���_�T�����ł��Ȃ��Ȃ��Ă��܂�
	*/

	/***
	�t�@�C���E�f�B���N�g���̌������s�����߂̃N���X�ł��B
	���\�b�h�`�F�[���ɂ���Ċe��ݒ�����肵���㌟�����s���Ƃ����C���^�[�t�F�C�X�ɂȂ��Ă��܂��B
	*/
	class Path
	{
	private:
		/***
		�T���̐[��(�w�肵���f�B���N�g�����������Ȃ̂��ȉ��S���Ȃ̂�)���w�肷��Ƃ��ɓn���^�ł��B
		*/
		class Depth
		{
		public:
			Depth(Path & p) :parent(p) {}
			void init(){ deep(); }
			Path & shallow()
			{
				mode = shallow_mode;
				return parent;
			}
			Path & deep()
			{
				mode = deep_mode;
				return parent;
			}

			bool ifshallow() const { return mode == shallow_mode; }
			bool ifdeep() const { return mode == deep_mode; }

		private:
			Path & parent;
			enum Mode{ shallow_mode, deep_mode };
			Mode mode;
		};

		/***
		�T������p�X�̎��(�t�@�C�������E�f�B���N�g�������E�t�@�C���ƃf�B���N�g��)���w�肷��Ƃ��ɓn���^�ł��B
		*/
		class Attribute
		{
		public:
			Attribute(Path & p) :parent(p) {}
			void init(){ all(); }
			Path & file()
			{
				mode = file_mode;
				return parent;
			}
			Path & dire()
			{
				mode = dire_mode;
				return parent;
			}
			Path & all()
			{
				mode = all_mode;
				return parent;
			}

			bool iffile() const { return mode == file_mode; }
			bool ifdire() const { return mode == dire_mode; }
			bool ifall() const { return mode == all_mode; }

		private:
			Path & parent;
			enum Mode{ file_mode, dire_mode, all_mode };
			Mode mode;
		};

	public:

		Path & init(){
			target_ = &mytarget;
			wild_ = &any;
			extens_ = &none;
			depth().init();
			attribute().init();
			return *this;
		}


#pragma warning(push)
#pragma warning(disable:4355)
		Path()
			:
			any("*"), none(""),
			mydepth(*this), myattribute(*this)
		{
			init();
		}

		/***
		@brief �T������f�B���N�g�����w�肵�܂��B
		*/
		Path & directory(const vstring & direpath){
			dire_path_ = direpath;
			return init();
		}
		Path & directory(const std::string & direpath){
			dire_path_ = direpath;
			return init();
		}

		/***
		@brief �T���������f�B���N�g�����w�肵�܂��B
		*/
		Path(const vstring & direpath)
			:
			any("*"), none(""),
			mydepth(*this), myattribute(*this)
		{
			directory(direpath);
		}
		Path(const std::string & direpath)
			:
			any("*"), none(""),
			mydepth(*this), myattribute(*this)
		{
			directory(direpath);
		}
#pragma warning(pop)

		/***
		@brief �T�����ʂ��i�[����X�g�����O�z����w�肵�܂��B
		*/
		Path & target(vstring & target){
			this->target_ = &target;
			return *this;
		}
		Path & deftarget(){ return this->target(this->mytarget); }

		/***
		@brief �T���������p�X���A���C���h�J�[�h���g���Ďw�肵�܂��B
		@detail extention�Ɠ����Ɏw�肷�邱�Ƃ͂ł��܂���B
		*/
		Path & wildcard(const std::string & wild){
			this->wild_ = &wild;
			return *this;
		}

		/***
		@brief �T���������p�X���A�g���q���g���Ďw�肵�܂��B
		@detail wildcard�Ɠ����Ɏw�肷�邱�Ƃ͂ł��܂���B
		*/
		Path & extention(const std::string & ext){
			this->extens_ = &ext;
			return *this;
		}

		Depth & depth(){ return mydepth; }
		Attribute & attribute(){ return myattribute; }

		/***
		@brief �T�������s���܂��B
		*/
		uint exe(){
			for (uint i = 0; i < dire_path_.size(); i++){
				dispose(dire_path_[i]);
			}

			return target_->size();
		}

		/***
		@brief �T�������s���A���̌��ʂ�Ԃ��܂��B
		*/
		vstring & get(){
			exe();
			return *target_;
		}

		/***
		@brief �T�����ʂ�Ԃ��܂��B
		*/
		vstring & got(){ return *target_; }

	private:

		vstring dire_path_;
		vstring * target_;
		const std::string * wild_;
		const std::string * extens_;
		Depth mydepth;
		Attribute myattribute;
		vstring mytarget;
		const std::string any;
		const std::string none;

		/***
		@brief �ċA�I�ɒT�����s���܂��B
		*/
		void dispose(const std::string & direpath){
			vstring & target = *(this->target_);
			const std::string & wild = *(this->wild_);
			const std::string & extens = *(this->extens_);

			WIN32_FIND_DATA file_data;	//�t�@�C�����̓t�H���_�̏�񂪂����Ɋi�[�����
			HANDLE file_hand;			//�������̃n���h�����i�[

			file_hand = FindFirstFile(fw::cnct() << direpath << "\\" < wild, &file_data);   //�������s���A�n���h�����擾

			do{
				if (file_hand == INVALID_HANDLE_VALUE) continue;
				// found file or folder

				if (file_data.cFileName == std::string(".") || file_data.cFileName == std::string("..")) continue;
				// It's not "." nor ".."

				std::string foundpath = fw::cnct() << direpath << "\\" <<= file_data.cFileName;

				if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)	// it's a folder
				{
					if (!mydepth.ifshallow()) dispose(foundpath);	// recursive processing
					if (myattribute.iffile()) continue;
				}
				else													// it's a file
				{
					if (myattribute.ifdire()) continue;
					if (extens != ""){
						const std::string & thextens(fw::extend(foundpath));
						if (extens.find(thextens, 0) == std::string::npos) continue;	// not found
					}
				}

				target += foundpath;

			} while (FindNextFile(file_hand, &file_data));

			FindClose(file_hand);   //�����Ɏg�p�����f�[�^��j��
		}
	};



}