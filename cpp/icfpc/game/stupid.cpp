#include "stupid.h"

#include <cstdlib>

enum ELastHorisontal {
    LH_None,
    LH_Left = 1,
    LH_Right = 2
};

class TStupidSolver : public IGame {
public:
    TStupidSolver(TBoard& board, bool goRight = true)
        : GoRight(goRight)
        , LastHorisontal(LH_None)
        , Board(board)
    {
    }
    ~TStupidSolver() override {}
    std::queue<EMove> MovesForUnit(const TUnit& unit, std::function<void(TUnit&)> visitor) override final {
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
                        LastHorisontal = LH_None;
                        visitor(current);
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
                        LastHorisontal = LH_None;
                        visitor(current);
                    }
                    else {
                        break;
                    }

                }
            }
            GoRight = !GoRight;
            budget = 2 * defaultBudget - rand() %(defaultBudget);
            if (!Board.IsValidUnit(current.MoveDownLeft()) && !Board.IsValidUnit(current.MoveDownRight())) {
                if (LastHorisontal == LH_None) {
                    if (Board.IsValidUnit(current.MoveLeft())) {
                        LastHorisontal = LH_Left;
                        current = current.MoveLeft();
                        moves.push(MoveLeft);
                        visitor(current);
                    }
                    else if (Board.IsValidUnit(current.MoveRight())) {
                        LastHorisontal = LH_Right;
                        current = current.MoveRight();
                        moves.push(MoveRight);
                        visitor(current);
                    }
                    else {
                        moves.push(MoveDownLeft);
                        Board.LockUnit(current);
                        break;
                    }
                }
                else if (LastHorisontal == LH_Left && Board.IsValidUnit(current.MoveLeft())) {
                    current = current.MoveLeft();
                    moves.push(MoveLeft);
                    visitor(current);
                }
                else if (LastHorisontal == LH_Right && Board.IsValidUnit(current.MoveRight())) {
                    current = current.MoveRight();
                    moves.push(MoveRight);
                    visitor(current);
                }
                else {
                    moves.push(MoveDownLeft);
                    Board.LockUnit(current);
                    break;
                }
            }
        }
        return std::move(moves);
    }
private:
    bool GoRight;
    ELastHorisontal LastHorisontal;
    TBoard& Board;
    int UnitWidth;
};

TStupidSolverFactory::TStupidSolverFactory()
    : GoRight(::rand() % 2)
{
}

TStupidSolverFactory::~TStupidSolverFactory()
{
}

std::unique_ptr<IGame> TStupidSolverFactory::Create(TBoard& board) {
    GoRight = !GoRight;
    return std::unique_ptr<IGame>(new TStupidSolver(board, GoRight));
}
