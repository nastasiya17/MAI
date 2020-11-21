#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double eps=0.0001;

double norm(vector <double> b) {
	double s=0;
	for (int i=0; i<b.size(); i++) {
		s+=pow(b[i],2);
	}
	return s;
}

int sign(double a) {
	if (a>0) return 1;
	if (a<0) return -1;
	return 0;
}

void print(vector <vector<double>> v) {
	for (int i=0; i<v.size(); i++) {
		for (int j=0; j<v.size(); j++) {
			cout << v[i][j] << "\t";
		}
		cout << endl;
	}
}

double max(vector <vector<double>> A) {
	double max=0;
	for (int k=1; k<A.size(); k++) {
		if (abs(A[k][0])>eps) {
			max+=pow(A[k][0],2);
		}
	}
	return pow(max,0.5);
}

void QR(vector <vector<double>> A) {
	int N=A.size();
	vector <vector <double>> newA (N, vector <double>(N,0));
	vector <vector <double>> H (N, vector <double>(N,0));
	vector <vector <double>> Q (N, vector <double>(N,0));
	vector <vector <double>> newQ (N, vector <double>(N,0));
	vector <vector <double>> Qtemp (N, vector <double>(N,0));
	vector <vector <double>> Qp (N, vector <double>(N,0));
	vector <vector <double>> R (N, vector <double>(N,0));
	vector <vector <double>> vvt (N, vector <double>(N,0));
	vector <double> v (N,0);

	for (int i=0; i<N; i++) {
		Q[i][i]=1;
	}

	for (int i=0; i<N; i++) {
		Qp[i][i]=1;
	}

	while (max(A)>eps) {
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

		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				for (int k=0; k<N; k++) {
					Qtemp[i][j]+=Qp[i][k]*Q[k][j];
				}
			}
		}

		Qp=Qtemp;
		Qtemp.assign(N, vector <double>(N,0));

		R=A;
		A.assign(N, vector <double>(N,0));
	 	for (int k=0; k<N; k++) {
			for (int l=0; l<N; l++) {
				for (int m=0; m<N; m++) {
					A[k][l]+=R[k][m]*Q[m][l];
				}
			}
		}

		Q.assign(N, vector <double>(N,0));
		for (int i=0; i<N; i++) {
			Q[i][i]=1;
		}
	}

	cout << "\nСобственные значения:\n\n";
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

	cout << "\nСобственные векторы:\n\n";
	for (int i=1; i<=N; i++) {
		cout << "X" << i << "\t\t";
	}
	cout << "\n------------------------------------------------\n";
	print(Qp);
}

int main() {
	int N;
	int k=3;
	cin >> N;
	vector <vector <double>> A (N, vector <double>(N,0));
	vector <vector <double>> q (k+2, vector <double>(N,0));
	vector <vector <double>> T (k, vector <double>(k,0));
	vector <double> b (N,0);
	vector <double> z (N,0);
	vector <double> temp (N,0);
	double alpha;
	double beta=0;

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> A[i][j];
		}
	}

	for (int i=0; i<N; i++) {
		cin >> b[i];
	}

	for (int i=0; i<N; i++) {
		q[1][i]=b[i]/norm(b);
	}

	for (int i=1; i<k+1; i++) {
		for (int j=0; j<N; j++) {
			double s=0;
			for (int k=0; k<N; k++) {
				s+=A[j][k]*q[i][k];
			}
			z[j]=s;
		}

		alpha=0;
		for (int j=0; j<N; j++) {
			alpha+=q[i][j]*z[j];
		}

		T[i-1][i-1]=alpha;
		if (i!=1) {
			T[i-1][i-2]=beta;
			T[i-2][i-1]=beta;
		}

		for (int p=0; p<2; p++) { // 2 times
			for (int j=0; j<N; j++) { // for z
				for (int k=1; k<i; k++) { // for sum
					double s=0;
					for (int m=0; m<N; m++) { // for z*q
						s+=z[m]*q[k][m];
					}
					for (int m=0; m<N; m++) { //for s*q
						temp[m]+=q[k][m]*s;
					}
				}
				z[j]-=temp[j];
			}
		}

		for (int j=0; j<N; j++) {
			z[j]=z[j]-alpha*q[i][j]-beta*q[i-1][j];
		}

		beta=norm(z);
		if (beta==0)
			break;

		for (int j=0; j<N; j++) {
			q[i+1][j]=z[j]/beta;
		}
	}

	QR(T);

	for (int i=0; i<N-k; i++) {
		for (int j=0; j<k; j++){
			cout << 0 << "\t\t";
		}
		cout << endl;
	}
	cout << "------------------------------------------------\n";
}