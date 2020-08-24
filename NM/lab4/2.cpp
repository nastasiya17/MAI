#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double eps=0.0001;

double f_z(double x, double y, double z) {
	return (2*z+exp(x)*y)/(exp(x)+1);
}

double sol(double x) {
	return exp(x)-1+1/(exp(x)+1);
}

double runge_cutta(double x, double y, double z, double b, double h) {
	double K1_y, K2_y, K3_y, K4_y, K1_z, K2_z, K3_z, K4_z, del_y, del_z;
	int n=(b-x)/h;
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
	}
	return z;
}

double runge_cutta2(double x, double y, double z, double b, double h) {
	double K1_y, K2_y, K3_y, K4_y, K1_z, K2_z, K3_z, K4_z, del_y, del_z;
	int n=(b-x)/h;
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
	}
	return z;
}

double Fi(double eta, double x,double z0, double z1,double b, double h) {
	return runge_cutta(x,eta,z0,b,h)-z1;
}

double Fi2(double eta, double x,double z0, double z1,double b, double h) {
	return runge_cutta2(x,eta,z0,b,h)-z1;
}

double new_eta(double eta0, double eta1, double x,double z0, double z1,double b, double h) {
	return eta1-Fi(eta1,x,z0,z1,b,h)*(eta1-eta0)/(Fi(eta1,x,z0,z1,b,h)-Fi(eta0,x,z0,z1,b,h));
}

double new_eta2(double eta0, double eta1, double x,double z0, double z1,double b, double h) {
	return eta1-Fi2(eta1,x,z0,z1,b,h)*(eta1-eta0)/(Fi2(eta1,x,z0,z1,b,h)-Fi2(eta0,x,z0,z1,b,h));
}

void shooting_method(double x,double z0,double z1,double b, double h) {
	double K1_y, K2_y, K3_y, K4_y, K1_z, K2_z, K3_z, K4_z, del_y, del_z;
	double K1_y2, K2_y2, K3_y2, K4_y2, K1_z2, K2_z2, K3_z2, K4_z2, del_y2, del_z2;
	double eta0=1;
	double eta1=0.8;
	double n_eta;
	double n_Fi;
	double e,R;

	double h2=h/2;
	double eta0_2=eta0;
	double eta1_2=eta1;
	double n_eta2;
	double n_Fi2;
	int n=(b-x)/h;

	n_Fi=Fi(eta1,x,z0,z1,b,h);
	while (abs(n_Fi)>eps) {
		n_eta=new_eta(eta0, eta1, x, z0, z1, b, h);
		eta0=eta1;
		eta1=n_eta;
		n_Fi=Fi(eta1,x,z0,z1,b,h);
	}

	n_Fi2=Fi2(eta1_2,x,z0,z1,b,h2);
	while (abs(n_Fi2)>eps) {
		n_eta2=new_eta2(eta0_2, eta1_2, x, z0, z1, b, h2);
		eta0_2=eta1_2;
		eta1_2=n_eta2;
		n_Fi2=Fi2(eta1_2,x,z0,z1,b,h2);
	}

	double z=z0;
	double y=eta1;

	double x2=x;
	double z2=z0;
	double y2=eta1_2;

	cout << "SHOOTING METHOD\n";
	cout << "x\ty\teps\tR\n";
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

		int p=4;
		e=abs(y-sol(x));
		R=(y-y2)/(pow(0.5,p)-1);
		cout << x << " | " << y << " | " << e << " | " << R << "\n\n";	
	}
}

double p(double x) {
	return -2/(exp(x)+1);
}

double q(double x) {
	return -exp(x)/(exp(x)+1);
}

double f(double x) {
	return 0;
}

double A(double x,double h) {
	return 1-p(x)*h/2;
}

double B(double x,double h) {
	return -2+pow(h,2)*q(x);
}

double C(double x,double h) {
	return 1+p(x)*h/2;
}

