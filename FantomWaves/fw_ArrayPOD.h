#pragma once

#include "fw_trade.h"
#include "fw_typedef.h"
#include "fw_includes.h"

namespace fw
{

	/*
	* �I���W�i���ϒ��z��N���X�B
	* ������POD�^�̂ݑΉ��B
	* �������v�[�����쐬���A�K�v�ɉ�����placement new�ŃI�u�W�F�N�g���쐬����B
	* visual studio �W����std::vector��荂���B
	* fw::Array��荂��
	* �폜�ƒǉ��͏�ɖ����ɂ����čs����B
	* �v�f�͏�ɘA�����ď��Ԓʂ�ɕ���ł��邱�Ƃ��ۏ؂���Ă���B
	*/
	template<typename X>
	class ArrayPOD
	{
	public:

		fw::ArrayPOD<X>& init(){
			zerosize();
			return *this;
		}

		ArrayPOD(){ construct(); }

		fw::ArrayPOD<X>& init(const fw::ArrayPOD<X>& req){
			zerosize();
			add(req);
			return *this;
		}

		ArrayPOD(const fw::ArrayPOD<X>& req){
			construct();
			init(req);
		}

		fw::ArrayPOD<X>& operator= (const fw::ArrayPOD<X>& req){ return init(req); }

		fw::ArrayPOD<X>& init(const X& req){
			zerosize();
			add(req);
			return *this;
		}

		ArrayPOD(const X& req){
			construct();
			init(req);
		}

		fw::ArrayPOD<X>& operator= (const X& req){ return init(req); }

		fw::ArrayPOD<X>& init(const X* arr, const uint size){
			zerosize();
			add(arr, size);
			return *this;
		}

		ArrayPOD(const X* arr, const uint size){
			construct();
			init(arr, size);
		}

		// �������v�[���̃T�C�Y(�v�f�̌�)�𒼐ڎw�肷��B
		// �v�f�������炩���ߑ�܂��ɂł��킩���Ă���ꍇ�͂��̕��̃������v�[�����������Ă����Ǝ��s���x�����シ��B
		// ���݂̗v�f���������T�C�Y���w�肷��Ɩⓚ���p�Ńf�X�g���N�^���Ă΂ꃁ�����v�[���T�C�Y���ύX�����B
		fw::ArrayPOD<X>& secure(const uint size){
			if (size != space) re_secure(size);
			return *this;
		}

		// �������v�[���̃T�C�Y(�v�f�̌�)�𑝉�������悤���N�G�X�g����B
		// size�ɂ͑�����̃T�C�Y���w�肷��B
		// �w�肵���T�C�Y��茻�݂̃T�C�Y�̕����傫�������ꍇ�͉����N����Ȃ��B
		fw::ArrayPOD<X>& requre(const uint size){
			if (size > space) re_secure(size);
			return *this;
		}

		// �������v�[���̃T�C�Y(�v�f�̌�)��size�Ɏw�肵������������������B
		fw::ArrayPOD<X>& addcure(const uint size){
			re_secure(this->size() + size);
			return *this;
		}

		// �������v�[���̃T�C�Y(�v�f�̌�)��size�Ɏw�肵������������������B
		fw::ArrayPOD<X>& popcure(const uint size){
			if (size >= this->size())
			{
				zerocure();
			}
			else
			{
				uint poped = this->size() - size;
				secure(poped);
			}
			return *this;
		}

		// �������v�[���̃T�C�Y(�v�f�̌�)���[���ɂ���B
		// �ⓚ���p�őS�Ẵf�X�g���N�^���Ă΂ꃁ�����v�[���͏��ł���B
		fw::ArrayPOD<X>& zerocure(){
			secure(0);
			return *this;
		}

		// �v�f�����w�肷��B
		// �V�K�ǉ����ꂽ�v�f�̓f�t�H���g�R���X�g���N�^�ŏ����������B
		// �폜���ꂽ�v�f�̓f�X�g���N�^���Ă΂��B
		fw::ArrayPOD<X>& setsize(const uint size){
			int gap = size - this->size();
			if (gap > 0) addsize(gap);
			if (gap < 0) popsize(-gap);
			return *this;
		}

		// �v�f���𑝉�������悤���N�G�X�g����B
		// size�ɂ͑�����̗v�f�����w�肷��B
		// �w�肵���v�f����茻�݂̗v�f���̕����傫�������ꍇ�͉����N����Ȃ��B
		fw::ArrayPOD<X>& reqsize(const uint size){
			if (size > this->size()) addsize(size - this->size());
			return *this;
		}

