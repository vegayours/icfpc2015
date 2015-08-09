#include "stupid.h"

#include <cstdlib>

TStupidGamePlayer::TStupidGamePlayer(const TBoard& board, bool startFromRight)
    : TPlayerBase(board)
    , GoRight(startFromRight)
{
}

TStupidGamePlayer::~TStupidGamePlayer()
{
}

folly::fbstring TStupidGamePlayer::Name() {
    return "stupid_refactored";
}

void TStupidGamePlayer::NextUnit(const TUnit& unit) {
    assert(Moves.empty());

    int defaultBudget = Board.Width - unit.Width;
    int budget = defaultBudget + rand() % (defaultBudget);
    TMove nextMove;
    TUnit next, current = unit;
    while (true) {
        while (budget--) {
            nextMove = TMove(GoRight ? MoveDownRight : MoveDownLeft);
            next = current.ApplyMove(nextMove.Move);
            if (Board.IsValidUnit(next)) {
                current = std::move(next);
                Moves.emplace_back(std::move(nextMove));
            }
            else {
                break;
            }
        }
        GoRight = !GoRight;
        bool hasValidMove = false;
        if (!Board.IsValidUnit(current.MoveDownLeft()) && !Board.IsValidUnit(current.MoveDownRight())) {
            if (Moves.empty() || (Moves.back().Move != MoveLeft && Moves.back().Move != MoveRight)) {
                bool startLeft = rand() % 2;
                EMove moves[] = {
                    startLeft ? MoveLeft : MoveRight,
                    startLeft ? MoveRight : MoveLeft
                };
                for (auto move : moves) {
                    next = current.ApplyMove(move);
                    if (Board.IsValidUnit(next)) {
                        hasValidMove = true;
                        current = next;
                        Moves.emplace_back(move);
                        break;
                    }
                }
            }
            else if (Moves.back().Move == MoveLeft && Board.IsValidUnit(current.MoveLeft())) {
                hasValidMove = true;
                current = current.MoveLeft();
                Moves.emplace_back(MoveLeft);
            }
            else if (Moves.back().Move == MoveRight && Board.IsValidUnit(current.MoveRight())) {
                hasValidMove = true;
                current = current.MoveRight();
                Moves.emplace_back(MoveRight);
            }

            if (!hasValidMove) {
                Moves.push_back(TMove(MoveDownLeft));
                return;
            }
        }
        budget = 2 * defaultBudget - rand() %(defaultBudget);
    }
}
