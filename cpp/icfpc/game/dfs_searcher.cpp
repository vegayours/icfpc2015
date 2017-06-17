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

static int LineProfit(const TUnit& unit, const TBoard& board) {
    auto lines = board.FilledInRow;
    int cnt = 0;
    for (auto& c : unit.Cells) {
        if (++lines[c.Row] == board.Width)
            cnt++;
    }
    return cnt * (cnt + 1) * board.Width;
}

static int HolePenalty(const TUnit& unit, const TBoard& board) {
    TBoard copy(board);
    int holes = 0;
    if (copy.LockUnit(unit) == 0) {
        for (auto& c : unit.Cells) {
            if (c.Row < board.Height - 1) {
                TCellPos left(c.Row % 2 == 0 ? c.Col - 1 : c.Col, c.Row + 1);
                TCellPos right(c.Row % 2 == 1 ? c.Col + 1 : c.Col, c.Row + 1);
                if (left.Col >= 0 && copy.Cells[left.Row][left.Col] == false)
                    holes++;
                if (right.Col < board.Width && copy.Cells[right.Row][right.Col] == false)
                    holes++;
            }
        }
        return holes;
    }
    return 0;
}

int TDfsSearcherPlayer::CountProfit(const TUnit& unit) {
    int profit = unit.MaxRow() * Board.Width;
    profit += std::max(unit.MinCol(), Board.Width - 1 - unit.MaxCol());
    profit += LineProfit(unit, Board);
    profit -= HolePenalty(unit, Board);
    return profit;
}

bool TDfsSearcherPlayer::CanMakeHorisontalMove(EMove move) {
    return HorisontalDepth < kMaxHorisontalDepth && (CurrentFrame.empty() || !CurrentFrame.back().IsInverse(move));
}

folly::fbstring TDfsSearcherPlayer::Name() {
    return "stupid_dfs";
}
