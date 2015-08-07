#pragma once

namespace NCommon {

struct TCellPosition {
    int Column;
    int Row;
    TCellPosition()
        : Column(0)
        , Row(0)
    {}
    TCellPosition(int x, int y)
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

}
