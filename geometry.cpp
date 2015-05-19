// Create a class structure to represent basic geometric shapes. Exercise from MIT Introduction to C++ open online course: http://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-096-introduction-to-c-january-iap-2011/

#include <cmath>
#include <iostream>
#include "stdafx.h"
#include "geometry.h"

using namespace std;

PointArray::PointArray() {
	size = 0;
	points = new Point[0];
}

PointArray::PointArray(const Point ptsToCopy[], const int toCopySize) {
	size = toCopySize;
	points = new Point[toCopySize];
	for(int i = 0; i < toCopySize; ++i) {
		points[i] = ptsToCopy[i];
	}
}

PointArray::PointArray(const PointArray &other) {
	size = other.size;
	points = new Point[size];
	for (int i = 0; i < size; i++) {
		points[i] = other.points[i];
	}
}

PointArray::~PointArray() {
	delete[] points;
}

void PointArray:: resize(int newSize) {
	Point *pts = new Point[newSize];
	int minSize = (newSize > size ? size : newSize);
	for (int i = 0; i < minSize; i++)
		pts[i] = points[i];
	delete[] points;
	size = newSize;
	points = pts;
}

void PointArray::push_back(const Point &p) {
	resize(size + 1);
	points[size - 1] = p;
}

void PointArray::insert(const int pos, const Point &p) {
	resize(size + 1);
	for (int i = size - 1; i > pos; i--) {
		points[i] = points[i-1];
	}
	points[pos] = p;
}

void PointArray::remove(const int pos) {
	if(pos >= 0 && pos < size) {
		for(int i = pos; i < size - 2; i++) {
			points[i] = points[i+1];
		}
		resize(size-1);
	}
}

void PointArray::clear() {
	resize(0);
}

Point *PointArray::get(const int pos) {
	return pos >= 0 && pos < size ? points + pos : NULL;
}

const Point *PointArray::get(const int pos) const {
	return pos >= 0 && pos < size ? points + pos : NULL;
}


int Polygon::numPolygons = 0;

Polygon::Polygon(const Point pointArr[], const int numPoints) : points(pointArr, numPoints) {
	++numPolygons;
}

Polygon::Polygon(const PointArray &pa) {
	++numPolygons;
}

Point constructorPoints[4];

Point *updateConstructorPoints(const Point &p1, const Point &p2, const Point &p3, const Point &p4 = Point(0,0)) {
	constructorPoints[0] = p1;
	constructorPoints[1] = p2;
	constructorPoints[2] = p3;
	constructorPoints[3] = p4;
	return constructorPoints;
}

Rectangle::Rectangle(const Point &ll, const Point &ur) : Polygon(updateConstructorPoints(ll, Point(ll.getX(), ur.getY()), ur, Point(ur.getX(), ll.getY())), 4) {}

Rectangle::Rectangle(const int llx, const int lly, const int urx, const int ury) : Polygon(updateConstructorPoints(Point(llx, lly), Point(llx, ury), Point(urx, ury), Point(urx, lly)), 4) {}

double Rectangle::area() const {
	int length = points.get(1)->getY() - points.get(0)->getY();
	int width = points.get(2)->getX() - points.get(1)->getX();
	return abs((double)length*width);
}


Triangle::Triangle(const Point &a, const Point &b, const Point &c) : Polygon(updateConstructorPoints(a,b,c),3) {}

double Triangle::area() const {
	double dx01 = points.get(0)->getX() - points.get(1)->getX(),
		dx12 = points.get(1)->getX() - points.get(2)->getX(),
		dx20 = points.get(2)->getX() - points.get(0)->getX();
	double dy01 = points.get(0)->getY() - points.get(1)->getY(),
		dy12 = points.get(1)->getY() - points.get(2)->getY(),
		dy20 = points.get(2)->getY() - points.get(0)->getY();

	double a = sqrt(dx01*dx01 + dy01*dy01),
		b = sqrt(dx12*dx12 + dy12*dy12),
		c = sqrt(dx20*dx20 + dy20*dy20);

	double s = (a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}


void printAttributes(Polygon *p) {
	cout << "p's area is " << p->area() << ".\n";

	cout << "p's points are:\n";
	const PointArray *pa = p->getPoints();
	for(int i = 0; i < pa->getSize(); ++i) {
		cout << "(" << pa->get(i)->getX() << ", " << pa->get(i)->getY() << ")\n";
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Enter lower left and upper right coords of rectangle as four space separated integers: ";
	int llx, lly, urx, ury;
	cin >> llx >> lly >> urx >> ury;
	Point ll(llx, lly), ur(urx, ury);
	Rectangle r(ll, ur);
	printAttributes(&r);

	cout << "Enter three coords of triangle as six space separated integers: ";
	int x1, y1, x2, y2, x3, y3;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	Point a(x1, y1), b(x2, y2), c(x3, y3);
	Triangle t(a, b, c);
	printAttributes(&t);
	return 0;
}

