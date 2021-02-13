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
bool comp(Point a, Point b);
int dist(Point a, Point b);
int vect_comp(Point a, Point b, Point p);


mt19937 _g(time(nullptr));

int randint(int a, int b) {
    int w = (_g() << 31LL) ^ _g(); 
    return a + abs(w) % (b - a + 1); 
}

class Point{
	public:
		int x = 0, y = 0, type = 0;
		pair<int, int> neighbors[5] = {{0, INF}, {0, INF}, 
							{0, INF}, {0, INF}, {0, INF}};

		Point() {}
		Point(int x, int y) {
			this -> x = x;
			this -> y = y;
		}

		void show() {
			cout << this -> x << " " << this -> y << endl;
		}

		void show(string file) {
			ofstream fout;
			fout.open(file);
			fout << this -> x << " " << this -> y << endl;
			
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

class SetPoints{
	public:
		vector <Point> mas;
		int size;
		void scan(string file) {
			ifstream fin;
			fin.open(file);
			int x, y;
			while (fin >> x) {
				fin >> y;
				Point a(x, y);
				mas.pb(a);
			}
			size = mas.size();
			cout << size;
			fin.close();
		}

		void fill_neighbors() {
			for (int i = 0; i < mas.size(); i++) {
				for (int j = 0; j < mas.size(); j++) {
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
			ofstream fout;
			fout.open("dist_to_neighbour.txt");
			for (int i = 0; i < mas.size(); i++) {
				fout << i + 1 << " " << mas[i].latest(4) << endl;
			}
			fout.close();
		}

};


class Shell{
	public:
		vector <Point> points;

		void get(string file) {
			ifstream fin;
			fin.open(file);
			int x, y;
			while (fin >> x, x != -1) {
				fin >> y;
				Point p(x, y);
				points.pb(p);
			}
			fin.close();
		}
		void show() {
			for (auto i : (this -> points)) {
				i.show();
			}
		}
		void fill(int min_x, int max_x, int min_y, int max_y, int color) {
			ofstream fout;
			fout.open("data_dbscan.txt", ios::app);
			
			for (int i = 0, x, y; i < 5000; i++) {
				x = randint(min_x, max_x);
				y = randint(min_y, max_y);
				Point l, r, a(x, y);
				int up = 0;
				for (int i = 0; i < points.size(); i++) {
					l = points[i];
					r = points[(i + 1) % points.size()];
					if (l.x > r.x) {
						r = points[i];
						l = points[(i + 1) % points.size()];
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
					fout << a.x << " " << a.y << " " << color << "\n";
				}
			}
			fout.close();
		}

};

class Menu{
	public:
		void start() {
			vector <Shell> Shells;

			//clean file
			ofstream fout;
			fout.open("data_dbscan.txt");
			fout.close();


			while(1) {
				cout << "Press 1 to generate n random points\n";
				cout << "Press 2 to get your shells and fill them\n";
				cout << "Press 3 to find clasters\n";
				cout << "Press 9 to exit\n";
				char t;
				cin >> t;
				if (t == '1') {
					cout << "Press how much points do you want\n";
					ofstream fout;
					fout.open("data_dbscan.txt", ios::app);
					int num;
					cin >> num;
					int color = 20;
					for (int i = 0; i < num; i++) {
						fout << randint(1, 500) << " ";
						fout << randint(1, 500) << " ";
						fout << color << "\n";
					}
					fout.close();
				} else if (t == '2') {
					vector <string> files = {"shell1.txt", "shell2.txt"};
					int color = 50;
					for (int i = 0; i < files.size(); i++) {
						Shell a;
						a.get(files[i]);
						a.fill(0, 500, 0, 500, color);
						Shells.pb(a);
						color -= 10;
					}
				} else if (t == '3') {
					string file = copy_points_from("data_dbscan.txt");
					SetPoints s;
					s.scan(file);
					s.fill_neighbors();
					s.sorting();
					s.print();
				} else if (t == '9') {
					break;
				}
			}
		}
	private:
		string copy_points_from(string file) {
			ifstream fin;
			fin.open(file);
			string output = "data.txt";
			ofstream fout;
			fout.open(output);
			int x, y, color;
			while (fin >> x) {
				fin >> y >> color;
				fout << x << " " << y << "\n";
			}
			fin.close();
			fout.close();
			return output;
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


int main() {
	Menu men1;
	men1.start();
	return 0;
}