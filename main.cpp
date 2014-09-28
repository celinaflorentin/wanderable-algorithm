// Wanderable takehome task #1: algorithm

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;


typedef struct {
	int id;
	double latitude; // y
	double longitude; // x
	double dist;
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


// remove a point from the coordinate vector given a specified distance value
void replace_coord(double dist, coord c, vector<coord> &coords) {
	for (vector<coord>::iterator i = coords.begin(); i != coords.end(); i++) {
		double distance = i->dist;
		if (distance == dist) {
			// replace old coord with new coord
			cout << "no more id " << i->id << " | added id " << c.id << endl;
			i->id = c.id;
			i->latitude = c.latitude;
			i->longitude = c.longitude;
			i->dist = c.dist;
		}
	}
}


int main(int argc, const char * argv[]) {
	int items = 0;
	double in_lat, in_long, line_lat, line_long;
	int line_id;

	// keep track of number of coordinates closest to point currently
	// only keep top 10
	int closest_count = 0;

	// store all coordinates in a vector
	vector<coord> coordinates;

	// keep track of maximum of the closest points so far. 0 at first
	double max_closest = 0; 

	cout << "Input latitude:" << endl;
	cin >> in_lat;

	cout << "Input longitude:" << endl;
	cin >> in_long;

	// create input file stream using the given csv file
	ifstream input("item_locations.csv");
	// ifstream input("test.csv");
	string line;

	if (!input) {
		cout << "Error reading input file" << endl;
	}

	getline(input,line); // heading string; not needed

	while (getline(input,line)) {
		items++;
		// cout << line << endl;
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
		}

		// compute the distance and create coord struct
		double dist = distance (in_lat, in_long, line_lat, line_long);

		// if this is the first point, add it to the vector
		if (closest_count == 0) {
			max_closest = dist;
			closest_count++;
			coord c = {line_id,line_lat,line_long,dist};
			coordinates.push_back(c);
		}
		// automatically add coordinate into vector if closest count < 10
		else if (closest_count < 10) {
			max_closest = max(max_closest, dist);
			closest_count++;
			coord c = {line_id,line_lat,line_long,dist};
			coordinates.push_back(c);
		}
		// if closest count >= 10, only add coordinate into vector if dist < max_closest
		else {
			if (dist < max_closest) {
				// we are replacing the currect max_closest vector, so no need to increment closest_count
				coord c = {line_id,line_lat,line_long,dist};
				cout << "about to replace dist " << max_closest << " with " << c.dist << endl; 
				replace_coord(max_closest, c, coordinates);
				max_closest = dist;

			}		
		}
		
		// cout << setprecision(10) << in_lat << " " << in_long << " " << c.id << " " << c.latitude << " " << c.longitude << " " << c.dist << endl;
		// cout << endl;

	}

	for (vector<coord>::iterator i = coordinates.begin(); i != coordinates.end(); i++) {
		// double distance = i->dist;
		// cout << distance << endl;
		cout << i->id << endl;
	}
	cout << "total items parsed: " << items << endl;
	cout << setprecision(10) << "total stuff in vector: " << closest_count << endl;
	cout << setprecision(10) << "max of the closest: " << max_closest << endl;
    return 0;
}

