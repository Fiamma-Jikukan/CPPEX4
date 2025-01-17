#include <fstream>
#include "Search.h"
using namespace std;

bool validateConfig(const string &config);

bool validateInit(const string &init);

bool validateOutput(const string &output);

Drone *GetDrones(const string &input2);

TDVector GetTarget(const string &input1);

unsigned int GetMaxIter(const string &input1);

unsigned int GetNumOfDrones(const string &input2);

unsigned int GetGlobalBest(const Drone *drones, const TDVector &target, unsigned int num_of_drones); // returns the index of the drone closest to the target


int main(const int argc, char **argv) {
    // validate input
    if (argc != 4) {
        cerr << "Error; invalid input" << endl;
        return 1;
    }
    const bool validConfig = validateConfig(argv[1]);
    const bool validInit = validateInit(argv[2]);
    const bool validOutput = validateOutput(argv[3]);
    if (!validConfig || !validInit || !validOutput) {
        cerr << "Error; invalid input" << endl;
        return 1;
    }

    // get data for search
    const TDVector target = GetTarget(argv[1]);
    const unsigned int maxIter = GetMaxIter(argv[1]);
    Drone *drones = GetDrones(argv[2]);
    const unsigned int numOfDrones = GetNumOfDrones(argv[2]);
    const unsigned int globalBest = GetGlobalBest(drones, target, numOfDrones);
    const Forest forest(drones, numOfDrones);
    for (unsigned int i = 0; i < numOfDrones; i++) {
        forest.AddDroneToCell(drones[i].GetPosition());
    }
    const string output = argv[3];

    // build and start search
    Search search(maxIter, forest, globalBest, target, false, output);
    search.StartSearch();



    return 0;
}

bool validateConfig(const string &config) {
    ifstream config_file(config);
    if (!config_file.is_open()) {
        return false;
    }
    double target_x, target_y;
    if (!(config_file >> target_x >> target_y)) {
        config_file.close();
        return false;
    }
    if (target_x < 0 || target_y < 0 || target_x > FOREST_WIDTH || target_y > FOREST_HEIGHT) {
        config_file.close();
        return false;
    }
    int max_iter;
    if (!(config_file >> max_iter) || max_iter < 0) {
        config_file.close();
        return false;
    }
    double extra_line;
    if (config_file >> extra_line) {
        config_file.close();
        return false;
    }
    config_file.close();
    return true;
}

bool validateInit(const string &init) {
    ifstream init_file(init);
    if (!init_file.is_open()) {
        return false;
    }
    unsigned int num_of_drones;
    if (!(init_file >> num_of_drones)) {
        init_file.close();
        return false;
    }
    if (num_of_drones <= 0) {
        init_file.close();
        return false;
    }
    for (unsigned int i = 0; i < num_of_drones; i++) {
        double pos_x, pos_y, vel_x, vel_y;
        if (!(init_file >> pos_x >> pos_y >> vel_x >> vel_y)) {
            init_file.close();
            return false;
        }
        if (pos_x < 0 || pos_x > FOREST_WIDTH || pos_y < 0 || pos_y > FOREST_HEIGHT) {
            init_file.close();
            return false;
        }
    }
    double extra_data;
    if (init_file >> extra_data) {
        init_file.close();
        return false;
    }
    init_file.close();
    return true;
}

bool validateOutput(const string &output) {
    ofstream output_file(output);
    if (!output_file.is_open()) {
        return false;
    }
    output_file.close();
    return true;
}

Drone *GetDrones(const string &input2) {
    ifstream input_drones(input2);
    unsigned int num_of_drones;
    input_drones >> num_of_drones;
    Drone *drones = new Drone[num_of_drones];
    for (unsigned int drone = 0; drone < num_of_drones; drone++) {
        double pos_x, pos_y, vel_x, vel_y;
        input_drones >> pos_x >> pos_y >> vel_x >> vel_y;
        TDVector pos = TDVector(pos_x, pos_y);
        TDVector vel = TDVector(vel_x, vel_y);
        const Drone d(drone, pos, vel, pos);
        drones[drone] = d;
    }
    input_drones.close();
    return drones;
}

unsigned int GetNumOfDrones(const string &input2) {
    ifstream input_drones(input2);
    unsigned int num_of_drones;
    input_drones >> num_of_drones;
    input_drones.close();
    return num_of_drones;
}

TDVector GetTarget(const string &input1) {
    ifstream input_target(input1);
    double target_x, target_y;
    input_target >> target_x >> target_y;
    TDVector target(target_x, target_y);
    input_target.close();
    return target;
}

unsigned int GetMaxIter(const string &input1) {
    ifstream input_target(input1);
    double target_x, target_y, max_iter;
    input_target >> target_x >> target_y >> max_iter;
    input_target.close();
    return max_iter;
}

unsigned int GetGlobalBest(const Drone *drones, const TDVector &target, const unsigned int num_of_drones) {
    unsigned int closest_drone_index = 0;
    double closest_distance = drones[0].GetPosition() * target; // calculates the distance between two coordinates - operator defined in TDVector
    for (unsigned int drone = 0; drone < num_of_drones; drone++) {
        const double distance = drones[drone].GetPosition() * target;
        if (distance < closest_distance) {
            closest_distance = distance;
            closest_drone_index = drone;
        }
    }
    return closest_drone_index;
}
