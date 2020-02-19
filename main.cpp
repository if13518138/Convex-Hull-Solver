#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <time.h>
#include "./matplotlib-cpp/matplotlibcpp.h"
namespace plt = matplotlibcpp;
using namespace std;

// Author : William / 13518138

/************* Data Struktur **************/

/*************************************************************************************
* Point Data Structure                                                               *
* => Data Struktur buatan untuk membantu penyimpanan data bentuk point               *
* Selektor :                                                                         *
* getAxis : mengembalikan nilai x suatu titik                                   *
* getOrdinat : mengembalikan nilai y suatu titik                                *
* Fungsi lainnya:                                                                    *
* printPoint : mengembalikan string representasi (x,y) point                    *
* isEq : mengembalikan true apabila kedua point terletak pada x dan y yang sama *
*************************************************************************************/
class Point
{
	public:
		Point(int x1, int y1);
		/* Properti Kelas Point */
		int x;
		int y;

		/* Selektor */
		int getAxis(void){
			return x;
		}
		int getOrdinat(void){
			return y;
		}

		/* Fungsi - fungsi lainnya */
		string printPoint(void){
			return "(" + to_string(x) + "," + to_string(y) + ")";
		}
		bool isEq(Point p2) {
			return (x == p2.x && y == p2.y);
		}
};
/*Konstruktor Pembentuk Objek Point*/
Point::Point(int x1, int y1) {
	x = x1;
	y = y1;
}

/********* Fungsi - fungsi Utama **********/

/*******************************************************************************
* Fungsi linier_equation                                                       *
* > Mengembalikan sifat suatu titik terhadap garis yang dibentuk 2 titik.      *
*     0: terletak di garis                                                     *
*     1: diatas garis / positif                                                *
*     2: dibawah garis / negatif                                               *
* > Proses ini dilakukan dengan membandingkan titik dan garis dengan persamaan *
*     ax + by = c                                                              *
*     dengan a = y2 - y1;b = x1 - x2;c = x1y2 - y1x2                           *
*******************************************************************************/
int linier_equation(Point p1, Point p2, Point p3){
	int a = p2.getOrdinat() - p1.getOrdinat();		// definisi a
	int b = p1.getAxis() - p2.getAxis();			// definisi b
	int c = p1.getAxis() * p2.getOrdinat() - p1.getOrdinat() * p2.getAxis(); // definisi c
	if (a * p3.getAxis() + b * p3.getOrdinat() == c) return 0;	// ax + by = c
	if (a * p3.getAxis() + b * p3.getOrdinat() > c) return 1;	// ax + by > c
	if (a * p3.getAxis() + b * p3.getOrdinat() < c) return 2;	// ax + by < c
}

bool isMember(vector<Point> vec, Point p){
	/* Mengembalikan nilai true apabila p (Point) terdapat pada vec */
	for (int i = 0; i < vec.size(); i++){
		if (vec[i].isEq(p)) {return true;}
	}
	return false;
}

/******************************************************************************************************************
* Fungsi getConvexHull                                                                                            *
* Merupakan fungsi yang digunakan untuk mencari seluruh titik berkait yang merupakan titik pembentuk convex hull. *
* Metode: Brute - Force dengan Exhaustive Search                                                                  *
* Algoritma :                                                                                                     *
*   1. Melakukan pencarian titik awal sebanyak n-1 kali (dari titik awal sampai titik kedua terakhir)             *
*   2. Kemudian cari titik lagi agar dapat dapat ditarik garis dari titik awal ke titik tersebut                  *
*   3. Selanjutnya, proses traversal dilakukan ke seluruh titik yang ada pada convex                              *
*   4. Apabila seluruh titik yang ada pada convex terletak hanya di salah satu bidang dari titik                  *
* (mis: di bagian positif), maka kedua titik adalah titik pembentuk convex hull                                   *
*   5. Proses pencarian terus dilakukan hingga n-1 titik                                                          *
******************************************************************************************************************/
vector<Point> getConvexHull(vector<Point> pointHolder){
	vector<Point> convexHull = {};
	int count_pos;
	int count_neg;
	int count_netral;
	for (int i = 0; i < pointHolder.size() - 1; i++){
		Point point1 = pointHolder[i];
		for(int j = i+1; j < pointHolder.size(); j++){
			count_pos = 0; count_neg = 0;
			Point point2 = pointHolder[j];
			for (int k = 0; k < pointHolder.size(); k++){
				Point point3 = pointHolder[k];
				if (linier_equation(point1,point2,point3) == 0){count_netral++;}
				else if (linier_equation(point1,point2,point3) == 1) {count_pos++;}
				else {count_neg++;}
			}
			if (count_pos == 0 || count_neg == 0) {
				if (!isMember(convexHull,point1)){convexHull.push_back(point1);}
				if (!isMember(convexHull,point2)){convexHull.push_back(point2);}
			}
		}
	}
	return convexHull;
}

