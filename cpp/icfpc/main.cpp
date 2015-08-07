#include "stub_fun.h"

#include <folly/Range.h>
#include <folly/FBString.h>
#include <folly/Malloc.h>
#include <folly/Conv.h>

int main() {
    folly::StringPiece str = "Hello";
    printf("1 + 3 = %d, so %s, folly!\n", add(1, 3), str.start());
    printf("We are using jemalloc: %s\n", folly::to<folly::fbstring>(folly::usingJEMalloc()).c_str());
}
