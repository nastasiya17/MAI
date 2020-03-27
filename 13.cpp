#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double eps=0.0001;

int main() {
	int N, it;
	double max, S, maxA, max1;
	cin >> N;
	vector <vector <double>> A (N, vector <double>(N,0));
	vector <vector <double>> A1 (N, vector <double>(N,0));
	vector <double> b (N);
	vector <double> x (N,0);
	vector <double> y (N,0);
	vector <double> e (N,0);

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> A[i][j];
		}
		cin >> b[i];
	}

	A1=A;

	//создание матрицы альфа

	for (int i=0; i<N; i++) {
		if (A1[i][i]!=0) {
			b[i]/=A1[i][i];
			for (int j=0; j<N; j++) {
				if (i!=j)
					A1[i][j]/=A1[i][i];
			}
			A1[i][i]=0;
		}
	}	

	//норма матрицы альфа

	maxA=0;
	for (int i=0; i<N; i++) {
		S=0;
		for (int j=0; j<N; j++) {
			S+=abs(A1[i][j]);
		}

		if (S>maxA) {
			maxA=S;
		}
	}

	cout << maxA << endl;

	it=1;

	cout << endl;

	while ((max>eps)||(it==1)) {
		cout << "-----------------------------------\n";
		cout << it << "\n-----------------------------------\nx=( ";
		for (int j=0; j<N; j++) {
			x[j]=b[j];
			for (int k=0; k<N; k++) {
				x[j]-=A1[j][k]*y[k];
			}
		}

		max=0;
		for (int j=0; j<N; j++) {
			e[j]=abs(x[j]-y[j]);
			if (e[j]>max)
				max=e[j];
			max1=max*maxA/(1-maxA);
			y[j]=x[j];
			cout << x[j] << " ";
		}
		cout << ")\n" << "eps=" << max1 << endl;
		it++;
	} 

	cout << endl;
}