/***********************************************************************************************************************
* Fungsi sortedConvexHull                                                                                              *
* Merupakan fungsi yang digunakan untuk mencari urutan dari titik-titik pembentuk convex hull                          *
* Prekondisi : Telah dilakukan proses pencarian titik pembentuk convex hull                                            *
* Metode: Brute - Force dengan Exhaustive Search                                                                       *
* Algoritma :                                                                                                          *
*   1. Dilakukan pencarian dengan memakai salah satu titik dari kumpulan titik pembentuk convex hull                   *
*   2. Pasangan titik berikutnya dipilih dari kumpulan titik tersebut                                                  *
*   3. Selanjutnya, traversal ke seluruh titik pada convex                                                             *
*   4. Apabila seluruh titik hanya terdapat pada suatu bagian bidang dari garis, maka kedua titik tersebut berpasangan *
*   5. Simpan kedua titik sebagai suatu pasangan, kemudian mulai cari lagi pasangan titik yang dipilih terakhir.       *
*   6. Ulangi langkah sampai semua titik telah terpasang                                                               *
***********************************************************************************************************************/
vector<Point> sortedConvexHull(vector<Point> convexHull, vector<Point> pointHolder){
	int count_pos;
	int count_neg;
	int count_netral;
	vector<Point> sortedPoint = {};
	Point first = convexHull[0];
	Point curr = convexHull[0];
	sortedPoint.push_back(curr);
	convexHull.erase(convexHull.begin() + 0);

	while(convexHull.size() > 0) {
		for (int i = 0; i < convexHull.size(); i++){
			Point curr2 = convexHull[i];
			count_pos = 0; count_neg = 0;
			for (int j = 0; j < pointHolder.size(); j++){
				Point p3 = pointHolder[j];
				if (linier_equation(curr,curr2,p3) == 0){count_netral++;}
				else if (linier_equation(curr,curr2,p3) == 1) {count_pos++;}
				else {count_neg++;}
			}
			if (count_pos == 0 || count_neg == 0) {
				sortedPoint.push_back(curr2);
				curr = curr2;
				convexHull.erase(convexHull.begin() + i);
				break;
			}
		}
	}

	if (pointHolder.size() > 2) {sortedPoint.push_back(sortedPoint[0]);} 
	return sortedPoint;
}

/******* Fungsi - fungsi Tambahan  ********/

void printListPoint(vector<Point> listPoint){
	/* Prosedur penulisan seluruh Point yang terdapat pada suatu Vector Of Point */
	for (int i = 0; i < listPoint.size(); i++){
		cout << "P"<< i + 1 << " : " <<listPoint[i].printPoint() << endl;
	}
}

void printResListPoint(vector<Point> convexHull){
	/* Prosedur untuk menampilkan list yang telah tersusun yang menunjukkan convex hull terhadap suatu himpunan titik */
	cout << "[ ";
	for (int i = 0; i < convexHull.size() - 1; i++){
		cout << convexHull[i].printPoint() << " --> ";
	}
	cout << convexHull[convexHull.size() - 1].printPoint();
	cout << " ]" << endl;
}

vector<Point> generateRandom(int n, int max){
	/* Fungsi untuk menghasilkan suatu kumpulan titik unique sebanyak n buah dengan nilai x dan y maksimum sebasar maks */
	vector<Point> pointHolder = {};
	srand(time(0));
	int x,y;
	int i = 0;
	while (i < n){
		x = rand() % max; y = rand() % max;
		Point point(x,y); 
		if (!isMember(pointHolder,point)){
			pointHolder.push_back(point);
			i++;
		}
	}
	return pointHolder;
}

vector<Point> createConvex(int n,vector<int> x_vec, vector<int> y_vec){
	/* Fungsi untuk membuat kumpulan Point dari nilai x dan y yang telah ditentukan sebelumnya sebanyak n buah */
	/* Digunakan dalam pembuatan Test Case */
	vector<Point> vec;
	int i = 0;
	int x,y;
	while(i < n) {
		x = x_vec[i]; y = y_vec[i];
		Point point(x,y);
		vec.push_back(point);
		i++; 
	}
	return vec;
}

