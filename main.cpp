#include <fstream>
#include <sstream>
#include "Search.h"
#include "BinarySearchTree.h"
#include "FixedWingDrone.h"
#include "FixedWingHybridVTOL.h"
#include "MultiRotorDrone.h"
#include "SingleRotorDrone.h"
using namespace std;

bool validateConfig(const string &config);

bool validateInit(const string &init, TDVector &forestMin, TDVector &forestMax);

bool validateOutput(const string &output);

// Drone *GetDrones(const string &input2);
TDVector GetForestMin(const string &input1);

TDVector GetForestMax(const string &input1);

TDVector GetTarget(const string &input1);

unsigned int GetMaxIter(const string &input1);

unsigned int GetNumOfDrones(const string &input2);

TDVector GetGlobalBest(const string &input2, const TDVector &target);


BinarySearchTree<Drone> GetDroneTree(const string &input2);

void PlaceDrones(Forest &forest, Node<Drone> *root);

bool makeRandSeed(const string &inputRand);

bool checkDroneType(char droneType);

int main(const int argc, char **argv) {
    // validate input
    if (argc != 4 && argc != 5) {
        cerr << "Error; invalid input - args arn't right" << endl;
        return 1;
    }
    const bool validConfig = validateConfig(argv[1]);
    if (!validConfig) {
        cerr << "Error; invalid input - config is not right" << endl;
        return 1;
    }
    TDVector max = GetForestMax(argv[1]);
    TDVector min = GetForestMin(argv[1]);
    const bool validInit = validateInit(argv[2], min, max);
    const bool validOutput = validateOutput(argv[3]);
    if (argc == 5) {
        const string seedInput = argv[4];
        if (makeRandSeed(seedInput) == false) {
            srand(time(NULL));
        }
    }

    if ( !validInit || !validOutput) {
        cerr << "Error; invalid input - init is not right or output is not right :(" << endl;
        return 1;
    }

    // get data for search
    const TDVector target = GetTarget(argv[1]);
    cout << target << endl;
    const unsigned int maxIter = GetMaxIter(argv[1]);
    cout << maxIter << endl;
    BinarySearchTree<Drone> drone_tree = GetDroneTree(argv[2]);
    drone_tree.print();
    TDVector globalBest = GetGlobalBest(argv[2], target);
    cout << globalBest << endl;
    const string output = argv[3];

    Forest forest(min, max,drone_tree, maxIter, globalBest, target, false, output );
    Node<Drone> *root = drone_tree.GetRoot();
    PlaceDrones(forest, root);
    cout << forest << endl;

    // build and start search
    // Search search(maxIter, forest, globalBest, target, false, output);
    //
    // search.StartSearch();
    forest.StartSearch();
    cout << forest << endl;


    return 0;
}

bool validateConfig(const string &config) {
    ifstream config_file(config);
    if (!config_file.is_open()) {
        config_file.close();
        return false;
    }
    // validate forest size
    unsigned int forest_x_min, forest_x_max, forest_y_min, forest_y_max;
    if (!(config_file >> forest_x_min >> forest_y_min  >> forest_x_max >> forest_y_max)) {
        cout << "Error - no 4 vals in config" << endl;
        config_file.close();
        return false;
    }
    if ((forest_x_min > forest_x_max) || (forest_y_min > forest_y_max)) {
        cout << "Error - max and min do not fit" << forest_x_max << forest_x_min<< endl;
        config_file.close();
        return false;
    }
    // validate target
    double target_x, target_y;
    if (!(config_file >> target_x >> target_y)) {
        cout << "Error - no target vals in second line" << endl;
        config_file.close();
        return false;
    }
    if (target_x < forest_x_min || target_y < forest_y_min || target_x > forest_x_max || target_y > forest_y_max) {
        cout << "Error - target vals out of range" << endl;
        config_file.close();
        return false;
    }
    // validate max num of iterations
    int max_iter;
    if (!(config_file >> max_iter) || max_iter < 0) {
        config_file.close();
        return false;
    }
    double extra_line;
    if (config_file >> extra_line) {
        cout << "Error - no iteration line" << endl;
        config_file.close();
        return false;
    }
    config_file.close();
    return true;
}

