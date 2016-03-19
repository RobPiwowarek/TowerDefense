#include "Path.h"


tower_defense::Path::Path(const double width, const std::vector<tower_defense::PathElement *> &elements) {
    this->width = width;
    this->elements = elements;
}

tower_defense::Path::~Path() {
    for (int i = 0; i < this->elements.size(); i++)
        delete this->elements[i];
}

double tower_defense::Path::getWidth() const {
    return this->width;
}

const tower_defense::PathElement *tower_defense::Path::getFirst() const {
    if (this->elements.size() > 0)
        return this->elements[0];
    return nullptr;
}

const tower_defense::PathElement *tower_defense::Path::getNext(const tower_defense::PathElement *current) const {
    if (this->elements.size() < current->getNInPath() || current == nullptr)
        return nullptr;
    return this->elements[current->getNInPath()];
}