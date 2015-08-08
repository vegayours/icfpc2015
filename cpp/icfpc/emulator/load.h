#pragma once

#include "common/board.h"
#include "common/unit.h"

#include <folly/dynamic.h>
#include <folly/FBVector.h>

TBoard LoadBoard(folly::dynamic problem);

folly::fbvector<TUnit> LoadUnits(folly::dynamic problem);
