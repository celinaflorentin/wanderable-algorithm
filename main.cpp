// Wanderable takehome task #1: algorithm

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;


typedef struct {
	int id;
	double latitude; // y
	double longitude; // x
} coord;


// distance function for coordinates of a sphere taken from the haversine formula
// http://en.wikipedia.org/wiki/Haversine_formula
double distance(double in_lat, double in_long, double line_lat, double line_long) {
	const double pi = 3.141592653589793238463; // pi taken from http://www.geom.uiuc.edu/~huberty/math5337/groupe/digits.html
	const double radius = 6371; // radius of the earth in km; taken from http://en.wikipedia.org/wiki/Earth_radius

	// convert difference of lat/long into radians
	double lat_rad = (in_lat - line_lat) * pi / 180;
	double long_rad = (in_long - line_long) * pi /180;

	// calculate angles needed
	double angle1 = lat_rad / 2;
	double angle2 = in_lat * pi / 180;
	double angle3 = line_lat * pi / 180;
	double angle4 =  long_rad / 2;

	double radicand = pow(sin(angle1), 2) + ( cos(angle2) * cos(angle3) * pow(sin(angle4),2));

	double dist = asin(sqrt(radicand)) * 2 * radius;

	return(dist);
}


int main(int argc, const char * argv[]) {

	double in_lat, in_long;
	double line_lat, line_long;
	int line_id;
	vector

	cout << "Input latitude:" << endl;
	cin >> in_lat;
	cout << in_lat << endl;

	cout << "Input longitude:" << endl;
	cin >> in_long;
	cout << in_long << endl;

	// create input file stream using the given csv file
	ifstream input("item_locations.csv");
	// ifstream input("test.csv");
	string line;

	if (!input) {
		cout << "Error reading input file" << endl;
	}

	getline(input,line); // heading string; not needed
	// cout << line << endl;

	while (getline(input,line)) {

		stringstream ss(line);
		string s;

		int i = 0;
		while (getline(ss,s,',')) {

			// convert each delimited string into a double
			double n = atof(s.c_str());

			if (i == 0) { // first number is id
				line_id = n;
				i++;
			} 
			else if (i == 1) { // second number is latitude (y-value)
				line_lat = n;
				i++;
			}
			else { // third number is longitude (x-value)
				line_long = n;
				i = 0;
			}
			// coord c1 = {line_id,line_lat,line_long};
			// cout << setprecision(10) << c1.id << " " << c1.latitude << " " << c1.longitude << endl;				
		}

		// coord c = {line_id,line_lat,line_long};
		// cout << c.id << " " << c.latitude << " " << c.longitude << endl;
	}
	cout << setprecision(10) << line_lat << " " << line_long << endl;
	double dist1 = distance (in_lat, in_long, line_lat, line_long);
	cout << "distance:" << setprecision(10) << dist1 << endl;

	// coord c = {1,2,3};
	// cout << c.id << " " << c.latitude << " " << c.longitude << endl;
	
    return 0;
}

