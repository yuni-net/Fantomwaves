#pragma once

namespace fw
{

	class ring
	{
		int count;
		int beg;
		int end;

	public:

		ring & subs(int num){
			int equally = num - beg;
			int minenum = equally%(end - beg + 1);
			int plusnum = minenum + (end - beg + 1);
			int minplnum = plusnum%(end - beg + 1);
			count = minplnum + beg;

			return *this;
		}
		ring & operator= (int num){ return subs(num); }

		operator int () const { return num(); }
		operator const int* () const { return &count; }
		operator const int& () const { return count; }

		ring & set(int beg, int end){
			int oldcount = count;
			this->beg = beg;
			this->end = end;
			subs(oldcount);
			return *this;
		}
		ring & set(int end){ return set(0, end); }

		ring & init(){
			count = beg;
			return *this;
		}
		ring & init(int beg, int end){
			set(beg, end);
			return init();
		}
		ring & init(int end){ return init(0, end); }

		ring(){}
		ring(int end){ init(end); }
		ring(int beg, int end){ init(beg, end); }


		ring & operator+= (int num){
			subs(count + num);
			return *this;
		}

		ring & operator-= (int num){
			*this += -num;
			return *this;
		}

		//前置きインクリメント
		ring & operator++(){
			*this += 1;
			return *this;
		}
		//後置きインクリメント
		ring operator++(int){
			ring answer = *this;
			*this += 1;
			return answer;
		}

		//前置きデクリメント
		ring & operator--(){
			*this -= 1;
			return *this;
		}
		//後置きデクリメント
		ring operator--(int){
			ring answer = *this;
			*this -= 1;
			return answer;
		}

		int num() const { return count; }

		int operator+ (int num) const { return this->num() + num; }
		int operator- (int num) const { return this->num() - num; }
		int operator* (int num) const { return this->num() * num; }
		int operator/ (int num) const { return this->num() / num; }
		int operator% (int num) const { return this->num() % num; }

		bool operator== (int num) const { return this->num() == num; }
		bool operator!= (int num) const { return this->num() != num; }
		bool operator<= (int num) const { return this->num() <= num; }
		bool operator>= (int num) const { return this->num() >= num; }
		bool operator< (int num) const { return this->num()<num; }
		bool operator> (int num) const { return this->num()>num; }
	};

}