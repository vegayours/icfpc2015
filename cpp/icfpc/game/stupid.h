#include "game.h"

#include "common/board.h"
#include "common/unit.h"

#include <queue>

class TStupidSolverFactory : public IGameFactory {
public:
    TStupidSolverFactory();
    ~TStupidSolverFactory() override;
    std::unique_ptr<IGame> Create(const TBoard& board) override final;
private:
    bool GoRight;
};
