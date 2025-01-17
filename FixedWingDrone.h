#ifndef FIXEDWINGDRONE_H
#define FIXEDWINGDRONE_H
#include "Drone.h"

class FixedWingDrone: virtual public Drone {
    public:
    FixedWingDrone(unsigned int id, const TDVector &position, const TDVector &velocity, const TDVector &personalBest);
    ~FixedWingDrone() override;
    void UpdateSpeed(const TDVector &globalBest, const TDVector &oldPosition, const TDVector &oldVelocity) override;

};

#endif //FIXEDWINGDRONE_H
