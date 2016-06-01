#include "Grid.h"
#include <cmath>

tower_defense::Grid::Grid(int width, int height, Map &m) : map(m) {
    this->width = width;
    this->height = height;

    this->elements = new GridElement **[width];
    for (int i = 0; i < width; i++) {
        this->elements[i] = new GridElement *[height];
        for (int j = 0; j < height; j++) {
            this->elements[i][j] = new GridElement(Point(i, j), *this);
        }
    }
}

inline double min(const double a, const double b) { return a > b ? b : a; }
inline double max(const double a, const double b) { return a > b ? a : b; }

std::set<tower_defense::GridElement*> tower_defense::Grid::getElementsInLine(const Point & startingPoint, const Point & endingPoint, const double width) const{
	if (startingPoint.getX() > endingPoint.getX()) return this->getElementsInLine(endingPoint, startingPoint);

	std::set<tower_defense::GridElement*> elements;
	for (int i = min(startingPoint.getX(), endingPoint.getX()) - width; i < max(startingPoint.getX(), endingPoint.getX()) + width; i++) {
		for (int j = min(startingPoint.getY(), endingPoint.getY()) - width; j < max(startingPoint.getY(), endingPoint.getY()) + width; j++) {
			if (inBounds(i, j))
				elements.insert(getElement(i, j));
		}
	}


	return elements;
}

bool tower_defense::Grid::inBounds(double x, double y)const {
	if (x > this->width - 1 || x < 0) return false; // x out of bounds
	else if (y > this->height - 1 || y < 0) return false; // y out of bounds
	else return true;
}

bool tower_defense::Grid::inBounds(int x, int y)const{
	if (x > this->width - 1 || x < 0) return false; // x out of bounds
	else if (y > this->height - 1 || y < 0) return false; // y out of bounds
	else return true;
}

std::set<tower_defense::GridElement*> tower_defense::Grid::getElementsInRadius(const Point & p, double radius) const{
	std::set<tower_defense::GridElement*> elements;

	for (int i = p.getY() - radius < 0 ? 0 : p.getY() - radius;
		i < p.getY() + radius && i < this->height; i++){
		for (int j = p.getX() - radius < 0 ? 0 : p.getX() - radius;
			j < p.getX() + radius && j < width; j++) {

			elements.insert(this->elements[j][i]);
		}
	}
	
	return elements;
}

