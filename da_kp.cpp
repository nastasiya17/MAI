#include <iostream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <math.h>
#include <ctime>

using namespace std;

double Distance(int x1,int y1, int x2, int y2) {
	return sqrt(pow((x2-x1),2)+pow((y2-y1),2));
}

int main() {

	int N,M,x,y,v,u, q, start, finish, current, gen;
	double temp;
	cin >> N >> M;
	vector <pair <int, int> > Coord; //вектор с координатами
	vector <vector <pair <int, double> > > Matrix (N+1); //матрица с расстрояниями между вершинами
	priority_queue <pair <double, double>, vector <pair <double, double> >, greater <pair <double, double> > > Open; 
	//очередь с еще не использованными вершинами
	//чтобы элементы были отсортированы по возрастанию
	vector <bool> Is_Open (N+1,false); //вектор с неиспользованными вершинами
	vector <bool> Is_Close (N+1,false); //вектор с использованными вершинами
	vector <double> g (N+1,0); //вектор с суммой расстояний 
	vector <double> f (N+1,0); //вектор с суммой расстояний + эвристика
	vector <int> generation_op (N+1,0); //вектор для очистки вектора Is_Open;
	vector <int> generation_cl (N+1,0); //вектор для очистки вектора Is_Close;
	vector <int> generation_g (N+1,0); //вектор для очистки вектора g;
	vector <int> generation_f (N+1,0); //вектор для очистки вектора f;


	Coord.push_back(make_pair(0,0));

	for (int i=0; i<N; i++) {
		cin >> x >> y;
		Coord.push_back(make_pair(x,y));
	}


	for (int i=0; i<M; i++) {
		cin >> v >> u;
		double d=Distance(Coord[v].first,Coord[v].second,Coord[u].first,Coord[u].second);
		Matrix[v].push_back(make_pair(u,d));
		Matrix[u].push_back(make_pair(v,d));
	}

	cin >> q;

	gen=0;

	for (int j=0; j<q; j++) {

		//очищаем очередь
		Open = priority_queue <pair <double, double>, vector <pair <double, double> >, greater <pair <double, double> > >();

		cin >> start >> finish;
		Open.push(make_pair(0,start));
		Is_Open[start]=true;
		g[start]=0;
		f[start]=g[start]+Distance(Coord[start].first,Coord[start].second,Coord[finish].first,Coord[finish].second);
		gen++;

		while (!Open.empty()) {
			current=Open.top().second;
			if (current==finish)
				break;
			Open.pop();
			Is_Open[current]=false;
			generation_op[current]=gen;
			Is_Close[current]=true;
			generation_cl[current]=gen;
			for (int i=0; i<Matrix[current].size(); i++) {
				int cur_u=Matrix[current][i].first;
				double cur_d=Matrix[current][i].second;
				if ((generation_cl[cur_u]==gen)and(!Is_Close[cur_u]) or (generation_cl[cur_u]!=gen)) { 
					if (generation_g[current]!=gen) {
						g[current]=0;
						generation_g[current]=gen;
					}
					if (generation_g[cur_u]!=gen) {
						g[cur_u]=0;
						generation_g[cur_u]=gen;
					}
					temp=g[current]+cur_d;
					if ((temp<g[cur_u])or(generation_op[cur_u]==gen)and(!Is_Open[cur_u])or(generation_op[cur_u]!=gen)) {
						g[cur_u]=temp;
						f[cur_u]=g[cur_u]+Distance(Coord[cur_u].first,Coord[cur_u].second,Coord[finish].first,Coord[finish].second);
						generation_f[cur_u]=gen;
						if ((generation_op[cur_u]==gen)and(!Is_Open[cur_u]) or (generation_op[cur_u]!=gen)) {
							Open.push(make_pair(f[cur_u],cur_u));
							Is_Open[cur_u]=true;
							generation_op[cur_u]=gen;
						}		
					}
				}
			}
		}

		if (generation_f[finish]==gen) 
			cout << f[finish] << endl;
		else cout << 0 << endl;
	}
}
