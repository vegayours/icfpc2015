#include "common/unit.h"

#include "emulator/load_board.h"
#include "emulator/show_board.h"
#include "emulator/load_units.h"

#include <folly/FileUtil.h>
#include <folly/dynamic.h>
#include <folly/json.h>

#include <cstdio>

using namespace folly;

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
    auto unit = units[0].PlaceToBoard(board);
    auto state = NEmulator::CreateState(board);
    NEmulator::ShowBoard(state, board, unit);
    int c;
    while ((c = getchar()) != '/') {
        switch (c) {
            case '\n':
            case EOF:
                continue;
            case 'p':
                unit = unit.MoveLeft();
                break;
            case 'b':
                unit = unit.MoveRight();
                break;
            case 'a':
                unit = unit.MoveDownLeft();
                break;
            case 'l':
                unit = unit.MoveDownRight();
                break;
            default:
                fprintf(stderr, "Wrong move!\n");
                break;
        }
        NEmulator::ShowBoard(state, board, unit);
    }
}
