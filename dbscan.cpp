/*
┏╗ ┏╗
║┃ ║┃╔━╦╦┳═╗
║┃ ┃╚┫║┃┃┃╩┫
┗╝ ╚━╩═┻━╩━╝
╔┓╔┓
║╚┛┣═╦┳╗
┗╗┏╣┃┃║┃   
┗╝┗═┻═╝
 
⣿⣿⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ 
⣿⣿⣿⣵⣿⣿⣿⠿⡟⣛⣧⣿⣯⣿⣝⡻⢿⣿⣿⣿⣿⣿⣿⣿ 
⣿⣿⣿⣿⣿⠋⠁⣴⣶⣿⣿⣿⣿⣿⣿⣿⣦⣍⢿⣿⣿⣿⣿⣿ 
⣿⣿⣿⣿⢷⠄⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⢼⣿⣿⣿⣿ 
⢹⣿⣿⢻⠎⠔⣛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⣿⣿⣿⣿ 
⢸⣿⣿⠇⡶⠄⣿⣿⠿⠟⡛⠛⠻⣿⡿⠿⠿⣿⣗⢣⣿⣿⣿⣿ 
⠐⣿⣿⡿⣷⣾⣿⣿⣿⣾⣶⣶⣶⣿⣁⣔⣤⣀⣼⢲⣿⣿⣿⣿ 
⠄⣿⣿⣿⣿⣾⣟⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⢟⣾⣿⣿⣿⣿ 
⠄⣟⣿⣿⣿⡷⣿⣿⣿⣿⣿⣮⣽⠛⢻⣽⣿⡇⣾⣿⣿⣿⣿⣿ 
⠄⢻⣿⣿⣿⡷⠻⢻⡻⣯⣝⢿⣟⣛⣛⣛⠝⢻⣿⣿⣿⣿⣿⣿ 
⠄⠸⣿⣿⡟⣹⣦⠄⠋⠻⢿⣶⣶⣶⡾⠃⡂⢾⣿⣿⣿⣿⣿⣿ 
⠄⠄⠟⠋⠄⢻⣿⣧⣲⡀⡀⠄⠉⠱⣠⣾⡇⠄⠉⠛⢿⣿⣿⣿ 
⠄⠄⠄⠄⠄⠈⣿⣿⣿⣷⣿⣿⢾⣾⣿⣿⣇⠄⠄⠄⠄⠄⠉⠉ 
⠄⠄⠄⠄⠄⠄⠸⣿⣿⠟⠃⠄⠄⢈⣻⣿⣿⠄⠄⠄⠄⠄⠄⠄ 
⠄⠄⠄⠄⠄⠄⠄⢿⣿⣾⣷⡄⠄⢾⣿⣿⣿⡄⠄⠄⠄⠄⠄⠄ 
⠄⠄⠄⠄⠄⠄⠄⠸⣿⣿⣿⠃⠄⠈⢿⣿⣿⠄⠄⠄⠄⠄.. 

//g++ -std=c++11 dbscan.cpp

*/
#include <bits/stdc++.h>
#define sec second
#define fir first
#define pb push_back

const int INF = 1e9;

using namespace std;
//почему нельзя задать размер вектора в классе

class Menu;
class Shell;
class Point;
class SetPoints;
int vect_comp(Point a, Point b, Point p);

mt19937 _g(time(nullptr));

int randint(int a, int b) {
    int w = (_g() << 31LL) ^ _g(); 
    return a + abs(w) % (b - a + 1); 
}
class Point{
	public:
		int x = 0, y = 0, type = 0;
		pair<int, int> neighbors[5] = {{0, INF}, {0, INF}, {0, INF}, {0, INF}, {0, INF}};
		Point() {}
		Point(int x, int y) {
			this -> x = x;
			this -> y = y;
		}
		void show() {
			cout << this -> x << " " << this -> y << endl;
		}
		int latest(int num) {
			return (this -> neighbors)[num].sec;
		}
		void insert_neighbor(pair<int, int> neighbor) {
			if ((this -> neighbors)[4].sec < neighbor.sec) return;
			(this -> neighbors)[4] = neighbor;
			for (int i = 4; i > 0; i--) {
				if ((this -> neighbors)[i].sec < (this -> neighbors)[i - 1].sec) {
					swap((this -> neighbors)[i], (this -> neighbors)[i - 1]);
				}
			}
		}

};