		fw::ArrayPOD<X>& addsize(const uint size = 1){
			uint needsize = this->size() + size;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			return *this;
		}
		fw::ArrayPOD<X>& addsize(const uint size, const X& req){
			uint needsize = this->size() + size;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			for (uint i = 0; i < size; ++i) add_object(req);
			return *this;
		}

		fw::ArrayPOD<X>& popsize(const uint size = 1){
			uint gap = size;
			if (size > this->size()) gap = this->size();
			for (uint i = 0; i < gap; ++i)
			{
				last().~X();
				--elem_size;
			}
			return *this;
		}

		fw::ArrayPOD<X>& zerosize(){
			setsize(0);
			return *this;
		}

		fw::ArrayPOD<X>& add(){
			uint needsize = size() + 1;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			++elem_size;
			return *this;
		}
		fw::ArrayPOD<X>& add(const X& req){
			uint needsize = size() + 1;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			++elem_size;
			last() = req;
			return *this;
		}
		fw::ArrayPOD<X> & operator+= (const X& input){
			add(input);
			return *this;
		}
		fw::ArrayPOD<X> & operator<< (const X& input){
			add(input);
			return *this;
		}
		fw::ArrayPOD<X>& add(const X& req, const uint num){
			uint needsize = size() + num;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			for (unsigned int index = elem_size; index < elem_size + num; ++index)
			{
				access(index) = req;
			}
			elem_size += num;
			return *this;
		}
		fw::ArrayPOD<X> & add(const fw::ArrayPOD<X>& input){
			requre(size()+input.size());
			for (unsigned int index = size(); index < size() + input.size(); ++index)
			{
				access(index) = input[index];
			}
			elem_size += input.size();
			return *this;
		}
		fw::ArrayPOD<X> & operator+= (const fw::ArrayPOD<X>& input){
			add(input);
			return *this;
		}
		fw::ArrayPOD<X> & operator<< (const fw::ArrayPOD<X>& input){
			add(input);
			return *this;
		}
		fw::ArrayPOD<X>& add(const X* arr, const uint size){
			requre(this->size()+size);
			memcpy(content+this->size(), arr, size)
			elem_size += input.size();
			return *this;
		}

		fw::ArrayPOD<X>& pop(const uint size = 1){ return popsize(size); }

		const X& access(const uint index) const {
			if (index >= size()){
				throw std::out_of_range("fw::ArrayPOD Out-of-Range Access Error");
			}
			return content[index];
		}
		const X& operator[] (const uint index) const { return access(index); }
		X& access(const uint index){
			const ArrayPOD<X>& ci = *this;
			return const_cast<X&>(ci.access(index));
		}
		X& operator[] (const uint index){ return access(index); }
		X value(const uint index) const { return access(index); }

		const X* address(const uint index) const { return &access(index); }
		X* address(const uint index){ return &access(index); }
		const X* head() const {
			if (size() == 0) return nullptr;
			return address(0);
		}
		X* head(){
			if (size() == 0) return nullptr;
			return address(0);
		}

		const X& last() const { return access(size() - 1); }
		X& last(){ return access(size() - 1); }
		X lastvalue() const { return last(); }

		X& next(){
			addsize();
			return last();
		}
		X nextvalue(){ return next(); }
		X& next(const X& req){
			add(req);
			return last();
		}
		X nextvalue(const X& req){ return next(req); }

		fw::ArrayPOD<X> member(const uint index, const uint size) const {
			fw::ArrayPOD<X> r(address(index), size);
			return r;
		}
		fw::ArrayPOD<X> member(const uint size) const {
			fw::ArrayPOD<X> r(address(0), size);
			return r;
		}

		fw::ArrayPOD<X> operator+ (const fw::ArrayPOD<X>& another) const {
			fw::ArrayPOD<X> r(*this);
			r += another;
			return r;
		}
		fw::ArrayPOD<X> operator+ (const X& another) const {
			fw::ArrayPOD<X> r(*this);
			r += another;
			return r;
		}

		uint size() const { return elem_size; }

		~ArrayPOD(){
			free(content);
		}


	private:
		X * content;
		uint elem_size;
		uint space;

		void re_secure(uint size){
			X* another = static_cast<X*>(malloc(sizeof(X) * size));
			trade(content, another);
			uint oldsize = this->size();
			elem_size = 0;
			memcpy(content, another, oldsize);
			free(another);
			space = size;
		}


		void construct(){
			content = nullptr;
			elem_size = 0;
			space = 0;
		}

	};

}