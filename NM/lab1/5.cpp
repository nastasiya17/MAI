#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double eps=0.0001;

int sign(double a) {
	if (a>0) return 1;
	if (a<0) return -1;
	return 0;
}

void print(vector <vector<double>> v) {
	for (int i=0; i<v.size(); i++) {
		for (int j=0; j<v.size(); j++) {
			cout << v[i][j] << "\t\t";
		}
		cout << endl;
	}
}

int main() {
	int N;
	cin >> N;
	vector <vector <double>> A (N, vector <double>(N,0));
	vector <vector <double>> newA (N, vector <double>(N,0));
	vector <vector <double>> H (N, vector <double>(N,0));
	vector <vector <double>> Q (N, vector <double>(N,0));
	vector <vector <double>> newQ (N, vector <double>(N,0));
	vector <vector <double>> R (N, vector <double>(N,0));
	vector <vector <double>> vvt (N, vector <double>(N,0));
	vector <double> v (N,0);

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> A[i][j];
		}
	}

	for (int i=0; i<N; i++) {
		Q[i][i]=1;
	}

	double max=0;
	for (int k=1; k<N; k++) {
		if (abs(A[k][0])>eps) {
			max+=pow(A[k][0],2);
		}
	}
	max=pow(max,0.5);

	while (max>eps) {
		for (int i=0; i<N-1; i++) {
			int j;
			for (j=0; j<i; j++) {
				v[j]=0;
			}
			double sum=0;
			for (int k=i; k<N; k++) {
				sum+=pow(A[k][i],2);
			}

			sum=pow(sum,0.5);
			v[j]=A[j][i]+sign(A[j][i])*sum;
			for (j=i+1; j<N; j++) {
				v[j]=A[j][i];
			}

			for (int k=0; k<N; k++) {
				for (int l=0; l<N; l++) {
					vvt[k][l]=v[k]*v[l];
				}
			}

			double vtv=0;
			for (int k=0; k<N; k++) {
				vtv+=v[k]*v[k];
			}

			for (int k=0; k<N; k++) {
				for (int l=0; l<N; l++) {
					if (k==l)
						H[k][l]=1-2*vvt[k][l]/vtv;
					else 
						H[k][l]=-2*vvt[k][l]/vtv;
				}
			}

			for (int k=0; k<N; k++) {
				for (int l=0; l<N; l++) {
					for (int m=0; m<N; m++) {
						newQ[k][l]+=Q[k][m]*H[m][l];
					}
				}
			}

			for (int k=0; k<N; k++) {
				for (int l=0; l<N; l++) {
					for (int m=0; m<N; m++) {
						newA[k][l]+=H[k][m]*A[m][l];
					}
				}
			}

			A=newA;
			Q=newQ;
			newA.assign(N, vector <double>(N,0));
			newQ.assign(N, vector <double>(N,0));
		}

		R=A;
		A.assign(N, vector <double>(N,0));
	 	for (int k=0; k<N; k++) {
			for (int l=0; l<N; l++) {
				for (int m=0; m<N; m++) {
					A[k][l]+=R[k][m]*Q[m][l];
				}
			}
		}

		max=0;
		for (int k=1; k<N; k++) {
			if (abs(A[k][0])>eps) {
				max+=pow(A[k][0],2);
			}
		}
		max=pow(max,0.5);

		Q.assign(N, vector <double>(N,0));
		for (int i=0; i<N; i++) {
			Q[i][i]=1;
		}
	}

	cout << "lambda1 = " << A[0][0] << endl;
	double d;
	d=pow(A[1][1]+A[2][2],2)-4*(A[1][1]*A[2][2]-A[1][2]*A[2][1]);
	if (d>=0) {
		d=pow(d,0.5);
		cout << "lambda2 = " << (A[1][1]+A[2][2]+d)/2 << endl;
		cout << "lambda3 = " << (A[1][1]+A[2][2]-d)/2 << endl;
	}
	else if (d<0) {
		d=pow(-d,0.5);
		cout << "lambda2 = " << (A[1][1]+A[2][2])/2 << " + " << d/2 << "i\n";
		cout << "lambda3 = " << (A[1][1]+A[2][2])/2 << " - " << d/2 << "i\n";	
	}
}
