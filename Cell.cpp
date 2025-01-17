#include "Cell.h"


Cell::Cell(const unsigned int x, const unsigned int y,
           const unsigned int numOfDrones): x(x), y(y), numOfDrones(numOfDrones) {
}

Cell::Cell(): x(0), y(0), numOfDrones(0) {
}

Cell::~Cell() = default;

Cell::Cell(const Cell &other)
    : x(other.x),
      y(other.y),
      numOfDrones(other.numOfDrones) {
}

Cell::Cell(Cell &&other) noexcept
    : x(other.x),
      y(other.y),
      numOfDrones(other.numOfDrones) {
    other.x = 0;
    other.y = 0;
    other.numOfDrones = 0;
}

Cell &Cell::operator=(const Cell &other) {
    if (this == &other)
        return *this;
    x = other.x;
    y = other.y;
    numOfDrones = other.numOfDrones;
    return *this;
}

Cell &Cell::operator=(Cell &&other) noexcept {
    if (this == &other)
        return *this;
    x = other.x;
    y = other.y;
    numOfDrones = other.numOfDrones;
    other.x = 0;
    other.y = 0;
    other.numOfDrones = 0;
    return *this;
}

unsigned int Cell::GetNumOfDrones() const {
    return numOfDrones;
}


unsigned int Cell::GetX() const {
    return x;
}

void Cell::SetX(const unsigned int x) {
    this->x = x;
}

unsigned int Cell::GetY() const {
    return y;
}

void Cell::SetY(const unsigned int y) {
    this->y = y;
}

Cell &Cell::operator++() {
    numOfDrones++;
    return *this;
}

Cell Cell::operator++(int) {
    Cell temp = *this;
    numOfDrones++;
    return temp;
}

Cell &Cell::operator--() {
    numOfDrones--;
    return *this;
}

Cell Cell::operator--(int) {
    Cell temp = *this;
    numOfDrones--;
    return temp;
}

bool Cell::operator==(const Cell &other) const {
    if (this == &other) {
        return true;
    }
    if (this->x == other.x && this->y == other.y) {
        return true;
    }
    return false;
}

bool Cell::operator!=(const Cell &other) const {
    if (this == &other) {
        return false;
    }
    if (this->x != other.x || this->y != other.y) {
        return true;
    }
    return false;
}
