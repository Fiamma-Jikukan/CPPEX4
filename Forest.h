#ifndef FOREST_H
#define FOREST_H
#include "Cell.h"
#include "Drone.h"
#include "TDVector.h"
#include "BinarySearchTree.h"


class Forest {
private:
    Cell **cells;
    unsigned int numOfDrones;
    BinarySearchTree<Drone> drones;
    Drone *globalBestDrone;

public:
    Forest(const BinarySearchTree<Drone> &drones, unsigned int numOfDrones, Drone *globalBestDrone);

    ~Forest();

    void FreeData() const;

    Forest(const Forest &other);

    Forest(Forest &&other) noexcept;

    Forest &operator=(const Forest &other);

    Forest &operator=(Forest &&other) noexcept;

    unsigned int operator()(unsigned int x, unsigned int y) const;

    void AddDroneToCell(const TDVector &coordinates) const;

    void RemoveDroneFromCell(const TDVector &coordinates) const;

    BinarySearchTree<Drone> GetDrones() const;

    unsigned int GetNumOfDrones() const;

    Drone *GetGlobalBestDrone() const;

    void SetGlobalBestDrone(Drone *drone);
};


#endif //FOREST_H
