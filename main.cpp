#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>

using namespace std;
typedef long long int64;
typedef vector<pair<double, int64> > Digits;

class Guesser {

public:
  Guesser(int64 N, int64 fraud) : mN(N), mFraud(fraud), mAttempt(0), MULT(4) {
    mL.resize(mN);
	for (size_t i = 0; i < mL.size(); ++i) {
		mL[i].first = 1;
	}
  }

  int64 Next() {
    return next_number1(mL, mFraud);
  }

  void Answer(int64 num, bool answer) {
    apply_answer(mL, num, answer);
    mAttempt++;
    std::cout << mAttempt << std::endl;
  }

  int64 Guess() {
    return answer_found(mL, mFraud);
  }

  int64 GetAttempt() { return mAttempt; }

private:

int64 next_number1(Digits& l, int64 fraud_number) {
 double sumLeft = 0, sumRight = 0;
 double m = 0;
 int64 i = 0;
 
 int64 left = 0;
 int64 right = l.size() - 1;
 while(left < right) {
	 
	 while(sumLeft <= sumRight && left < right) {
		sumLeft += l[left++].first;
	 }
	 if (left < right)
		 sumRight += l[right--].first;
 }
 int64 res = right > l.size() / 2 + 1 ? right  : right - 1;
 return res;
}

void apply_answer(Digits& l, int64 number, bool answer) {	
	for(int64 i = 0; i < l.size(); ++i) {
		if (l[i].second > mFraud) {
			l[i].first = 0;
			continue;
		}
		if ((i <= number && answer) || (i > number && !answer)) {
			l[i].second++;
			l[i].first /= MULT;
		}
	    //else
		//	l[i].first *= MULT;
	}
}

int64 answer_found(Digits& l, int64 number) {
	int64 answer = -1;
	int64 count = 0;
	for(int64 i = 0; i < l.size(); ++i) {
		if (l[i].second > number)
			count++;
		else
			answer = i;
	}
	if (count == l.size() - 1)
		return answer;
	return -1;
}

private:
  int64 mN;
  int64 mFraud;
  Digits mL;
  int64 mAttempt;
  const double MULT;
};


void check() {

  Guesser g(1000000, 100);
  int64 digit = 453456;
  int lie = 0;
  while(g.Guess() == -1) {
    int64 number = g.Next();
	cout << " " << number << " ";
	bool answer = digit > number;
    if (lie < 100) {
  		bool answer2 = 100000 > number;
        if (answer2 != answer) {
          answer = !answer;
          lie++;
		  cout << "lie: " << lie << endl;
       }
    }
    g.Answer(number, answer);
	}
  cout << std::endl << "Answer is: " << g.Guess() << std::endl;
  cout << "Attempts: " << g.GetAttempt() << std::endl;
}


int main() {
  srand(time(0));
  check();
  system("pause");
  return 0;
}