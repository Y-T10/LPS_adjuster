#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

TEST_CASE("Sample test") {
    CHECK(1+1 == 2);
    CHECK(true);
    CHECK(false);
};

const int frac(const int n, const int cur = 1) noexcept {
    if (n == 0) {
        return cur;
    }
    return frac(n - 1, n * cur);
}

TEST_CASE("Another test") {
    TestEncode(frac(0) == 1);
    TestEncode(frac(1) == 1);
    TestEncode(frac(2) == 2);
    TestEncode(frac(3) == 6);
    TestEncode(frac(4) == 24);
    TestEncode(frac(5) == 120);
}
