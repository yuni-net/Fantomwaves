#pragma once

#include "fw_trade.h"
#include "fw_typedef.h"
#include "fw_includes.h"

namespace fw
{

	template<typename X>
	class Array;

	template<typename X>
	class vecmemdata
	{
		fw::Array<X> myvec;
		const fw::Array<X> & wvec;
		fw::Array<X> & rvec;
		bool rflag;
		uint mybeg;
		uint mynum;

	public:

		vecmemdata(const fw::Array<X> & target, uint num) :wvec(target), rvec(myvec) {
			mybeg = 0;
			mynum = num;
			rflag = false;
		}
		vecmemdata(const fw::Array<X> & target, uint beg, uint num) :wvec(target), rvec(myvec) {
			mybeg = beg;
			mynum = num;
			rflag = false;
		}
		vecmemdata(fw::Array<X> & target, uint num) :rvec(target) : wvec(target), rvec(target) {
			mybeg = 0;
			mynum = num;
			rflag = true;
		}
		vecmemdata(fw::Array<X> & target, uint beg, uint num) :wvec(target), rvec(target) {
			mybeg = beg;
			mynum = num;
			rflag = true;
		}

		const fw::Array<X> & cvec() const {
			if (rflag) return rvec;
			return wvec;
		}
		fw::Array<X> & vec() const { return rvec; }

		uint beg() const { return mybeg; }
		uint num() const { return mynum; }

		const void * cbegress() const {
			if (rflag) return rvec.address(mybeg);
			return wvec.address(mybeg);
		}
		void * begress() const { return rvec.address(beg); }
	};





	/*
	* オリジナル可変長配列クラス。
	* メモリプールを作成し、必要に応じてplacement newでオブジェクトを作成する。
	* visual studio 標準のstd::vectorより高速。
	* 削除と追加は常に末尾において行われる。
	* 要素は常に連続して順番通りに並んでいることが保証されている。
	*/
	template<typename X>
	class Array
	{
	public:

		fw::Array<X>& init(){
			zerosize();
			return *this;
		}

		Array(){ construct(); }

		fw::Array<X>& init(const fw::Array<X>& req){
			zerosize();
			add(req);
			return *this;
		}

		Array(const fw::Array<X>& req){
			construct();
			init(req);
		}

		fw::Array<X>& operator= (const fw::Array<X>& req){ return init(req); }

		fw::Array<X>& init(const X& req){
			zerosize();
			add(req);
			return *this;
		}

		Array(const X& req){
			construct();
			init(req);
		}

		fw::Array<X>& operator= (const X& req){ return init(req); }

		fw::Array<X>& init(const X* arr, const uint size){
			zerosize();
			add(arr, size);
			return *this;
		}

		Array(const X* arr, const uint size){
			construct();
			init(arr, size);
		}

		// メモリプールのサイズ(要素の個数)を直接指定する。
		// 要素数があらかじめ大まかにでもわかっている場合はその分のメモリプールを準備しておくと実行速度が向上する。
		// 現在の要素数を下回るサイズを指定すると問答無用でデストラクタが呼ばれメモリプールサイズが変更される。
		fw::Array<X>& secure(const uint size){
			if (size != space) re_secure(size);
			return *this;
		}

		// メモリプールのサイズ(要素の個数)を増加させるようリクエストする。
		// sizeには増加後のサイズを指定する。
		// 指定したサイズより現在のサイズの方が大きかった場合は何も起こらない。
		fw::Array<X>& requre(const uint size){
			if (size > space) re_secure(size);
			return *this;
		}

		// メモリプールのサイズ(要素の個数)をsizeに指定した数だけ増加させる。
		fw::Array<X>& addcure(const uint size){
			re_secure(this->size() + size);
			return *this;
		}

		// メモリプールのサイズ(要素の個数)をsizeに指定した数だけ減少させる。
		fw::Array<X>& popcure(const uint size){
			uint popsize = this->size();
			if (size < this->size()) popsize = size;
			secure(popsize);
			return *this;
		}

		// メモリプールのサイズ(要素の個数)をゼロにする。
		// 問答無用で全てのデストラクタが呼ばれメモリプールは消滅する。
		fw::Array<X>& zerocure(){
			secure(0);
			return *this;
		}

