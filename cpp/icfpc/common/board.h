#pragma once

#include <stdint.h>
#include <folly/FBVector.h>


namespace NCommon {

struct TCellPosition {
    uint32_t Column;
    uint32_t Row;
    TCellPosition()
        : Column(0)
        , Row(0)
    {}
    TCellPosition(uint32_t x, uint32_t y)
        : Column(x)
        , Row(y)
    {}
};

enum ECellState : char {
    Empty  = '.',
    Filled = '#',
    Unit = 'o',
    Pivot = '*',
    PivotUnit = 'O'
};

struct TCell {
    ECellState State;
    TCell(ECellState state = Empty)
        : State(state)
    {
    }
};

class TBoard {
public:
    using TCellData = folly::fbvector<folly::fbvector<TCell>>;

    TBoard(uint32_t width, uint32_t height, const folly::fbvector<TCellPosition>& filled = folly::fbvector<TCellPosition>())
        : Width(width)
        , Height(height)
        , Cells(height, folly::fbvector<TCell>(width))
    {
        for (const auto& pos : filled)
            Cells[pos.Row][pos.Column].State = Filled;
    }
public:
    const TCellData& CellData() const {
        return Cells;
    }
    uint32_t GetWidth() const {
         return Width;
    }
    uint32_t GetHeight() const {
        return Height;
    }
private:
    uint32_t Width;
    uint32_t Height;
    TCellData Cells;
};

} // namespace NCommon
