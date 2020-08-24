#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double f(double x) {
	return pow(x,2)/(pow(x,3)-27);
}

double rectangle(double X0, double Xk, double h) {
	int N=(Xk-X0)/h;
	double S=0;
	double temp;
	for (int i=0; i<N; i++) {
		temp=X0+i*h;
		S+=f((2*temp+h)/2);
	}
	return h*S;
}

double trapeze(double X0, double Xk, double h) {
	int N=(Xk-X0)/h;
	double S=f(X0)/2;
	double temp;
	for (int i=1; i<N; i++) {
		temp=X0+i*h;
		S+=f(temp);
	}
	S+=f(temp+h)/2;
	return h*S;
}

double simpson(double X0, double Xk, double h) {
	int N=(Xk-X0)/h;
	double S=f(X0);
	double temp;
	for (int i=1; i<N; i++) {
		temp=X0+i*h;
		S+=2*f(temp)*(i%2+1);
	}
	S+=f(temp+h);
	return h*S/3;
}

double rectangle_RRR(double X0, double Xk, double h1, double h2) {
	double F_h=rectangle(X0, Xk, h1);
	double F_hk=rectangle(X0, Xk, h2);
	double k=h2/h1;
	int p=2;
	return F_h + (F_h-F_hk)/(pow(k,p)-1);
}

double trapeze_RRR(double X0, double Xk, double h1, double h2) {
	double F_h=trapeze(X0, Xk, h1);
	double F_hk=trapeze(X0, Xk, h2);
	double k=h2/h1;
	int p=2;
	return F_h + (F_h-F_hk)/(pow(k,p)-1);
}

double simpson_RRR(double X0, double Xk, double h1, double h2) {
	double F_h=simpson(X0, Xk, h1);
	double F_hk=simpson(X0, Xk, h2);
	double k=h2/h1;
	int p=2;
	return F_h + (F_h-F_hk)/(pow(k,p)-1);
}

int main() {

	double h1=1;
	double h2=0.5;
	double X0=-2;
	double Xk=2;
	double sol=-0.203636;

	cout << "h=" << h1 << endl;
	cout << "rectangle\ttrapeze\t\tsimpson\n";
	cout << rectangle(X0, Xk, h1) << "\t" << trapeze(X0, Xk, h1) << "\t" << simpson(X0, Xk, h1) << endl; 

	cout << endl;

	cout << "h=" << h2 << endl;
	cout << "rectangle\ttrapeze\t\tsimpson\n";
	cout << rectangle(X0, Xk, h2) << "\t" << trapeze(X0, Xk, h2) << "\t" << simpson(X0, Xk, h2) << endl; 

	cout << endl;

	cout << "exact solution=" << sol << endl;

	cout << endl;

	cout << "method R-R-R\n";
	cout << "rectangle\ttrapeze\t\tsimpson\n";
	cout << rectangle_RRR(X0, Xk, h1, h2) << "\t"<< trapeze_RRR(X0, Xk, h1, h2) << "\t" << simpson_RRR(X0, Xk, h1, h2) << endl; 

	cout << endl;

	cout << "error\n"; 
	cout << "rectangle\ttrapeze\t\tsimpson\n";
	cout << abs(sol-rectangle_RRR(X0, Xk, h1, h2)) << "\t" << abs(sol-trapeze_RRR(X0, Xk, h1, h2)) << "\t" << abs(sol-simpson_RRR(X0, Xk, h1, h2)) << endl; 
}