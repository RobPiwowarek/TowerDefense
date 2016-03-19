#ifndef ENTITY_H
#define ENTITY_H

#include "Point.h"


namespace tower_defense
{
	/// class for basic entity,
	/// base for any game object
	class Entity
	{
	public:
		/// creates a new instance of Entity object,
		/// with given values
		Entity(const tower_defense::Point& location, const double angle, const double size, const int objClass);

		/// creates new instance of Entity object,
		/// being a copy of e
		Entity(const Entity& e);

		/// gets the direction of the entity
		double getAngle() const;
		/// sets the direction of the entity
		void setAngle(const double angle);

		/// gets the location of the entity
		tower_defense::Point getLocation() const;
		/// sets the location of the entity
		void setLocation(const tower_defense::Point& location);

		/// refreshes the entity, return whether it should be removed or not
		virtual bool refresh() = 0;

		/// gets size of the entity
		double getSize() const;

		/// gets square of the distance between this entity and the given
		double getSqDistance(const Entity* e) const;

		/// gets type of the entity
		int getObjClass() const;

	protected:
		tower_defense::Point location;
		double angle;
		double size;
		int objClass;
	};

}

#endif