class Shell{
	public:
		vector <Point> points;

		void get() {
			ifstream fin;
			fin.open("shells.txt");
			int x, y;
			while (fin >> x, x != -1) {
				fin >> y;
				Point p(x, y);
				points.pb(p);
			}
		}
		void show() {
			for (auto i : this -> points) {
				i.show();
			}
		}
		void fill(int min_x, int max_x, int min_y, int max_y) {
			ofstream fout;
			fout.open("data_dbscan.txt");
			
			for (int i = 0, x, y; i < 10000; i++) {
				x = randint(min_x, max_x);
				y = randint(min_y, max_y);
				Point l, r, a(x, y);
				int up = 0;
				for (int i = 0; i < (this -> points).size(); i++) {
					l = points[i];
					r = points[(i + 1) % (this -> points).size()];
					if (l.x > r.x) {
						r = (this -> points)[i];
						l = (this ->points)[(i + 1) % (this -> points).size()];
					}
					if (l.x >= a.x || a.x >= r.x) {
						if (l.x == a.x && r.x != a.x && l.y > a.y) {
							up++;
						}
						continue;
					}
					if (vect_comp(r, l, a) >= 0) {
						up++;
					} 
				}
				if (up % 2 != 0) {
					fout << a.x << " " << a.y << " 50\n";
				}
			}
			for (auto i : points) {
				fout << i.x << " " << i.y << " " << "20\n";
			}
		}

};

class Menu{
	public:
		void start() {
			vector <Shell> Shells;
			while(1) {
				cout << "Press 1 to generate random of 1000 points\n";
				cout << "Press 2 to form your shell\n";
				cout << "Press 3 to fill shells\n";
				cout << "Press 4 to exit\n";
				char t;
				cin >> t;
				if (t == '1') {
					ofstream fout;
					fout.open("input.txt");
					for (int i = 0; i < 1000; i++) {
						fout << randint(1, 500) << " ";
						fout << randint(1, 500) << "\n";
					}
				} else if (t == '2') {
					cout << "Indicate your points, press -1 finish\n";
					Shell a;
					a.get();
					Shells.pb(a);
				} else if (t == '3') {
					for (auto i : Shells) {
						i.fill(0, 500, 0, 500);
					}
				} else if (t == '4') {
					break;
				}
			}
			for (auto i : Shells) {
				i.show();
			}
			
		}
};

bool comp(Point a, Point b) {
	return a.latest(4) < b.latest(4);
}

int dist(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int vect_comp(Point a, Point b, Point p) {
	return (a.x - p.x) * (b.y - p.y) - (a.y - p.y) * (b.x - p.x);
}


class SetPoints{
	public:
		vector <Point> mas;
		int size;
		void scan(string file) {
			ifstream fin;
			fin.open(file);
			fin >> this -> size;
			(this -> mas).resize(this -> size);
			for (int i = 0; i < (this -> size); i++) {
				fin >> (this -> mas)[i].x >> (this -> mas)[i].y;
			}
		}

		void fill_neighbors() {
			for (int i = 0; i < (this -> size); i++) {
				for (int j = 0; j < (this -> size); j++) {
					if (i == j) continue;
					int d = dist((this -> mas)[i], (this -> mas)[j]);
					(this -> mas)[i].insert_neighbor({j, d});
				}
			}
		}
		void sorting() {
			sort(mas.begin(), mas.end(), comp);
		}
		void print() {
			for (auto i : mas) {
				cout << i.latest(4) << endl;
			}
		}

};


int main() {
	string file = "input.txt";
	Menu men1;
	men1.start();
	return 0;
	SetPoints s;
	Point t1(1, 3), t2(3, 3), p(2, 2);
	cout << vect_comp(t2, t1, p) << "\n";
	return 0;
	s.scan(file);
	s.fill_neighbors();
	s.sorting();
	s.print();
	return 0;
}