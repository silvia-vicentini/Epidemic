#include "key.hpp"

namespace ep {
// Constructor
Key::Key(sf::RenderWindow& window)
    : window_(window),
      y_location_(window_.getSize().y - margin_ / 2),
      dot_y_(window_.getSize().y - 43.f),
      text_y_(window_.getSize().y - 50.f) {
  font_.loadFromFile("../../Arialn.ttf");
}

const sf::Color SusceptibleColor(0, 0, 255);
const sf::Color InfectiousColor(230, 0, 0);
const sf::Color RemovedColor(20, 230, 0);

// Private methods
sf::VertexArray Key::create_line(const float x, const sf::Color& color) const {
  sf::VertexArray line(sf::Lines, 2);
  line[0].position = sf::Vector2f(x, y_location_);
  line[1].position = sf::Vector2f(x + length_, y_location_);
  line[0].color = line[1].color = color;
  return line;
}

sf::CircleShape Key::create_dot(const float x, const sf::Color& color) const {
  sf::CircleShape dot(dot_radius_);
  dot.setFillColor(color);
  dot.setPosition(x + dot_delta_, dot_y_);
  return dot;
}

sf::Text Key::create_text(const std::string& text, const float x) const {
  sf::Text desc(text, font_, font_size_);
  desc.setFillColor(sf::Color::Black);
  desc.setPosition(x + text_delta_, text_y_);
  return desc;
}

// Public methods
std::vector<sf::VertexArray> Key::key_lines() const {
  std::vector<sf::VertexArray> lines;
  lines.push_back(create_line(susceptible_x_, SusceptibleColor));
  lines.push_back(create_line(infectious_x_, InfectiousColor));
  lines.push_back(create_line(removed_x_, RemovedColor));
  return lines;
}

std::vector<sf::CircleShape> Key::key_dots() const {
  std::vector<sf::CircleShape> dots;
  dots.push_back(create_dot(susceptible_x_, SusceptibleColor));
  dots.push_back(create_dot(infectious_x_, InfectiousColor));
  dots.push_back(create_dot(removed_x_, RemovedColor));
  return dots;
}

std::vector<sf::Text> Key::key_description() const {
  std::vector<sf::Text> description;
  description.push_back(create_text("Susceptible", susceptible_x_));
  description.push_back(create_text("Infectious", infectious_x_));
  description.push_back(create_text("Removed", removed_x_));
  return description;
}

}  // namespace ep