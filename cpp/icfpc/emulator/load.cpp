#include "load.h"

using namespace folly;

TBoard LoadBoard(dynamic problem) {
    uint32_t width =  problem["width"].asInt();
    uint32_t height = problem["height"].asInt();
    dynamic jsonFilled = problem["filled"];
    fbvector<TCellPos> filled(jsonFilled.size());
    for (auto& cell : jsonFilled) {
        filled.push_back(TCellPos(cell["x"].asInt(), cell["y"].asInt()));
    }
    return TBoard(width, height, filled);
}

fbvector<TUnit> LoadUnits(dynamic problem) {
    dynamic unitsJson = problem["units"];
    fbvector<TUnit> units;
    units.reserve(unitsJson.size());
    fbvector<TCellPos> unitCells;
    for (auto& unit : unitsJson) {
        fbvector<TCellPos> members;
        for (auto& member : unit["members"]) {
            members.emplace_back(member["x"].asInt(), member["y"].asInt());
        }
        dynamic pivot = unit["pivot"];
        units.emplace_back(std::move(members), TCellPos(pivot["x"].asInt(), pivot["y"].asInt()));
    }
    return std::move(units);
}
