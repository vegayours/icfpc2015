#include "stub_fun.h"

#include <folly/FBString.h>

int main() {
    folly::fbstring str = "Hello";
    printf("1 + 3 = %d, so %s, folly!\n", add(1, 3), str.c_str());
}
