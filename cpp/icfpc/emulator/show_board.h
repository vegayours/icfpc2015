#pragma once

#include "common/board.h"
#include "common/unit.h"

#include <folly/FBString.h>
#include <folly/FBVector.h>

using TBoardState = folly::fbvector<folly::fbstring>;

TBoardState CreateState(const TBoard& board);

// Pivot show is buggy (if pivot outside the board it will segfault)
void ShowBoard(TBoardState& state, const TBoard& board, const TUnit* unit = nullptr, bool showPivot = false);
