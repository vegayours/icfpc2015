#pragma once

#include "cell.h"
#include "board.h"

#include <folly/FBVector.h>

#include <algorithm>
#include <functional>

enum EMove {
    MoveLeft = 0,
    MoveRight = 1,
    MoveDownLeft = 2,
    MoveDownRight = 3,

    MoveCount
};

struct TBoard;

struct TUnit {
public:
    TUnit();
    TUnit(folly::fbvector<TCellPos> cells, const TCellPos& pivot);
    ~TUnit();

    TUnit PlaceToBoard(const TBoard& board) const;
    TUnit ApplyMove(EMove move) const;
    TUnit MoveLeft() const;
    TUnit MoveRight() const;
    TUnit MoveDownLeft() const;
    TUnit MoveDownRight() const;

    int MinRow() const;
    int MaxRow() const;
    int MinCol() const;
    int MaxCol() const;
    int Width() const;
    int Height() const;
public:
    folly::fbvector<TCellPos> Cells;
    TCellPos Pivot;
private:

    TUnit MoveUnit(int rowDiff, int colDiff) const;

    TUnit MoveUnit(std::function<void(TCellPos& pos)> move) const;

};

