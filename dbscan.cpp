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
const int MAX_RAND = 32292;
const double DERIVATIVE = 0.5;
const int MAX_DOUBLE = 1e9;
const int DENSITY = 7000;

using namespace std;
//почему нельзя задать размер вектора в классе

vector <string> files = {	"shells/shell1.txt", 
							"shells/shell2.txt", 
							"shells/shell3.txt"};

/*vector <string> files = {	"shells/shell4.txt", 
							"shells/shell5.txt",
							"shells/shell6.txt"};*/

class Menu;
class Shell;
class Point;
class SetPoints;
double randDouble(double min, double max);
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
		//наследовать class center от point с полем sum_distance
		double lenX = 0.0, lenY = 0.0;
		int qX = 0, qY = 0;

		int type = 0;
		bool used = false;
		double x, y, dist_to_center = MAX_DOUBLE;
		pair<int, double> neighbours[5] = {{0, INF}, {0, INF}, 
							{0, INF}, {0, INF}, {0, INF}};


		Point() {}
		Point(double x, double y) {
			this -> x = x;
			this -> y = y;
		}
		Point(double minX, double maxX, double minY, double maxY) {
			x = randDouble(minX, maxX);
			y = randDouble(minY, maxY);
		}

		void show() {
			cout << x << " " << y << endl;
		}

		void show(string file) {
			ofstream fout;
			fout.open(file);
			fout << x << " " << y << endl;
			
		}

		double latest(int num) {
			return neighbours[num - 1].sec;
		}


		void insert_neighbour(pair<int, double> neighbour) {
			if (neighbours[4].sec < neighbour.sec) return;
			neighbours[4] = neighbour;
			for (int i = 4; i > 0; i--) {
				if (neighbours[i].sec < neighbours[i - 1].sec) {
					swap(neighbours[i], neighbours[i - 1]);
				}
			}
		}

};

class SetPoints{
	public:
		vector <Point> mas;
		vector <double> distanses;
		vector <Point> centers;
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
			fin.close();
		}

		void fill_neighbours() {
			for (int i = 0; i < mas.size(); i++) {
				for (int j = 0; j < mas.size(); j++) {
					if (i == j) continue;
					double d = distAB(mas[i], mas[j]);
					mas[i].insert_neighbour({j, d});
				}
			}
		}

		void print_distances() {
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

		void print_centers() {
			ofstream fout;
			fout.open("output.txt", ios::app);
			for (int i = 0; i < centers.size(); i++) {
				fout << centers[i].x << " " << centers[i].y << " 0\n";
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
			for (int i = 0; i < distanses.size(); i += step) {
				if (i + dX >= distanses.size()) {
					dist = distanses[i];
					return dist;
				}
				double dY = distanses[i + dX] - distanses[i];
				double der = dY/dX;
				if (der >= DERIVATIVE) {
					dist = distanses[i];
					return dist;
				}
			}
			return dist;
		}

		void connect_points(double dist) {
			int CLASTER_NUM = 1;

			//определяем и соеденяем основные точки
			for (int i = 0; i < mas.size(); i++) {
				if (mas[i].used) continue;
				mas[i].used = true;
				if (mas[i].latest(4) <= dist) { // основная точка
					dfs(i, CLASTER_NUM, dist);
					CLASTER_NUM++;
				}
			}

			//добавляем пограничные точки
			for (int i = 0; i < mas.size(); i++) {
				if (!mas[i].type) {
					for (int j = 0; j < 4; j++) {
						pair <int, double> neighbour = mas[i].neighbours[j];
						if (neighbour.sec > dist) {
							break;
						}
						if (mas[neighbour.fir].latest(4) <= dist) {
							cout << "insert borderline point: ";
							mas[i].show();
							mas[i].type = mas[neighbour.fir].type;
							break;
						}
					}
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

		void make_centers(int num) {
			centers.resize(num);
			for (int i = 0; i < num; i++) {
				Point a(0, 500, 0, 500);
				centers[i] = a;
			}
			for (auto i : centers) {
				cout << "random center: ";
				i.show();
			}
			for (int k = 1; k <= 100; k++) {
				for (int i = 0; i < mas.size(); i++) {
					mas[i].dist_to_center = 1e9;
					for (int j = 0; j < centers.size(); j++) {
						if (distAB(mas[i], centers[j]) < mas[i].dist_to_center) {
							mas[i].dist_to_center = distAB(mas[i], centers[j]);
							mas[i].type = j + 1;
						}
					}
					centers[mas[i].type - 1].lenX += mas[i].x;
					centers[mas[i].type - 1].lenY += mas[i].y;
					centers[mas[i].type - 1].qX++;
					centers[mas[i].type - 1].qY++;
				}
				if (k == 10) continue;
				for (int i = 0; i < num; i++) {
					centers[i].x = centers[i].lenX / centers[i].qX;
					centers[i].y = centers[i].lenY / centers[i].qY;
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
			while (fin >> x) {
				fin >> y;
				Point p(x, y);
				points.pb(p);
			}
			fin.close();
		}

		void show() {
			for (auto i : points) {
				i.show();
			}
		}

		void fill(double min_x, double max_x, double min_y, double max_y, int color) {
			ofstream fout;
			fout.open("data_dbscan.txt", ios::app);
			
			for (int i = 0; i < DENSITY; i++) {
				double x, y;
				x = randDouble(min_x, max_x);
				y = randDouble(min_y, max_y);;
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
				cout << "Press 3 to find clasters with dbscan\n";
				cout << "Press 4 to find claster with k-means\n";
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
						fout << randDouble(0.0, 500.0) << " ";
						fout << randDouble(0.0, 500.0) << " ";
						fout << color << "\n";
					}
					fout.close();
				} 
				else if (t == '2') {
					int color = 50;
					for (int i = 0; i < files.size(); i++) {
						Shell a;
						a.get(files[i]);
						a.fill(0, 500, 0, 500, color);
						Shells.pb(a);
						color -= 10;
					}
				} 
				else if (t == '3') {
					string file = copy_points_from("data_dbscan.txt");
					SetPoints s;
					s.scan(file);
					s.fill_neighbours();
					double dist = s.find_optimal_dist();
					s.connect_points(dist);
					s.print_distances();
					s.print_answer();
				} 
				else if (t == '4') {
					cout << "Enter how many clasters do you want to find\n";
					int num;
					cin >> num;
					string file = copy_points_from("data_dbscan.txt");
					SetPoints s;
					s.scan(file);
					s.make_centers(num);
					s.print_answer();
					s.print_centers();
				}
				else if (t == '9') {
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

double randDouble(double min, double max) {
	return min + (max - min) * (double)(abs(rand()) % RAND_MAX) / RAND_MAX;
}

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