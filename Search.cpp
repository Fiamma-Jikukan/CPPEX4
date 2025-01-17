#include "Search.h"



Search::Search(unsigned int max_num_of_iter, const Forest &forest,
               unsigned int global_best, const TDVector &target, bool ended,
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
    other.globalBest = 0;
}


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
    other.globalBest = 0;

    return *this;
}

void Search::StartSearch() {

    unsigned int num_of_iterations = 0;
    unsigned int num_of_drones = forest.GetNumOfDrones();
    Drone *drones = forest.GetDrones();

    while (num_of_iterations < maxNumOfIter) {
        for (unsigned int i = 0; i < num_of_drones; i++) {
            UpdateDrone(drones[i], i);
        }
        num_of_iterations++;
        if (ended) {
            break;
        }
    }
    EndSearch(num_of_iterations);
}

void Search::EndSearch(const unsigned int numOfIterations) const {
    ofstream outfile(outputFileName);
    outfile << numOfIterations << "\n";
    unsigned int num_of_drones = forest.GetNumOfDrones();
    Drone *drones = forest.GetDrones();
    for (unsigned int i = 0; i < num_of_drones; i++) {
        outfile << FormatNumber(drones[i].GetPosition().GetX()) << " " << FormatNumber(drones[i].GetPosition().GetY())
                << "\n";
    }
    outfile.close();
}

void Search::UpdateDrone(Drone &drone, const unsigned int index) {
    // get drone data before the move
    const TDVector old_position = drone.GetPosition();
    const Cell old_cell = drone.GetCurrentCell();
    const double prev_distance = drone.GetDistanceFromTarget(target);
    const Drone global_best = forest.GetGlobalBestDrone(globalBest);

    // move the drone and update speed
    const TDVector global = global_best.GetPosition();
    drone.MoveDrone(global);

    // update personal best if the drone is closer to the target
    const double new_distance = drone.GetDistanceFromTarget(target);
    if (new_distance < prev_distance) {
        drone.SetPersonalBest(drone.GetPosition());
    }

    // update global best if the drone is closest to the target so far
    const double current_best_distance = global_best.GetDistanceFromTarget(target);
    if (new_distance < current_best_distance) {
        globalBest = index;
    }

    // update cell information if the drone moved to a new cell
    const Cell new_cell = drone.GetCurrentCell();
    if (old_cell != new_cell) {
        const TDVector new_position = drone.GetPosition();
        forest.RemoveDroneFromCell(old_position);
        forest.AddDroneToCell(new_position);
    }

    // see if target was reached
    const Cell target_cell = GetTargetCell();
    if (new_cell == target_cell) {
        ended = true;
    }
}


void Search::OldUpdateSpeed(Drone &drone, const TDVector &oldPosition) const {
    const double r1 = (((double) rand()) / RAND_MAX);
    const double r2 = (((double) rand()) / RAND_MAX);

    const TDVector personal = drone.GetPersonalBest();
    const TDVector velocity = drone.GetVelocity();
    const Drone global_best = forest.GetGlobalBestDrone(globalBest);

    const TDVector global_position = global_best.GetPosition();


    const TDVector new_speed = (0.25 * velocity) + (r1 * (personal - oldPosition)) + (
                                   r2 * (global_position - oldPosition));
    drone.SetVelocity(new_speed);
}

unsigned int Search::GetGlobalBest() const {
    return globalBest;
}

TDVector Search::GetTarget() {
    return target;
}

void Search::UpdateGlobalBest(const unsigned int newGlobalBest) {
    globalBest = newGlobalBest;
}

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
