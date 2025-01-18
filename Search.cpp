#include "Search.h"


Search::Search(unsigned int max_num_of_iter,  Forest &forest,
               TDVector &global_best, const TDVector &target, bool ended,
               const string &outputFileName): maxNumOfIter(max_num_of_iter),
                                              forest(forest),
                                              globalBest(global_best),
                                              target(target),
                                              ended(ended),
                                              outputFileName(outputFileName) {
}


Search::~Search() = default;

Search::Search(const Search &other) : maxNumOfIter(other.maxNumOfIter),
                                      forest(other.forest),
                                      globalBest(other.globalBest),
                                      target(other.target),
                                      ended(other.ended),
                                      outputFileName(other.outputFileName) {
}

Search::Search(Search &&other) noexcept : maxNumOfIter(other.maxNumOfIter),
                                          forest(move(other.forest)),
                                          globalBest(other.globalBest),
                                          target(move(other.target)),
                                          ended(other.ended),
                                          outputFileName(move(other.outputFileName)) {
    other.maxNumOfIter = 0;
    other.ended = false;
}
//
//
Search &Search::operator=(const Search &other) {
    if (this == &other)
        return *this;
    maxNumOfIter = other.maxNumOfIter;
    forest = other.forest;
    globalBest = other.globalBest;
    target = other.target;
    ended = other.ended;
    outputFileName = other.outputFileName;
    return *this;
}
//
Search &Search::operator=(Search &&other) noexcept {
    if (this == &other)
        return *this;
    maxNumOfIter = other.maxNumOfIter;
    forest = move(other.forest);
    globalBest = other.globalBest;
    target = move(other.target);
    ended = other.ended;
    outputFileName = move(other.outputFileName);
    other.maxNumOfIter = 0;
    other.ended = false;

    return *this;
}

void Search::StartSearch() {
    unsigned int num_of_iterations = 0;
    const BinarySearchTree<Drone> drones = forest.GetDrones();
    TDVector forest_max = forest.GetMaxSize();
    TDVector forest_min = forest.GetMinSize();
    while (num_of_iterations < maxNumOfIter) {
        Node<Drone> *root = drones.GetRoot();
        AdvanceDrones(root, forest_max, forest_min);
        num_of_iterations++;
        if (ended) {
            break;
        }
    }
    EndSearch(num_of_iterations);
}

void Search::AdvanceDrones(Node<Drone> *root, TDVector &max, TDVector &min) {
    const Cell old_cell = root->getData().GetCurrentCell();
    const TDVector old_position = root->getData().GetPosition();
    root->getData().MoveDrone(globalBest, max, min);
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
        forest.RemoveDroneFromCell(old_position);
        forest.AddDroneToCell(new_position);
    }

    // see if target was reached
    const Cell target_cell = GetTargetCell();
    if (new_cell == target_cell) {
        ended = true;
    }

    if (root->getLeft() != nullptr) {
        AdvanceDrones(root->getLeft(), max, min);
    }
    if (root->getRight() != nullptr) {
        AdvanceDrones(root->getRight(), max, min);
    }
}

void Search::EndSearch(const unsigned int numOfIterations) const {
    ofstream outfile(outputFileName);
    outfile << numOfIterations << "\n";
    EndSearchHelper(outfile, forest.GetDrones().GetRoot());
    outfile.close();
}

void Search::EndSearchHelper(ofstream &output, Node<Drone> *node) const {
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


//
// void Search::UpdateDrone(Drone &drone, const unsigned int index) {
//     // get drone data before the move
//     const TDVector old_position = drone.GetPosition();
//     const Cell old_cell = drone.GetCurrentCell();
//     const double prev_distance = drone.GetDistanceFromTarget(target);
//     const Drone global_best = forest.GetGlobalBestDrone(globalBest);
//
//     // move the drone and update speed
//     const TDVector global = global_best.GetPosition();
//     drone.MoveDrone(global);
//
//     // update personal best if the drone is closer to the target
//     const double new_distance = drone.GetDistanceFromTarget(target);
//     if (new_distance < prev_distance) {
//         drone.SetPersonalBest(drone.GetPosition());
//     }
//
//     // update global best if the drone is closest to the target so far
//     const double current_best_distance = global_best.GetDistanceFromTarget(target);
//     if (new_distance < current_best_distance) {
//         globalBest = index;
//     }
//
//     // update cell information if the drone moved to a new cell
//     const Cell new_cell = drone.GetCurrentCell();
//     if (old_cell != new_cell) {
//         const TDVector new_position = drone.GetPosition();
//         forest.RemoveDroneFromCell(old_position);
//         forest.AddDroneToCell(new_position);
//     }
//
//     // see if target was reached
//     const Cell target_cell = GetTargetCell();
//     if (new_cell == target_cell) {
//         ended = true;
//     }
// }


TDVector Search::GetTarget() {
    return target;
}

//
// void Search::UpdateGlobalBest(const unsigned int newGlobalBest) {
//     globalBest = newGlobalBest;
// }

Cell Search::GetTargetCell() const {
    const int x = target.GetX();
    const int y = target.GetY();
    Cell cell(x, y, 0);
    return cell;
}


double Search::FormatNumber(const double number) {
    const int temp = (int) (number * 100.0 + 0.5);
    const double result = temp / 100.0;
    return result;
}
