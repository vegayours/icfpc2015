#include "dfs_searcher.h"

const int kMaxHorisontalDepth = 100;
const int kMaxSuccessUpdates = 1000;
const int kMaxFailUpdates = 30000;


TDfsSearcherPlayer::TDfsSearcherPlayer(const TBoard& board)
    : TPlayerBase(board)
    , CurrentFrame()
{
}

TDfsSearcherPlayer::~TDfsSearcherPlayer()
{
}

void TDfsSearcherPlayer::Reset() {
    MaxProfit = 0;
    SuccessUpdates = 0;
    FailureUpdates = 0;
    HorisontalDepth = 0;
    CurrentFrame.clear();
}
void TDfsSearcherPlayer::NextUnit(const TUnit& unit) {
    Reset();
    dfs(unit);
}

void TDfsSearcherPlayer::dfs(const TUnit& unit) {
    if (SuccessUpdates > kMaxSuccessUpdates || FailureUpdates > kMaxFailUpdates)
        return;
    bool wasLocked = false;
    TUnit next;
    for (auto move : { MoveDownLeft, MoveDownRight }) {
        next = unit.ApplyMove(move);
        if (Board.IsValidUnit(next)) {
            CurrentFrame.push_back(TMove(move));
            HorisontalDepth = 0;
            dfs(next);
            CurrentFrame.pop_back();
        }
        else if (!wasLocked) {
            UpdateProfit(unit, move);
            wasLocked = true;
        }
    }
    for (auto move : { MoveLeft, MoveRight }) {
        if (CanMakeHorisontalMove(move)) {
            next = unit.ApplyMove(move);
            if (Board.IsValidUnit(next)) {
                CurrentFrame.push_back(TMove(move));
                HorisontalDepth++;
                dfs(next);
                CurrentFrame.pop_back();
            }
            else if (!wasLocked) {
                UpdateProfit(unit, move);
                wasLocked = true;
            }
        }
    }
}

void TDfsSearcherPlayer::UpdateProfit(const TUnit& unit, EMove lockMove) {
    int profit = CountProfit(unit);
    if (profit > MaxProfit) {
        SuccessUpdates++;
        Moves = CurrentFrame;
        Moves.push_back(TMove(lockMove));
        MaxProfit = profit;
    }
    else {
         FailureUpdates++;
    }
}

int TDfsSearcherPlayer::CountProfit(const TUnit& unit) {
    int profit = unit.MinRow() * Board.Width;
    profit += std::max(unit.MinCol(), Board.Width - 1 - unit.MaxCol());
    return profit;
}

bool TDfsSearcherPlayer::CanMakeHorisontalMove(EMove move) {
    return HorisontalDepth < kMaxHorisontalDepth && (CurrentFrame.empty() || !CurrentFrame.back().IsInverse(move));
}

folly::fbstring TDfsSearcherPlayer::Name() {
    return "stupid_dfs";
}
