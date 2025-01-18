#ifndef DRONE_H
#define DRONE_H

#include "Cell.h"
#include "TDVector.h"

using namespace std;


class Drone {
private:
    unsigned int id;
    TDVector position;
    TDVector velocity;
    TDVector personalBest;
    bool globalBest;

public:
    Drone();

    Drone(unsigned int id, const TDVector &position, const TDVector &velocity, const TDVector &personalBest);

    virtual ~Drone();

    Drone(const Drone &other);

    Drone &operator=(const Drone &other);

    Drone(Drone &&other) noexcept;

    Drone &operator=(Drone &&other) noexcept;


    unsigned int GetId() const;

    TDVector GetPosition() const;

    void SetPosition(const TDVector &position);

    TDVector GetVelocity() const;

    void SetVelocity(const TDVector &velocity);

    TDVector GetPersonalBest() const;

    void SetPersonalBest(const TDVector &personalBest);

    Cell GetCurrentCell() const;

    void MoveDrone(const TDVector &globalBest, const TDVector &forestMin, const TDVector &forestMax);

    virtual void UpdateSpeed(const TDVector &globalBest, const TDVector &oldPosition, const TDVector &oldVelocity);

    double GetDistanceFromTarget(const TDVector &target) const;

    bool operator<(const Drone &other) const;

    bool operator>(const Drone &other) const;

    bool operator==(const Drone &other) const;

    bool operator!=(const Drone &other) const;

    friend ostream &operator<<(ostream &os, const Drone &drone) {
        os << "Drone ID: " << drone.GetId() << " currently at position: " << drone.GetPosition() << " at velocity: " <<
                drone.GetVelocity() << endl;
        return os;
    }
};


#endif //DRONE_H
