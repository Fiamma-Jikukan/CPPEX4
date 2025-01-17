#ifndef FOREST_H
#define FOREST_H
#include "Cell.h"
#include "Drone.h"
#include "TDVector.h"




class Forest {
private:
    Cell **cells;
    unsigned int numOfDrones;
    Drone *drones;


public:
    Forest(Drone *drones, unsigned int numOfDrones);

    ~Forest();

    void FreeData() const;

    Forest(const Forest &other);

    Forest(Forest &&other) noexcept;

    Forest & operator=(const Forest &other);

    Forest & operator=(Forest &&other) noexcept;

    unsigned int operator()(unsigned int x, unsigned int y) const;

    void AddDroneToCell(const TDVector& coordinates) const;

    void RemoveDroneFromCell(const TDVector& coordinates) const;

    Drone * GetDrones() const;

    unsigned int GetNumOfDrones() const;

    Drone GetGlobalBestDrone(unsigned int globalBest) const;

};


#endif //FOREST_H
