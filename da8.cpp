#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int main() {
	vector <int> v;
	int N;
	int a;
	int count1=0;
	int count2=0;
	int lim1;
	int lim2;
	int swap=0;
	cin >> N;
	for (int i=0; i<N; i++){
		cin >> a;
		if (a==1) count1++;
		else if(a==2) count2++;
		v.push_back(a);
	}

	lim1=count1;
	lim2=count1+count2;

	for (int i=0; i<lim1; i++) {
		if (v[i]==2) {
			for (int j=lim1; j<N; j++) {
				if (v[j]==1) {
					v[i]=1;
					v[j]=2;
					swap++;
					break;
				}
			}
		}
		else if (v[i]==3) {
			for (int j=N-1; j>=lim1; j--) {
				if (v[j]==1) {
					v[i]=1;
					v[j]=3;
					swap++;
					break;
				}
			}
		}
	}

	for (int i=lim1; i<lim2; i++) {
		if (v[i]==3) {
			for (int j=lim2; j<N; j++) {
				if (v[j]==2) {
					v[i]=2;
					v[j]=3;
					swap++;
					break;
				}
			}
		}
	}

	cout << swap << endl;
}
