#include <iostream>
#define _USE_MATH_DEFINES 
#include <cmath>
#include <vector>

using namespace std;

double f(double x) {
	return cos(x)+x;
}

void lag(vector <double> x, vector <int> k, double X) {
	double w,L,P,f_i;
	L=0;
	cout << "L_3(x)=";
	for (int i=0; i<x.size(); i++) {
		w=1;
		for (int j=0; j<x.size(); j++) {
			if (i==j)
				continue;
			w=w*(x[i]-x[j]);
		}
		f_i=f(x[i]);

		if ((i!=0)&&(f_i/w>0))
			cout << "+";
		cout << f_i/w;

		P=f_i/w;
		for (int j=0; j<x.size(); j++) {
			if (i==j)
				continue;

			if (j!=0)
				cout << "(x-П/" << k[j] << ")";
			else 
				cout << "x";

			P=P*(X-x[j]);
		}
		L=L+P;
	}
	cout << endl;
	cout << "L_3(" << X << ")=" << L << endl;
	cout << "cos(" << X << ")+" << X << "=" << f(X) << endl;
	cout << "delta=" << abs(f(X)-L) << endl;
}

void newt(vector <double> x, vector <int> k, double X) {
	int N = x.size();
	vector <vector <double>> mat (N, vector <double> (N,0));
	int i, j, m;
	double P, S;

	for (i=0; i<N; i++) {
		mat[i][i]=f(x[i]);
	}

	i=0;
	j=1;
	m=1;

	while (j<N) {
		while (j<N) {
			mat[i][j]=(mat[i+1][j]-mat[i][j-1])/(x[j]-x[i]);
			i++;
			j=i+m;
		}
		m++;
		i=0;
		j=m;
	}

	cout << "P_3(x)=";
	P=0;

	for (i=0; i<N; i++) {		
		if ((mat[0][i]>0)&&(i!=0))
			cout << "+";
		cout << mat[0][i] << "x";
		S=mat[0][i]*X;

		for (j=1; j<i; j++) {
			cout << "(x-П/" << k[j] << ")";
			S=S*(X-x[j]);
		}
		P=P+S;
	}

	cout << endl;
	cout << "P_3(" << X << ")=" << P << endl;
	cout << "cos(" << X << ")+" << X << "=" << f(X) << endl;
	cout << "delta=" << abs(f(X)-P) << endl;
}

int main() {
	vector <double> x1 = {0, M_PI/6, M_PI/3, M_PI/2};
	vector <int> k1 = {0, 6, 3, 2};
	vector <double> x2 = {0, M_PI/6, M_PI/4, M_PI/2};
	vector <int> k2 = {0, 6, 4, 2};
	double X=1;

	cout << "LAGRANGE:\na)\n";
	lag(x1,k1,X);
	cout << "\nb)\n";
	lag(x2,k2,X);

	cout << "\nNEWTON:\na)\n";
	newt(x1, k1, X);
	cout << "\nb)\n";
	newt(x2, k2, X);
}