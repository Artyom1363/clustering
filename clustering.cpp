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


int getInt(int min, int max = 1000000) {
	int num = 0;
	bool fl = false;
	while (true) {
		fl = false;
		try {
			string s;
			cin >> s;
			num = stoi(s);
			if (num < min || num > max) {
				throw 1;
			}
		}
		catch (...) {
			cout << "Your answere must be 'int' and belong: [" << min << ", " << max << "]\n";
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
	int qX = 0, qY = 0, type = 0;
	double x, y, dist_to_center = MAX_DOUBLE;


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
		fout.open(file, ios_base::app);
		fout << x << " " << y << endl;
		fout.close();
		
	}

};

class PointDbscan: public Point{
public: 
	int quantity;
	bool used = false;
	vector <pair<double, int>> neighbours;


	PointDbscan(int x, int y, int q) : Point(x, y), quantity(q) {}


	double latest() {
		return neighbours[quantity - 1].fir;
	}

	void processNeighbours() {
		sort(neighbours.begin(), neighbours.end());
		neighbours.resize(quantity);
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
		cout << "Enter how many points will be in cloud\n"; size = getInt(1, 10000);
		cout << "Enter height of cloud\n"; height = getInt(1, 1000);
		cout << "Enter weight of cloud\n"; weight = getInt(1, 1000);
		cout << "Enter x coordinate of center of cloud\n"; X_center = getInt(-10000, 10000);
		cout << "Enter y coordinate of center of cloud\n"; Y_center = getInt(-10000, 10000);
		genPoints(size, height, weight);
		move();
		turn();
		turn2(X_center, Y_center);
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
		x_bias = getInt(-10000, 10000);
		cout << "Enter bias y (more 0 means to upper, less than 0 means to down)\n";
		y_bias = getInt(-10000, 10000);
		for (auto &i : vect_of_points) {
			i.x += x_bias;
			i.y += y_bias;
		}
		cout << "Your cloud moved\n";

	}
	void turn() {
		double radians, degrees;
		cout << "Enter degree in degrees to move\n";
		degrees = getInt(-360, 360);
		radians = (degrees / 180.0) * M_PI; 
		for (auto &i : vect_of_points) {
			double x = i.x * cos(radians) - i.y * sin(radians);
			double y = i.x * sin(radians) + i.y * cos(radians);
			i.x = x;
			i.y = y;
		}
	}


	void turn2(double x_center, double y_center) {
		double radians, degrees;
		cout << "Enter degree in degrees to move about himself\n";
		degrees = getInt(-360, 360);
		radians = (degrees / 180.0) * M_PI; 
		for (auto &i : vect_of_points) {
			double x = (i.x - x_center) * cos(radians) - (i.y - y_center) * sin(radians);
			double y = (i.x - x_center) * sin(radians) + (i.y - y_center) * cos(radians);
			i.x = x + x_center;
			i.y = y + y_center;
		}
	}

};

//field
class SetPoints{
public:
	vector <Point> mas;

	int size;

	void scanFromFile() {
		string file;
		cout << "Enter name of file to load data:\n";
		cin >> file;
		scan(file);
	}


	void printToFile() {
		string file;
		cout << "Enter name of file to write data:\n";
		cin >> file;
		print(file);
	}

	void makeRandomPoints() {
		int size, left, right, upper, down;
		cout << "Enter how many points do you want\n"; cin >> size;
		cout << "Enter left positions\n"; cin >> left;
		cout << "Enter right position\n"; cin >> right;
		cout << "Enter down position\n"; cin >> upper;
		cout << "Enter upper position\n"; cin >> down;

		//check left < right
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


	void print_answer(string file = "output.txt") {

		ofstream fout;
		fout.open(file);
		for (int i = 0; i < mas.size(); i++) {
			fout << mas[i].x << " " << mas[i].y << " ";
			fout << mas[i].type * 10 << "\n";
		}
		fout.close();


		cout << "answere is situated in " << file << "\n\n\n";
	}

private:
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

	void print(string file) {
		for (auto &i : mas) {
			i.show(file);
		}
	}

};


class Hierarchical{
public:
	void makeClasters(SetPoints &set) {
		int num;
		cout << "Enter how many clasters do you want to find\n"; cin >> num;


		UnitePoints(set, num);


		//make result file
		string file = "data_hier.txt";
		set.print_answer(file);
	}

private:
	vector <pair <int, pair <int, int> > > ribs;

	void UnitePoints(SetPoints &set, int num) {
		for (int i = 0; i < set.mas.size(); ++i) {
			for (int j = i + 1; j < set.mas.size(); ++j) {
				ribs.push_back({distAB(set.mas[i], set.mas[j]), {i, j}});
			}
		}
		sort(ribs.begin(), ribs.end());
		map <int, vector <int> > clasters;
		for (int i = 0; i < set.mas.size(); ++i) {
			set.mas[i].type = i + 1;
			clasters[i + 1].push_back(i);
		}
		int ptr = 0;
		while (clasters.size() > num) {
			if (ptr >= ribs.size()) {
				cout << "debug\n ptr >= ribs.size()\n";
				cout << "clasters.size(): " << clasters.size() << endl;
				exit(0);
			}
			pair <int, int> p = ribs[ptr].sec;
			++ptr;
			int type1 = set.mas[p.fir].type;
			int type2 = set.mas[p.sec].type;
			if (type1 == type2) continue;
			int size1 = clasters[type1].size();
			int size2 = clasters[type2].size();
			if (size1 > size2) {
				deleteClaster(set, clasters, type2, type1);
			} else {
				deleteClaster(set, clasters, type1, type2);
			}
		}
	}

	void deleteClaster(SetPoints &set, map <int, vector <int> > &clasters, int typeDel, int typeUnite) {
		for (auto i : clasters[typeDel]) {
			set.mas[i].type = typeUnite;
			clasters[typeUnite].push_back(i);
		}
		clasters.erase(typeDel);
	}
};


class Kmeans{
public:
	void makeClasters(SetPoints &set) {
		cout << "Enter how many clasters do you want to find\n"; 
		num = getInt(1);


		make_centers(set);


		//make result file
		string file = "data_Kmeans.txt";
		set.print_answer(file);

	}

private:
	int num;
	vector <Point> centers;
	void make_centers(SetPoints &set) {
		centers.resize(num);
		for (int i = 0; i < num; i++) {
			Point a(-500, 500, -500, 500);
			centers[i] = a;
		}
		/*for (auto i : centers) {
			cout << "random center: ";
			i.show();
		}*/
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
		double radius;
		cout << "Enter point search radius\n"; cin >> radius;
		cout << "Enter quantity of points in radius to consider main point\n";
		quantity = getInt(1, 100);

		//make new class based on point
		copyToNewFormat(set);

		//find nearest neighbours
		fill_neighbours();

		//connects poitns to clasters
		connect_points(radius);

		//transfer the resulting labels
		copyLabels(set);

		//make result file
		string file = "data_dbscan.txt";
		set.print_answer(file);

	}

private:

	int quantity;
	vector <PointDbscan> points;


	void copyToNewFormat(SetPoints &set) {
		for (auto i : set.mas) {
			PointDbscan p(i.x, i.y, quantity);
			points.push_back(p);
		}
	}


	void fill_neighbours() {
		for (int i = 0; i < points.size(); ++i) {
			for (int j = 0; j < points.size(); ++j) {
				if (i == j) continue;
				double d = distAB(points[i], points[j]);
				points[i].neighbours.push_back({d, j});
			}
			points[i].processNeighbours();
		}
	}


	void connect_points(double radius) {
		int CLASTER_NUM = 1;

		//определяем и соеденяем основные точки
		for (int i = 0; i < points.size(); i++) {
			if (points[i].used) continue;
			points[i].used = true;
			if (points[i].latest() <= radius) { // основная точка
				dfs(i, CLASTER_NUM, radius);
				++CLASTER_NUM;
			}
		}
		cout << "Quantity of clasters:\n" << CLASTER_NUM << endl;

		//добавляем пограничные точки
		for (int i = 0; i < points.size(); i++) {
			if (!points[i].type) {
				for (int j = 0; j < quantity; j++) {
					pair <double, int> neighbour = points[i].neighbours[j];
					if (neighbour.fir > radius) {
						break;
					}
					if (points[neighbour.sec].latest() <= radius) {
						points[i].type = points[neighbour.sec].type;
						break;
					}
				}
			}
		}
	}

	void dfs(int num, int col, double radius) {
		points[num].used = true;
		if (points[num].latest() > radius) {
			return;
		}
		points[num].type = col;
		for (int i = 0; i < points.size(); i++) {
			if (points[i].used) continue;
			if (distAB(points[num], points[i]) <= radius) {
				dfs(i, col, radius);
			}
		}
	}

	void copyLabels(SetPoints &set) {
		for (int i = 0; i < set.mas.size(); ++i) {
			set.mas[i].type = points[i].type;
		}
	}

};

 
class Menu{
public:
	SetPoints s;
	void start() {
		//vector <Shell> Shells;

		//clean file
		ofstream fout;
		fout.open("data_dbscan.txt");
		fout.close();
		cout << "\nSETTING TO VISUALISATION:\n";
		cout << "To see the result you must set this settings to console:\n";
		cout << "gnuplot\nset xrange [-200:200]\nset yrange [-200:200]\n\n\n";
		//cout << "set title "set palette defined ( 20 \"#101010\", 30 \"#ff0000\", 40 \"#00ff00\", 50 \"#e0e0e0\" )""

		while(1) {

			cout << "Press 1 to generate n random points\n";
			cout << "Press 2 to make cloud of points\n";
			cout << "Press 3 to find clasters with dbscan\n";
			cout << "Press 4 to find claster with k-means\n";
			cout << "Press 5 to find claster with hierarchy\n";
			cout << "Press 6 to load data from file\n";
			cout << "Press 7 to write all current clouds to file\n";
			cout << "Press 8 to exit\n";


			int user = getInt(1, 8);
			if (user == 1) {

				s.makeRandomPoints();

			}
			else if (user == 2) {

				s.genSetPoints();

			}
			else if (user == 3) {

				Dbscan db;
				db.makeClasters(s);

			}
			else if (user == 4) {

				Kmeans km;
				km.makeClasters(s);
				
			}
			else if (user == 5) {

				Hierarchical hr;
				hr.makeClasters(s);

			}
			else if (user == 6) {

				s.scanFromFile();

			} 
			else if (user == 7) {

				s.printToFile();

			}
			else if (user == 8) {
				break;
			}
		}
	}

};

double randDouble(double min, double max) {
	return min + (max - min) * (double)(abs(rand()) % RAND_MAX) / RAND_MAX;
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
