#include "common/unit.h"
#include "common/rnd_gen.h"

#include "emulator/load_board.h"
#include "emulator/show_board.h"
#include "emulator/load_units.h"

#include <folly/FileUtil.h>
#include <folly/dynamic.h>
#include <folly/json.h>

#include <cstdio>

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

void RunBoard(NCommon::TBoard board, TUnitStream& stream) {
    auto state = NEmulator::CreateState(board);
    NCommon::TUnit unit, next;
    stream.Next(unit);
    unit = unit.PlaceToBoard(board);
    NEmulator::ShowBoard(state, board, &unit);
    int c;
    fbstring commands;
    bool hasCommand = false;
    while ((c = getchar()) != '/') {
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
            commands.clear();
            if (!stream.Next(unit)) {
                fprintf(stderr, "Unit stream end, final board:\n");
                NEmulator::ShowBoard(state, board, nullptr);
                return;
            }
            unit = unit.PlaceToBoard(board);
            if (!board.IsValidUnit(unit)) {
                fprintf(stderr, "Unable to place next unit, game will end!\n");
                return;
            }
        }
        else {
            unit = std::move(next);
        }
        NEmulator::ShowBoard(state, board, &unit);
    }
}

int main(int argc, const char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Need more arguments: ./emulator problem.json\n");
        return 1;
    }
    fbstring json;
    readFile(argv[1], json);
    dynamic problem = parseJson(json);
    printf("%s\n", toPrettyJson(problem).c_str());
    auto board = NEmulator::ParseBoard(problem);
    auto units = NEmulator::LoadUnits(problem);
    uint32_t limit = problem["sourceLength"].asInt();
    uint32_t seed = problem["sourceSeeds"][0].asInt();
    TUnitStream stream(seed, limit, std::move(units));
    RunBoard(board, stream);
    return 0;
}
