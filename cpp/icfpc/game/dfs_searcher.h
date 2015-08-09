#pragma once

#include "game.h"

class TDfsSearcherPlayer : public TPlayerBase {
public:
    TDfsSearcherPlayer(const TBoard& board);
    ~TDfsSearcherPlayer() override;

    void NextUnit(const TUnit& unit) final;
    folly::fbstring Name() final;
private:
    void Reset();
    void dfs(const TUnit& unit);
    bool CanMakeHorisontalMove(EMove move);
    void UpdateProfit(const TUnit& unit, EMove move);
    int CountProfit(const TUnit& unit);
private:
    int MaxProfit;
    int Profit;
    int SuccessUpdates;
    int FailureUpdates;
    int HorisontalDepth;
    std::deque<TMove> CurrentFrame;
};
