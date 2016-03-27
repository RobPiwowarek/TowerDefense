#include "ResourceManager.h"

ResourceManager<class T>::ResourceManager(T* res) {
	this->resource = res;
}

ResourceManager<class T>::~ResourceManager() {
	delete this->resource;
}

T* ResourceManager<class T>::get() {
	lock.lock();
	return this->resource;
}

void ResourceManager<class T>::release() {
	lock.unlock();
}