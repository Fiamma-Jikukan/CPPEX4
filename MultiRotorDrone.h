#ifndef MULTIROTORDRONE_H
#define MULTIROTORDRONE_H
#include "Drone.h"


class MultiRotorDrone final : public Drone {
public:
    MultiRotorDrone(unsigned int id, const TDVector &position, const TDVector &velocity, const TDVector &personalBest);

    ~MultiRotorDrone();

    void UpdateSpeed(const TDVector &globalBest, const TDVector &oldPosition, const TDVector &oldVelocity) override;
};


#endif //MULTIROTORDRONE_H
