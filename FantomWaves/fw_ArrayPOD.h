#pragma once

#include <vector>
#include "fw_Array.h"
#include "fw_trade.h"
#include "fw_typedef.h"
#include "fw_includes.h"

namespace fw
{

	/*
	* �I���W�i���ϒ��z��N���X�B
	* ������POD�^�̂ݑΉ��B
	* �R���X�g���N�^��f�X�g���N�^�̌Ăяo���͕ۏ؂���Ȃ��B(��{�I�ɌĂяo����Ȃ�)
	* visual studio �W����std::vector��荂���B
	* fw::Array��荂��
	* �폜�ƒǉ��͏�ɖ����ɂ����čs����B
	* �v�f�͏�ɘA�����ď��Ԓʂ�ɕ���ł��邱�Ƃ��ۏ؂���Ă���B
	*/
	template<typename X>
	class ArrayPOD
	{
	public:
		ArrayPOD(){ construct(); }
		ArrayPOD(const fw::ArrayPOD<X> & req){
			construct();
			init(req);
		}
		ArrayPOD(const X * arr, const uint size){
			construct();
			init(arr, size);
		}
		ArrayPOD(const fw::Array<X> & req){
			construct();
			init(req);
		}
		ArrayPOD(const std::vector<X> & req){
			construct();
			init(req);
		}

		fw::ArrayPOD<X> & init(const fw::ArrayPOD<X> & req){
			setsize(req.size());
			memcpy(content, req.content, sizeof(X)*req.size());
			return *this;
		}
		fw::ArrayPOD<X>& init(const X* arr, const uint size){
			setsize(size);
			memcpy(content, arr, sizeof(X)*size);
			return *this;
		}
		fw::ArrayPOD<X> & init(const fw::Array<X> & req){
			setsize(req.size());
			memcpy(content, req.head(), sizeof(X)*req.size());
			return *this;
		}
		fw::ArrayPOD<X> & init(const std::vector<X> & req){
			setsize(req.size());
			memcpy(content, &(req[0]), sizeof(X)*req.size());
			return *this;
		}

		fw::ArrayPOD<X> & operator= (const fw::ArrayPOD<X> & req){ return init(req); }
		fw::ArrayPOD<X> & operator= (const fw::Array<X> & req){ return init(req); }
		fw::ArrayPOD<X> & operator= (const std::vector<X> & req){ return init(req); }

		uint size() const { return elem_size; }

		// �v�f�����w�肷��B
		fw::ArrayPOD<X> & setsize(const uint size){
			int gap = size - this->size();
			if (gap > 0) addsize(gap);
			if (gap < 0) popsize(-gap);
			return *this;
		}

		// �v�f���𑝉�������悤���N�G�X�g����B
		// size�ɂ͑�����̗v�f�����w�肷��B
		// �w�肵���v�f����茻�݂̗v�f���̕����傫�������ꍇ�͉����N����Ȃ��B
		fw::ArrayPOD<X> & reqsize(const uint size){
			if (size > this->size()) addsize(size - this->size());
			return *this;
		}

		fw::ArrayPOD<X> & addsize(const uint size = 1){
			uint needsize = this->size() + size;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			elem_size += size;
			return *this;
		}
		fw::ArrayPOD<X> & addsize(const uint size, const X & req){
			uint needsize = this->size() + size;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			for (uint i = this->size(); i < this->size() + size; ++i){
				content[i] = req;
			}
			elem_size += size;
			return *this;
		}

		fw::ArrayPOD<X> & popsize(const uint size = 1){
			if (size >= this->size())
			{
				elem_size = 0;
				return *this;
			}

			elem_size -= size;
			return *this;
		}

		fw::ArrayPOD<X> & zerosize(){
			setsize(0);
			return *this;
		}

		// �������v�[���̃T�C�Y(�v�f�̌�)�𒼐ڎw�肷��B
		// �v�f�������炩���ߑ�܂��ɂł��킩���Ă���ꍇ�͂��̕��̃������v�[�����������Ă����Ǝ��s���x�����シ��B
		// ���݂̗v�f���������T�C�Y���w�肵���ꍇ�ł��ⓚ���p�Ń������v�[���T�C�Y���ύX����A�v�f�������̃T�C�Y�ɂȂ�B
		fw::ArrayPOD<X> & secure(const uint size){
			if (size != space){ re_secure(size); }
			if (size < this->size()){ elem_size = size; }
			return *this;
		}

		// �������v�[���̃T�C�Y(�v�f�̌�)�𑝉�������悤���N�G�X�g����B
		// size�ɂ͑�����̃T�C�Y���w�肷��B
		// �w�肵���T�C�Y��茻�݂̃T�C�Y�̕����傫�������ꍇ�͉����N����Ȃ��B
		fw::ArrayPOD<X> & requre(const uint size){
			if (size > space) re_secure(size);
			return *this;
		}

		// �������v�[���̃T�C�Y(�v�f�̌�)��size�Ɏw�肵������������������B
		fw::ArrayPOD<X> & addcure(const uint size){
			re_secure(this->size() + size);
			return *this;
		}

		// �������v�[���̃T�C�Y(�v�f�̌�)��size�Ɏw�肵������������������B
		fw::ArrayPOD<X> & popcure(const uint size){
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
		// �ⓚ���p�Ń������v�[���͏��ł���B
		fw::ArrayPOD<X> & zerocure(){
			secure(0);
			return *this;
		}

		const X & operator[] (const uint index) const { return access(index); }
		X & operator[] (const uint index){ return access(index); }
		const X & access(const uint index) const {
			if (index >= size()){
				throw std::out_of_range("fw::ArrayPOD Out-of-Range Access Error");
			}
			return content[index];
		}
		X & access(const uint index){
			const ArrayPOD<X>& ci = *this;
			return const_cast<X&>(ci.access(index));
		}
		X value(const uint index) const { return access(index); }

		const X * address(const uint index) const { return &access(index); }
		X * address(const uint index){ return &access(index); }
		const X * head() const {
			return content;
		}
		X * head(){
			return content;
		}

		const X & last() const { return access(size() - 1); }
		X & last(){ return access(size() - 1); }
		X lastvalue() const { return last(); }






		fw::ArrayPOD<X> & add(){
			return addsize(1);
		}
		fw::ArrayPOD<X> & add(const X & req){
			return addsize(1, req);
		}
		fw::ArrayPOD<X> & operator+= (const X & input){
			add(input);
			return *this;
		}
		fw::ArrayPOD<X> & operator<< (const X & input){
			add(input);
			return *this;
		}
		fw::ArrayPOD<X>& add(const X& req, const uint num){
			requre(num);
			for (uint index = size(); index < size() + num; ++index){
				access(index) = req;
			}
			elem_size += num;
			return *this;
		}
		fw::ArrayPOD<X> & add(const fw::ArrayPOD<X>& input){
			requre(size()+input.size());
			memcpy(content + this->size(), input.content, sizeof(X)*input.size());
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
			memcpy(content + this->size(), arr, sizeof(X)*size);
			elem_size += size;
			return *this;
		}

		fw::ArrayPOD<X>& pop(const uint size = 1){ return popsize(size); }




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


		~ArrayPOD(){
			free(content);
		}


	private:
		X * content;
		uint elem_size;
		uint space;

		void re_secure(uint size){
			X * another = static_cast<X*>(malloc(sizeof(X) * size));
			trade(content, another);
			uint copy_size = this->size();
			if (copy_size > size){ copy_size = size; }
			memcpy(content, another, copy_size);
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