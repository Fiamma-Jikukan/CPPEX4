#include "Drone.h"

Drone::Drone(): id(0), position(TDVector(0, 0)), velocity(TDVector(0, 0)), personalBest(0, 0) {
}

Drone::Drone(const unsigned int id, const TDVector &position, const TDVector &velocity,
             const TDVector &personalBest) : id(id),
                                             position(position), velocity(velocity), personalBest(personalBest) {
}

Drone::~Drone() = default;

Drone::Drone(const Drone &other) : id(other.id), position(other.position), velocity(other.velocity),
                                   personalBest(other.personalBest) {
}

Drone &Drone::operator=(const Drone &other) {
    if (this == &other) {
        return *this;
    }
    id = other.id;
    position = other.position;
    velocity = other.velocity;
    personalBest = other.personalBest;
    return *this;
}

Drone::Drone(Drone &&other) noexcept
    : id(other.id),
      position(move(other.position)),
      velocity(move(other.velocity)),
      personalBest(move(other.personalBest)) {
    other.id = 0;
}

Drone &Drone::operator=(Drone &&other) noexcept {
    id = other.id;
    position = move(other.position);
    velocity = move(other.velocity);
    personalBest = move(other.personalBest);
    other.id = 0;
    return *this;
}

unsigned int Drone::GetId() const {
    return id;
}

TDVector Drone::GetPosition() const {
    return position;
}

void Drone::SetPosition(const TDVector &position) {
    this->position = position;
}

TDVector Drone::GetVelocity() const {
    return velocity;
}

void Drone::SetVelocity(const TDVector &velocity) {
    this->velocity = velocity;
}

TDVector Drone::GetPersonalBest() const {
    return personalBest;
}

void Drone::SetPersonalBest(const TDVector &personalBest) {
    this->personalBest = personalBest;
}

Cell Drone::GetCurrentCell() const {
    const int x = position.GetX();
    const int y = position.GetY();
    Cell cell(x, y, 0);
    return cell;
}


void Drone::MoveDrone(const TDVector &globalBest) {
    cout << *this;

    const TDVector old_position = position;
    const TDVector old_velocity = velocity;

    const TDVector new_position = position + velocity;
    double new_x = new_position.GetX();
    double new_y = new_position.GetY();

    UpdateSpeed(globalBest,old_position, old_velocity );


    // make sure the new position is within the limits of the forest:
    if (new_x > FOREST_WIDTH) {
        new_x = FOREST_WIDTH;
    } else if (new_x < 0) {
        new_x = 0;
    }
    position.SetX(new_x);

    if (new_y > FOREST_HEIGHT) {
        new_y = FOREST_HEIGHT;
    } else if (new_y < 0) {
        new_y = 0;
    }
    position.SetY(new_y);


}

void Drone::UpdateSpeed(const TDVector &globalBest,const TDVector &oldPosition, const TDVector &oldVelocity ) {
    const double r1 = (((double) rand()) / RAND_MAX);
    const double r2 = (((double) rand()) / RAND_MAX);

    const TDVector personal = GetPersonalBest();

    const TDVector new_speed = (0.25 * oldVelocity) + (r1 * (personal - oldPosition)) + (
                                   r2 * (globalBest - oldPosition));
    SetVelocity(new_speed);
}

bool Drone::operator<(const Drone &other) const {
    return id < other.id;
}

bool Drone::operator>(const Drone &other) const {
    return id > other.id;
}

bool Drone::operator==(const Drone &other) const {
    return id == other.id;
}

bool Drone::operator!=(const Drone &other) const {
    return id != other.id;
}

double Drone::GetDistanceFromTarget(const TDVector &target) const {
    return position * target;
    // in TDVector, the * operator is defined to calculate the distance between two sets of coordinates
}


