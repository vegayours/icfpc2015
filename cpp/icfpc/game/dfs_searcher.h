#pragma once

#include "game.h"

class TDfsSearcherPlayer : public TPlayerBase {
public:
    TDfsSearcherPlayer(const TBoard& board);
    ~TDfsSearcherPlayer() override;

    void NextUnit(const TUnit& unit) final;
    folly::fbstring Name() final;
private:
};
