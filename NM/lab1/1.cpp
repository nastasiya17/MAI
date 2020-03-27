#include <iostream>
#include <vector>

using namespace std;

void print(vector <vector<double>> v) {
	for (int i=0; i<v.size(); i++) {
		for (int j=0; j<v.size(); j++) {
			cout << v[i][j] << "\t\t";
		}
		cout << endl;
	}
}

double det(vector <vector<double>> v) {
	double p=1;
	for (int i=0; i<v.size(); i++) {
		p*=v[i][i];
	}
}

int main() {
	int N;
	cin >> N;
	vector <vector <double>> A (N, vector <double>(N,0));
	vector <vector <double>> A1 (N, vector <double>(N,0));
	vector <vector <double>> Y1 (N, vector <double>(N,0));
	vector <vector <double>> L (N, vector <double>(N,0));
	vector <vector <double>> U (N, vector <double>(N,0));
	vector <vector <double>> LU (N, vector <double>(N,0));
	vector <double> b (N);
	vector <double> x (N);
	vector <double> y (N);
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> A[i][j];
		}
		cin >> b[i];
	}

	U=A;

	//алгоритм 

	for (int k=0; k<N-1; k++) {

		for (int i=k; i<N; i++) {
			for (int j=i; j<N; j++) {
				L[j][i]=U[j][i]/U[i][i];
			}
		}

		for (int i=k+1; i<N; i++) {
			for (int j=k; j<N; j++) {
				U[i][j]=U[i][j]-L[i][k]*U[k][j];
			}
		}
	}

	//проверка

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			for (int k=0; k<N; k++) {
				LU[i][j]+=L[i][k]*U[k][j];
			}
		}
	}

	//решение системы

	for (int i=0; i<N; i++) {
		double S=0;
		for (int j=0; j<i; j++) {
				S+=L[i][j]*y[j];
		}
		y[i]=b[i]-S;
	}

	for (int i=N-1; i>=0; i--) {
		double S=0;
		for (int j=N-1; j>i; j--) {
				S+=U[i][j]*x[j];
		}
		x[i]=(y[i]-S)/U[i][i];
	}

//	L*U*A1=E
//	L*Y1=E
//	U*A1=Y1

	//нахождение обратной матрицы

	for (int k=0; k<N; k++) {
		for (int i=0; i<N; i++) {
			double S=0;
			for (int j=0; j<i; j++) {
				S+=L[i][j]*Y1[j][k];
			}
			if (i==k)
				Y1[i][k]=1-S;
			else
				Y1[i][k]=-S;
		}
	}

	for (int k=0; k<N; k++) {
		for (int i=N-1; i>=0; i--) {
			double S=0;
			for (int j=N-1; j>i; j--) {
					S+=U[i][j]*A1[j][k];
			}
			A1[i][k]=(Y1[i][k]-S)/U[i][i];
		}
	}

	cout << "\n\tMatrix L\n";
	cout << "-------------------------------------------------------------------\n";
	print(L);
	cout << "\n\n\tMatrix U\n";
	cout << "-------------------------------------------------------------------\n";
	print(U);
	cout << "\n\n\tMatrix L*U\n";
	cout << "-------------------------------------------------------------------\n";
	print(LU);
	cout << "\n\n\tMatrix A1\n";
	cout << "-------------------------------------------------------------------\n";
	print(A1);
	cout << "\n\nsolution=( ";
	for (int i=0; i<N; i++) {
		cout << x[i] << " ";
	}
	cout << ")\n\ndet=" << det(U) << endl;
}
