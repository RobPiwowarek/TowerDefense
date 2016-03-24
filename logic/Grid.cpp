#include "Grid.h"
#include <cmath>

tower_defense::Grid::Grid(int width, int height) {
	this->width = width;
	this->height = height;

	this->elements = new GridElement**[width];
	for (int i = 0; i < width; i++) {
		this->elements[i] = new GridElement*[height];
		for (int j = 0; j < height; j++) {
			this->elements[i][j] = new GridElement(Point(i, j));
		}
	}

}

tower_defense::Grid::~Grid() {

	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->height; j++) {
			delete this->elements[i][j];
		}
		delete[] this->elements[i];
	}
	delete[] this->elements;
}

int tower_defense::Grid::getWidth() const {
	return this->width;
}

int tower_defense::Grid::getHeight() const {
	return this->height;
}

tower_defense::GridElement& tower_defense::Grid::getElement(const Point& p) {
	int x = p.getX() == this->width ? this->width - 1 : (int)floor(p.getX());
	int y = p.getY() == this->height ? this->height - 1 : (int)floor(p.getY());
	return *this->elements[x][y];
}