#include "emulator/load.h"

#include "game/unit_stream.h"
#include "game/game.h"
#include "game/stupid.h"
#include "game/dfs_searcher.h"

#include <folly/FileUtil.h>
#include <folly/json.h>


using namespace folly;

struct TSolverGameClient : public IGameClient {
public:
    ~TSolverGameClient() override {}
    void OnMove(TMove move, const TUnit&, const TBoard&) final {
        Moves.push_back(move.Letter);
    }
    void OnUnitLocked(TMove move, const TBoard&, int) final {
        Moves.push_back(move.Letter);
    }
public:
    fbstring Moves;
};


void RunBoard(TBoard& board, TUnitStream& stream, IGameClient* client)
{
    TDfsSearcherPlayer player(board);
    TGame game(board, stream, &player, client);
    game.Run();
}

int main(int argc, const char** argv) {
    if (argc < 4) {
        fprintf(stderr, "Need more arguments: ./emulator problem.json id out.json\n");
        return 1;
    }
    fbstring json;
    readFile(argv[1], json);
    dynamic problem = parseJson(json);
    auto board = LoadBoard(problem);
    auto units = LoadUnits(problem);
    uint32_t limit = problem["sourceLength"].asInt();
    TUnitStream stream(0, 0, std::move(units));
    dynamic result = {};
    for (auto& seed : problem["sourceSeeds"]) {
        TBoard boardClone(board);
        stream.Reset(seed.asInt(), limit);
        TSolverGameClient client;
        RunBoard(boardClone, stream, &client);
        assert(!client.Moves.empty());
        dynamic solution = dynamic::object()
            ("problemId", to<int>(argv[2]))
            ("seed", seed)
            ("tag", "stupid_dfs")
            ("solution", client.Moves);
        result.push_back(solution);
    }
    fbstring outJson = toPrettyJson(result);
    writeFile(outJson, argv[3]);
}
