#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "epidemic.hpp"

#include "../doctest.h"

template <typename type>
bool result(ep::Population<type> p, ep::Population<type> v) {
  return p.S == doctest::Approx(v.S) && p.I == doctest::Approx(v.I) &&
         p.R == doctest::Approx(v.R);
}

TEST_CASE("Testing throws") {
  SUBCASE("beta < 0") {
    CHECK_THROWS(ep::Epidemic{-0.5, 0.6, {400, 100, 0}, 30});
  }
  SUBCASE("beta > 1.") {
    CHECK_THROWS(ep::Epidemic{1.5, 0.6, {400, 100, 0}, 30});
  }
  SUBCASE("gamma < 0") {
    CHECK_THROWS(ep::Epidemic{0.5, -0.6, {400, 100, 0}, 30});
  }
  SUBCASE("gamma > 1.") {
    CHECK_THROWS(ep::Epidemic{0.5, 1.6, {400, 100, 0}, 30});
  }
  SUBCASE("gamma > beta") {
    CHECK_THROWS(ep::Epidemic{0.5, 0.6, {400, 100, 0}, 30});
  }
  SUBCASE("S < 0") { CHECK_THROWS(ep::Epidemic{0.5, 0.3, {-400, 100, 0}, 30}); }
  SUBCASE("I < 0") { CHECK_THROWS(ep::Epidemic{0.5, 0.3, {400, -100, 0}, 30}); }
  SUBCASE("R < 0") { CHECK_THROWS(ep::Epidemic{0.5, 0.3, {400, 100, -3}, 30}); }
  SUBCASE("T < 0") { CHECK_THROWS(ep::Epidemic{0.5, 0.3, {400, 100, 0}, -30}); }
}

TEST_CASE("Testing the calculate function") {
  SUBCASE("Epidemic 1") {
    ep::Population<int> initial_population{518, 3, 0};
    ep::Epidemic epidemic(0.16, 0.156, initial_population, 1);
    const auto state = epidemic.get_simulation_double();
    CHECK(result(state[0], {518, 3, 0}));
    CHECK(result(state[1], {517.5227639, 3.009236084, 0.468}));
  }

  SUBCASE("Epidemic 2") {
    const ep::Population<int> initial_population{40392, 3728, 56};
    ep::Epidemic epidemic(0.48, 0.21, initial_population, 1);
    const auto state = epidemic.get_simulation_double();
    CHECK(result(state[0], {40392, 3728, 56}));
    CHECK(result(state[1], {38755.83873, 4581.281275, 838.88}));
  }

  SUBCASE("Epidemic 3") {
    const ep::Population<int> initial_population{227, 21, 9};
    ep::Epidemic epidemic(0.32, 0.08, initial_population, 1);
    const auto state = epidemic.get_simulation_double();
    CHECK(result(state[0], {227, 21, 9}));
    CHECK(result(state[1], {221.0644358, 25.2555642, 10.68}));
  }
}

TEST_CASE("Testing the lockdown function") {
  SUBCASE("Epidemic 1") {
    const ep::Population<int> initial_population{198, 371, 0};
    ep::Epidemic epidemic(0.2, 0.1, initial_population, 1);
    const auto state = epidemic.get_simulation_double();
    CHECK(result(state[0], {198, 371, 0}));
    CHECK(result(state[1], {198, 333.9, 37.1}));
  }

  SUBCASE("Epidemic 2") {
    const ep::Population<int> initial_population{132, 643, 7};
    ep::Epidemic epidemic(0.35, 0.12, initial_population, 1);
    const auto state = epidemic.get_simulation_double();
    CHECK(result(state[0], {132, 643, 7}));
    CHECK(result(state[1], {132, 565.84, 84.16}));
  }

  SUBCASE("Epidemic 3") {
    const ep::Population<int> initial_population{10167, 18606, 16};
    ep::Epidemic epidemic(0.71, 0.43, initial_population, 1);
    const auto state = epidemic.get_simulation_double();
    CHECK(result(state[0], {10167, 18606, 16}));
    CHECK(result(state[1], {10167, 10605.42, 8016.58}));
  }
}

