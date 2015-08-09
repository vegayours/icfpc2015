#include "load.h"
#include "show_board.h"

#include "common/unit.h"
#include "common/rnd_gen.h"
#include "game/game.h"
#include "game/stupid.h"

#include <folly/FileUtil.h>
#include <folly/dynamic.h>
#include <folly/json.h>

#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace folly;

class TEmulatorGameClient : public IGameClient {
public:
    TEmulatorGameClient(const TBoard& board, int timeoutMs)
        : State(CreateState(board))
        , DurationMs(timeoutMs)
    {
    }
    void OnMove(TMove move, const TUnit& unit, const TBoard& board) final {
        Commands.push_back(move.Letter);
        ShowBoard(State, board, &unit);
        Wait();
    }
    void OnUnitLocked(TMove move, const TBoard& board, int score) final {
        Commands.push_back(move.Letter);
        printf("Unit locked, score: %d, commands: %s\n", score, Commands.c_str());
        Commands.clear();
        ShowBoard(State, board);
        Wait(5);
    }
    void OnUnitStreamEnd(const TBoard& board) final {
        printf("Unit stream end, final board:\n");
        ShowBoard(State, board);
        Wait();
    }
    void OnInitialPlacement(const TUnit& unit, const TBoard& board) final {
        ShowBoard(State, board, &unit);
        Wait();
    }
    void OnPlacementFailed(const TUnit&, const TBoard& board) final {
        printf("Unit placement failed, final board: \n");
        ShowBoard(State, board);
        Wait();
    }
    virtual void OnFinalScore(int score) final {
        printf("Total game score: %d\n", score);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
private:
    void Wait(int mult = 1) {
        std::this_thread::sleep_for(mult * DurationMs);
    }
private:
    TBoardState State;
    std::chrono::milliseconds DurationMs;
    fbstring Commands;
};

void RunBoard(TBoard& board, TUnitStream& stream, TPlayerBase* player, int timeoutMs) {
    TEmulatorGameClient client(board, timeoutMs);
    TGame game(board, stream, player, &client);
    game.Run();
}

int main(int argc, const char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Need more arguments: ./emulator problem.json [timeout=100]\n");
        return 1;
    }
    fbstring json;
    readFile(argv[1], json);
    int timeoutMs = argc < 3 ? 100 : to<int>(argv[2]);
    dynamic problem = parseJson(json);
    auto board = LoadBoard(problem);
    auto units = LoadUnits(problem);
    uint32_t limit = problem["sourceLength"].asInt();
    TUnitStream stream(0, 0, std::move(units));
    for (auto& seed : problem["sourceSeeds"]) {
        stream.Reset(seed.asInt(), limit);
        TBoard boardClone(board);
        TStupidGamePlayer player(boardClone);
        RunBoard(boardClone, stream, &player, timeoutMs);
    }
    return 0;
}
