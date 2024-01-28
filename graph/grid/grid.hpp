#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

#include "../../epidemic/epidemic.hpp"

namespace ep {

class Grid {
 private:
  // Window on which to draw the grid
  sf::RenderWindow& window_;

  // Distance between the window side and the graph side
  const float margin_{80.f};

  // Division of the x and y axis
  const int x_partition_{8};
  const int y_partition_{6};

  // y coordinate of the points on the x axis
  const float bottom_y_;

  // x coordinate of the points on the right side of the grid
  const float right_x_;

  // Distance between two vertical lines
  const float delta_x_;

  // Distance between two horizontal lines
  const float delta_y_;

  // Function that generates a single line
  sf::VertexArray create_line(const float, const float, const float,
                              const float, const sf::Color&) const;

  // Function that generates a series of parallel lines
  std::vector<sf::VertexArray> create_lines(int, bool) const;

 public:
  // Constructor
  Grid(sf::RenderWindow&);

  // Bottom side of the grid
  sf::VertexArray bottom_side() const;

  // Top side of the grid
  sf::VertexArray top_side() const;

  // Left side of the grid
  sf::VertexArray left_side() const;

  // Right side of the grid
  sf::VertexArray right_side() const;

  // Vertical lines of teh grid
  std::vector<sf::VertexArray> vertical_lines() const;

  // Horizontal lines of the grid
  std::vector<sf::VertexArray> horizontal_lines() const;
};
}  // namespace ep
#endif
