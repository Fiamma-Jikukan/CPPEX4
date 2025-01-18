#include "Forest.h"

Forest::Forest(const TDVector &min, const TDVector &max, const BinarySearchTree<Drone> &drones): minSize(min),
    maxSize(max), drones(drones) {
    const unsigned int x_range = max.GetX() - min.GetX();
    const unsigned int y_range = max.GetY() - min.GetY();
    cells = new Cell *[x_range];

    for (unsigned int i = 0; i < x_range; i++) {
        cells[i] = new Cell[y_range];
    }
    unsigned int x = min.GetX(), y = min.GetY();
    for (unsigned int i = 0; i < x_range; i++) {
        unsigned int y = min.GetY();
        for (unsigned int j = 0; j < y_range; j++) {
            cells[i][j].SetX(x);
            cells[i][j].SetY(y);
            y++;
        }
        x++;
    }
}

void Forest::FreeData() {
    unsigned int x_range = maxSize.GetX() - minSize.GetX();
    for (unsigned int i = 0; i < x_range; i++) {
        delete[] cells[i];
    }
    delete[] cells;
}

Forest::~Forest() {
    FreeData();
}

Forest::Forest(const Forest &other): minSize(other.minSize), maxSize(other.maxSize), drones(other.drones) {
    const unsigned int x_range = maxSize.GetX() - minSize.GetX();
    const unsigned int y_range = maxSize.GetY() - minSize.GetY();
    cells = new Cell *[x_range];

    for (unsigned int i = 0; i < x_range; i++) {
        cells[i] = new Cell[y_range];
    }
    for (unsigned int i = 0; i < x_range; i++) {
        for (unsigned int j = 0; j < y_range; j++) {
            cells[i][j] = other.cells[i][j];
        }
    }

}

Forest::Forest(Forest &&other) noexcept: minSize(other.minSize), maxSize(other.maxSize), drones(other.drones) {
    other.cells = nullptr;
}

Forest & Forest::operator=(const Forest &other) {
    if (this == &other) {
        return *this;
    }
    FreeData();

    minSize = other.minSize;
    maxSize = other.maxSize;
    drones = other.drones;

    const unsigned int x_range = maxSize.GetX() - minSize.GetX();
    const unsigned int y_range = maxSize.GetY() - minSize.GetY();
    cells = new Cell*[x_range];

    for (unsigned int i = 0; i < x_range; i++) {
        cells[i] = new Cell[y_range];
        for (unsigned int j = 0; j < y_range; j++) {
            cells[i][j] = other.cells[i][j];
        }
    }
    return *this;
}

Forest & Forest::operator=(Forest &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    minSize = other.minSize;
    maxSize = other.maxSize;
    drones = other.drones;
    cells = other.cells;
    other.cells = nullptr;
    return *this;

}


unsigned int Forest::operator()(const unsigned int x, const unsigned int y) const {
    unsigned int x_index = x - minSize.GetX(), y_index = y - minSize.GetY();
    return cells[x_index][y_index].GetNumOfDrones();
}

void Forest::AddDroneToCell(const TDVector &coordinates) const {
    const unsigned int x = coordinates.GetX() - minSize.GetX();
    const unsigned int y = coordinates.GetY() - minSize.GetY();
    ++cells[x][y];
}

void Forest::RemoveDroneFromCell(const TDVector &coordinates) const {
    const unsigned int x = coordinates.GetX() - minSize.GetX();
    const unsigned int y = coordinates.GetY() - minSize.GetY();
    --cells[x][y];
}

BinarySearchTree<Drone> Forest::GetDrones() const {
    return drones;
}

TDVector Forest::GetMinSize() const {
    return minSize;
}

TDVector Forest::GetMaxSize() const {
    return maxSize;
}

void Forest::PrintTree() const {
    Node<Drone> *node = drones.GetRoot();
    node = node->getLeft();
    PrintNode(node);
}

void Forest::PrintNode( Node<Drone> *root) const {
    cout << root->getData() << endl;
    if (root->getLeft() != nullptr) {
        PrintNode(root->getLeft());
    }
    if (root->getRight() != nullptr) {
        PrintNode(root->getRight());
    }

}

std::ostream & operator<<(std::ostream &os, const Forest &forest) {
    os << "min size: "  << forest.minSize << " max size: " << forest.maxSize << " " << endl << "  ";
    for (unsigned int j = 0; j < forest.maxSize.GetX(); j++) {
        os << j << " ";
    }
    os << endl;
    int i = 0;
    for (unsigned int y = forest.minSize.GetY(); y < forest.maxSize.GetY(); y++) {
        os << i << " ";
        for (unsigned int x = forest.minSize.GetX(); x < forest.maxSize.GetX(); x++) {
            os << forest(x,y) << " ";
        }
        i++;
        os << endl;
    }
    return os;
}
