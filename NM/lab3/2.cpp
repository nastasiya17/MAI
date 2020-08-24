#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {
	vector <double> x = {0, 1, 2, 3, 4};
	vector <double> f = {1, 1.5403, 1.5839, 2.01, 3.3464};
	int N=4;
	vector <double> h (N+1,0);
	vector <vector <double >> c (N-1, vector <double> (N-1,0));
	vector <vector <double>> L (N-1, vector <double> (N-1,0));
	vector <vector <double>> U (N-1, vector <double> (N-1,0));
	vector <double> b (N-1,0);
	vector <double> C (N+1,0);
	vector <double> y (N-1,0);
	double X = 1.5;
	vector <double> A (N+1,0);
	vector <double> B (N+1,0);
	vector <double> D (N+1,0);

	for (int i=1; i<N+1; i++) {
		h[i]=x[i]-x[i-1];
	}

	c[0][0]=2*(h[1]+h[2]);
	c[0][1]=h[2];

	c[1][0]=h[2];
	c[1][1]=2*(h[2]+h[3]);
	c[1][2]=h[4];

	c[2][1]=h[3];
	c[2][2]=2*(h[3]+h[4]);

	b[0]=3*((f[2]-f[1])/h[2]-(f[1]-f[0])/h[1]);
	b[1]=3*((f[3]-f[2])/h[3]-(f[2]-f[1])/h[2]);
	b[2]=3*((f[4]-f[3])/h[4]-(f[3]-f[2])/h[3]);

	int K=N-1;

	U=c;

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
				S+=L[i][j]*y[j];
		}
		y[i]=b[i]-S;
	}

	for (int i=K-1; i>=0; i--) {
		double S=0;
		for (int j=K-1; j>i; j--) {
				S+=U[i][j]*C[j];
		}
		C[i]=(y[i]-S)/U[i][i];
	}

	for (int i=K-1; i>=0; i--) {
		C[i+2]=C[i];
	}
	C[0]=0;
	C[1]=0;

	int r=ceil(X);

	for (int i=1; i<N+1; i++) {
		A[i]=f[i-1];
		if (i==N) {
			B[i]=(f[i]-f[i-1])/h[i]-2*h[i]*C[i]/3;
			D[i]=-C[i]/(3*h[i]);
		}
		else {
			B[i]=(f[i]-f[i-1])/h[i]-1*h[i]*(C[i+1]+2*C[i])/3;
			D[i]=(C[i+1]-C[i])/(3*h[i]);
		}
	}

	for (int i=1; i<N+1; i++) {
		cout << "f(x)=" << A[i];
		if (B[i]>=0) 
			cout << "+";
		cout << B[i] << "(x-" << x[i-1] << ")";
		if (C[i]>=0) 
			cout << "+";
		cout << C[i] << "(x-" << x[i-1] << ")^2";
		if (D[i]>=0) 
			cout << "+";
		cout << D[i] << "(x-" << x[i-1] << ")^3,  ";
		cout << x[i-1] << "<x<" << x[i] << "\n\n";
	}

	cout << "f(" << X << ")=" << A[r]+B[r]*(X-x[r-1])+C[r]*pow((X-x[r-1]),2)+D[r]*pow((X-x[r-1]),3) << endl;
}
