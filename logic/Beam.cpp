#include "Beam.h"

tower_defense::Beam::Beam(const int damage, const double maxSize, const int fireClass)
        : WeaponFire(damage, maxSize, 1, beam, fireClass) {
    this->hitOnlyFirst = hitOnlyFirst;
}

tower_defense::Beam::Beam(const Beam &base, const double angleModifier)
        : WeaponFire(base, angleModifier) {
    this->hitOnlyFirst = base.hitOnlyFirst;
}

tower_defense::Beam::Beam(const Beam &base, const Point &location, const double angle)
        : WeaponFire(base, location, angle) {
    this->hitOnlyFirst = base.hitOnlyFirst;
}

/// returns if beam hits only first target in line
bool tower_defense::Beam::isHitOnlyFirst() const {
    return this->hitOnlyFirst;
}