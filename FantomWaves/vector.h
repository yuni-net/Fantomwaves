#pragma once

#include "trade.h"

namespace fw
{

	template<typename X>
	class vector;

	template<typename X>
	class vecmemdata
	{
		fw::vector<X> myvec;
		const fw::vector<X> & wvec;
		fw::vector<X> & rvec;
		bool rflag;
		uint mybeg;
		uint mynum;

	public:

		vecmemdata(const fw::vector<X> & target, uint num) :wvec(target), rvec(myvec) {
			mybeg = 0;
			mynum = num;
			rflag = false;
		}
		vecmemdata(const fw::vector<X> & target, uint beg, uint num) :wvec(target), rvec(myvec) {
			mybeg = beg;
			mynum = num;
			rflag = false;
		}
		vecmemdata(fw::vector<X> & target, uint num) :rvec(target) : wvec(target), rvec(target) {
			mybeg = 0;
			mynum = num;
			rflag = true;
		}
		vecmemdata(fw::vector<X> & target, uint beg, uint num) :wvec(target), rvec(target) {
			mybeg = beg;
			mynum = num;
			rflag = true;
		}

		const fw::vector<X> & cvec() const {
			if (rflag) return rvec;
			return wvec;
		}
		fw::vector<X> & vec() const { return rvec; }

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
	class vector
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

		fw::vector<X>& init(){
			zeroqure();
			return *this;
		}
		vector(){ Init(); }
		fw::vector<X>& init(const fw::vector<X>& req){
			zerosize();
			add(req);
			return *this;
		}
		vector(const fw::vector<X>& req){
			Init();
			init(req);
		}
		fw::vector<X>& operator= (const fw::vector<X>& req){ return init(req); }
		fw::vector<X>& init(const X& req){
			zerosize();
			add(req);
			return *this;
		}
		vector(const X& req){
			Init();
			init(req);
		}
		fw::vector<X>& operator= (const X& req){ return init(req); }
		fw::vector<X>& init(const X* arr, const uint size){
			zerosize();
			add(arr, size);
			return *this;
		}
		vector(const X* arr, const uint size){
			Init();
			init(arr, size);
		}

		fw::vector<X>& secure(const uint size){
			if (size != space) ReSecure(size);
			return *this;
		}
		fw::vector<X>& requre(const uint size){
			if (size > space) ReSecure(size);
			return *this;
		}
		fw::vector<X>& addcure(const uint size){
			ReSecure(this->size() + size);
			return *this;
		}
		fw::vector<X>& popcure(const uint size){
			uint popsize = this->size();
			if (size < this->size()) popsize = size;
			secure(popsize);
			return *this;
		}
		fw::vector<X>& zerocure(){
			secure(0);
			return *this;
		}

		fw::vector<X>& setsize(const uint size){
			int gap = size - this->size();
			if (gap > 0) addsize(gap);
			if (gap < 0) popsize(-gap);
			return *this;
		}

		fw::vector<X>& reqsize(const uint size){
			if (size > this->size()) addsize(size - this->size());
			return *this;
		}

		fw::vector<X>& addsize(const uint size = 1){
			uint needsize = this->size() + size;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				ReSecure(needsize * 2);
			}
			for (uint i = 0; i<size; ++i) AddObject();
			return *this;
		}
		fw::vector<X>& addsize(const uint size, const X& req){
			uint needsize = this->size() + size;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				ReSecure(needsize * 2);
			}
			for (uint i = 0; i < size; ++i) AddObject(req);
			return *this;
		}
		fw::vector<X>& operator++ (){ return addsize(); }
		fw::vector<X> operator++ (int){
			fw::vector<X> old(*this);
			addsize();
			return old;
		}

		fw::vector<X>& popsize(const uint size = 1){
			uint gap = size;
			if (size > this->size()) gap = this->size();
			for (uint i = 0; i < gap; ++i)
			{
				last().~X();
				--Size;
			}
			return *this;
		}
		fw::vector<X>& operator-- (){ return popsize(); }
		fw::vector<X> operator-- (int){
			fw::vector<X> old(*this);
			popsize();
			return old;
		}

		fw::vector<X>& zerosize(){
			setsize(0);
			return *this;
		}

		fw::vector<X>& add(){
			uint needsize = size() + 1;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				ReSecure(needsize * 2);
			}
			AddObject();
			return *this;
		}
		fw::vector<X>& add(const X& req){
			uint needsize = size() + 1;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				ReSecure(needsize * 2);
			}
			AddObject(req);
			return *this;
		}
		fw::vector<X> & operator+= (const X& input){
			add(input);
			return *this;
		}
		fw::vector<X> & operator<< (const X& input){
			add(input);
			return *this;
		}
		fw::vector<X>& add(const X& req, const uint num){
			uint needsize = size() + num;
			if (needsize > space){
				if (needsize < 128) needsize = 128;
				ReSecure(needsize * 2);
			}
			for (uint i = 0; i < num; ++i) AddObject(req);
			return *this;
		}
		fw::vector<X> & add(const fw::vector<X>& input){
			requre(input.size());
			for (uint i = 0; i < input.size(); ++i) add(input[i]);
			return *this;
		}
		fw::vector<X> & operator+= (const fw::vector<X>& input){
			add(input);
			return *this;
		}
		fw::vector<X> & operator<< (const fw::vector<X>& input){
			add(input);
			return *this;
		}
		fw::vector<X>& add(const X* arr, const uint size){
			requre(size);
			for (uint i = 0; i < size; ++i) add(arr[i]);
			return *this;
		}

		fw::vector<X>& pop(const uint size = 1){ return popsize(size); }

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
			const vector<X>& ci = *this;
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

		fw::vector<X> member(const uint index, const uint size) const {
			fw::vector<X> r(address(index), size);
			return r;
		}
		fw::vector<X> member(const uint size) const {
			fw::vector<X> r(address(0), size);
			return r;
		}

		fw::vector<X> operator+ (const fw::vector<X>& another) const {
			fw::vector<X> r(*this);
			r += another;
			return r;
		}
		fw::vector<X> operator+ (const X& another) const {
			fw::vector<X> r(*this);
			r += another;
			return r;
		}

		uint size() const { return Size; }

		~vector(){
			for (uint i = 0; i < size(); ++i) access(i).~X();
			free(content);
		}
	};

}