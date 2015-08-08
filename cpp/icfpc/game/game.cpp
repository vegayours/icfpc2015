#include "game.h"

folly::fbvector<folly::fbstring> MovesMap = {
    "p'!.03",
    "bcefy2",
    "aghij4",
    "lmno 5"
};

TUnit ApplyMove(EMove move, const TUnit& unit) {
    switch (move) {
        case MoveLeft:
            return unit.MoveLeft();
        case MoveRight:
            return unit.MoveRight();
        case MoveDownLeft:
            return unit.MoveDownLeft();
        case MoveDownRight:
            return unit.MoveDownRight();
        default:
            fprintf(stderr, "Unknown move!\n");
            assert(false);
            break;
    }
    assert(false);
    return TUnit();
}
