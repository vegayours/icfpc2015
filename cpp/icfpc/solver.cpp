#include "emulator/load_board.h"
#include "emulator/load_units.h"
#include "emulator/unit_stream.h"

#include "game/stupid.h"

#include <folly/FileUtil.h>
#include <folly/json.h>


using namespace folly;


fbstring RunBoard(TBoard board, TUnitStream& stream, IGameFactory& factory)
{
    TUnit unit, next;
    fbstring commands;
    int totalMoves = 0;
    while (stream.Next(unit)) {
        unit = unit.PlaceToBoard(board);
        if (!board.IsValidUnit(unit)) {
            //printf("Total moves: %d\n", totalMoves);
            return commands;
        }
        auto moves = factory.Create(board)->MovesForUnit(unit, [](TUnit&) {});
        while (!moves.empty()) {
            auto& line = MovesMap[moves.front()];
            commands.push_back(line[rand() % line.size()]);
            totalMoves++;
            moves.pop();
        }
    }
    //printf("Total moves: %d\n", totalMoves);
    return commands;
}

int main(int argc, const char** argv) {
    if (argc < 4) {
        fprintf(stderr, "Need more arguments: ./emulator problem.json id out.json\n");
        return 1;
    }
    fbstring json;
    readFile(argv[1], json);
    dynamic problem = parseJson(json);
    auto board = ParseBoard(problem);
    auto units = LoadUnits(problem);
    uint32_t limit = problem["sourceLength"].asInt();
    TUnitStream stream(0, 0, std::move(units));
    TStupidSolverFactory factory;
    dynamic result = {};
    for (auto& seed : problem["sourceSeeds"]) {
        stream.Reset(seed.asInt(), limit);
        auto commands = RunBoard(board, stream, factory);
        assert(!commands.empty());
        dynamic solution = dynamic::object()
            ("problemId", to<int>(argv[2]))
            ("seed", seed)
            ("tag", "hopeless_fix")
            ("solution", commands);
        result.push_back(solution);
    }
    fbstring outJson = toPrettyJson(result);
    writeFile(outJson, argv[3]);
}
