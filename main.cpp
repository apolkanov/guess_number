#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int next_number(const vector<pair<int, int> >& l, int fraud_number, int attempt) {
	int sum = 0;
	int m = 0;
	int i = 0;
	vector<pair<int, int> >::const_iterator it = l.begin();
	for (; it != l.end(); ++it) {
		if (it->second <= fraud_number) {	
		  int w = fraud_number - it->second + 1; 
		  sum += w;
		  m += w * i;		  
		}
		++i;		
	}
	if (0 == sum)
		return l.size() / 2;
	return m / sum;
}

void apply_answer(vector<pair<int, int> >& l, int number, bool answer) {	
	for(int i = 0; i < l.size(); ++i) {
		if ((i <= number && answer) || (i >= number && !answer))
			l[i].second++;
	    else
			l[i].first++;
	}
}

int answer_found(vector<pair<int, int> >& l, int number) {
	int answer = -1;
	int count = 0;
	for(int i = 0; i < l.size(); ++i) {
		if (l[i].second > number)
			count++;
		else
			answer = i;
	}
	if (count == l.size() - 1)
		return answer;
	return -1;
}

int main() {
	int N = 0; // number of digits
	int fraud_count = 0;
	cout << "Enter digit count:" << endl;
	cin >> N;
	cout << "Enter fraud count:" << endl;
	cin >> fraud_count;

	vector<pair<int, int> > l;
	l.resize(N);

	int answer = -1;
	int attempt = 0;
	while((answer = answer_found(l, fraud_count)) == -1) {
		attempt++;
		bool answer = 0;
		int number = next_number(l, fraud_count, attempt);
		cout << "Greater than " << number << "?" << std::endl;
		cin >> answer;
		apply_answer(l, number, answer);
	}
	cout << std::endl << "Answer is: " << answer << std::endl;
	cout << "Attempts: " << attempt << std::endl;
	system("pause");
}