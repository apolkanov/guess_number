#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>

using namespace std;
typedef long long int64;

class Guesser {

public:
  Guesser(int64 N, int64 fraud) : mN(N), mFraud(fraud), mAttempt(0) {
    mL.resize(mN);
  }

  int64 Next() {
    return next_number(mL, mFraud);
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
int64 next_number(const vector<pair<int64, int64> >& l, int64 fraud_number) {
 double sum = 0;
 double m = 0;
 int64 i = 0;
 vector<pair<int64, int64> >::const_iterator it = l.begin();
 for (; it != l.end(); ++it) {
  if (it->second <= fraud_number) { 
    double w = pow(1.2, fraud_number - it->second + 1.0);
    sum += w;
    m += w * i;
  }
  ++i;  
 }
 if (0 == sum)
  return l.size() / 2;
 return m / sum;
}

void apply_answer(vector<pair<int64, int64> >& l, int64 number, bool answer) {	
	for(int64 i = 0; i < l.size(); ++i) {
		if ((i <= number && answer) || (i > number && !answer))
			l[i].second++;
	    else
			l[i].first++;
	}
}

int64 answer_found(vector<pair<int64, int64> >& l, int64 number) {
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
  vector<pair<int64, int64> > mL;
  int64 mAttempt;
};


void check() {

  Guesser g(1000000, 100);
  int64 digit = 50011;
  int i = 0;
  while(g.Guess() == -1) {
    i++;
    int64 number = g.Next();
		bool answer = digit > number;
    int lie = 0;
    //if (lie < 100) {
  		//bool answer2 = 100000 > number;
    //  if (answer2 != answer) {
    //    answer = !answer;
    //    lie++;
    //  }
    //}
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