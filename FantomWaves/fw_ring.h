#pragma once

namespace fw
{
	/***
	�z������舵���^�ł��B
	*/
	class Ring
	{
		int count;
		int beg;
		int end;

	public:

		Ring & subs(int num){
			int equally = num - beg;
			int minenum = equally%(end - beg + 1);
			int plusnum = minenum + (end - beg + 1);
			int minplnum = plusnum%(end - beg + 1);
			count = minplnum + beg;

			return *this;
		}
		Ring & operator= (int num){ return subs(num); }

		operator int () const { return num(); }
		operator const int* () const { return &count; }
		operator const int& () const { return count; }

		Ring & set(int beg, int end){
			int oldcount = count;
			this->beg = beg;
			this->end = end;
			subs(oldcount);
			return *this;
		}
		Ring & set(int end){ return set(0, end); }

		Ring & init(){
			count = beg;
			return *this;
		}
		Ring & init(int beg, int end){
			set(beg, end);
			return init();
		}
		Ring & init(int end){ return init(0, end); }

		Ring(){}
		Ring(int end){ init(end); }
		Ring(int beg, int end){ init(beg, end); }


		Ring & operator+= (int num){
			subs(count + num);
			return *this;
		}

		Ring & operator-= (int num){
			*this += -num;
			return *this;
		}

		//�O�u���C���N�������g
		Ring & operator++(){
			*this += 1;
			return *this;
		}
		//��u���C���N�������g
		Ring operator++(int){
			Ring answer = *this;
			*this += 1;
			return answer;
		}

		//�O�u���f�N�������g
		Ring & operator--(){
			*this -= 1;
			return *this;
		}
		//��u���f�N�������g
		Ring operator--(int){
			Ring answer = *this;
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