#include "common/unit.h"
#include "common/board.h"

#include <folly/FBString.h>
#include <folly/FBVector.h>

#include <queue>
#include <memory>

enum EMove {
    MoveLeft = 0,
    MoveRight = 1,
    MoveDownLeft = 2,
    MoveDownRight = 3,

    MoveCount
};

extern folly::fbvector<folly::fbstring> MovesMap;

class IGame {
public:
    virtual ~IGame() {}
    virtual std::queue<EMove> MovesForUnit(const TUnit& unit) = 0;
};

class IGameFactory {
public:
    virtual ~IGameFactory() {}
    virtual std::unique_ptr<IGame> Create(const TBoard& board) = 0;
};
