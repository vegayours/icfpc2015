#pragma once

#include "common/board.h"
#include "common/unit.h"

#include <folly/FBString.h>
#include <folly/FBVector.h>

enum ECellView : char {
    CV_Empty = '.',
    CV_Filled = '#',
    CV_Unit = 'o',
    CV_Pivot = '*',
    CV_PivotUnit = 'O'
};

using TBoardState = folly::fbvector<folly::fbstring>;

TBoardState CreateState(const TBoard& board);

void ShowBoard(TBoardState& state, const TBoard& board, const TUnit* unit);
