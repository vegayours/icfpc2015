#pragma once

#include "common/board.h"
#include "common/unit.h"

#include <folly/FBString.h>
#include <folly/FBVector.h>

namespace NEmulator {

enum ECellView : char {
    Empty = '.',
    Filled = '#',
    Unit = 'o',
    Pivot = '*',
    PivotUnit = 'O'
};

using TBoardState = folly::fbvector<folly::fbstring>;

TBoardState CreateState(const NCommon::TBoard& board);

void ShowBoard(TBoardState& state, const NCommon::TBoard& board, const NCommon::TUnit* unit);

}
