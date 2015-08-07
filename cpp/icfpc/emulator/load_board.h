#pragma once

#include "common/board.h"
#include <folly/dynamic.h>

namespace NEmulator {
    NCommon::TBoard ParseBoard(folly::dynamic problem);
}
