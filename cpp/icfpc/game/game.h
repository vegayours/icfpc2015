#pragma once

#include "unit_stream.h"

#include "common/unit.h"
#include "common/board.h"

#include <folly/FBString.h>
#include <folly/FBVector.h>

#include <queue>
#include <memory>


extern folly::fbvector<folly::fbstring> MovesMap;
char RandomLetter(EMove move);

struct TMove {
    EMove Move;
    char Letter;

    TMove();
    TMove(EMove move);
    TMove(EMove move, char letter);
};

struct IPlayer {
    virtual ~IPlayer() {}
    virtual void NextUnit(const TUnit& unit) = 0;
    // return true on normal move, false on lock
    virtual bool NextMove(TMove& move) = 0;
};

struct IGameClient {
    virtual ~IGameClient() {}
    virtual void OnMove(TMove move, const TUnit& unit, const TBoard& board) = 0;
    virtual void OnUnitLocked(TMove move, const TBoard&, int) = 0;
    virtual void OnUnitStreamEnd(const TBoard&) {}
    virtual void OnInitialPlacement(const TUnit&, const TBoard&) {}
    virtual void OnPlacementFailed(const TUnit&, const TBoard&) {}
    virtual void OnFinalScore(int) {}
};

struct TGame {
public:
    TGame(TBoard& board, TUnitStream& stream, IPlayer* player, IGameClient* client);
    ~TGame();

    void Run();

    int UpdateScore(const TUnit&, int linesCleared);
public:
    TBoard& Board;
    TUnit CurrentUnit;
    TUnitStream& Stream;
    IPlayer* const Player;
    IGameClient* const Client;
    int LastLinesCleared;
    int Score;
};
