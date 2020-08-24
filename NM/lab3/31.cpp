#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {

	int K=2;
	int N=6;
	double S_x=0;
	double S_x2=0;
	double S_y=0;
	double S_xy=0;
	double Q=0;
	vector <double> x = {-1, 0, 1, 2, 3, 4};
	vector <double> y = {-0.4597, 1, 1.5403, 1.5839, 2.010, 3.3464};
	vector <double> f (N,0);
	vector <vector <double>> A (K, vector <double> (K,0));
	vector <vector <double>> L (K, vector <double> (K,0));
	vector <vector <double>> U (K, vector <double> (K,0));
	vector <double> b (K,0);
	vector <double> z (K,0);
	vector <double> a (K,0);


	for (int i=0; i<N; i++) {
		S_x+=x[i];
		S_x2+=pow(x[i],2);
		S_y+=y[i];
		S_xy+=x[i]*y[i];
	}

	A[0][0]=N;
	A[0][1]=S_x;
	A[1][0]=S_x;
	A[1][1]=S_x2;

	b[0]=S_y;
	b[1]=S_xy;

	U=A;

	for (int k=0; k<K-1; k++) {

		for (int i=k; i<K; i++) {
			for (int j=i; j<K; j++) {
				L[j][i]=U[j][i]/U[i][i];
			}
		}

		for (int i=k+1; i<K; i++) {
			for (int j=k; j<K; j++) {
				U[i][j]=U[i][j]-L[i][k]*U[k][j];
			}
		}
	}

	for (int i=0; i<K; i++) {
		double S=0;
		for (int j=0; j<i; j++) {
				S+=L[i][j]*z[j];
		}
		z[i]=b[i]-S;
	}

	for (int i=K-1; i>=0; i--) {
		double S=0;
		for (int j=K-1; j>i; j--) {
				S+=U[i][j]*a[j];
		}
		a[i]=(z[i]-S)/U[i][i];
	}

	for (int i=0; i<N; i++) {
		f[i]=a[0]+a[1]*x[i];
		Q+=pow(f[i]-y[i],2);
	}

	cout << "F_1(x)=" << a[0] << "+" << a[1] << "x\n\n";

	cout << "x\t";
	for (int i=0; i<N; i++) {
		cout << x[i] << "\t";
	}
	cout << endl;

	cout << "F_1(x)\t";
	for (int i=0; i<N; i++) {
		cout << f[i] << " ";
	}
	cout << endl << endl;

	cout << "Q=" << Q << endl;
}