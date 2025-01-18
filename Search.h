#ifndef SEARCH_H
#define SEARCH_H

#include <fstream>
#include "Drone.h"
#include "Forest.h"


class Search {
private:
    unsigned int maxNumOfIter;
    Forest forest;
    TDVector globalBest; // the possition of the drone that is closest to the target
    TDVector target;
    bool ended; // indicates if the target was reached
    string outputFileName;

public:
    Search(unsigned int max_num_of_iter, Forest &forest,
           TDVector &global_best, const TDVector &target, bool ended, const string &outputFileName);


    ~Search();

    Search(const Search &other);

    Search(Search &&other) noexcept;

    Search &operator=(const Search &other);

    Search &operator=(Search &&other) noexcept;

    void StartSearch();

    void AdvanceDrones(Node<Drone> *root, TDVector &max, TDVector &min);

    void EndSearch(unsigned int numOfIterations) const;

    void EndSearchHelper(ofstream &output, Node<Drone> *node) const;

    void UpdateDrone(Drone &drone, unsigned int index);

    void OldUpdateSpeed(Drone &drone, const TDVector &oldPosition) const;

    unsigned int GetGlobalBest() const;

    TDVector GetTarget();

    void UpdateGlobalBest(unsigned int newGlobalBest);

    Cell GetTargetCell() const;

    unsigned int GetNumOfDrones() const;

    static double FormatNumber(double number);


};


#endif //SEARCH_H
