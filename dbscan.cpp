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

//g++ -std=c++11 task.cpp

*/
#include <bits/stdc++.h>
#define sec second
#define fir first

const int INF = 1e9;

using namespace std;
//почему нельзя задать размер вектора в классе

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
bool comp(Point a, Point b) {
	return a.latest(4) < b.latest(4);
}
int dist(Point a, Point b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
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
	SetPoints s;
	s.scan(file);
	s.fill_neighbors();
	s.sorting();
	s.print();
	return 0;
}