/********************************************************************************
* Prosedur draw                                                                 *
* Merupakan suatu prosedur yang mempermudah proses ilustrasi gambar convex hull *
* Legenda :                                                                     *
*  x : titik                                                                    *
*  o : titik ekstrem / titik penghubung dalam convex hull                       *
********************************************************************************/
void draw (vector<Point> pointHolder, vector<Point> convexHull){
	char plot[100][100];
	for (int i = 0; i < 100; i++){
		for (int j = 0; j<100; j++){
			plot[i][j] = '-';
		}
	}
	cout << "================================================================================================" << endl;
	cout << "Command - Line Plotting :" << endl;
	for(int i = 0; i < pointHolder.size(); i++){
		plot[99-pointHolder[i].getOrdinat()][pointHolder[i].getAxis()] = 'x';
	}

	for (int i = 0; i < convexHull.size(); i++){
		plot[99-convexHull[i].getOrdinat()][convexHull[i].getAxis()] = 'o';
	}
	cout << endl;
	for (int i = 1; i < 100 + 1; i++){
		if (i < 10) {cout << "  " << i << " |";}
		else if (i < 100) {cout << " " << i << " |";}
		else {cout << i << " |";}
		for (int j = 0; j < 100; j++){
			cout << plot[i-1][j];
		}
		cout << endl;
	}
	cout << endl;
	cout << "Legends : " << endl;
	cout << " -> x : point" << endl;
	cout << " -> o : point that create convex hull" << endl;
}

/********************************************************************************
* Prosedur draw Matplotlib                                                      *
* Merupakan suatu prosedur yang mempermudah proses ilustrasi gambar convex hull *
* dengan menggunakan modul Matplotlib	                                        *					   						                        *
********************************************************************************/
void drawMatplotlib(vector<Point> point_vec, vector<Point> res_vec){
	vector<int> x_vec = {}; vector<int> y_vec = {};
	vector<int> x_vec_res = {}; vector<int> y_vec_res = {};
	for(int i = 0; i < point_vec.size(); i++){
		x_vec.push_back(point_vec[i].getAxis());
		y_vec.push_back(point_vec[i].getOrdinat());
	}

	for(int i = 0; i < res_vec.size(); i++){
		x_vec_res.push_back(res_vec[i].getAxis());
		y_vec_res.push_back(res_vec[i].getOrdinat());
	}
	plt::scatter(x_vec,y_vec,50,{{"color","aqua"},{"marker","o"}});
	plt::plot(x_vec_res,y_vec_res,"or-");
	plt::title("Convex Hull Solution\nby William");
	plt::xlabel("X-Axis");
	plt::ylabel("Y-Axis");
	plt::xlim(0,1000);
	plt::ylim(0,1000);
	cout << "Showing the image : " << endl;
	plt::show();
	cout << "Program Ended..." << endl;

}

/************** Main Program **************/
int main(){
	/* Inisialisasi Nilai Konfigurasi Program */
	int max,n;
	max = 1000;
	clock_t t;
	vector<Point> pointHolder;
	vector<Point> convexHull;
	bool use_test_case = false; // pengecekan dengan test case atau tidak
	
	/*********** Kumpulan Test Case ***********/
	// Test Case 1
	vector<int> x_vec1 = {35,65,36,30,15};
	vector<int> y_vec1 = {29,32,21,45,49};
	int n_test1 = 5;
	// Test Case 2
	vector<int> x_vec2 = {2,5,6,5,1};
	vector<int> y_vec2 = {6,3,3,7,9};
	int n_test2 = 5;
	// Test Case 3
	vector<int> x_vec3 = {57,53,26,57,53};
	vector<int> y_vec3 = {72,72,19,19,26};
	int n_test3 = 5;
	/*********** End Kumpulan Test Case ***********/

	if (!use_test_case){
		cout << "Input a number : ";
		cin >> n;
	}
	if (use_test_case) {pointHolder = createConvex(n_test1,x_vec1,y_vec1);}
	else {pointHolder = generateRandom(n, max);}	// randomize jika tidak pakai test case
	
	cout << "List of Point Generated: " << endl;
	printListPoint(pointHolder);
	t = clock(); // start counting timer
	convexHull = sortedConvexHull(getConvexHull(pointHolder),pointHolder);	// Finding the convex Hull
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
	cout << "Time taken to find the sorted convex hull :" << time_taken << " seconds" << endl; // output timer

	cout << "List of Point to create Convex Hull :" << endl;printResListPoint(convexHull);
	// Gambar Hasil Pada Command Line Interface (CLI) // draw(pointHolder,convexHull);
	// Gambar Hasil Dengan Modul Matplotlib 
	drawMatplotlib(pointHolder,convexHull);
	return 0;
}