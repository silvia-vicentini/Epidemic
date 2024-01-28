#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "draw.hpp"

TEST_CASE("Testing the nearest_multiple function") {
  SUBCASE("T = 40 and N = 600") {
    ep::Population<int> initial_population{590, 10, 0};
    ep::Epidemic epidemic{0.8, 0.6, initial_population, 40};
    sf::RenderWindow window(sf::VideoMode(1000, 600), "");
    ep::Text text(epidemic, window);
    CHECK(text.nearest_multiple(8, 40) == 40);
    CHECK(text.nearest_multiple(6, 600) == 600);
  }
  SUBCASE("T = 38 and N = 557") {
    ep::Population<int> initial_population{550, 7, 0};
    ep::Epidemic epidemic{0.8, 0.6, initial_population, 38};
    sf::RenderWindow window(sf::VideoMode(1000, 600), "");
    ep::Text text(epidemic, window);
    CHECK(text.nearest_multiple(8, 38) == 40);
    CHECK(text.nearest_multiple(6, 557) == 558);
  }
  SUBCASE("T = 14 and N = 35") {
    ep::Population<int> initial_population{30, 5, 0};
    ep::Epidemic epidemic{0.8, 0.6, initial_population, 40};
    sf::RenderWindow window(sf::VideoMode(1000, 600), "");
    ep::Text text(epidemic, window);
    CHECK(text.nearest_multiple(8, 14) == 16);
    CHECK(text.nearest_multiple(6, 35) == 36);
  }
}

TEST_CASE("Testing the draw_graph function") {
  const ep::Population<int> initial_population{997, 1, 0};
  ep::Epidemic epidemic(0.8, 0.4, initial_population, 40);
  sf::RenderWindow window(sf::VideoMode(1000, 600), "Graph");
  ep::Draw draw{epidemic, window};

  // Testing this function directly printing the results to file
  draw.draw_graph();
}