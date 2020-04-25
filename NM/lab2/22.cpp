#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double eps=0.0001;

double det (vector <vector <double>> A) {
	return A[0][0]*A[1][1] - A[0][1]*A[1][0];
}

int main() {
	double f1, f2, x1, x2, e, x1_n, x2_n;
	double d_f1_x1, d_f1_x2, d_f2_x1, d_f2_x2;
	vector <vector <double>> A1 (2, vector <double> (2,0));
	vector <vector <double>> A2 (2, vector <double> (2,0));
	vector <vector <double>> J (2, vector <double> (2,0));
	int it=0;
	x1=0.4;
	x2=1;
	e=max(x1,x2);
	while (e>eps) {
		it++;
		f1=pow(x1,2)/4+pow(x2,2)-1;
		f2=2*x2-exp(x1)-x1;
		d_f1_x1=x1/2;
		d_f1_x2=2*x2;
		d_f2_x1=-exp(x1)-1;
		d_f2_x2=2;

		A1[0][0]=f1;
		A1[1][0]=f2;
		A1[0][1]=d_f1_x2;
		A1[1][1]=d_f2_x2;

		A2[0][0]=d_f1_x1;
		A2[1][0]=d_f2_x1;
		A2[0][1]=f1;
		A2[1][1]=f2;

		J[0][0]=d_f1_x1;
		J[0][1]=d_f1_x2;
		J[1][0]=d_f2_x1;
		J[1][1]=d_f2_x2;

		x1_n=x1-det(A1)/det(J);
		x2_n=x2-det(A2)/det(J);
		e=max(abs(x1_n-x1), abs(x2_n-x2));
		x1=x1_n;
		x2=x2_n;
	}
	cout << "Iterations " << it << endl;
	cout << "x1=" << x1 << endl;
	cout << "x2=" << x2 << endl;
}
