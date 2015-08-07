#include "load_units.h"


namespace NEmulator {

using namespace folly;
using namespace NCommon;

fbvector<TUnit> LoadUnits(dynamic problem) {
    dynamic unitsJson = problem["units"];
    fbvector<TUnit> units;
    units.reserve(unitsJson.size());
    fbvector<TCellPosition> unitCells;
    for (auto& unit : unitsJson) {
        fbvector<TCellPosition> members;
        for (auto& member : unit["members"]) {
            members.emplace_back(member["x"].asInt(), member["y"].asInt());
        }
        dynamic pivot = unit["pivot"];
        units.emplace_back(std::move(members), TCellPosition(pivot["x"].asInt(), pivot["y"].asInt()));
    }
    return std::move(units);
}

}
