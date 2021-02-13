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
const int MAX_RAND = 1e9;
const double DERIVATIVE = 0.5;

using namespace std;
//почему нельзя задать размер вектора в классе

class Menu;
class Shell;
class Point;
class SetPoints;
bool comp(Point a, Point b);
double distAB(Point a, Point b);
double vect_comp(Point a, Point b, Point p);


mt19937 _g(time(nullptr));

int randint(int a, int b) {
    int w = (_g() << 31LL) ^ _g(); 
    return a + abs(w) % (b - a + 1); 
}

class Point{
	public:
		int type = 0;
		bool used = false;
		double x, y;
		pair<int, double> neighbors[5] = {{0, INF}, {0, INF}, 
							{0, INF}, {0, INF}, {0, INF}};

		Point() {}
		Point(double x, double y) {
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

		double latest(int num) {
			return (this -> neighbors)[num - 1].sec;
		}


		void insert_neighbour(pair<int, double> neighbor) {
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
		vector <double> distanses;
		int size;
		void scan(string file) {
			ifstream fin;
			fin.open(file);
			double x, y;
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
					double d = distAB((this -> mas)[i], mas[j]);
					mas[i].insert_neighbour({j, d});
				}
			}
		}

		/*void sorting() {
			//change this place
			sort(mas.begin(), mas.end(), comp);
		}*/

		void print() {
			ofstream fout;
			fout.open("dist_to_neighbour.txt");
			
			for (int i = 0; i < distanses.size(); i++) {
				fout << i + 1 << " " << distanses[i] << endl;
			}
			fout.close();
		}
		void print_answer() {
			ofstream fout;
			fout.open("output.txt");
			for (int i = 0; i < mas.size(); i++) {
				fout << mas[i].x << " " << mas[i].y << " ";
				fout << mas[i].type * 10 << "\n";
			}
			fout.close();
		}
		double find_optimal_dist() {
			distanses.resize(mas.size());
			for (int i = 0; i < distanses.size(); i++) {
				distanses[i] = mas[i].latest(4);
			}
			sort(distanses.begin(), distanses.end());
			int dX = distanses.size() / 50;
			int step = distanses.size() / 100;
			double dist = 0.0;
			//cout << "MAS.SIZE(): " << distanses.size() << "\n";
			for (int i = 0; i < distanses.size(); i += step) {
				if (i + dX >= distanses.size()) {
					dist = distanses[i];
					return dist;
				}
				double dY = distanses[i + dX] - distanses[i];
				double der = dY/dX;
				//cout << "der: " << der << "\n";
				if (der >= DERIVATIVE) {
					dist = distanses[i];
					return dist;
				}
			}
			return dist;
		}
		void connect(double dist) {
			int CLASTER_NUM = 1;
			for (int i = 0; i < mas.size(); i++) {
				if (mas[i].used) continue;
				mas[i].used = true;
				if (mas[i].latest(4) <= dist) { // основная точка
					dfs(i, CLASTER_NUM, dist);
					CLASTER_NUM++;
				}
			}
		}
		void dfs(int num, int col, double dist) {
			mas[num].used = true;
			if (mas[num].latest(4) > dist) {
				return;
			}
			mas[num].type = col;
			for (int i = 0; i < mas.size(); i++) {
				if (mas[i].used) continue;
				if (distAB(mas[num], mas[i]) <= dist) {
					dfs(i, col, dist);
				}
			}
		}

};


class Shell{
	public:
		vector <Point> points;

		void get(string file) {
			ifstream fin;
			fin.open(file);
			double x, y;
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
		void fill(double min_x, double max_x, double min_y, double max_y, int color) {
			ofstream fout;
			fout.open("data_dbscan.txt", ios::app);
			
			for (int i = 0; i < 5000; i++) {
				double x, y;
				x = min_x + (max_x - min_x) * (double)(rand() % RAND_MAX) / RAND_MAX;
				y = min_y + (max_y - min_y) * (double)(rand() % RAND_MAX) / RAND_MAX;
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
						fout << (double) (rand() % 500 + rand() / MAX_RAND) << " ";
						fout << (double) (rand() % 500 + rand() / MAX_RAND) << " ";
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
					double dist = s.find_optimal_dist();
					s.connect(dist);
					s.print();
					s.print_answer();
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
			fout.setf(ios::fixed);
			fout.precision(7);
			int color;
			double x, y;
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

double distAB(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double vect_comp(Point a, Point b, Point p) {
	return (a.x - p.x) * (b.y - p.y) - (a.y - p.y) * (b.x - p.x);
}


int main() {
	cout.setf(ios::fixed);
	cout.precision(7);
	srand((unsigned)time(NULL));
	Menu men1;
	men1.start();
	return 0;
}