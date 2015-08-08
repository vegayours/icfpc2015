#include "show_board.h"

#include <folly/FBString.h>

#include <cstdio>

using namespace folly;

TBoardState CreateState(const TBoard& board) {
    return TBoardState(board.Height, fbstring(2 * board.Width - 1, ' '));
}

void ShowBoard(TBoardState& state, const TBoard& board, const TUnit* unit, bool showPivot) {
    for (int i = 0; i < board.Height; i++) {
        for (int j = 0; j < board.Width; j++) {
            //state[i][2 * j] = board.Cells[i][j] ? ECellView::Filled : ECellView::Empty;
            if (board.Cells[i][j]) {
                state[i][2 * j] = ECellView::Filled;
            }
            else {
                state[i][2 * j] = ECellView::Empty;
            }
        }
    }
    if (unit) {
        for (const auto& pos: unit->Cells) {
            state[pos.Row][2 * pos.Col] = ECellView::Unit;
        }
        if (showPivot) {
            const auto& pivot = unit->Pivot;
            state[pivot.Row][2 * pivot.Col] = (state[pivot.Row][2 * pivot.Col] == ECellView::Unit)
                ? ECellView::PivotUnit
                : ECellView::Pivot;
        }
    }

    fbstring head(2 * board.Width - 1, '=');
    printf("%s\n", head.c_str());

    for (size_t rowIndex = 0; rowIndex < state.size(); rowIndex++) {
        if (rowIndex % 2 == 1)
            printf(" ");
        printf("%s\n", state[rowIndex].c_str());
    }
}
