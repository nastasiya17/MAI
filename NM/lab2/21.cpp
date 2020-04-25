#include <iostream>
#include <cmath>

using namespace std;

const double eps=0.0001;

int main() {
	double x1, x2, q, t1, t2, e, g1, g2, x1_n, x2_n;
	double d_phi1_x1, d_phi1_x2, d_phi2_x1, d_phi2_x2;
	int it=0;
	x1=0.4;
	x2=1;
	g1=0.6;
	g2=1.2;
	d_phi1_x1=(g1/pow(4-pow(g1,2),0.5)-1)/(pow(4-pow(g1,2),0.5)-g1);
	d_phi1_x2=0;
	d_phi2_x1=1/4*g1/pow(1-pow(g1,2)/4,0.5);
	d_phi2_x2=0;
	t1=abs(d_phi1_x1)+abs(d_phi1_x2);
	t2=abs(d_phi2_x1)+abs(d_phi2_x2);
	q=max(t1,t2);
	e=q/(1-q)*max(x1,x2);
	while (e>eps) {
		it++;
		x1_n=log(pow(4-pow(x1,2),0.5)-x1);
		x2_n=pow(1-pow(x1,2)/4,0.5);
		e=q/(1-q)*max(abs(x1_n-x1), abs(x2_n-x2));
		x1=x1_n;
		x2=x2_n;
	}
	cout << "Iterations " << it << endl;
	cout << "x1=" << x1 << endl;
	cout << "x2=" << x2 << endl;
	cout << "eps=" << e << endl;
}
