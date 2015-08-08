#include "common/board.h"
#include "common/unit.h"

#include <queue>

namespace NGame {

enum EMove : char {
    Left = 'p',
    Right = 'b',
    LeftDown = 'a',
    RightDown = 'l'
};

class TStupidSolver {
public:
    TStupidSolver(const NCommon::TBoard& board, bool goRight)
        : GoRight(goRight)
        , Board(board)
    {
    }
    std::queue<EMove> MovesForUnit(const NCommon::TUnit& unit) {
        std::queue<EMove> moves;
        int AvailHeight = Board.GetHeight();
        int pass = Board.GetWidth() / 2 - unit.GetWidth() / 2;
        // initial pass from center
        int current = pass / 2;
        while (AvailHeight--) {
            for (int i = 0; i < 2 * current; i++) {
                moves.push(GoRight ? RightDown : LeftDown);
            }
            GoRight = !GoRight;
            current = pass;
        }
        return std::move(moves);
    }
private:
    bool GoRight;
    const NCommon::TBoard& Board;
    int UnitWidth;
};
}
