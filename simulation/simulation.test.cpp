#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "simulation.hpp"

#include "../doctest.h"

sf::RenderWindow window(sf::VideoMode(1250, 1000), "Cellular Automaton");

TEST_CASE("Testing parts_ value") {
  SUBCASE("Epidemic 1") {
    ep::Population<int> initial_population{79, 2, 0};
    ep::Epidemic epidemic(0.16, 0.156, initial_population, 15);
    ep::Simulation simulation(window, epidemic);
    CHECK(simulation.get_parts_() == 9);
  }

  SUBCASE("Epidemic 2") {
    const ep::Population<int> initial_population{7395, 85, 0};
    ep::Epidemic epidemic(0.48, 0.21, initial_population, 4);
    ep::Simulation simulation(window, epidemic);
    CHECK(simulation.get_parts_() == 87);
  }

  SUBCASE("Epidemic 3") {
    const ep::Population<int> initial_population{224, 21, 9};
    ep::Epidemic epidemic(0.32, 0.08, initial_population, 1);
    ep::Simulation simulation(window, epidemic);
    CHECK(simulation.get_parts_() == 16);
  }
}

TEST_CASE("Testing the wrapValue function") {
  const ep::Population<int> initial_population{15, 1, 0};
  ep::Epidemic epidemic(0.2, 0.1, initial_population, 1);
  ep::Simulation simulation(window, epidemic);

  SUBCASE("Cell on the left side or on the top side of the grid") {
    const int coordinate{};
    CHECK(simulation.wrapValue(coordinate - 1, simulation.get_parts_()) == 3);
    CHECK(simulation.wrapValue(coordinate, simulation.get_parts_()) == 0);
    CHECK(simulation.wrapValue(coordinate + 1, simulation.get_parts_()) == 1);
  }

  SUBCASE("Cell on the right side or on the bottom side of the grid") {
    const int coordinate{3};
    CHECK(simulation.wrapValue(coordinate - 1, simulation.get_parts_()) == 2);
    CHECK(simulation.wrapValue(coordinate, simulation.get_parts_()) == 3);
    CHECK(simulation.wrapValue(coordinate + 1, simulation.get_parts_()) == 0);
  }

  SUBCASE("Cell in the center of the grid") {
    const int coordinate{2};
    CHECK(simulation.wrapValue(coordinate - 1, simulation.get_parts_()) == 1);
    CHECK(simulation.wrapValue(coordinate, simulation.get_parts_()) == 2);
    CHECK(simulation.wrapValue(coordinate + 1, simulation.get_parts_()) == 3);
  }
}

TEST_CASE("Testing the probability function") {
  const int neighborSum{3};
  const ep::Population<int> initial_population{15, 1, 0};
  ep::Epidemic epidemic(0.4, 0.1, initial_population, 1);
  ep::Simulation simulation(window, epidemic);
  CHECK(simulation.probability(neighborSum) == doctest::Approx(0.784));
}

TEST_CASE("Testing the calculate_neighborSum function") {
  SUBCASE("The susceptible person is sorrounded by infected individuals") {
    const ep::Population<int> initial_population{1, 8, 0};
    ep::Epidemic epidemic(0.4, 0.1, initial_population, 1);
    ep::Simulation simulation(window, epidemic);
    int neighborSum{};
    const std::vector<int>& grid{1, 1, 1, 1, 0, 1, 1, 1, 1};
    CHECK(simulation.calculate_neighborSum(1, 1, neighborSum, grid) == 8);
  }

  SUBCASE("The susceptible person is not sorrounded by infected individuals") {
    const ep::Population<int> initial_population{1, 8, 0};
    ep::Epidemic epidemic(0.4, 0.1, initial_population, 1);
    ep::Simulation simulation(window, epidemic);
    int neighborSum{};
    const std::vector<int>& grid{0, 1, 3, 1, 0, 1, 2, 2, 3};
    CHECK(simulation.calculate_neighborSum(0, 0, neighborSum, grid) == 3);
  }
}

TEST_CASE("Testing the cellular_automaton function") {
  ep::Epidemic epidemic(0.5, 0.15, {27000, 50, 0}, 40);
  ep::Simulation cellular_automaton{window, epidemic};

  // Testing this function directly printing the results to file
  cellular_automaton.cellular_automaton();
}
