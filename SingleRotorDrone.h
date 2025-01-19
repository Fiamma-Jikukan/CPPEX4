#ifndef SINGLEROTORDRONE_H
#define SINGLEROTORDRONE_H

#include "Drone.h"

class SingleRotorDrone : virtual public Drone {
public:
    SingleRotorDrone(unsigned int id, const TDVector &position, const TDVector &velocity, const TDVector &personalBest);
    ~SingleRotorDrone() override;

    void UpdateSpeed(const TDVector &globalBest, const TDVector &oldPosition, const TDVector &oldVelocity) override;


};


#endif //SINGLEROTORDRONE_H
