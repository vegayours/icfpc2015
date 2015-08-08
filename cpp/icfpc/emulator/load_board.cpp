#include "load_board.h"

using namespace folly;

TBoard ParseBoard(dynamic problem) {
    uint32_t width =  problem["width"].asInt();
    uint32_t height = problem["height"].asInt();
    dynamic jsonFilled = problem["filled"];
    fbvector<TCellPosition> filled(jsonFilled.size());
    for (auto& cell : jsonFilled) {
        filled.push_back(TCellPosition(cell["x"].asInt(), cell["y"].asInt()));
    }
    return TBoard(width, height, filled);
}
