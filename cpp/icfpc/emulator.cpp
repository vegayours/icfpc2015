#include "common/unit.h"
#include "common/rnd_gen.h"
#include "game/stupid.h"

#include "emulator/load_board.h"
#include "emulator/show_board.h"
#include "emulator/load_units.h"
#include "emulator/unit_stream.h"

#include <folly/FileUtil.h>
#include <folly/dynamic.h>
#include <folly/json.h>

#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace folly;


void RunBoard(TBoard board, TUnitStream& stream, IGameFactory& factory, int timeoutMs) {
    auto state = CreateState(board);
    TUnit unit, next;
    int totalMoves = 0;
    while(stream.Next(unit)) {
        unit = unit.PlaceToBoard(board);
        if (!board.IsValidUnit(unit)) {
            fprintf(stderr, "Unable to place next unit, game will end( %d moves )!\n", totalMoves);
            ShowBoard(state, board, nullptr);
            return;
        }
        ShowBoard(state, board, &unit);
        std::unique_ptr<IGame> game = factory.Create(board);
        std::queue<EMove> moves = game->MovesForUnit(unit, [&] (TUnit& current) {
            ShowBoard(state, board, &current);
            std::this_thread::sleep_for(std::chrono::milliseconds(timeoutMs));
        });
        totalMoves += moves.size();
        printf("Moves: ");
        while (!moves.empty()) {
            printf("%c", 'a' + moves.front());
            moves.pop();
        }
        printf("\n");
    }
    fprintf(stderr, "Unit stream end, final board (%d moves):\n", totalMoves);
    ShowBoard(state, board, nullptr);
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
    auto board = ParseBoard(problem);
    auto units = LoadUnits(problem);
    uint32_t limit = problem["sourceLength"].asInt();
    TUnitStream stream(0, 0, std::move(units));
    TStupidSolverFactory factory;
    for (auto& seed : problem["sourceSeeds"]) {
        stream.Reset(seed.asInt(), limit);
        RunBoard(board, stream, factory, timeoutMs);
    }
    return 0;
}
