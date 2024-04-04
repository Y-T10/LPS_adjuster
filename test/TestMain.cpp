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
    CHECK(frac(0) == 1);
    CHECK(frac(1) == 1);
    CHECK(frac(2) == 2);
    CHECK(frac(3) == 6);
    CHECK(frac(4) == 24);
    CHECK(frac(5) == 120);
}
