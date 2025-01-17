#include "Forest.h"

Forest::Forest(Drone *drones, const unsigned int numOfDrones): cells(new Cell *[FOREST_WIDTH]), numOfDrones(numOfDrones), drones(drones) {
    for (unsigned int i = 0; i < FOREST_WIDTH; i++) {
        cells[i] = new Cell[FOREST_HEIGHT];
    }
    for (unsigned int i = 0; i < FOREST_WIDTH; i++) {
        for (unsigned int j = 0; j < FOREST_HEIGHT; j++) {
            cells[i][j].SetX(i);
            cells[i][j].SetY(j);
        }
    }
}

void Forest::FreeData() const {
    for (unsigned int i = 0; i < FOREST_WIDTH; i++) {
        delete[] cells[i];
    }
    delete[] cells;
    delete[] drones;
}

Forest::~Forest() {
    FreeData();
}

Forest::Forest(const Forest &other)
    : cells(new Cell *[FOREST_WIDTH]), numOfDrones(other.numOfDrones), drones(new Drone [numOfDrones]) {
    for (unsigned int i = 0; i < FOREST_WIDTH; i++) {
        cells[i] = new Cell[FOREST_HEIGHT];
        for (unsigned int j = 0; j < FOREST_HEIGHT; j++) {
            cells[i][j] = other.cells[i][j];
        }
    }

    for (unsigned int i = 0; i < numOfDrones; i++) {
        drones[i] = Drone(other.drones[i].GetId(), other.drones[i].GetPosition(), other.drones[i].GetVelocity() , other.drones[i].GetPersonalBest() );
    }
}

Forest::Forest(Forest &&other) noexcept
    : cells(other.cells), numOfDrones(other.numOfDrones), drones(other.drones) {
    other.cells = nullptr;
    other.numOfDrones = 0;
    other.drones = nullptr;
}

Forest &Forest::operator=(const Forest &other) {
    if (this == &other) {
        return *this;
    }
    FreeData();
    cells = new Cell *[FOREST_WIDTH];
    for (unsigned int i = 0; i < FOREST_WIDTH; i++) {
        cells[i] = new Cell[FOREST_HEIGHT];
        for (unsigned int j = 0; j < FOREST_HEIGHT; j++) {
            cells[i][j] = other.cells[i][j];
        }
    }
    drones = new Drone [other.numOfDrones];
    for (unsigned int i = 0; i < other.numOfDrones; i++) {
        drones[i] = other.drones[i];
    }
    numOfDrones = other.numOfDrones;
    return *this;
}

Forest &Forest::operator=(Forest &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    FreeData();
    cells = other.cells;
    numOfDrones = other.numOfDrones;
    drones = other.drones;
    other.cells = nullptr;
    other.numOfDrones = 0;
    other.drones = nullptr;
    return *this;
}

unsigned int Forest::operator()(const unsigned int x, const unsigned int y) const {
    return cells[y][x].GetNumOfDrones();
}

void Forest::AddDroneToCell(const TDVector& coordinates) const {
    const unsigned int x = coordinates.GetX();
    const unsigned int y = coordinates.GetY();
    ++cells[y][x];
}

void Forest::RemoveDroneFromCell(const TDVector &coordinates) const {
    const unsigned int x = coordinates.GetX();
    const unsigned int y = coordinates.GetY();
    --cells[y][x];
}

Drone * Forest::GetDrones() const {
    return drones;
}

unsigned int Forest::GetNumOfDrones() const {
    return numOfDrones;
}

Drone Forest::GetGlobalBestDrone(const unsigned int globalBest) const {
    return drones[globalBest];
}
