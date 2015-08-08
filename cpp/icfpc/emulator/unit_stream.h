#include "common/unit.h"
#include "common/rnd_gen.h"

#include <folly/FBVector.h>

#include <stdint.h>

class TUnitStream {
public:
    TUnitStream(uint32_t seed, uint32_t limit, folly::fbvector<TUnit> units)
        : Rnd(seed)
        , Available(limit)
        , Units(std::move(units))
    {
    }
    bool Next(TUnit& unit) {
        if (Available > 0) {
            size_t next = Rnd.Next() % Units.size();
            unit = Units[next];
            Available--;
            return true;
        }
        return false;
    }
    void Reset(uint32_t seed, uint32_t limit) {
        Available = limit;
        Rnd.Reset(seed);
    }
private:
    TRndGen Rnd;
    uint32_t Available;
    folly::fbvector<TUnit> Units;
};
