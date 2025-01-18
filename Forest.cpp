#include "Forest.h"

Forest::Forest(const BinarySearchTree<Drone> &drones, const unsigned int numOfDrones, const TDVector &min,
               const TDVector &max): numOfDrones(numOfDrones), drones(drones),
                                     minSize(min), maxSize(max) {
    const unsigned int x_range = max.GetX() - min.GetX();
    const unsigned int y_range = max.GetY() - min.GetY();
    cells = new Cell *[x_range];

    for (unsigned int i = 0; i < x_range; i++) {
        cells[i] = new Cell[y_range];
    }
    unsigned int x = min.GetX(), y = min.GetY();
    for (unsigned int i = 0; i < x_range; i++) {
        for (unsigned int j = 0; j < y_range; j++) {
            cells[i][j].SetX(x);
            cells[i][j].SetY(y);
            y++;
        }
        x++;
    }
}

void Forest::FreeData() const {
    unsigned int x_range = maxSize.GetX() - minSize.GetX();
    for (unsigned int i = 0; i < x_range; i++) {
        delete[] cells[i];
    }
    delete[] cells;
}

Forest::~Forest() {
    FreeData();
}

// Forest::Forest(const Forest &other)
//     : cells(new Cell *[FOREST_WIDTH]), numOfDrones(other.numOfDrones), drones(new Drone [numOfDrones]) {
//     for (unsigned int i = 0; i < FOREST_WIDTH; i++) {
//         cells[i] = new Cell[FOREST_HEIGHT];
//         for (unsigned int j = 0; j < FOREST_HEIGHT; j++) {
//             cells[i][j] = other.cells[i][j];
//         }
//     }
//
//     for (unsigned int i = 0; i < numOfDrones; i++) {
//         drones[i] = Drone(other.drones[i].GetId(), other.drones[i].GetPosition(), other.drones[i].GetVelocity() , other.drones[i].GetPersonalBest() );
//     }
// }
//
// Forest::Forest(Forest &&other) noexcept
//     : cells(other.cells), numOfDrones(other.numOfDrones), drones(other.drones) {
//     other.cells = nullptr;
//     other.numOfDrones = 0;
//     other.drones = nullptr;
// }
//
// Forest &Forest::operator=(const Forest &other) {
//     if (this == &other) {
//         return *this;
//     }
//     FreeData();
//     cells = new Cell *[FOREST_WIDTH];
//     for (unsigned int i = 0; i < FOREST_WIDTH; i++) {
//         cells[i] = new Cell[FOREST_HEIGHT];
//         for (unsigned int j = 0; j < FOREST_HEIGHT; j++) {
//             cells[i][j] = other.cells[i][j];
//         }
//     }
//     drones = new Drone [other.numOfDrones];
//     for (unsigned int i = 0; i < other.numOfDrones; i++) {
//         drones[i] = other.drones[i];
//     }
//     numOfDrones = other.numOfDrones;
//     return *this;
// }
//
// Forest &Forest::operator=(Forest &&other) noexcept {
//     if (this == &other) {
//         return *this;
//     }
//     FreeData();
//     cells = other.cells;
//     numOfDrones = other.numOfDrones;
//     drones = other.drones;
//     other.cells = nullptr;
//     other.numOfDrones = 0;
//     other.drones = nullptr;
//     return *this;
// }

unsigned int Forest::operator()(const unsigned int x, const unsigned int y) const {
    return cells[y - minSize.GetY()][x - minSize.GetX()].GetNumOfDrones();
}

void Forest::AddDroneToCell(const TDVector &coordinates) const {
    const unsigned int x = coordinates.GetX() - minSize.GetX();
    const unsigned int y = coordinates.GetY() - minSize.GetY();
    ++cells[y][x];
}

void Forest::RemoveDroneFromCell(const TDVector &coordinates) const {
    const unsigned int x = coordinates.GetX() - minSize.GetX();
    const unsigned int y = coordinates.GetY() - minSize.GetY();
    --cells[y][x];
}

BinarySearchTree<Drone> Forest::GetDrones() const {
    return drones;
}

unsigned int Forest::GetNumOfDrones() const {
    return numOfDrones;
}

TDVector Forest::GetMinSize() const {
    return minSize;
}

TDVector Forest::GetMaxSize() const {
    return maxSize;
}
