#include "TDVector.h"

TDVector::TDVector(const double x, const double y): x(x), y(y) {
}

TDVector::~TDVector() = default;

TDVector::TDVector(const TDVector &other) {
    this->x = other.x;
    this->y = other.y;
}

TDVector::TDVector(TDVector &&other) noexcept : x(other.x),
                                                y(other.y) {
    other.x = 0;
    other.y = 0;
}

TDVector &TDVector::operator=(const TDVector &other) {
    if (this == &other)
        return *this;
    x = other.x;
    y = other.y;
    return *this;
}

TDVector &TDVector::operator=(TDVector &&other) noexcept {
    if (this == &other)
        return *this;
    x = other.x;
    y = other.y;
    other.x = 0;
    other.y = 0;
    return *this;
}

double TDVector::GetX() const {
    return x;
}

double TDVector::GetY() const {
    return y;
}

void TDVector::SetX(const double x) {
    this->x = x;
}

void TDVector::SetY(const double y) {
    this->y = y;
}

TDVector TDVector::operator+(const TDVector &other) const {
    return TDVector(x + other.x, y + other.y);
}

TDVector TDVector::operator-(const TDVector &other) const {
    return TDVector(x - other.x, y - other.y);
}

TDVector operator*(const double scalar, const TDVector &vec) {
    return TDVector(scalar * vec.GetX(), scalar * vec.GetY());
}

double operator*(const TDVector &vec1, const TDVector &vec2) {
    const double x = (vec1.GetX() - vec2.GetX()) * (vec1.GetX() - vec2.GetX());
    const double y = (vec1.GetY() - vec2.GetY()) * (vec1.GetY() - vec2.GetY());
    return sqrt(x + y); // returns the distance between 2 coordinates
}

bool operator==(const TDVector &lhs, const TDVector &rhs) {
    return lhs.x == rhs.x
           && lhs.y == rhs.y;
}

bool operator!=(const TDVector &lhs, const TDVector &rhs) {
    return !(lhs == rhs);
}