TEST_CASE("Testing the get_simulation_double function") {
  SUBCASE("Epidemic 1") {
    const ep::Population<int> initial_population{997, 3, 0};
    ep::Epidemic epidemic(0.8, 0.4, initial_population, 40);
    const auto state = epidemic.get_simulation_double();
    CHECK(result(state[0], {997, 3, 0}));
    CHECK(result(state[10], {852.8286648, 70.10394161, 77.06739357}));
    CHECK(result(state[20], {271.4392924, 112.5118638, 616.0488437}));
    CHECK(result(state[30], {182.1803511, 8.149674139, 809.6699748}));
    CHECK(result(state[40], {177.819437, 0.420224319, 821.7603386}));
  }

  SUBCASE("Epidemic 2") {
    const ep::Population<int> initial_population{299, 1, 0};
    ep::Epidemic epidemic(0.8, 0.79, initial_population, 34);
    const auto state = epidemic.get_simulation_double();
    CHECK(result(state[0], {299, 1, 0}));
    CHECK(result(state[10], {291.064074, 0.977467831, 7.958458207}));
    CHECK(result(state[20], {284.1674629, 0.778635128, 15.05390198}));
    CHECK(result(state[30], {279.1772583, 0.524938992, 20.29780273}));
    CHECK(result(state[34], {277.7219318, 0.432915035, 21.84515315}));
  }

  SUBCASE("Epidemic 3") {
    const ep::Population<int> initial_population{299, 1, 0};
    ep::Epidemic epidemic(0.99, 0.01, initial_population, 100);
    const auto state = epidemic.get_simulation_double();
    CHECK(result(state[0], {299, 1, 0}));
    CHECK(result(state[8], {135.8675229, 162.0220782, 2.110398918}));
    CHECK(result(state[9], {63.22284608, 233.0465342, 3.7306197}));
    CHECK(result(state[10], {63.22284608, 230.7160689, 6.061085042}));
    CHECK(result(state[23], {63.22284608, 202.4582008, 34.31895314}));
    CHECK(result(state[24], {63.22284608, 200.4336188, 36.34353514}));
    CHECK(result(state[25], {63.22284608, 198.4292826, 38.34787133}));
    CHECK(result(state[38], {26.52706978, 210.8216434, 62.65128687}));
    CHECK(result(state[39], {26.52706978, 208.7134269, 64.7595033}));
    CHECK(result(state[40], {26.52706978, 206.6262927, 66.84663757}));
    CHECK(result(state[41], {26.52706978, 204.5600297, 68.9129005}));
    CHECK(result(state[53], {26.52706978, 181.3189157, 92.15401452}));
    CHECK(result(state[54], {26.52706978, 179.5057265, 93.96720368}));
    CHECK(result(state[55], {26.52706978, 177.7106693, 95.76226094}));
    CHECK(result(state[67], {12.59858536, 171.4485332, 115.9528814}));
    CHECK(result(state[71], {0.387348016, 176.615366, 122.997286}));
    CHECK(result(state[100], {3.7729E-10, 132.2565762, 167.7434238}));
  }
}

TEST_CASE("Testing the approx function") {
  SUBCASE("For S + I + R > N") {
    ep::Population<int> initial_population{997, 3, 0};
    ep::Epidemic epidemic(0.8, 0.4, initial_population, 40);
    const auto state = epidemic.evolution();
    CHECK(result(state[7], {943, 30, 27}));
    CHECK(result(state[17], {399, 166, 435}));
    CHECK(result(state[34], {179, 3, 818}));
    CHECK(result(state[35], {179, 2, 819}));
    CHECK(result(state[39], {178, 1, 821}));
  }

  SUBCASE("For S + I + R < N") {
    ep::Population<int> initial_population{997, 3, 0};
    ep::Epidemic epidemic(0.8, 0.4, initial_population, 40);
    const auto state = epidemic.evolution();
    CHECK(result(state[4], {981, 11, 8}));
    CHECK(result(state[14], {608, 153, 239}));
    CHECK(result(state[23], {216, 57, 727}));
    CHECK(result(state[33], {180, 3, 817}));
    CHECK(result(state[36], {179, 1, 820}));
  }
}

TEST_CASE("Testing the keep_total_constant function") {
  SUBCASE("Epidemic 1") {
    const ep::Population<int> initial_population{997, 3, 0};
    ep::Epidemic epidemic(0.8, 0.4, initial_population, 40);
    const auto state = epidemic.evolution();
    CHECK(result(state[0], {997, 3, 0}));
    CHECK(result(state[10], {853, 70, 77}));
    CHECK(result(state[20], {271, 113, 616}));
    CHECK(result(state[30], {182, 8, 810}));
    CHECK(result(state[40], {178, 0, 822}));
  }

  SUBCASE("Epidemic 2") {
    const ep::Population<int> initial_population{299, 1, 0};
    ep::Epidemic epidemic(0.8, 0.79, initial_population, 34);
    const auto state = epidemic.evolution();
    CHECK(result(state[0], {299, 1, 0}));
    CHECK(result(state[10], {291, 1, 8}));
    CHECK(result(state[20], {284, 1, 15}));
    CHECK(result(state[30], {279, 1, 20}));
    CHECK(result(state[34], {278, 0, 22}));
  }

  SUBCASE("Epidemic 3") {
    const ep::Population<int> initial_population{299, 1, 0};
    ep::Epidemic epidemic(0.99, 0.01, initial_population, 80);
    const auto state = epidemic.evolution();
    CHECK(result(state[0], {299, 1, 0}));
    CHECK(result(state[10], {63, 231, 6}));
    CHECK(result(state[20], {63, 209, 28}));
    CHECK(result(state[30], {63, 189, 48}));
    CHECK(result(state[40], {27, 207, 66}));
    CHECK(result(state[50], {27, 187, 86}));
    CHECK(result(state[60], {27, 169, 104}));
    CHECK(result(state[70], {1, 178, 121}));
    CHECK(result(state[80], {0, 162, 138}));
  }
}

TEST_CASE("Testing the print_results function") {
    const ep::Population<int> initial_population{299, 1, 0};
    ep::Epidemic epidemic(0.99, 0.01, initial_population, 655);

    // Testing this function directly printing the results to file
    epidemic.print_results();
}