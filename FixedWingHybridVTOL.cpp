#include "FixedWingHybridVTOL.h"

FixedWingHybridVTOL::FixedWingHybridVTOL(unsigned int id, const TDVector &position, const TDVector &velocity,
    const TDVector &personalBest) : Drone(id, position, velocity, personalBest), SingleRotorDrone(id, position, velocity, personalBest), FixedWingDrone(id, position, velocity, personalBest) {
}

FixedWingHybridVTOL::~FixedWingHybridVTOL() = default;

void FixedWingHybridVTOL::UpdateSpeed(const TDVector &globalBest, const TDVector &oldPosition,
    const TDVector &oldVelocity) {
    SingleRotorDrone::UpdateSpeed(globalBest, oldPosition, oldVelocity);

}
