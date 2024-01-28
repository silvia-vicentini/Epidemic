#include "grid.hpp"

namespace ep {
// Constructor
Grid::Grid(sf::RenderWindow& window)
    : window_(window),
      bottom_y_(window_.getSize().y - margin_),
      right_x_(window_.getSize().x - margin_ + 5.f),
      delta_x_((window_.getSize().x - 2 * margin_ + 5.f) / x_partition_),
      delta_y_((window_.getSize().y - 2 * margin_) / y_partition_) {}

// Private methods
sf::VertexArray Grid::create_line(const float x1, const float y1,
                                  const float x2, const float y2,
                                  const sf::Color& color) const {
  sf::VertexArray line(sf::Lines, 2);
  line[0].position = sf::Vector2f(x1, y1);
  line[1].position = sf::Vector2f(x2, y2);
  line[0].color = line[1].color = color;
  return line;
}

std::vector<sf::VertexArray> Grid::create_lines(int count,
                                                bool isVertical) const {
  std::vector<sf::VertexArray> lines;
  const sf::Color blue(175, 238, 238);
  for (int i = 1; i < count; ++i) {
    if (isVertical) {
      sf::VertexArray line = create_line(margin_ + delta_x_ * i, bottom_y_,
                                         margin_ + delta_x_ * i, margin_, blue);
      lines.push_back(line);
    } else {
      sf::VertexArray line =
          create_line(margin_, margin_ + delta_y_ * i, right_x_,
                      margin_ + delta_y_ * i, blue);
      lines.push_back(line);
    }
  }
  return lines;
}

// Public methods
sf::VertexArray Grid::bottom_side() const {
  return create_line(margin_, bottom_y_, right_x_, bottom_y_, sf::Color::Black);
}

sf::VertexArray Grid::top_side() const {
  return create_line(margin_, bottom_y_, margin_, margin_, sf::Color::Black);
}

sf::VertexArray Grid::left_side() const {
  return create_line(margin_, margin_, right_x_, margin_, sf::Color::Black);
}

sf::VertexArray Grid::right_side() const {
  return create_line(right_x_, bottom_y_, right_x_, margin_, sf::Color::Black);
}

std::vector<sf::VertexArray> Grid::vertical_lines() const {
  return create_lines(x_partition_, true);
}

std::vector<sf::VertexArray> Grid::horizontal_lines() const {
  return create_lines(y_partition_, false);
}

}  // namespace ep