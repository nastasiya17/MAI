#include <iostream>
#include <cstdio>
#include <vector>
#include <limits.h>

using namespace std;
const long INF=LONG_MAX;

int main() {
	int n, m, start, finish;
	cin >> n >> m >> start >> finish;
	vector<long> v(n+1, INF);
	vector <vector<long> > edges_list(m, vector<long> (3));
	v[start]=0;

	for (int i=0; i<m; i++) {
		cin >> edges_list[i][0] >> edges_list[i][1] >> edges_list[i][2];
	}

	for (int k=1; k<n; k++){
		bool move=false;
		for (int i=0; i<m; i++) {
			int st=edges_list[i][0];
			int fin=edges_list[i][1];
			int wei=edges_list[i][2];
			if (v[st]<INF)
				if (v[st] + wei < v[fin]) {
					v[fin]=v[st] + wei;
					move=true;
				}
		}
		if (!move)
			break;
	}

	if (v[finish]!=INF)
		cout << v[finish] << endl;
	else 
		cout << "No solution" << endl;
}
