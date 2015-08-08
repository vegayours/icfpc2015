#pragma once

#include "cell.h"
#include "unit.h"

#include <folly/FBVector.h>

struct TUnit;

struct TBoard {
public:
    using TCellData = folly::fbvector<folly::fbvector<bool>>;

    TBoard(int width, int height, const folly::fbvector<TCellPos>& filled = folly::fbvector<TCellPos>());
    ~TBoard();

    bool IsValidUnit(const TUnit& unit) const;
    void LockUnit(const TUnit& unit);

    void RemoveFilled();
    void ShiftRow(int row);
public:
    int Width;
    int Height;
    TCellData Cells;
    folly::fbvector<int> FilledInRow;
};
