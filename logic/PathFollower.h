#ifndef PATH_FOLLOWER
#define PATH_FOLLOWER

#include "Path.h"

namespace tower_defense
{
	/// class reperesenting an entity that follows a path
	class  PathFollower : public Entity
	{
	public:
		/// creates a new (unrefreshable!) PathFollower instance with given values
		PathFollower(const double velocity, const double size, const int objClass);
		/// creates a new PathFollower instance, that begins at the beginning of the current path
		PathFollower(const PathFollower& p, const Path* path);

		/// refreshes the object,
		/// returns whether it should be removed (reached the end of the path)
		bool refresh();

	private:
		double velocity;
		const Path* path;
		const PathElement* curElement;
	};
}

#endif