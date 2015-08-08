#include "stupid.h"

#include <cstdlib>

class TStupidSolver : public IGame {
public:
    TStupidSolver(const TBoard& board, bool goRight = true)
        : GoRight(goRight)
        , Board(board)
    {
    }
    ~TStupidSolver() override {}
    std::queue<EMove> MovesForUnit(const TUnit& unit) override final {
        TUnit current = unit;
        std::queue<EMove> moves;
        int defaultBudget = (Board.GetWidth() - unit.GetWidth());
        int budget = defaultBudget + rand() % (defaultBudget);
        while (true) {
            if (GoRight) {
                while (budget--) {
                    if (Board.IsValidUnit(current.MoveDownRight())) {
                        current = current.MoveDownRight();
                        moves.push(MoveDownRight);
                    }
                    else {
                        break;
                    }

                }
            }
            else {
                while(budget--) {
                    if (Board.IsValidUnit(current.MoveDownLeft())) {
                        current = current.MoveDownLeft();
                        moves.push(MoveDownLeft);
                    }
                    else {
                        break;
                    }

                }
            }
            GoRight = !GoRight;
            budget = 2 * defaultBudget - rand() %(defaultBudget);
            if (!Board.IsValidUnit(current.MoveDownLeft()) && !Board.IsValidUnit(current.MoveDownRight())) {
                moves.push(MoveDownRight);
                break;
            }
        }
        return std::move(moves);
    }
    /*
     * p
        int AvailHeight = Board.GetHeight();
        int boardWidth = Board.GetWidth() + 1;
        int unitWidth = unit.GetWidth() + 1;
        int pass = (boardWidth + unitWidth) / 2  - 1;
        int current = pass / 2 - (pass / 2) % (unitWidth / 2);
        // initial pass from center
        while (AvailHeight) {
            for (int i = 0; i < 2 * current; i++) {
                moves.push(GoRight ? MoveRightDown : MoveLeftDown);
                if (!--AvailHeight)
                    break;
            }
            GoRight = !GoRight;
            current = pass - pass % (unitWidth / 2);
        }
        */
private:
    bool GoRight;
    const TBoard& Board;
    int UnitWidth;
};

TStupidSolverFactory::TStupidSolverFactory()
    : GoRight(::rand() % 2)
{
}

TStupidSolverFactory::~TStupidSolverFactory()
{
}

std::unique_ptr<IGame> TStupidSolverFactory::Create(const TBoard& board) {
    GoRight = !GoRight;
    return std::unique_ptr<IGame>(new TStupidSolver(board, GoRight));
}
