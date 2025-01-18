#include "Forest.h"

Forest::Forest(const TDVector &min, const TDVector &max, const BinarySearchTree<Drone> &drones,
               unsigned int max_num_of_iter,
               TDVector &global_best, const TDVector &target, bool ended, const string &outputFileName): minSize(min),
    maxSize(max), drones(drones), maxNumOfIter(max_num_of_iter), globalBest(global_best), target(target), ended(ended),
    outputFileName(outputFileName) {
    const unsigned int x_range = max.GetX() - min.GetX() + 1;
    const unsigned int y_range = max.GetY() - min.GetY() + 1;
    cout << "x_range: " << x_range << " y_range: " << y_range << endl;
    cells = new Cell *[x_range];

    for (unsigned int i = 0; i < x_range; i++) {
        cells[i] = new Cell[y_range];
    }
    unsigned int x = min.GetX();
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
    drones.clear();
}

Forest::~Forest() {
    FreeData();
}

Forest::Forest(const Forest &other): minSize(other.minSize), maxSize(other.maxSize), drones(other.drones),
                                     maxNumOfIter(other.maxNumOfIter), globalBest(other.globalBest),
                                     target(other.target), ended(other.ended), outputFileName(other.outputFileName) {
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

Forest::Forest(Forest &&other) noexcept: minSize(other.minSize), maxSize(other.maxSize), drones(other.drones),
                                         maxNumOfIter(other.maxNumOfIter), globalBest(other.globalBest),
                                         target(other.target), ended(other.ended),
                                         outputFileName(other.outputFileName) {
    cells = other.cells;
    other.cells = nullptr;
}

Forest &Forest::operator=(const Forest &other) {
    if (this == &other) {
        return *this;
    }
    FreeData();

    minSize = other.minSize;
    maxSize = other.maxSize;
    drones = other.drones;
    maxNumOfIter = other.maxNumOfIter;
    globalBest = other.globalBest;
    target = other.target;
    ended = other.ended;
    outputFileName = other.outputFileName;

    const unsigned int x_range = maxSize.GetX() - minSize.GetX();
    const unsigned int y_range = maxSize.GetY() - minSize.GetY();
    cells = new Cell *[x_range];

    for (unsigned int i = 0; i < x_range; i++) {
        cells[i] = new Cell[y_range];
        for (unsigned int j = 0; j < y_range; j++) {
            cells[i][j] = other.cells[i][j];
        }
    }
    return *this;
}

Forest &Forest::operator=(Forest &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    minSize = other.minSize;
    maxSize = other.maxSize;
    drones = other.drones;
    cells = other.cells;
    other.cells = nullptr;
    maxNumOfIter = other.maxNumOfIter;
    globalBest = other.globalBest;
    target = other.target;
    ended = other.ended;
    outputFileName = other.outputFileName;
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

void Forest::PrintNode(Node<Drone> *root) const {
    cout << root->getData() << endl;
    if (root->getLeft() != nullptr) {
        PrintNode(root->getLeft());
    }
    if (root->getRight() != nullptr) {
        PrintNode(root->getRight());
    }
}

void Forest::StartSearch() {
    unsigned int num_of_iterations = 0;
    while (num_of_iterations < maxNumOfIter) {
        Node<Drone> *root = drones.GetRoot();
        AdvanceDrones(root);
        num_of_iterations++;
        if (ended) {
            break;
        }
        // drones.print();

    }
    EndSearch(num_of_iterations);
}

void Forest::AdvanceDrones(Node<Drone> *root) {
    const Cell old_cell = root->getData().GetCurrentCell();
    const TDVector old_position = root->getData().GetPosition();
    root->getData().MoveDrone(globalBest, minSize , maxSize );
    if (root->getData().GetDistanceFromTarget(target) < root->getData().GetPersonalBest() * target) {
        const TDVector drone_pos = root->getData().GetPosition();
        root->getData().SetPersonalBest(drone_pos);
    }
    const double drone_distance = root->getData().GetDistanceFromTarget(target);
    if (globalBest * target > drone_distance) {
        globalBest = root->getData().GetPosition();
    }

    // update cell information if the drone moved to a new cell
    const Cell new_cell = root->getData().GetCurrentCell();
    if (old_cell != new_cell) {
        const TDVector new_position = root->getData().GetPosition();
        RemoveDroneFromCell(old_position);
        AddDroneToCell(new_position);
    }

    // see if target was reached
    const Cell target_cell = GetTargetCell();
    if (new_cell == target_cell) {
        ended = true;
    }

    if (root->getLeft() != nullptr) {
        AdvanceDrones(root->getLeft());
    }
    if (root->getRight() != nullptr) {
        AdvanceDrones(root->getRight());
    }
}

void Forest::EndSearch(unsigned int numOfIterations) const {
    ofstream outfile(outputFileName);
    outfile << numOfIterations << "\n";
    EndSearchHelper(outfile, drones.GetRoot());
    outfile.close();
}

void Forest::EndSearchHelper(ofstream &output, Node<Drone> *node) const {
    Drone drone = node->getData();
    string drone_type = "bugalu";
    cout << typeid(drone).name();
    if (typeid(drone).name() == "SingleRotorDrone") {
        drone_type = 'S';
    } else if (typeid(drone).name() == "MultiRotorDrone") {
        drone_type = 'M';
    } else if (typeid(drone).name() == "FixedWingDrone") {
        drone_type = 'W';
    } else {
        drone_type = 'H';
    }
    output << drone_type << " ";
    output << drone.GetPosition().GetX() << " " << drone.GetPosition().GetY() << " ";
    output << "\n";
    if (node->getLeft() != nullptr) {
        EndSearchHelper(output, node->getLeft());
    }
    if (node->getRight() != nullptr) {
        EndSearchHelper(output, node->getRight());
    }
}


std::ostream &operator<<(std::ostream &os, const Forest &forest) {
    os << "min size: " << forest.minSize << " max size: " << forest.maxSize << " " << endl << "  ";
    for (unsigned int j = 0; j < forest.maxSize.GetX(); j++) {
        os << j << " ";
    }
    os << endl;
    int i = 0;
    for (unsigned int y = forest.minSize.GetY(); y < forest.maxSize.GetY(); y++) {
        os << i << " ";
        for (unsigned int x = forest.minSize.GetX(); x < forest.maxSize.GetX(); x++) {
            os << forest(x, y) << " ";
        }
        i++;
        os << endl;
    }
    return os;
}

Cell Forest::GetTargetCell() const {
    const int x = target.GetX();
    const int y = target.GetY();
    Cell cell(x, y, 0);
    return cell;
}

double Forest::FormatNumber(const double number) {
    const int temp = (int) (number * 100.0 + 0.5);
    const double result = temp / 100.0;
    return result;
}
