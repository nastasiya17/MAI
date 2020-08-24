#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double sol(double x) {
//	return pow(cos(x),3)+sin(x)*(1+2*pow(cos(x),2));
	return exp(-pow(2,0.5)*x)*((2+3*pow(2,0.5))*exp(2*x*pow(2,0.5)) +2-3*pow(2,0.5))/(4*cos(x));
}

double f_z(double x, double y, double z) {
	return 2*tan(x)*z+3*y;
}

void eiler(double x, double y, double z, double b, double h) {
	double h2=h/2;
	double x2=x;
	double y2=y;
	double z2=z;
	double R, del_y, del_z, del_y2, del_z2, eps;
	int n=(b-x)/h;
	cout << "EILER\n";
	cout << "x\ty\ty_t\teps\tR\n";
	cout << "---------------------------------\n";
	for (int i=0; i<n; i++) {
		del_y=h*z;
		del_z=h*f_z(x,y,z);
		y+=del_y;
		z+=del_z;
		x+=h;

		del_y2=h2*z2;
		del_z2=h2*f_z(x2,y2,z2);
		y2+=del_y2;
		z2+=del_z2;
		x2+=h2;

		del_y2=h2*z2;
		del_z2=h2*f_z(x2,y2,z2);
		y2+=del_y2;
		z2+=del_z2;
		x2+=h2;

		eps=abs(y-sol(x));	
		R=(y-y2)/(0.5-1);
		cout << x << " | " << y << " | " <<  sol(x) << " | " << eps << " | " << R << "\n\n";
	}
}

void runge_cutta(double x, double y, double z, double b, double h) {
	double K1_y, K2_y, K3_y, K4_y, K1_z, K2_z, K3_z, K4_z, del_y, del_z;
	double K1_y2, K2_y2, K3_y2, K4_y2, K1_z2, K2_z2, K3_z2, K4_z2, del_y2, del_z2;
	double eps, R;
	int n=(b-x)/h;
	double h2=h/2;
	double x2=x;
	double y2=y;
	double z2=z;
	cout << "RUNGE_CUTTA\n";
	cout << "x\ty\ty_t\teps\tR\n";
	cout << "---------------------------------\n";
	for (int i=0; i<n; i++) {
		K1_y=h*z;
		K1_z=h*f_z(x,y,z);
		K2_y=h*(z+0.5*K1_z);
		K2_z=h*f_z(x+0.5*h, y+0.5*K1_y, z+0.5*K1_z);
		K3_y=h*(z+0.5*K2_z);
		K3_z=h*f_z(x+0.5*h, y+0.5*K2_y, z+0.5*K2_z);
		K4_y=h*(z+K3_z);
		K4_z=h*f_z(x+h, y+K3_y, z+K3_z);

		del_y=(K1_y+2*K2_y+2*K3_y+K4_y)/6;
		del_z=(K1_z+2*K2_z+2*K3_z+K4_z)/6;
		y+=del_y;
		z+=del_z;
		x+=h;

		K1_y2=h2*z2;
		K1_z2=h2*f_z(x2,y2,z2);
		K2_y2=h2*(z2+0.5*K1_z2);
		K2_z2=h2*f_z(x2+0.5*h2, y2+0.5*K1_y2, z2+0.5*K1_z2);
		K3_y2=h2*(z2+0.5*K2_z2);
		K3_z2=h2*f_z(x2+0.5*h2, y2+0.5*K2_y2, z2+0.5*K2_z2);
		K4_y2=h2*(z2+K3_z2);
		K4_z2=h2*f_z(x2+h2, y2+K3_y2, z2+K3_z2);

		del_y2=(K1_y2+2*K2_y2+2*K3_y2+K4_y2)/6;
		del_z2=(K1_z2+2*K2_z2+2*K3_z2+K4_z2)/6;
		y2+=del_y2;
		z2+=del_z2;
		x2+=h2;

		K1_y2=h2*z2;
		K1_z2=h2*f_z(x2,y2,z2);
		K2_y2=h2*(z2+0.5*K1_z2);
		K2_z2=h2*f_z(x2+0.5*h2, y2+0.5*K1_y2, z2+0.5*K1_z2);
		K3_y2=h2*(z2+0.5*K2_z2);
		K3_z2=h2*f_z(x2+0.5*h2, y2+0.5*K2_y2, z2+0.5*K2_z2);
		K4_y2=h2*(z2+K3_z2);
		K4_z2=h2*f_z(x2+h2, y2+K3_y2, z2+K3_z2);

		del_y2=(K1_y2+2*K2_y2+2*K3_y2+K4_y2)/6;
		del_z2=(K1_z2+2*K2_z2+2*K3_z2+K4_z2)/6;
		y2+=del_y2;
		z2+=del_z2;
		x2+=h2;

		eps=abs(y-sol(x));
		int p=4;
		R=(y-y2)/(pow(0.5,p)-1);
		cout << x << " | " << y << " | " <<  sol(x) << " | " << eps << " | " << R << "\n\n";
	}
}

