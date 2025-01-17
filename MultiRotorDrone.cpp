#include "MultiRotorDrone.h"

MultiRotorDrone::MultiRotorDrone(unsigned int id, const TDVector &position, const TDVector &velocity,
                                 const TDVector &personalBest): Drone(id, position, velocity, personalBest) {
}

MultiRotorDrone::~MultiRotorDrone() = default;

void MultiRotorDrone::UpdateSpeed(const TDVector &globalBest, const TDVector &oldPosition,
                                  const TDVector &oldVelocity) {
    const double r1 = (((double) rand()) / RAND_MAX);
    const double r2 = (((double) rand()) / RAND_MAX);
    constexpr double alpha = 0.05;
    constexpr double beta = 0.1;
    constexpr double gamma = 0;

    const TDVector personal = GetPersonalBest();

    const TDVector element1 = alpha * oldVelocity;
    const TDVector element2 = beta * r1 * (personal - oldPosition);
    const TDVector element3 = gamma * r2 * (globalBest - oldPosition);


    const TDVector new_speed = element1 + element2 + element3;
    SetVelocity(new_speed);
}
