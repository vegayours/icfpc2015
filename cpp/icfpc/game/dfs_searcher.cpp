#include "dfs_searcher.h"

TDfsSearcherPlayer::TDfsSearcherPlayer(const TBoard& board)
    : TPlayerBase(board)
{
}

TDfsSearcherPlayer::~TDfsSearcherPlayer()
{
}

void TDfsSearcherPlayer::NextUnit(const TUnit& unit) {
    (void) unit;
    assert(false);
}

folly::fbstring TDfsSearcherPlayer::Name() {
    return "dfs_sercher";
}
