#ifndef SINGLEROTORDRONE_H
#define SINGLEROTORDRONE_H

#include "Drone.h"

class SingleRotorDrone : virtual public Drone {
public:
    SingleRotorDrone(unsigned int id, const TDVector &position, const TDVector &velocity, const TDVector &personalBest);
    ~SingleRotorDrone() override;

    void UpdateSpeed(const TDVector &globalBest, const TDVector &oldPosition, const TDVector &oldVelocity) override;
    void MoveDrone(const TDVector &globalBest, const TDVector &forestMin, const TDVector &forestMax);
    friend ostream &operator<<(ostream &os, const SingleRotorDrone &drone) {
        os << "S Drone ID: " << drone.GetId() << " currently at position: " << drone.GetPosition() << " at velocity: " <<
                drone.GetVelocity() << endl;
        return os;
    }

};


#endif //SINGLEROTORDRONE_H
