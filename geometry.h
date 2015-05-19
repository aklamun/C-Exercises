class Point {
private:
	int x, y;
public:
	Point(int xx = 0, int yy = 0) {x = xx; y = yy;}
	int getX() const {return x;}
	int getY() const {return y;}
	void setX(const int xx) {x = xx;}
	void setY(const int yy) {y = yy;}
};

class PointArray {
private:
	int size;
	Point *points;

	void resize(int size);

public:
	PointArray();
	PointArray(const Point pts[], const int size);
	PointArray(const PointArray &pv);
	~PointArray();

	void push_back(const Point &p);
	void insert(const int position, const Point &p);
	void remove(const int pos);
	int getSize() const {return size;}
	void clear();
	Point * get(const int position);
	const Point * get(const int position) const;
};

class Polygon {
protected:
	static int numPolygons;
	PointArray points;

public:
	Polygon(const Point points[], const int numPoints);
	Polygon(const PointArray &pa);
	~Polygon() {--numPolygons;}
	virtual double area() const = 0;
	static int getNumPolygons() {return numPolygons;}
	int getNumSides() const {return points.getSize();}
	const PointArray *getPoints() const {return &points;}
};

class Rectangle : public Polygon {
public:
	Rectangle(const Point &a, const Point &b);
	Rectangle(const int a, const int b, const int c, const int d);
	virtual double area() const;
};

class Triangle : public Polygon {
public:
	Triangle(const Point &a, const Point &b, const Point &c);
	virtual double area() const;
};