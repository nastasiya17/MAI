#include <iostream>
#include <vector>
#include <limits.h>
#include <cmath>

using namespace std;

bool del(vector <int> v, int k) {
	int s, prev, i;
	s=0;
	prev=0;
	while (prev < v.size()) {
		for (i=prev; i<v.size(); i++) {
			s=s*10+v[i];
			if (s>=k)
				break;
		}
		prev=i+1;
		s=s%k;
	}

	if (s) return false;
	else return true;
}

bool simple(int k) {
	for (int i=2; i<=floor(sqrt(k)); i++) {
		if (k%i==0) 
			return false;
	}
	return true;
}

int max_N(vector <int> v) {
	if (v.size()<10) {
		int R=0;
		for (int k=0; k<v.size(); k++) {
			R=R*10+v[k];
		}
		return floor(sqrt(R));
	}
	return INT_MAX;
}

int main() {
	vector <int> v = {1,2,3,2,4,8,2,6,8,9,1,1,9,3,7,9,2,3,1,9,9,9,0,6,1,4,1,2,1,6,6,4,5,3,6,3,6,6,5,0,8,7,0,4,5,4,2,2,6,8,9,3,5,8,1,0,4,0,8,9,1,8,5,3,1,6,1,4,8,9,1,1,4,9,6,1,0,3};
	vector <int> res;
	vector <int> answer;
	int j;

	for (j=2; j<=max_N(v); j++) {
		if ((del(v,j))&&(simple(j))) {
			answer.push_back(j);
			int s, prev, i;
			s=0;
			prev=0;
			while (prev < v.size()) {
				for (i=prev; i<v.size(); i++) {
					s=s*10+v[i];
					if (s>=j)
						break;

					if (i)
						res.push_back(0);
				}
				prev=i+1;
				res.push_back(s/j);
				s=s%j;
			}

			v=res;
			res.assign(0,0);
			j--;
		}
	}

	int R=0;
	for (int i=0; i<v.size(); i++) {
		R=R*10+v[i];
	}
	answer.push_back(R);

	for (int i=0; i<answer.size(); i++) {
		cout << answer[i] << "\t";
	}
	cout << endl;

}
