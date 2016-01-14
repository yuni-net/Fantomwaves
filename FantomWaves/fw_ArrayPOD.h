#pragma once

#include "fw_trade.h"
#include "fw_typedef.h"
#include "fw_includes.h"

namespace fw
{

	/*
	* オリジナル可変長配列クラス。
	* ただしPOD型のみ対応。
	* メモリプールを作成し、必要に応じてplacement newでオブジェクトを作成する。
	* visual studio 標準のstd::vectorより高速。
	* fw::Arrayより高速
	* 削除と追加は常に末尾において行われる。
	* 要素は常に連続して順番通りに並んでいることが保証されている。
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

		// メモリプールのサイズ(要素の個数)を直接指定する。
		// 要素数があらかじめ大まかにでもわかっている場合はその分のメモリプールを準備しておくと実行速度が向上する。
		// 現在の要素数を下回るサイズを指定すると問答無用でデストラクタが呼ばれメモリプールサイズが変更される。
		fw::ArrayPOD<X>& secure(const uint size){
			if (size != space) re_secure(size);
			return *this;
		}

		// メモリプールのサイズ(要素の個数)を増加させるようリクエストする。
		// sizeには増加後のサイズを指定する。
		// 指定したサイズより現在のサイズの方が大きかった場合は何も起こらない。
		fw::ArrayPOD<X>& requre(const uint size){
			if (size > space) re_secure(size);
			return *this;
		}

		// メモリプールのサイズ(要素の個数)をsizeに指定した数だけ増加させる。
		fw::ArrayPOD<X>& addcure(const uint size){
			re_secure(this->size() + size);
			return *this;
		}

		// メモリプールのサイズ(要素の個数)をsizeに指定した数だけ減少させる。
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

		// メモリプールのサイズ(要素の個数)をゼロにする。
		// 問答無用で全てのデストラクタが呼ばれメモリプールは消滅する。
		fw::ArrayPOD<X>& zerocure(){
			secure(0);
			return *this;
		}

		// 要素数を指定する。
		// 新規追加された要素はデフォルトコンストラクタで初期化される。
		// 削除された要素はデストラクタが呼ばれる。
		fw::ArrayPOD<X>& setsize(const uint size){
			int gap = size - this->size();
			if (gap > 0) addsize(gap);
			if (gap < 0) popsize(-gap);
			return *this;
		}

		// 要素数を増加させるようリクエストする。
		// sizeには増加後の要素数を指定する。
		// 指定した要素数より現在の要素数の方が大きかった場合は何も起こらない。
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