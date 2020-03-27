#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double eps=0.0001;

int main() {
	int N, maxi, maxj;
	double max, phi, sl;
	cin >> N;
	vector <vector <double>> A (N, vector <double>(N,0));
	vector <vector <double>> H (N, vector <double>(N,0));
	vector <vector <double>> Hp (N, vector <double>(N,0));
	vector <vector <double>> Htemp (N, vector <double>(N,0));
	vector <vector <double>> Ht (N, vector <double>(N,0));
	vector <vector <double>> HtA (N, vector <double>(N,0));
	vector <vector <double>> HtAH (N, vector <double>(N,0));

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> A[i][j];
		}
	}

	max=abs(A[0][N-1]);
	maxi=0;
	maxj=N-1;

	for (int i=0; i<N; i++) {
		for (int j=i+1; j<N; j++) {
			if (abs(A[i][j])>max) {
				max=abs(A[i][j]);
				maxi=i;
				maxj=j;
			}
		}
	}

	for (int i=0; i<N; i++) {
		Hp[i][i]=1;
	}

	while (max>eps) {
		phi=atan(2*A[maxi][maxj]/(A[maxi][maxi]-A[maxj][maxj]))/2;
		vector <vector <double>> H (N, vector <double>(N,0));
		for (int i=0; i<N; i++) 
			H[i][i]=1;

		H[maxi][maxi]=cos(phi);
		H[maxi][maxj]=-sin(phi);
		H[maxj][maxi]=sin(phi);
		H[maxj][maxj]=cos(phi);

		//произведение матриц H

		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				Htemp[i][j]=0;
				for (int k=0; k<N; k++) {
					Htemp[i][j]+=Hp[i][k]*H[k][j];
				}
			}
		}

		Hp=Htemp;

		Ht=H;

		//вычисление H транспонированного 

		for (int i=0; i<N; i++) {
			for (int j=i+1; j<N; j++) {
				double tmp=Ht[i][j];
				Ht[i][j]=Ht[j][i];
				Ht[j][i]=tmp;
			}
		}

		//произведение HtAH

		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				HtA[i][j]=0;
				for (int k=0; k<N; k++) {
					HtA[i][j]+=Ht[i][k]*A[k][j];
				}
			}
		}

		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				HtAH[i][j]=0;
				for (int k=0; k<N; k++) {
					HtAH[i][j]+=HtA[i][k]*H[k][j];
				}
			}
		}

		A=HtAH;

		//вычисление максимального элемента в матрице 

		max=abs(A[0][N-1]);
		maxi=0;
		maxj=N-1;

		for (int i=0; i<N; i++) {
			for (int j=i+1; j<N; j++) {
				if (abs(A[i][j])>max) {
					max=abs(A[i][j]);
					maxi=i;
					maxj=j;
				}
			}
		}

	}

	cout << "\nСобственные векторы:\n\n";
	for (int i=1; i<=N; i++) {
		cout << "X" << i << "\t\t";
	}
	cout << "\n------------------------------------------\n";

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cout << Hp[i][j] << " \t";
		}
		cout << endl;
	}
	cout << "------------------------------------------\n";

	sl=0;
	cout << "\nСобственные значения:\n";
	for (int i=0; i<N; i++) {
		sl+=A[i][i];
		cout << A[i][i] << "  ";
	}

	cout << "\n\nСлед равен " << sl << "\n\n";
}