#pragma once

#include "common/unit.h"

#include <folly/FBVector.h>
#include <folly/dynamic.h>

folly::fbvector<TUnit> LoadUnits(folly::dynamic problem);
