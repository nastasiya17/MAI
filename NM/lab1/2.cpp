#include <iostream>
#include <vector>

using namespace std;

int main() {
	int N, i;
	double y;
	cin >> N;
	vector <vector <double>> A (N, vector <double>(N,0));
	vector <double> b (N);
	vector <double> x (N);
	vector <double> al (N);
	vector <double> bet (N);

	for (i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> A[i][j];
		}
		cin >> b[i];
	}

	//прямой ход

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

	//обратный ход

	x[N-1]=bet[N-1];
	for (i=N-2; i>=0; i--) {
		x[i]=al[i]*x[i+1]+bet[i];
	}

	cout << "\nsolution=( ";
	for (i=0; i<N; i++) {
		cout << x[i] << " ";
	}	
	cout << ")\n";

}
