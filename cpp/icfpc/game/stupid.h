#pragma once

#include "game.h"

#include "common/board.h"
#include "common/unit.h"

class TStupidGamePlayer : public TPlayerBase {
public:
    TStupidGamePlayer(const TBoard& board, bool startFromRight = true);
    ~TStupidGamePlayer() override;

    void NextUnit(const TUnit& unit) final;

    folly::fbstring Name() final;

private:
    bool GoRight;
};
