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

std::set<tower_defense::GridElement*> tower_defense::Grid::getElementsInRadius(const Point & p, double radius) {
	std::set<tower_defense::GridElement*> elements;

	for (int i = p.getY() - radius; i < p.getY() + radius; i++){
		for (int j = p.getX() - radius; i < p.getX() + radius; i++){
			int x = j == this->width ? this->width - 1 : (int)floor(j);
			int y = i == this->height ? this->height - 1 : (int)floor(i);

			if (x >= this->width || y >= this->height) continue;

			elements.insert(this->elements[x][y]);
		}
	}
	
	return elements;
}

std::set<tower_defense::GridElement*> tower_defense::Grid::getElementsInRadius(Minion * minion, double radius){
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
        initialNodes.push(std::make_pair(0, this->getElement(item->getLocation())));
        this->getElement(item->getLocation())->setDistToTarget(0);
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
		if (target == Turret) { /// todo: necessary check?
			if (neighbour->getDistToTurret() == -1 && !(neighbour->hasTurret())) {
				neighbour->setDistToTurret(node.first + 1);
				nodes.push(std::make_pair(node.first + 1, neighbour));
			}
		}
		else {
			if (neighbour->getDistToTarget() == -1 && !(neighbour->hasTurret())) {
				neighbour->setDistToTarget(node.first + 1);
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
			else
				this->elements[i][j]->setDistToTurret(-1);
        }
    }

    /// 2. setting initial node for items
	_calcDistNodeQueue initialNodes;

    if (target == Turret) {
        this->calcDistTurrets(initialNodes);
    }
    else
        this->calcDistItems(initialNodes);

    /// 3. start checking nodes
    while (!initialNodes.empty()) {
        _calcDistNode node = initialNodes.top();
		initialNodes.pop();
		//std::cout << "n" << node.first;

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

tower_defense::GridElement *tower_defense::Grid::getElement(const Point &p) const {
    int x = floor(p.getX());
    int y = floor(p.getY());

    if (x >= this->width || y >= this->height || x < 0 || y < 0) return nullptr;

    return this->elements[x][y];
}