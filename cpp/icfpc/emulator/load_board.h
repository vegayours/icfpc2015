#pragma once

#include "common/board.h"
#include <folly/dynamic.h>

TBoard ParseBoard(folly::dynamic problem);
