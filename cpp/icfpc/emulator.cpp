#include "common/unit.h"
#include "common/rnd_gen.h"
#include "game/stupid.h"

#include "emulator/load_board.h"
#include "emulator/show_board.h"
#include "emulator/load_units.h"

#include <folly/FileUtil.h>
#include <folly/dynamic.h>
#include <folly/json.h>

#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>

using namespace folly;

class TUnitStream {
public:
    TUnitStream(uint32_t seed, uint32_t limit, fbvector<NCommon::TUnit> units)
        : Rnd(seed)
        , Available(limit)
        , Units(std::move(units))
    {
    }
    bool Next(NCommon::TUnit& unit) {
        if (Available > 0) {
            size_t next = Rnd.Next() % Units.size();
            unit = Units[next];
            Available--;
            return true;
        }
        return false;
    }
    void Reset(uint32_t seed, uint32_t limit) {
        Available = limit;
        Rnd.Reset(seed);
    }
private:
    NCommon::TRndGen Rnd;
    uint32_t Available;
    fbvector<NCommon::TUnit> Units;
};

fbstring RunBoard(NCommon::TBoard board, TUnitStream& stream) {
    auto state = NEmulator::CreateState(board);
    NCommon::TUnit unit, next;
    stream.Next(unit);
    unit = unit.PlaceToBoard(board);
    NEmulator::ShowBoard(state, board, &unit);
    NGame::TStupidSolver solver(board, true);
    fbstring commands, resultCommands;
    bool hasCommand = false;
    std::queue<NGame::EMove> moves = solver.MovesForUnit(unit);

    while (!moves.empty()) {
        int c = moves.front();
        moves.pop();
        hasCommand = false;
        switch (c) {
            case '\n':
            case EOF:
                continue;
            case 'p':
                hasCommand = true;
                next = unit.MoveLeft();
                commands.push_back(c);
                break;
            case 'b':
                hasCommand = true;
                next = unit.MoveRight();
                commands.push_back(c);
                break;
            case 'a':
                hasCommand = true;
                next = unit.MoveDownLeft();
                commands.push_back(c);
                break;
            case 'l':
                hasCommand = true;
                next = unit.MoveDownRight();
                commands.push_back(c);
                break;
            default:
                fprintf(stderr, "Unknown move!\n");
                break;
        }
        if (!hasCommand)
            continue;
        if (!board.IsValidUnit(next)) {
            fprintf(stderr, "Invalid move, will lock now, unit commands: '%s'!\n", commands.c_str());
            board.LockUnit(unit);
            resultCommands.append(commands);
            commands.clear();
            if (!stream.Next(unit)) {
                fprintf(stderr, "Unit stream end, final board:\n");
                NEmulator::ShowBoard(state, board, nullptr);
                return std::move(resultCommands);
            }
            moves = solver.MovesForUnit(unit);
            unit = unit.PlaceToBoard(board);
            if (!board.IsValidUnit(unit)) {
                fprintf(stderr, "Unable to place next unit, game will end!\n");
                return std::move(resultCommands);
            }
        }
        else {
            unit = std::move(next);
        }
        NEmulator::ShowBoard(state, board, &unit);
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return "";
}

int main(int argc, const char** argv) {
    if (argc < 4) {
        fprintf(stderr, "Need more arguments: ./emulator problem.json id out.json\n");
        return 1;
    }
    fbstring json;
    readFile(argv[1], json);
    dynamic problem = parseJson(json);
    printf("%s\n", toPrettyJson(problem).c_str());
    auto board = NEmulator::ParseBoard(problem);
    auto units = NEmulator::LoadUnits(problem);
    uint32_t limit = problem["sourceLength"].asInt();
    TUnitStream stream(0, 0, std::move(units));
    dynamic result = {};
    for (auto& seed : problem["sourceSeeds"]) {
        stream.Reset(seed.asInt(), limit);
        auto commands = RunBoard(board, stream);
        assert(!commands.empty());
        dynamic solution = dynamic::object()
            ("problemId", to<int>(argv[2]))
            ("seed", seed)
            ("tag", "stupid")
            ("solution", commands);
        result.push_back(solution);
    }
    fbstring outJson = toPrettyJson(result);
    writeFile(outJson, argv[3]);
    return 0;
}
