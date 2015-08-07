#pragma once

#include "cell.h"
#include "unit.h"

#include <stdint.h>
#include <cassert>
#include <folly/FBVector.h>


namespace NCommon {

struct TCell {
    ECellState State;
    TCell(ECellState state = Empty)
        : State(state)
    {
    }
};

class TUnit;

class TBoard {
public:
    using TCellData = folly::fbvector<folly::fbvector<TCell>>;

    TBoard(int width, int height, const folly::fbvector<TCellPosition>& filled = folly::fbvector<TCellPosition>());
    ~TBoard();

    bool IsValidUnit(const TUnit& unit) const;
    void LockUnit(const TUnit& unit);
public:
    const TCellData& CellData() const {
        return Cells;
    }
    int GetWidth() const {
         return Width;
    }
    int GetHeight() const {
        return Height;
    }
private:
    int Width;
    int Height;
    TCellData Cells;
};

} // namespace NCommon
