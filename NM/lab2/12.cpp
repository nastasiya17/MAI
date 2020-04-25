#include <iostream>
#include <cmath>

using namespace std;

const double eps=0.0001;

int main() {
	double t2, f, f_pp, x, x1, e;
	int it=0;
	t2=0.5;
	f=log(t2+1)-2*t2+0.5;
	f_pp=-1/pow((t2+1),2);
	if (f*f_pp>0) {
		e=t2;
		x=t2;
		while (e>eps) {
			it++;
			x1=x-(log(x+1)-2*x+0.5)/(1/(x+1)-2);
			e=abs(x1-x);
			x=x1;
		}
		cout << "Iterations " << it << endl;
		cout << "x=" << x1 << endl;
	}
}
