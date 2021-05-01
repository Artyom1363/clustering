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


int positive_int(string s);
int check_in_set(string s, set <int> set_of_elems);


mt19937 _g(time(nullptr));

int randint(int a, int b) {
    int w = (_g() << 31LL) ^ _g(); 
    return a + abs(w) % (b - a + 1); 
}


int getInt(string message) {
	int num = 0;
	bool fl = false;
	while (true) {
		fl = false;
		try {
			cout << message;
			string s;
			cin >> s;
			num = stoi(s);
		}
		catch (...) {
			cout << "Your answere must be int, please try again\n";
			fl = true;
		}	
		if (!fl) {
			return num;
		}
	}
}


int check_in_set(string s, set <int> set_of_elems) {
	int res = positive_int(s);
	if (res == -1) return -1;
	int start = set_of_elems.size();
	set_of_elems.insert(res);
	//cout << "yes\n";
	if (set_of_elems.size() > start) {
		return -1;
	}
	return res;
}

int positive_int(string s) {
	for (auto i : s) {
		if (!(i >= '0' && i <= '9')) {
			return -1;
		}
	}
	int res = 0;
	for (int i = 0; i < s.size(); ++i) {
		res *= 10;
		res += s[i] - '0';
	}
	return res;
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


class Cloud{
public:
	int X_center, Y_center;
	vector <Point> vect_of_points;
	
	Cloud() {
		X_center = 0;
		Y_center = 0;
	}

	vector <Point> getPoints() {
		int size, height, weight;
		cout << "Enter how many points will be in cloud\n"; cin >> size;
		cout << "Enter height of cloud\n"; cin >> height;
		cout << "Enter weight of cloud\n"; cin >> weight;
		cout << "Enter x coordinate of center of cloud\n"; cin >> X_center;
		cout << "Enter y coordinate of conter of cloud\n"; cin >> Y_center;
		genPoints(size, height, weight);
		move();
		turn();
		return vect_of_points;
	}

private:
	void genPoints(int size, int height, int weight) {

		std::default_random_engine generator;

	  	//first param is mean, second is standart diviation
	  	std::normal_distribution<double> distributionX(0.0, weight/2.0);
	  	std::normal_distribution<double> distributionY(0.0, height/2.0);

	  	for (int i = 0; i < size; ++i) {
	    	double x = distributionX(generator);
	    	double y = distributionY(generator);
	    	Point p(x + X_center, y + Y_center);
	    	vect_of_points.pb(p);
	    }

	}

	void move() {
		int x_bias, y_bias;
		cout << "Enter bias x (more 0 means to right, less than 0 means to left)\n";
		cin >> x_bias;
		cout << "Enter bias y (more 0 means to upper, less than 0 means to down)\n";
		cin >> y_bias;
		for (auto &i : vect_of_points) {
			i.x += x_bias;
			i.y += y_bias;
		}
		cout << "Your cloud moved\n";

	}
	void turn() {
		double radians;
		cout << "Enter degree in radians to move\n";
		cin >> radians;
		for (auto &i : vect_of_points) {
			double x = i.x * cos(radians) - i.y * sin(radians);
			double y = i.x * sin(radians) + i.y * cos(radians);
			i.x = x;
			i.y = y;
		}
	}

};

//field
class SetPoints{
	public:
		vector <Point> mas;
		//vector <vector <Point>> matr_dist;
		vector <pair<double, pair<int, int>>> ribs;

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

		void makeRandomPoints() {
			int size, left, right, upper, down;
			cout << "Enter how many points do you want\n"; cin >> size;
			cout << "Enter left positions\n"; cin >> left;
			cout << "Enter right position\n"; cin >> right;
			cout << "Enter upper position\n"; cin >> upper;
			cout << "Enter down position\n"; cin >> down;
			for (int i = 0; i < size; ++i) {
				Point point;
				point.x = randDouble(left, right);
				point.y = randDouble(down, upper);
				mas.push_back(point);
			}
		}


		void genSetPoints() {

			Cloud cloud;
			vector <Point> points_from_new_cloud;
			points_from_new_cloud = cloud.getPoints();

			for (auto i : points_from_new_cloud) {
				mas.push_back(i);
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


		void print_answer(string file = "output.txt") {

			ofstream fout;
			fout.open(file);

			//debug
			
			for (int i = 0; i < mas.size(); i++) {
				fout << mas[i].x << " " << mas[i].y << " ";
				fout << mas[i].type * 10 << "\n";
			}
			fout.close();

			//debug
			cout << "answere is situated in " << file << "\n\n\n";
		}

		
		void hierarchy() {
			//matr_dist.resize(mas.size());
			/*for (int i = 0; i < matr_dist.size(); i++) {
				matr_dist[i].resize(matr_dist.size());
			}*/
			cout << "yes" << endl;
			for (int i = 0; i < mas.size(); i++) {
				for (int j = i + 1; j < mas.size(); j++) {
					ribs.pb({distAB(mas[i], mas[j]), {i, j}});
				}
			}
			sort(ribs.begin(), ribs.end());
			ofstream fout;
			fout.open("hier_dist.txt");
			for (int i = 0; i < ribs.size(); i++) {
				fout << i + 1 << " " << ribs[i].fir << endl;
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


class Kmeans{
public:
	void makeClasters(SetPoints &set) {
		int num;
		cout << "Enter how many clasters do you want to find\n"; cin >> num;


		make_centers(set, num);


		//make result file
		string file = "data_Kmeans.txt";
		set.print_answer(file);

	}

private:
	void make_centers(SetPoints &set, int num) {
		vector <Point> centers(num);
		for (int i = 0; i < num; i++) {
			Point a(0, 500, 0, 500);
			centers[i] = a;
		}
		for (auto i : centers) {
			cout << "random center: ";
			i.show();
		}
		for (int k = 1; k <= 100; k++) {
			for (int i = 0; i < set.mas.size(); i++) {
				set.mas[i].dist_to_center = 1e9;
				for (int j = 0; j < centers.size(); j++) {
					if (distAB(set.mas[i], centers[j]) < set.mas[i].dist_to_center) {
						set.mas[i].dist_to_center = distAB(set.mas[i], centers[j]);
						set.mas[i].type = j + 1;
					}
				}
				centers[set.mas[i].type - 1].lenX += set.mas[i].x;
				centers[set.mas[i].type - 1].lenY += set.mas[i].y;
				centers[set.mas[i].type - 1].qX++;
				centers[set.mas[i].type - 1].qY++;
			}
			if (k == 10) continue;
			for (int i = 0; i < num; i++) {
				centers[i].x = centers[i].lenX / centers[i].qX;
				centers[i].y = centers[i].lenY / centers[i].qY;
			}	
		}
	}
};


class Dbscan{  
public:
	void makeClasters(SetPoints &set) {

		fill_neighbours(set);

		//find optimal dist
		double dist = find_optimal_dist(set);

		//connects poitns to clasters
		connect_points(set, dist);

		//make result file
		string file = "data_dbscan.txt";
		set.print_answer(file);
	}

private:
	void fill_neighbours(SetPoints &set) {
		for (int i = 0; i < set.mas.size(); i++) {
			for (int j = 0; j < set.mas.size(); j++) {
				if (i == j) continue;
				double d = distAB(set.mas[i], set.mas[j]);
				set.mas[i].insert_neighbour({j, d});
			}
		}
	}

	void connect_points(SetPoints &set, double dist) {
		int CLASTER_NUM = 1;

		//определяем и соеденяем основные точки
		for (int i = 0; i < set.mas.size(); i++) {
			if (set.mas[i].used) continue;
			set.mas[i].used = true;
			if (set.mas[i].latest(4) <= dist) { // основная точка
				dfs(set, i, CLASTER_NUM, dist);
				CLASTER_NUM++;
			}
		}

		//добавляем пограничные точки
		for (int i = 0; i < set.mas.size(); i++) {
			if (!set.mas[i].type) {
				for (int j = 0; j < 4; j++) {
					pair <int, double> neighbour = set.mas[i].neighbours[j];
					if (neighbour.sec > dist) {
						break;
					}
					if (set.mas[neighbour.fir].latest(4) <= dist) {
						cout << "insert borderline point: ";
						set.mas[i].show();
						set.mas[i].type = set.mas[neighbour.fir].type;
						break;
					}
				}
			}
		}
	}

	void dfs(SetPoints &set, int num, int col, double dist) {
		set.mas[num].used = true;
		if (set.mas[num].latest(4) > dist) {
			return;
		}
		set.mas[num].type = col;
		for (int i = 0; i < set.mas.size(); i++) {
			if (set.mas[i].used) continue;
			if (distAB(set.mas[num], set.mas[i]) <= dist) {
				dfs(set, i, col, dist);
			}
		}
	}

	double find_optimal_dist(SetPoints &set) {
		vector <double> distanses(set.mas.size());

		for (int i = 0; i < distanses.size(); i++) {
			distanses[i] = set.mas[i].latest(4);
		}

		sort(distanses.begin(), distanses.end());
		int dX = distanses.size() / 50;
		int step = max(1, (int)(distanses.size() / 100));
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
};


class Menu{
public:
	SetPoints s;
	void start() {
		vector <Shell> Shells;

		//clean file
		ofstream fout;
		fout.open("data_dbscan.txt");
		fout.close();

		cout << "To see the result you must set this settings to console:\n";
		cout << "gnuplot\nset xrange [-200:200]\nset yrange [-200:200]\n";
		//cout << "set title "set palette defined ( 20 \"#101010\", 30 \"#ff0000\", 40 \"#00ff00\", 50 \"#e0e0e0\" )""

		while(1) {

			cout << "Press 1 to generate n random points\n";
			cout << "Press 2 to make cloud of points\n";
			cout << "Press 3 to find clasters with dbscan\n";
			cout << "Press 4 to find claster with k-means\n";
			cout << "Press 5 to find claster with hierarchy\n";
			cout << "Press 9 to exit\n";


			char t;
			cin >> t;
			if (t == '1') {

				s.makeRandomPoints();

			}
			else if (t == '2') {

				s.genSetPoints();

			}
			else if (t == '3') {

				Dbscan db;
				db.makeClasters(s);

			}
			else if (t == '4') {

				Kmeans km;
				km.makeClasters(s);
				
			}
			else if (t == '5') {
				string file = copy_points_from("data_dbscan.txt");
				SetPoints s;
				s.scan(file);
				s.hierarchy();
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