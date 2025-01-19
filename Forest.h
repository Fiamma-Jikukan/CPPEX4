#ifndef FOREST_H
#define FOREST_H
#include "Cell.h"

#include "FixedWingDrone.h"
#include "MultiRotorDrone.h"
#include "SingleRotorDrone.h"#include "TDVector.h"
#include "BinarySearchTree.h"
#include <fstream>



class Forest {
private:
    TDVector minSize;
    TDVector maxSize;
    Cell **cells;
    BinarySearchTree<Drone*> drones;
    unsigned int maxNumOfIter;
    TDVector globalBest; // the possition of the drone that is closest to the target
    TDVector target;
    bool ended; // indicates if the target was reached
    string outputFileName;


public:
    Forest( const TDVector &min, const TDVector &max, const BinarySearchTree<Drone*> &drones, unsigned int max_num_of_iter,
           const TDVector &global_best, const TDVector &target, bool ended, const string &outputFileName);

    ~Forest();

    void FreeData() ;

    Forest(const Forest &other);

    Forest(Forest &&other) noexcept;

    Forest &operator=(const Forest &other);

    Forest &operator=(Forest &&other) noexcept;

    unsigned int operator()(unsigned int x, unsigned int y) const;

    void AddDroneToCell(const TDVector &coordinates) const;

    void RemoveDroneFromCell(const TDVector &coordinates) const;

    TDVector GetMinSize() const;

    TDVector GetMaxSize() const;

    void PrintTree() const;

    void PrintNode( Node<Drone*> * root) const;

    void StartSearch();

    void AdvanceDrones(Node<Drone*> *root);

    void EndSearch(unsigned int numOfIterations) const;

    void EndSearchHelper(ofstream &output, Node<Drone*> *node) const;

    Cell GetTargetCell() const;

    static double FormatNumber(double number);

    friend std::ostream &operator<<(std::ostream &os, const Forest &forest);
};


#endif //FOREST_H
