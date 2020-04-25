#include <iostream>
#include <cmath>

using namespace std;

const double eps=0.0001;

int main() {
	double t1, t2, phi1, phi2, q, x, x1, e;
	int it=0;
	t1=0.35;
	t2=0.5;
	phi1=(log(t1+1)+0.5)/2;
	phi2=(log(t2+1)+0.5)/2;
	q=1/(2*(t1+1));
	if ((phi1>=t1) and (phi2<=t2) and (q<1)) {
		x=(t1+t2)/2;
		q=1/(2*(x+1));
		e=q/(1-q)*abs(x);
		while (e>eps) {
			it++;
			x1=(log(x+1)+0.5)/2;
			q=1/(2*(x1+1));
			e=q/(1-q)*abs(x1-x);
			x=x1;
		}
		cout << "Iterations " << it << endl;
		cout << "x=" << x1 << endl;
		cout << "eps=" << e << endl;
	}
}
