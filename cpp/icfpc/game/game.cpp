#include "game.h"

folly::fbvector<folly::fbstring> MovesMap = {
    "p'!.03",
    "bcefy2",
    "aghij4",
    "lmno 5"
};

char RandomLetter(EMove move) {
    auto line = MovesMap[move];
    return line[ rand() % line.size() ];
}

TMove::TMove() {}

TMove::TMove(EMove move)
    : Move(move)
    , Letter(RandomLetter(move))
{
}

TMove::TMove(EMove move, char letter)
    : Move(move)
    , Letter(letter)
{
}

TPlayerBase::TPlayerBase(const TBoard& board)
    : Board(board)
{
}

TPlayerBase::~TPlayerBase()
{
}

bool TPlayerBase::NextMove(TMove& move) {
    assert(!Moves.empty());
    move = Moves.front();
    Moves.pop_front();
    return !Moves.empty();
}

TGame::TGame(TBoard& board, TUnitStream& stream, TPlayerBase* player, IGameClient* client)
    : Board(board)
    , Stream(stream)
    , Player(player)
    , Client(client)
    , LastLinesCleared(0)
    , Score(0)
{
}

TGame::~TGame()
{
}

void TGame::Run() {
    while (Stream.Next(CurrentUnit)) {
        CurrentUnit = CurrentUnit.PlaceToBoard(Board);
        if (!Board.IsValidUnit(CurrentUnit)) {
            Client->OnPlacementFailed(CurrentUnit, Board);
            break;
        }
        Client->OnInitialPlacement(CurrentUnit, Board);
        Player->NextUnit(CurrentUnit);
        TMove nextMove;
        while (Player->NextMove(nextMove)) {
            CurrentUnit = CurrentUnit.ApplyMove(nextMove.Move);
            Client->OnMove(nextMove, CurrentUnit, Board);
        }
        int linesCleared = Board.LockUnit(CurrentUnit);
        int score = UpdateScore(CurrentUnit, linesCleared);
        Client->OnUnitLocked(nextMove, Board, score);
    }
    Client->OnFinalScore(Score);
}

int TGame::UpdateScore(const TUnit& unit, int linesCleared) {
    int score = unit.Cells.size() + 50 * (1 + linesCleared) * linesCleared;
    if (LastLinesCleared > 1)
        score += (LastLinesCleared - 1) * score / 10;
    LastLinesCleared = linesCleared;
    Score += score;
    return score;
}