void adams(double x, double y, double z, double b, double h) {
	double K1_y, K2_y, K3_y, K4_y, K1_z, K2_z, K3_z, K4_z, del_y, del_z;
	double K1_y2, K2_y2, K3_y2, K4_y2, K1_z2, K2_z2, K3_z2, K4_z2, del_y2, del_z2;
	int n=(b-x)/h;
	vector <double> X (n,0);
	vector <double> Y (n,0);
	vector <double> Z (n,0);
	vector <double> X2 (n,0);
	vector <double> Y2 (n,0);
	vector <double> Z2 (n,0);
	X[0]=x;
	Y[0]=y;
	Z[0]=z;
	double eps, R;
	double h2=h/2;
	double x2=x;
	double y2=y;
	double z2=z;
	X2[0]=x;
	Y2[0]=y;
	Z2[0]=z;
	cout << "ADAMS\n";
	cout << "x\ty\ty_t\teps\tR\n";
	cout << "---------------------------------\n";
	for (int i=1; i<4; i++) {
		K1_y=h*z;
		K1_z=h*f_z(x,y,z);
		K2_y=h*(z+0.5*K1_z);
		K2_z=h*f_z(x+0.5*h, y+0.5*K1_y, z+0.5*K1_z);
		K3_y=h*(z+0.5*K2_z);
		K3_z=h*f_z(x+0.5*h, y+0.5*K2_y, z+0.5*K2_z);
		K4_y=h*(z+K3_z);
		K4_z=h*f_z(x+h, y+K3_y, z+K3_z);

		del_y=(K1_y+2*K2_y+2*K3_y+K4_y)/6;
		del_z=(K1_z+2*K2_z+2*K3_z+K4_z)/6;
		y+=del_y;
		z+=del_z;
		x+=h;

		K1_y2=h2*z2;
		K1_z2=h2*f_z(x2,y2,z2);
		K2_y2=h2*(z2+0.5*K1_z2);
		K2_z2=h2*f_z(x2+0.5*h2, y2+0.5*K1_y2, z2+0.5*K1_z2);
		K3_y2=h2*(z2+0.5*K2_z2);
		K3_z2=h2*f_z(x2+0.5*h2, y2+0.5*K2_y2, z2+0.5*K2_z2);
		K4_y2=h2*(z2+K3_z2);
		K4_z2=h2*f_z(x2+h2, y2+K3_y2, z2+K3_z2);

		del_y2=(K1_y2+2*K2_y2+2*K3_y2+K4_y2)/6;
		del_z2=(K1_z2+2*K2_z2+2*K3_z2+K4_z2)/6;
		y2+=del_y2;
		z2+=del_z2;
		x2+=h2;

		K1_y2=h2*z2;
		K1_z2=h2*f_z(x2,y2,z2);
		K2_y2=h2*(z2+0.5*K1_z2);
		K2_z2=h2*f_z(x2+0.5*h2, y2+0.5*K1_y2, z2+0.5*K1_z2);
		K3_y2=h2*(z2+0.5*K2_z2);
		K3_z2=h2*f_z(x2+0.5*h2, y2+0.5*K2_y2, z2+0.5*K2_z2);
		K4_y2=h2*(z2+K3_z2);
		K4_z2=h2*f_z(x2+h2, y2+K3_y2, z2+K3_z2);

		del_y2=(K1_y2+2*K2_y2+2*K3_y2+K4_y2)/6;
		del_z2=(K1_z2+2*K2_z2+2*K3_z2+K4_z2)/6;
		y2+=del_y2;
		z2+=del_z2;
		x2+=h2;

		X[i]=x;
		Y[i]=y;
		Z[i]=z;

		X2[i]=x2;
		Y2[i]=y2;
		Z2[i]=z2;

		int p=4;
		eps=abs(y-sol(x));
		R=(y-y2)/(pow(0.5,p)-1);
		cout << x << " | " << y << " | " <<  sol(x) << " | " << eps << " | " << R << "\n\n";
	}

	for (int i=3; i<n; i++) {
		del_y=h*(55*Z[i]-59*Z[i-1]+37*Z[i-2]-9*Z[i-3])/24;
		del_z=h*(55*f_z(X[i],Y[i],Z[i])-59*f_z(X[i-1],Y[i-1],Z[i-1])+37*f_z(X[i-2],Y[i-2],Z[i-2])-9*f_z(X[i-3],Y[i-3],Z[i-3]))/24;
		X[i+1]=X[i]+h;
		Y[i+1]=Y[i]+del_y;
		Z[i+1]=Z[i]+del_z;

		del_y2=h2*(55*Z2[i]-59*Z2[i-1]+37*Z2[i-2]-9*Z2[i-3])/24;
		del_z2=h2*(55*f_z(X2[i],Y2[i],Z2[i])-59*f_z(X2[i-1],Y2[i-1],Z2[i-1])+37*f_z(X2[i-2],Y2[i-2],Z2[i-2])-9*f_z(X2[i-3],Y2[i-3],Z2[i-3]))/24;
		X2[i]+=h2;
		Y2[i]+=del_y2;
		Z2[i]+=del_z2;

		del_y2=h2*(55*Z2[i]-59*Z2[i-1]+37*Z2[i-2]-9*Z2[i-3])/24;
		del_z2=h2*(55*f_z(X2[i],Y2[i],Z2[i])-59*f_z(X2[i-1],Y2[i-1],Z2[i-1])+37*f_z(X2[i-2],Y2[i-2],Z2[i-2])-9*f_z(X2[i-3],Y2[i-3],Z2[i-3]))/24;
		X2[i+1]=X2[i]+h2;
		Y2[i+1]=Y2[i]+del_y2;
		Z2[i+1]=Z2[i]+del_z2;

		int p=4;
		eps=abs(Y[i+1]-sol(X[i+1]));
		R=(Y[i+1]-Y2[i+1])/(pow(0.5,p)-1);
		cout << X[i+1] << " | " << Y[i+1] << " | " << sol(X[i+1]) << " | " << eps << " | " << R << "\n\n";	
	}
}

int main() {
	double x=0;
	double y=1;
	double z=3;
	double b=1;
	double h=0.1;
//	eiler(x,y,z,b,h);
//	runge_cutta(x,y,z,b,h);
	adams(x,y,z,b,h);
}