std::set<tower_defense::GridElement*> tower_defense::Grid::getElementsInRadius(Minion * minion, double radius) const{
	return this->getElementsInRadius(minion->getLocation(), radius); 
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

void tower_defense::Grid::calcDistItems(_calcDistNodeQueue &initialNodes) {
    for (tower_defense::Item *item: this->map.getItems()) {
		if (!item->isHeld()) {
			initialNodes.push(std::make_pair(0, this->getElement(item->getLocation())));
			this->getElement(item->getLocation())->setDistToTarget(0);
		}
    }
}

void tower_defense::Grid::calcDistEscapeCorners(_calcDistNodeQueue &initialNodes) {
	initialNodes.push(std::make_pair(0, this->getElement(0, 0)));
	this->getElement(0, 0)->setDistToCorner(0);
	initialNodes.push(std::make_pair(0, this->getElement(this->width-1, this->height-1)));
	this->getElement(this->width - 1, this->height - 1)->setDistToCorner(0);
	initialNodes.push(std::make_pair(0, this->getElement(0, this->height-1)));
	this->getElement(0, this->height - 1)->setDistToCorner(0);
	initialNodes.push(std::make_pair(0, this->getElement(this->width-1, 0)));
	this->getElement(this->width - 1, 0)->setDistToCorner(0);
}

void tower_defense::Grid::calcDistEscapeEdges(_calcDistNodeQueue &initialNodes) {
	for (int i = 0; i < this->width; i++){
		initialNodes.push(std::make_pair(0, this->getElement(i, 0)));
		this->getElement(i, 0)->setDistToEdge(0);
		initialNodes.push(std::make_pair(0, this->getElement(i, this->height-1)));
		this->getElement(i, this->height - 1)->setDistToEdge(0);
	}

	/// 1 i -2 bo rogi w teorii dodaja sie w petli wyzej?
	for (int i = 0; i < this->height-1; i++){
		initialNodes.push(std::make_pair(0, this->getElement(0, i)));
		this->getElement(0, i)->setDistToEdge(0);
		initialNodes.push(std::make_pair(0, this->getElement(this->width-1, i)));
		this->getElement(this->width - 1, i)->setDistToEdge(0);
	}
}

void tower_defense::Grid::calcDistTurrets(_calcDistNodeQueue &initialNodes) {
    for (tower_defense::Turret *turret: this->map.getTurrets()) {
        initialNodes.push(std::make_pair(0, this->getElement(turret->getLocation())));
        this->getElement(turret->getLocation())->setDistToTurret(0);
    }
}

inline void tower_defense::Grid::calculateDistance_checkNeighbour(const tower_defense::Grid::Target target,
	tower_defense::GridElement* neighbour,
	_calcDistNode& node,
	_calcDistNodeQueue& nodes) {
	if (neighbour != nullptr) {
		if (target == Turret) { 
			if (neighbour->getDistToTurret() == -1 && !(neighbour->hasTurret())) {
				neighbour->setDistToTurret(node.first + 1);
				nodes.push(std::make_pair(node.first + 1, neighbour));
			}
		}
		else if (target == Item){
			if (neighbour->getDistToTarget() == -1 && !(neighbour->hasTurret())) {
				neighbour->setDistToTarget(node.first + 1);
				nodes.push(std::make_pair(node.first + 1, neighbour));
			}
		}
		else if (target == Escape){
			if (neighbour->getDistToCorner() == -1 && !(neighbour->hasTurret())){
				neighbour->setDistToCorner(node.first + 1);
				nodes.push(std::make_pair(node.first + 1, neighbour));
			}
		}
	}

}
#include <iostream>
void tower_defense::Grid::calculateDistance(const Target target) {
/// 1. set values to -1 (can't access)
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
			if (target == Item)
				this->elements[i][j]->setDistToTarget(-1);
			else if (target == Turret)
				this->elements[i][j]->setDistToTurret(-1);
			else if (target == Escape)
				this->elements[i][j]->setDistToCorner(-1);
        }
    }

    /// 2. setting initial node for items
	_calcDistNodeQueue initialNodes;

    if (target == Turret) {
        this->calcDistTurrets(initialNodes);
    }
	else if (target == Item)
		this->calcDistItems(initialNodes);
	else if (target == Escape)
		this->calcDistEscapeCorners(initialNodes);

    /// 3. start checking nodes
    while (!initialNodes.empty()) {
        _calcDistNode node = initialNodes.top();
		initialNodes.pop();

        GridElement *up = node.second->getUpNeighbour();
        GridElement *down = node.second->getDownNeighbour();
        GridElement *left = node.second->getLeftNeighbour();
        GridElement *right = node.second->getRightNeighbour();

		calculateDistance_checkNeighbour(target, up, node, initialNodes);
		calculateDistance_checkNeighbour(target, down, node, initialNodes);
		calculateDistance_checkNeighbour(target, left, node, initialNodes);
		calculateDistance_checkNeighbour(target, right, node, initialNodes);
    }
}

tower_defense::GridElement *tower_defense::Grid::getElement(const double xx, const double yy) const{
	int x = floor(xx);
	int y = floor(yy);

	if (x >= this->width || y >= this->height || x < 0 || y < 0) return nullptr;

	return this->elements[x][y];
}

tower_defense::GridElement *tower_defense::Grid::getElement(const Point &p) const {
    int x = floor(p.getX());
    int y = floor(p.getY());

    if (x >= this->width || y >= this->height || x < 0 || y < 0) return nullptr;

    return this->elements[x][y];
}

std::set<tower_defense::GridElement*> tower_defense::Grid::getOccupied(const tower_defense::Entity & entity) {
	return this->getOccupied(entity, entity.getLocation());
}
std::set<tower_defense::GridElement*> tower_defense::Grid::getOccupied(const tower_defense::Entity & entity, const Point& p) {
	std::set<GridElement*> toRet;
	for (int i = 0; i < entity.getSize(); i++) {
		for (int j = 0; j < entity.getSize(); j++) {
			tower_defense::Point temp = p - (Point(entity.getSize(), entity.getSize()) / 2) + Point(i, j);
			toRet.insert(this->getElement(temp));
		}
	}

	return toRet;
}

std::set<tower_defense::GridElement*> tower_defense::Grid::getOccupied(
	const tower_defense::Entity & entity, const double x, const double y) {
	std::set<GridElement*> toRet;
	for (int i = 0; i < entity.getSize(); i++) {
		for (int j = 0; j < entity.getSize(); j++) {
			double tempX = x - entity.getSize() / 2 + i;
			double tempY = y - entity.getSize() / 2 + j;
			toRet.insert(this->getElement(tempX, tempY));
		}
	}

	return toRet;
}