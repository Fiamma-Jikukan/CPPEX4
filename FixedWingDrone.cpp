#include "FixedWingDrone.h"

FixedWingDrone::FixedWingDrone(const unsigned int id, const TDVector &position, const TDVector &velocity,
                               const TDVector &personalBest): Drone(id, position, velocity, personalBest) {
}

FixedWingDrone::~FixedWingDrone() = default;

void FixedWingDrone::UpdateSpeed(const TDVector &globalBest, const TDVector &oldPosition, const TDVector &oldVelocity) {
    const double r1 = (((double) rand()) / RAND_MAX);
    const double r2 = (((double) rand()) / RAND_MAX);
    constexpr double alpha = 0.25;
    constexpr double beta = 1;
    constexpr double gamma = 1;

    const TDVector personal = GetPersonalBest();

    const TDVector element1 = alpha * oldVelocity;
    const TDVector element2 = beta * r1 * (personal - oldPosition);
    const TDVector element3 = gamma * r2 * (globalBest - oldPosition);


    const TDVector new_speed = element1 + element2 + element3;
    SetVelocity(new_speed);
}
