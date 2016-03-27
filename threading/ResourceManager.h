#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <mutex>

template<class T> class ResourceManager {
public:
	/// creates an instance of ResourceManager object that manages given resource
	/// the resource must be created with the new keyword and will be deleted upon
	/// deleting the manager
	ResourceManager(T* res);
	~ResourceManager();
	/// returns and locks the resource if unused
	/// else waits for release
	/// release() should be called after work with resource is finished
	T* get();
	/// releases resource and allows other threads to use it
	/// resource mustn't be used after releasing it without calling get()
	void release();
private:
	std::mutex lock;
	T* resource;
};

#endif