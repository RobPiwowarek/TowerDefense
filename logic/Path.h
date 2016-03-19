#ifndef PATH_H
#define PATH_H

#include <vector>

#include "PathElement.h"
#include "Entity.h"

namespace tower_defense
{
	/// represents a path on the map 
	/// for the PathFollower
	class Path
	{
	public:
		/// creates Path object with given values
		/// assuming that pointers refer to
		/// elements created using 'new' operator
		Path(const double width, const std::vector<PathElement*>& elements);
		~Path();

		/// returns width of the path
		double getWidth() const;

		/// returns ponter to first element int the path
		const PathElement* getFirst() const;

		/// returns pointer to the element following the current
		const PathElement* getNext(const PathElement* current) const;

		/// returns square distance from path to the entity
		double getSqDistance(const Entity* e) const;

	private:
		double width;
		std::vector<PathElement*> elements;
	};
}

#endif