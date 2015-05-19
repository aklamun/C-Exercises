// Approximate pi using a simple Monte Carlo method. Exercise from MIT Introduction to C++ open online course: http://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-096-introduction-to-c-january-iap-2011/

#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

double calculatePi(const int n) {
	srand(time(0)); // set the seed to the current time

	int inCircle = 0;

	for(int i=0; i<n; ++i) {
		double x = rand() / (double)RAND_MAX;
		double y = rand() / (double)RAND_MAX;
		if(sqrt(x*x + y*y) < 1) {
			inCircle += 1;
		}
	}

	// pi = 4 * (area/4) / radius&2; here radius^2 = 1 and a/4 = inCircle/n
	double pi = 4 * inCircle / (double)n;
	return pi;
}

int main() {
	char yn = 'n';
		while(yn != 'y') {
		cout << "Enter n: ";
		int n;
		cin >> n;
		cout << "\n" << calculatePi(n) << "\n";
		cout << "enter y to exit or n to continue: ";
		cin >> yn;
		if(yn != 'y') {
			cout << "\n";
		}
	}

}