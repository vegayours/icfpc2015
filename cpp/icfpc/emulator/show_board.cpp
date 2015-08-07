#include "show_board.h"

#include <folly/FBString.h>

#include <cstdio>

namespace NEmulator {
using namespace folly;
using namespace NCommon;

TBoardState CreateState(const TBoard& board) {
    return TBoardState(board.GetHeight(), fbstring(2 * board.GetWidth() - 1, ' '));
}

void ShowBoard(TBoardState& state, const TBoard& board, const TUnit* unit) {
    for (int i = 0; i < board.GetHeight(); i++) {
        for (int j = 0; j < board.GetWidth(); j++) {
            state[i][2 * j] = board.CellData()[i][j].State;
        }
    }
    if (unit) {
        for (const auto& pos: unit->GetCells()) {
            state[pos.Row][2 * pos.Column] = ECellState::Unit;
        }
        const auto& pivot = unit->GetPivot();
        state[pivot.Row][2 * pivot.Column] = (state[pivot.Row][2 * pivot.Column] == ECellState::Unit)
            ? ECellState::PivotUnit
            : ECellState::Pivot;
    }

    fbstring head(2 * board.GetWidth() - 1, '=');
    printf("%s\n", head.c_str());

    for (size_t rowIndex = 0; rowIndex < state.size(); rowIndex++) {
        if (rowIndex % 2 == 1)
            printf(" ");
        printf("%s\n", state[rowIndex].c_str());
    }
}

}
