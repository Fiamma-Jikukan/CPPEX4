#ifndef CELL_H
#define CELL_H
#include <iostream>

constexpr unsigned int FOREST_WIDTH = 72;
constexpr unsigned int FOREST_HEIGHT = 42;
using namespace std;


class Cell {
private:
    unsigned int x;
    unsigned int y;
    unsigned int numOfDrones;

public:
    Cell(unsigned int x, unsigned int y, unsigned int numOfDrones);

    Cell();

    ~Cell();

    Cell(const Cell &other);

    Cell(Cell &&other) noexcept;

    Cell &operator=(const Cell &other);

    Cell &operator=(Cell &&other) noexcept;

    unsigned int GetNumOfDrones() const;


    unsigned int GetX() const;

    void SetX(unsigned int x);

    unsigned int GetY() const;

    void SetY(unsigned int y);


    Cell &operator++();

    Cell operator++(int);

    Cell &operator--();

    Cell operator--(int);

    bool operator==(const Cell &other) const;

    bool operator!=(const Cell &other) const;

    friend ostream &operator<<(ostream &os, const Cell &cell) {
        os << "(" << cell.GetX() << ", " << cell.GetY() << ")";
        return os;
    }
};


#endif //CELL_H
