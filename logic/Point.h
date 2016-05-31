#ifndef POINT_H
#define POINT_H

#include <string>

namespace tower_defense {

    ///the Point class, representing a point on the map
    class Point {
    public:
        /// creates a new instance of Point class,
        /// with coordintase (0, 0)
        Point();

        /// creates a new instance of Point class,
        /// with coordintase (x, y)
        Point(const double x, const double y);
		Point(const int x, const int y);

        /// creates a new instance of Point class,
        /// equal to the p
        Point(const Point &p);

        /// returns the x coordinate
        double getX() const;

        /// returns the y coordinate
        double getY() const;

        /// sets x coordinate
        void setX(double x);

        /// sets y coordinate
        void setY(double y);

		/// returns square distance between 2 points
		double getSquareDistance(const tower_defense::Point &p);

		/// prints (x, y) to standard output
		void print() const;

		/// returns string representation of point
		std::string toString() const;

        /// sets xy
        void setPoint(const Point &p);

		Point operator-(const Point &p) const;
		Point operator+(const Point &p) const;
		Point operator+(const double val) const;
		Point operator-(const double val) const;
		Point& operator+=(const Point &p);
		Point& operator-=(const Point &p);
		Point operator*(double i) const;
		Point operator/(double i) const;
		Point& operator*=(double i);
		Point& operator/=(double i);
    private:
        double x;
        double y;
    };

}

#endif