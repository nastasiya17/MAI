#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main() {

	double X=0.8;
	int border=2;
	double y_pl, y_pr, y_p, y_pp;

	vector <double> x = {0.2, 0.5, 0.8, 1.1, 1.4};
	vector <double> y = {12.906, 5.5273, 3.8777, 3.2692, 3.0319};
	y_pl=(y[border]-y[border-1])/(x[border]-x[border-1]);
	y_pr=(y[border+1]-y[border])/(x[border+1]-x[border]);
	y_p=y_pl+(y_pr-y_pl)/(x[border+1]-x[border-1])*(2*X-x[border]-x[border-1]);
	y_pp=2*(y_pr-y_pl)/(x[border+1]-x[border-1]);
	cout << "Left-side y'("  << X << ")=" << y_pl << endl;
	cout << "Right-side y'(" << X << ")=" << y_pr << endl;
	cout << "y'(" << X << ")=" << y_p << endl;
	cout << "y''(" << X << ")=" << y_pp << endl;
}