		// 要素数を指定する。
		// 新規追加された要素はデフォルトコンストラクタで初期化される。
		// 削除された要素はデストラクタが呼ばれる。
		fw::Array<X>& setsize(const uint size){
			int gap = size - this->size();
			if (gap > 0) addsize(gap);
			if (gap < 0) popsize(-gap);
			return *this;
		}

		// 要素数を増加させるようリクエストする。
		// sizeには増加後の要素数を指定する。
		// 指定した要素数より現在の要素数の方が大きかった場合は何も起こらない。
		fw::Array<X>& reqsize(const uint size){
			if (size > this->size()) addsize(size - this->size());
			return *this;
		}

		fw::Array<X>& addsize(const uint size = 1){
			uint needsize = this->size() + size;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			for (uint i = 0; i<size; ++i) add_object();
			return *this;
		}
		fw::Array<X>& addsize(const uint size, const X& req){
			uint needsize = this->size() + size;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			for (uint i = 0; i < size; ++i) add_object(req);
			return *this;
		}

		fw::Array<X>& popsize(const uint size = 1){
			uint gap = size;
			if (size > this->size()) gap = this->size();
			for (uint i = 0; i < gap; ++i)
			{
				last().~X();
				--elem_size;
			}
			return *this;
		}

		fw::Array<X>& zerosize(){
			setsize(0);
			return *this;
		}

		fw::Array<X>& add(){
			uint needsize = size() + 1;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			add_object();
			return *this;
		}
		fw::Array<X>& add(const X& req){
			uint needsize = size() + 1;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			add_object(req);
			return *this;
		}
		fw::Array<X> & operator+= (const X& input){
			add(input);
			return *this;
		}
		fw::Array<X> & operator<< (const X& input){
			add(input);
			return *this;
		}
		fw::Array<X>& add(const X& req, const uint num){
			uint needsize = size() + num;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				re_secure(needsize * 2);
			}
			for (uint i = 0; i < num; ++i) add_object(req);
			return *this;
		}
		fw::Array<X> & add(const fw::Array<X>& input){
			requre(input.size());
			for (uint i = 0; i < input.size(); ++i) add(input[i]);
			return *this;
		}
		fw::Array<X> & operator+= (const fw::Array<X>& input){
			add(input);
			return *this;
		}
		fw::Array<X> & operator<< (const fw::Array<X>& input){
			add(input);
			return *this;
		}
		fw::Array<X>& add(const X* arr, const uint size){
			requre(size);
			for (uint i = 0; i < size; ++i) add(arr[i]);
			return *this;
		}

		fw::Array<X>& pop(const uint size = 1){ return popsize(size); }

		const X& access(const uint index) const {
			if (index >= size()){
				throw std::out_of_range("fw::Array Out-of-Range Access Error");
			}
			return content[index];
		}
		const X& operator[] (const uint index) const { return access(index); }
		X& access(const uint index){
			const Array<X>& ci = *this;
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

		fw::Array<X> member(const uint index, const uint size) const {
			fw::Array<X> r(address(index), size);
			return r;
		}
		fw::Array<X> member(const uint size) const {
			fw::Array<X> r(address(0), size);
			return r;
		}

		fw::Array<X> operator+ (const fw::Array<X>& another) const {
			fw::Array<X> r(*this);
			r += another;
			return r;
		}
		fw::Array<X> operator+ (const X& another) const {
			fw::Array<X> r(*this);
			r += another;
			return r;
		}

		uint size() const { return elem_size; }

		~Array(){
			for (uint i = 0; i < size(); ++i) access(i).~X();
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
			for (uint i = 0; i < oldsize; ++i){
				add_object(another[i]);
				another[i].~X();
			}
			free(another);
			space = size;
		}

		void add_object(){
			++elem_size;
			new(address(size() - 1)) X;
		}
		void add_object(const X& req){
			++elem_size;
			new(address(size() - 1)) X(req);
		}

		void construct(){
			content = nullptr;
			elem_size = 0;
			space = 0;
		}

	};

}