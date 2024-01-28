#ifndef CURVE_HPP
#define CURVE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <vector>

#include "../../epidemic/epidemic.hpp"

namespace ep {

class Curve {
 private:
  const Epidemic epidemic_;

  // Window on which to draw the curves
  sf::RenderWindow& window_;

  std::vector<Population<int>> population_state_;
  const int T_;
  const int N_;

  // Distance between the side of the window and the graph
  const float margin_;

  // Dot radius
  const float dot_radius_;

  // How many parts the x and y axis are divided into
  const int x_partition_;
  const int y_partition_;

  // Biggest number expressed on the x and y axis
  const int max_x_val_;
  const int max_y_val_;

  // x scale
  const float xscale_;

  // Function to set the scale on x and y axis
  int nearest_multiple(const int, const int) const;

  // Function to generate a curve
  std::vector<sf::VertexArray> generate_curve(const std::vector<int>&,
                                              const sf::Color&) const;

  // Function to generate dots of a curve
  std::vector<sf::CircleShape> generate_dots(const std::vector<int>&,
                                             const sf::Color&) const;

  // Functions to get the developmento of the number of people in S, I and R
  // separated
  std::vector<int> S_values() const;
  std::vector<int> I_values() const;
  std::vector<int> R_values() const;

 public:
  // Constructor
  Curve(const Epidemic&, sf::RenderWindow&);

  // Creating curves and dots
  std::vector<sf::VertexArray> S_curve() const;

  std::vector<sf::VertexArray> I_curve() const;

  std::vector<sf::VertexArray> R_curve() const;

  std::vector<sf::CircleShape> S_dots() const;

  std::vector<sf::CircleShape> I_dots() const;

  std::vector<sf::CircleShape> R_dots() const;
};
}  // namespace ep
#endif