#ifndef TDVECTOR_H
#define TDVECTOR_H
#include <cmath>
#include <ostream>

using namespace std;

class TDVector {
private:
    double x;
    double y;

public:
    TDVector(double x, double y);

    ~TDVector();

    TDVector(const TDVector &other);

    TDVector(TDVector &&other) noexcept;

    TDVector &operator=(const TDVector &other);

    TDVector &operator=(TDVector &&other) noexcept;

    double GetX() const;

    double GetY() const;

    void SetX(double x);

    void SetY(double y);

    TDVector operator+(const TDVector &other) const;

    TDVector operator-(const TDVector &other) const;

    friend TDVector operator*(double scalar, const TDVector &vec);

    friend double operator*(const TDVector &vec1, const TDVector &vec2); // returns distance between 2 coordinates

    friend bool operator==(const TDVector &lhs, const TDVector &rhs);

    friend bool operator!=(const TDVector &lhs, const TDVector &rhs);

    friend ostream &operator<<(ostream &os, const TDVector &vec) {
        os << "( " << vec.GetX() << " , " << vec.GetY() << " )";
        return os;
    }
};


#endif //TDVECTOR_H
