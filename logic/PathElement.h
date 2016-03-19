#ifndef PATH_ELEMENT_H
#define PATH_ELEMENT_H

#include "Point.h"
#include "Entity.h"

namespace tower_defense
{
	
	/// class reperesenting a single, basic piece of a Path object
	class PathElement
	{
	public:
		/// creates new instance of PathElement
		/// using given values
		PathElement(const int nInPath, const tower_defense::Point& translation, const tower_defense::Point& x0);

		/// returns angle of the element translation
		double getAngle() const;

		/// returns number of this element in the path
		int getNInPath() const;

		/// returns starting point of this element
		const Point& getX0() const;

		/// returns translation at this element
		const Point& getTranslation() const;

		/// returns square of the distance from this element to the entity
		int getSqDistance(const Entity& e) const;

	private:
		int nInPath;
		Point x0;
		Point translation;
	};

}

#endif