void run_method(vector <vector<double>> A, vector <double> b, double x_i, 
	double h, vector <vector<double>> A2, vector <double> b2) {
	int N=b.size();
	int i;
	double y,e,R;
	vector <double> x (N);
	vector <double> al (N);
	vector <double> bet (N);

	double h2=h/2;
	double y2;
	int N2=b2.size();
	vector <double> x2 (N2);
	vector <double> al2 (N2);
	vector <double> bet2 (N2);

	y=A[0][0];
	al[0]=-A[0][1]/y;
	bet[0]=b[0]/y;
	for (i=1; i<N-1; i++) {
		y=A[i][i]+A[i][i-1]*al[i-1];
		al[i]=-A[i][i+1]/y;
		bet[i]=(b[i]-A[i][i-1]*bet[i-1])/y;
	}

	y=A[i][i]+A[i][i-1]*al[i-1];
	bet[i]=(b[i]-A[i][i-1]*bet[i-1])/y;

	x[N-1]=bet[N-1];
	for (i=N-2; i>=0; i--) {
		x[i]=al[i]*x[i+1]+bet[i];
	}

	y2=A2[0][0];
	al2[0]=-A2[0][1]/y2;
	bet2[0]=b2[0]/y2;
	for (i=1; i<N2-1; i++) {
		y2=A2[i][i]+A2[i][i-1]*al2[i-1];
		al2[i]=-A2[i][i+1]/y2;
		bet2[i]=(b2[i]-A2[i][i-1]*bet2[i-1])/y2;
	}

	y2=A2[i][i]+A2[i][i-1]*al2[i-1];
	bet2[i]=(b2[i]-A2[i][i-1]*bet2[i-1])/y2;

	x2[N2-1]=bet2[N2-1];
	for (i=N2-2; i>=0; i--) {
		x2[i]=al2[i]*x2[i+1]+bet2[i];
	}

	cout << "FINITE_DIF_METHOD\n";
	cout << "x\ty\teps\tR\n";
	cout << "---------------------------------\n";
	for (i=0; i<N; i++) {
		x_i+=h;
		int p=4;
		e=abs(sol(x_i)-x[i]);
		R=(x[i]-x2[2*i])/(pow(0.5,p)-1);
		cout << x_i << " | " << x[i] << " | " << e << " | " << R << endl << endl;
	}	
}

void finite_dif_method(double x,double z0,double z1,double b,double h) {
	int N=(b-x)/h;
	vector <double> s (N,0);
	vector <vector <double>> matrix (N,vector <double> (N,0));
	double x_i=x+h;

	double h2=h/2;
	int N2=(b-x)/h2;
	double x_i2=x+h2;
	vector <double> s2 (N2,0);
	vector <vector <double>> matrix2 (N2,vector <double> (N2,0));

//	matrix[0][0]=B(x_i,h);
//	matrix[0][1]=C(x_i,h);
//	s[0]=pow(h,2)*f(x_i)-A(x_i,h)*z0;

	matrix[0][0]=-1;
	matrix[0][1]=1;
	s[0]=h*z0;

	for (int i=1; i<N-1; i++) {
		x_i+=h;
		matrix[i][i-1]=A(x_i,h);
		matrix[i][i]=B(x_i,h);
		matrix[i][i+1]=C(x_i,h);
		s[i]=pow(h,2)*f(x_i);
	}
	x_i+=h;

//	matrix[N-1][N-2]=A(x_i,h);
//	matrix[N-1][N-1]=B(x_i,h);
//	s[N-1]=pow(h,2)*f(x_i)-C(x_i,h)*z1;

	matrix[N-1][N-2]=-1;
	matrix[N-1][N-1]=1;
	s[N-1]=h*z1;

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cout << matrix[i][j] << "  ";
		}
		cout << "=" << s[i] << endl;
	}

//	matrix2[0][0]=B(x_i2,h2);
//	matrix2[0][1]=C(x_i2,h2);
//	s2[0]=pow(h2,2)*f(x_i2)-A(x_i2,h2)*z0;

	matrix2[0][0]=-1;
	matrix2[0][1]=1;
	s2[0]=h2*z0;

	for (int i=1; i<N2-1; i++) {
		x_i2+=h2;
		matrix2[i][i-1]=A(x_i2,h2);
		matrix2[i][i]=B(x_i2,h2);
		matrix2[i][i+1]=C(x_i2,h2);
		s2[i]=pow(h2,2)*f(x_i2);
	}
	x_i2+=h2;

//	matrix2[N2-1][N2-2]=A(x_i2,h2);
//	matrix2[N2-1][N2-1]=B(x_i2,h2);
//	s2[N2-1]=pow(h2,2)*f(x_i2)-C(x_i2,h2)*z1;

	matrix2[N2-1][N2-2]=-1;
	matrix2[N2-1][N2-1]=1;
	s2[N2-1]=h2*z1;

	run_method(matrix,s,x,h,matrix2,s2);
}

int main() {
	double x=0;
	double z0=0.75;
	double z1=exp(2)*(exp(1)+2)/pow((exp(1)+1),2);
	double b=1;
	double h=0.1;
//	shooting_method(x,z0,z1,b,h);
	finite_dif_method(x,z0,z1,b,h);
}