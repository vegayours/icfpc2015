#pragma once

#include "common/unit.h"

#include <folly/FBVector.h>
#include <folly/dynamic.h>

namespace NEmulator {

folly::fbvector<NCommon::TUnit> LoadUnits(folly::dynamic problem);

}