bool validateInit(const string &init, TDVector &forestMin, TDVector &forestMax) {
    ifstream init_file(init);
    if (!init_file.is_open()) {
        return false;
    }
    // validate num of drones
    unsigned int num_of_drones;
    if (!(init_file >> num_of_drones)) {
        init_file.close();
        return false;
    }
    if (num_of_drones <= 0) {
        init_file.close();
        return false;
    }
    // validate drones
    for (unsigned int i = 0; i < num_of_drones; i++) {
        char type_of_drone;
        double pos_x, pos_y, vel_x, vel_y;
        if (!(init_file >> type_of_drone >> pos_x >> pos_y >> vel_x >> vel_y)) {
            init_file.close();
            return false;
        }
        if (!checkDroneType(type_of_drone)) {
            init_file.close();
            return false;
        }
        if (pos_x < forestMin.GetX() || pos_x > forestMax.GetX() || pos_y < forestMin.GetY() || pos_y > forestMax.
            GetY()) {
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

// Drone *GetDrones(const string &input2) {
//     ifstream input_drones(input2);
//     unsigned int num_of_drones;
//     input_drones >> num_of_drones;
//     Drone *drones = new Drone[num_of_drones];
//     for (unsigned int drone = 0; drone < num_of_drones; drone++) {
//         double pos_x, pos_y, vel_x, vel_y;
//         input_drones >> pos_x >> pos_y >> vel_x >> vel_y;
//         TDVector pos = TDVector(pos_x, pos_y);
//         TDVector vel = TDVector(vel_x, vel_y);
//         const Drone d(drone, pos, vel, pos);
//         drones[drone] = d;
//     }
//     input_drones.close();
//     return drones;
// }

unsigned int GetNumOfDrones(const string &input2) {
    ifstream input_drones(input2);
    unsigned int num_of_drones;
    input_drones >> num_of_drones;
    input_drones.close();
    return num_of_drones;
}

TDVector GetForestMin(const string &input1) {
    ifstream input_target(input1);
    double forest_min_x, forest_min_y, forest_max_x, forest_max_y, target_x, target_y;
    input_target >> forest_min_x >> forest_min_y >> forest_max_x >> forest_max_y >> target_x >> target_y;
    TDVector forest_min(forest_min_x, forest_min_y);
    input_target.close();
    return forest_min;
}

TDVector GetForestMax(const string &input1) {
    ifstream input_target(input1);
    double forest_min_x, forest_min_y, forest_max_x, forest_max_y, target_x, target_y;
    input_target >> forest_min_x >> forest_min_y >> forest_max_x >> forest_max_y >> target_x >> target_y;
    TDVector forest_max(forest_max_x, forest_max_y);
    input_target.close();
    return forest_max;
}

TDVector GetTarget(const string &input1) {
    ifstream input_target(input1);
    double forest_min_x, forest_min_y, forest_max_x, forest_max_y, target_x, target_y;
    input_target >> forest_min_x >> forest_min_y >> forest_max_x >> forest_max_y >> target_x >> target_y;
    TDVector target(target_x, target_y);
    input_target.close();
    return target;
}

unsigned int GetMaxIter(const string &input1) {
    ifstream input_target(input1);
    double forest_min_x, forest_min_y, forest_max_x, forest_max_y, target_x, target_y;
    unsigned int max_iter;
    input_target >> forest_min_x >> forest_min_y >> forest_max_x >> forest_max_y >> target_x >> target_y >> max_iter;
    input_target.close();
    return max_iter;
}

TDVector GetGlobalBest(const string &input2, const TDVector &target) {
    unsigned int num_of_drones;
    ifstream input_target(input2);
    input_target >> num_of_drones;
    double global_best_distance = 0.0;
    TDVector global_best(0, 0);
    for (unsigned int droneID = 0; droneID < num_of_drones; droneID++) {
        char type_of_drone;
        double pos_x, pos_y, vel_x, vel_y;
        input_target >> type_of_drone >> pos_x >> pos_y >> vel_x >> vel_y;
        TDVector pos = TDVector(pos_x, pos_y);
        const double current_distance = pos * target;
        if (droneID == 0 || current_distance < global_best_distance) {
            global_best_distance = current_distance;
            global_best = pos;
        }
    }
    input_target.close();
    return global_best;
}


BinarySearchTree<Drone> GetDroneTree(const string &input2) {
    BinarySearchTree<Drone> *tree = new BinarySearchTree<Drone>();
    unsigned int num_of_drones;
    ifstream input_target(input2);
    input_target >> num_of_drones;
    for (unsigned int droneID = 0; droneID < num_of_drones; droneID++) {
        char type_of_drone;
        double pos_x, pos_y, vel_x, vel_y;
        input_target >> type_of_drone >> pos_x >> pos_y >> vel_x >> vel_y;
        TDVector pos = TDVector(pos_x, pos_y);
        TDVector vel = TDVector(vel_x, vel_y);
        Drone *drone;
        if (type_of_drone == 'S') {
           drone = new SingleRotorDrone(droneID, pos, vel, pos);
        } else if (type_of_drone == 'M') {
            drone = new MultiRotorDrone(droneID, pos, vel, pos);
        } else if (type_of_drone == 'W') {
           drone = new FixedWingDrone(droneID, pos, vel, pos);
        } else if (type_of_drone == 'H') {
           drone = new FixedWingHybridVTOL(droneID, pos, vel, pos);
        }
        tree->insert(*drone);
    }
    return *tree;
}

bool makeRandSeed(const string &inputRand) {
    istringstream input(inputRand);
    int seed;
    if (input >> seed) {
        srand(seed);
        return true;
    }
    return false;
}

bool checkDroneType(const char droneType) {
    if (droneType != 'S' && droneType != 'M' && droneType != 'W' && droneType != 'H') {
        return false;
    }
    return true;
}

void PlaceDrones(Forest &forest, Node<Drone> *root) {
    TDVector cell_coordinate = root->getData().GetPosition();
    forest.AddDroneToCell(cell_coordinate);
    if (root->getLeft() != nullptr) {
        PlaceDrones(forest, root->getLeft());
    }
    if (root->getRight() != nullptr) {
        PlaceDrones(forest, root->getRight());
    }
}
