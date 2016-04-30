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

void tower_defense::Grid::calcDistItems(std::priority_queue<std::pair<int, GridElement *>> &initialNodes) {
    for (tower_defense::Item *item: this->map.getItems()) {
        initialNodes.push(std::make_pair(0, this->getElement(item->getLocation())));
        this->getElement(item->getLocation())->setDistToTarget(0);
    }
}

void tower_defense::Grid::calcDistTurrets(std::priority_queue<std::pair<int, GridElement *>> &initialNodes) {
    for (tower_defense::Turret *turret: this->map.getTurrets()) {
        initialNodes.push(std::make_pair(0, this->getElement(turret->getLocation())));
        this->getElement(turret->getLocation())->setDistToTurret(0);
    }
}

void tower_defense::Grid::calculateDistance(const Target target) {
/// 1. set values to -1 (can't access)
    for (int i = 0; i < this->width; i++) {
        for (int j = 0; j < this->height; j++) {
            this->elements[i][j]->setDistToTarget(-1);
            this->elements[i][j]->setDistToTurret(-1);
        }
    }

    /// 2. setting initial node for items
    std::priority_queue<std::pair<int, GridElement *>> initialNodes;

    if (target == Turret) {
        this->calcDistTurrets(initialNodes);
    }
    else
        this->calcDistItems(initialNodes);

    /// 3. start checking nodes
    while (!initialNodes.empty()) {
        std::pair<int, GridElement *> node = initialNodes.top();
        initialNodes.pop();

        GridElement *up = node.second->getUpNeighbour();
        GridElement *down = node.second->getDownNeighbour();
        GridElement *left = node.second->getLeftNeighbour();
        GridElement *right = node.second->getRightNeighbour();

        if (up != nullptr) {
            if (target == Turret) { /// todo: necessary check?
                if (up->getDistToTurret() == -1 && !(up->hasTurret())) {
                    up->setDistToTurret(node.first + 1);
                    initialNodes.push(std::make_pair(node.first + 1, up));
                }
            }
            else {
                if (up->getDistToTarget() == -1 && !(up->hasTurret())) {
                    up->setDistToTarget(node.first + 1);
                    initialNodes.push(std::make_pair(node.first + 1, up));
                }
            }
        }

        if (down != nullptr) {
            if (target == Turret) {
                if (down->getDistToTurret() == -1 && !(down->hasTurret())) {
                    down->setDistToTurret(node.first + 1);
                    initialNodes.push(std::make_pair(node.first + 1, down));
                }
            }
            else {
                if (down->getDistToTarget() == -1 && !(down->hasTurret())) {
                    down->setDistToTarget(node.first + 1);
                    initialNodes.push(std::make_pair(node.first + 1, down));
                }
            }
        }

        if (left != nullptr) {
            if (target == Turret) {
                if (left->getDistToTurret() == -1 && !(left->hasTurret())) {
                    left->setDistToTurret(node.first + 1);
                    initialNodes.push(std::make_pair(node.first + 1, left));
                }
            }
            else {
                if (left->getDistToTarget() == -1 && !(left->hasTurret())) {
                    left->setDistToTarget(node.first + 1);
                    initialNodes.push(std::make_pair(node.first + 1, left));
                }
            }
        }

        if (right != nullptr) {

            if (target == Turret) {
                if (right->getDistToTurret() == -1 && !(right->hasTurret())) {
                    right->setDistToTurret(node.first + 1);
                    initialNodes.push(std::make_pair(node.first + 1, right));
                }
            }
            else {
                if (right->getDistToTarget() == -1 && !(right->hasTurret())) {
                    right->setDistToTarget(node.first + 1);
                    initialNodes.push(std::make_pair(node.first + 1, right));
                }
            }
        }
    }
}

tower_defense::GridElement *tower_defense::Grid::getElement(const Point &p) const {
    int x = p.getX() == this->width ? this->width - 1 : (int) floor(p.getX());
    int y = p.getY() == this->height ? this->height - 1 : (int) floor(p.getY());

    if (x >= this->width || y >= this->height) return nullptr;

    return this->elements[x][y];
}