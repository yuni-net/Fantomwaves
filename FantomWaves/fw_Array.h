#pragma once

#include "fw_trade.h"

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





	// constructfull

	template<typename X>
	class Array
	{
		X * content;
		uint Size;
		uint space;

		void ReSecure(uint size){
			X* another = static_cast<X*>(malloc(sizeof(X) *size));
			::fw::trade(content, another);
			uint oldsize = this->size();
			Size = 0;
			for (uint i = 0; i < oldsize; ++i){
				AddObject(another[i]);
				another[i].~X();
			}
			free(another);
			space = size;
		}

		void AddObject(){
			++Size;
			new(address(size() - 1)) X;
		}
		void AddObject(const X& req){
			++Size;
			new(address(size() - 1)) X(req);
		}

		void Init(){
			content = NULL;
			Size = 0;
			space = 0;
		}

	public:

		fw::Array<X>& init(){
			zeroqure();
			return *this;
		}
		Array(){ Init(); }
		fw::Array<X>& init(const fw::Array<X>& req){
			zerosize();
			add(req);
			return *this;
		}
		Array(const fw::Array<X>& req){
			Init();
			init(req);
		}
		fw::Array<X>& operator= (const fw::Array<X>& req){ return init(req); }
		fw::Array<X>& init(const X& req){
			zerosize();
			add(req);
			return *this;
		}
		Array(const X& req){
			Init();
			init(req);
		}
		fw::Array<X>& operator= (const X& req){ return init(req); }
		fw::Array<X>& init(const X* arr, const uint size){
			zerosize();
			add(arr, size);
			return *this;
		}
		Array(const X* arr, const uint size){
			Init();
			init(arr, size);
		}

		fw::Array<X>& secure(const uint size){
			if (size != space) ReSecure(size);
			return *this;
		}
		fw::Array<X>& requre(const uint size){
			if (size > space) ReSecure(size);
			return *this;
		}
		fw::Array<X>& addcure(const uint size){
			ReSecure(this->size() + size);
			return *this;
		}
		fw::Array<X>& popcure(const uint size){
			uint popsize = this->size();
			if (size < this->size()) popsize = size;
			secure(popsize);
			return *this;
		}
		fw::Array<X>& zerocure(){
			secure(0);
			return *this;
		}

		fw::Array<X>& setsize(const uint size){
			int gap = size - this->size();
			if (gap > 0) addsize(gap);
			if (gap < 0) popsize(-gap);
			return *this;
		}

		fw::Array<X>& reqsize(const uint size){
			if (size > this->size()) addsize(size - this->size());
			return *this;
		}

		fw::Array<X>& addsize(const uint size = 1){
			uint needsize = this->size() + size;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				ReSecure(needsize * 2);
			}
			for (uint i = 0; i<size; ++i) AddObject();
			return *this;
		}
		fw::Array<X>& addsize(const uint size, const X& req){
			uint needsize = this->size() + size;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				ReSecure(needsize * 2);
			}
			for (uint i = 0; i < size; ++i) AddObject(req);
			return *this;
		}
		fw::Array<X>& operator++ (){ return addsize(); }
		fw::Array<X> operator++ (int){
			fw::Array<X> old(*this);
			addsize();
			return old;
		}

		fw::Array<X>& popsize(const uint size = 1){
			uint gap = size;
			if (size > this->size()) gap = this->size();
			for (uint i = 0; i < gap; ++i)
			{
				last().~X();
				--Size;
			}
			return *this;
		}
		fw::Array<X>& operator-- (){ return popsize(); }
		fw::Array<X> operator-- (int){
			fw::Array<X> old(*this);
			popsize();
			return old;
		}

		fw::Array<X>& zerosize(){
			setsize(0);
			return *this;
		}

		fw::Array<X>& add(){
			uint needsize = size() + 1;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				ReSecure(needsize * 2);
			}
			AddObject();
			return *this;
		}
		fw::Array<X>& add(const X& req){
			uint needsize = size() + 1;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				ReSecure(needsize * 2);
			}
			AddObject(req);
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
				ReSecure(needsize * 2);
			}
			for (uint i = 0; i < num; ++i) AddObject(req);
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
#ifdef FW_VECTOR_POP_UP_
				MessageBox(NULL, "範囲外アクセスが発生しました", "エラー", MB_OK);
#endif
				throw std::out_of_range("範囲外アクセスエラー");
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
			if (size() == 0) return NULL;
			return address(0);
		}
		X* head(){
			if (size() == 0) return NULL;
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

		uint size() const { return Size; }

		~Array(){
			for (uint i = 0; i < size(); ++i) access(i).~X();
			free(content);
		}
	};

}