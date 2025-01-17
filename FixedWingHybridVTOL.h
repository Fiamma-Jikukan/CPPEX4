#ifndef FIXEDWINGHYBRIDVTOL_H
#define FIXEDWINGHYBRIDVTOL_H
#include "SingleRotorDrone.h"
#include "FixedWingDrone.h"

class FixedWingHybridVTOL final : public SingleRotorDrone, public FixedWingDrone {
    public:
    FixedWingHybridVTOL(unsigned int id, const TDVector &position, const TDVector &velocity, const TDVector &personalBest);
    ~FixedWingHybridVTOL() override;
    void UpdateSpeed(const TDVector &globalBest, const TDVector &oldPosition, const TDVector &oldVelocity) override;
};

#endif //FIXEDWINGHYBRIDVTOL_H
