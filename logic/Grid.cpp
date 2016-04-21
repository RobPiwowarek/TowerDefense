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

void tower_defense::Grid::calculateDistance() {

    /// 1. set values to -1 (can't access)
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->elements[i][j]->setDistToTarget(-1);
            this->elements[i][j]->setDistToTurret(-1);
        }
    }

    /// 2. setting initial node for items
    std::priority_queue<std::pair<int, GridElement *>> initialNodes;

    for (Item *item: this->map.getItems()) {
        initialNodes.push(std::make_pair(0, this->getElement(item->getLocation())));
        this->getElement(item->getLocation())->setDistToTarget(0);
    }
    //for (std::iterator i = this->map.getItems().begin(); i < this->map.getItems().end());

    /// 3. start checking nodes
    while (!initialNodes.empty()) {
        std::pair<int, GridElement *> node = initialNodes.top();
		initialNodes.pop();

        GridElement* up = node.second->getUpNeighbour();
        GridElement* down = node.second->getDownNeighbour();
        GridElement* left = node.second->getLeftNeighbour();
        GridElement* right = node.second->getRightNeighbour();

        if (up != nullptr) {
            if (up->getDistToTarget() == -1 && !(up->hasTurret())) {

            }
        }

        if (down != nullptr) {
            if (down->getDistToTarget() == -1 && !(down->hasTurret())) {

            }
        }

        if (left != nullptr) {
            if (left->getDistToTarget() == -1 && !(left->hasTurret())) {

            }
        }

        if (right != nullptr) {
            if (right->getDistToTarget() == -1 && !(right->hasTurret())) {

            }
        }

    }


}

tower_defense::GridElement *tower_defense::Grid::getElement(const Point &p) const {
    int x = p.getX() == this->width ? this->width - 1 : (int) floor(p.getX());
    int y = p.getY() == this->height ? this->height - 1 : (int) floor(p.getY());
    this->elements[x][y];

    if (x >= this->width || y >= this->height) return nullptr;

    return this->elements[x][y];
}