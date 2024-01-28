#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <random>
#include <vector>

#include "../epidemic/epidemic.hpp"

namespace ep {
class Simulation {
 private:
  // Window on which to draw the cellular automaton
  sf::RenderWindow& window_;

  const Epidemic epidemic_;
  const Population<int> initial_population_;
  const double beta_;
  const double gamma_;
  const int T_;
  const int N_;

  // Number of cells in a line
  const int parts_;

  // Total number of cells in the grid
  const int N_cells_;

  // Cell length
  const int cell_length_;

  // Width of cells used in the key
  const float key_cells_width_;

  int dayCounter{};
  int SCounter{initial_population_.S};
  int ICounter{initial_population_.I};
  int RCounter{initial_population_.R};

  std::random_device rd;
  std::default_random_engine eng;

  // Font used to draw texts on window
  sf::Font font;

  // Function generating cells used in the key
  std::vector<sf::RectangleShape> key_cells() const;

  // Function generating texts used in the key
  std::vector<sf::Text> key_texts() const;

  // Function setting the number of people in each group at the beginning of
  // the epidemic
  sf::Text set_text() const;

  // Function generating the initial values of grid
  std::vector<int> display_grid_values();

  // Funtion to generate the grid
  void draw_grid(const std::vector<int>&, const sf::Vector2f&) const;

  // Function to calculate the passage from grid to gridNext
  void calculate(const std::vector<int>&,  std::vector<int>&) ;

  // Function that updates S, I or R value
  int counter(const std::vector<int>&, const int);

 public:
  // Constructor
  Simulation(sf::RenderWindow&, const Epidemic&);

  // Function that calculates how many I people sorrownd a S person
  int calculate_neighborSum(const int, const int, int,
                            const std::vector<int>&);

  // Function to calculate the probability of passing from S to I
  double probability(const int) const;

  // studying the cellulat automaton as if it was on a sphere
  int wrapValue(const int, const int) const;

  // Getter method
  int get_parts_() const;

  // Creation of the cellular automaton
  void cellular_automaton();
};
}  // namespace ep

#endif