#include <iostream>
#include <cstdio>
#include <cstring>

const int MAX = 100;
using namespace std;

int main() {
	char s[MAX];
	cin >> s;
	int n = strlen(s);
	long matrix[MAX][MAX];

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			if (i==j) matrix[i][j]=1;
			else matrix[i][j]=0;
		}
	}

	for (int i=0; i<n; i++) {
		for (int j=i-1; j>=0; j--) {
			if (s[i]==s[j])
				matrix[i][j]=matrix[i-1][j]+matrix[i][j+1]+1;
			else
				matrix[i][j]=matrix[i-1][j]+matrix[i][j+1]-matrix[i-1][j+1];
		}
	} 

	cout << matrix[n-1][0] << endl;
}
