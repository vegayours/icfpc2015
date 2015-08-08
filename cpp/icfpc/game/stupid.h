#pragma once

#include "game.h"

#include "common/board.h"
#include "common/unit.h"

#include <deque>

class TStupidGamePlayer : public IPlayer {
public:
    TStupidGamePlayer(const TBoard& board, bool startFromRight = true);
    ~TStupidGamePlayer();

    void NextUnit(const TUnit& unit) final;
    bool NextMove(TMove& move) final;

private:
    const TBoard& Board;
    std::deque<TMove> Moves;
    bool GoRight;
};
