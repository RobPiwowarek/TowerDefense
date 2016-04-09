#ifndef POINT_H
#define POINT_H

namespace tower_defense {

    ///the Point class, representing a point on the map
    class Point 
	{
    public:
        /// creates a new instance of Point class,
        /// with coordintase (0, 0)
        Point();

        /// creates a new instance of Point class,
        /// with coordintase (x, y)
        Point(const double x, const double y);

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

        /// sets xy
        void setPoint(const Point &p);

    private:
        double x;
        double y;
    };

}

#endif