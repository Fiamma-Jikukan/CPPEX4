#ifndef FOREST_H
#define FOREST_H
#include "Cell.h"
#include "Drone.h"
#include "TDVector.h"
#include "BinarySearchTree.h"


class Forest {
private:
    TDVector minSize;
    TDVector maxSize;
    Cell **cells;
    BinarySearchTree<Drone> drones;


public:
    Forest( const TDVector &min, const TDVector &max, const BinarySearchTree<Drone> &drones);

    ~Forest();

    void FreeData() ;

    Forest(const Forest &other);

    Forest(Forest &&other) noexcept;

    Forest &operator=(const Forest &other);

    Forest &operator=(Forest &&other) noexcept;

    unsigned int operator()(unsigned int x, unsigned int y) const;

    void AddDroneToCell(const TDVector &coordinates) const;

    void RemoveDroneFromCell(const TDVector &coordinates) const;

    BinarySearchTree<Drone> GetDrones() const;

    TDVector GetMinSize() const;

    TDVector GetMaxSize() const;

    void PrintTree() const;
    void PrintNode( Node<Drone> * root) const;

    friend std::ostream &operator<<(std::ostream &os, const Forest &forest);
};


#endif //FOREST_H
