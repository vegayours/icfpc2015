#pragma once

struct TCellPos {
    int Col;
    int Row;
    TCellPos()
        : Col(0)
        , Row(0)
    {}
    TCellPos(int x, int y)
        : Col(x)
        , Row(y)
    {}
};

enum ECellView : char {
    Empty  = '.',
    Filled = '#',
    Unit = 'o',
    Pivot = '*',
    PivotUnit = 'O'
};
