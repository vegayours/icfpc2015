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

TGame::TGame(TBoard& board, TUnitStream& stream, IPlayer* player, IGameClient* client)
    : Board(board)
    , Stream(stream)
    , Player(player)
    , Client(client)
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
            return;
        }
        Client->OnInitialPlacement(CurrentUnit, Board);
        Player->NextUnit(CurrentUnit);
        TMove nextMove;
        while (Player->NextMove(nextMove)) {
            CurrentUnit = CurrentUnit.ApplyMove(nextMove.Move);
            Client->OnMove(nextMove, CurrentUnit, Board);
        }
        Board.LockUnit(CurrentUnit);
        Client->OnUnitLocked(nextMove, Board);
    }
}
