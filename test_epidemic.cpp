#include "doctest.h"

#include "epidemic.hpp"
#include "state.hpp"

TEST_CASE("Testing Epidemic") {
  State s0{};
  int const N = 100;
  s0.S = N - 1;
  s0.I = 1;
  Epidemic e(s0, N);

  SUBCASE("no epidemic") {
    double const beta = 0.;
    double const gamma = 0.5;
    CHECK_THROWS(e.evolve(beta, gamma));
  }

  SUBCASE("no chance of recovery") {
    double const beta = 0.5;
    double const gamma = 0.;
    CHECK_THROWS(e.evolve(beta, gamma));
  }

  SUBCASE("beta=0.1, gamma=0.9") { // test values for beta, gamma
    double const beta = 0.1;
    double const gamma = 0.9;
    auto spread = e.evolve(beta, gamma);
    State const &s = spread[1];
    CHECK(s.S ==
          doctest::Approx(89.1).epsilon(0.5)); // test 2nd element of spread
    CHECK(s.I == doctest::Approx(10.).epsilon(0.5));
    CHECK(s.R == doctest::Approx(0.9).epsilon(0.5));
    State const &s_last = spread.back();
    CHECK(s_last.S ==
          doctest::Approx(0.0).epsilon(0.5)); // test last element of spread
    CHECK(s_last.I == doctest::Approx(0.0).epsilon(0.5));
    CHECK(s_last.R == doctest::Approx(100.0).epsilon(0.5));
  }

  SUBCASE("beta=0.4, gamma=0.1") { // test values for beta, gamma
    double const beta = 0.4;
    double const gamma = 0.1;
    auto spread = e.evolve(beta, gamma);
    State const &s = spread[1];
    CHECK(s.S ==
          doctest::Approx(59.4).epsilon(0.5)); // test 2nd element of spread
    CHECK(s.I == doctest::Approx(40.5).epsilon(0.5));
    CHECK(s.R == doctest::Approx(0.1).epsilon(0.5));
    State const &s_last = spread.back();
    CHECK(s_last.S ==
          doctest::Approx(0.0).epsilon(0.5)); // test last element of spread
    CHECK(s_last.I == doctest::Approx(0.0).epsilon(0.5));
    CHECK(s_last.R == doctest::Approx(100.0).epsilon(0.5));
  }
}