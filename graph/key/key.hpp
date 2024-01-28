#ifndef KEY_HPP
#define KEY_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

#include "../../epidemic/epidemic.hpp"

namespace ep {

class Key {
 private:
  // Window on which to draw the key
  sf::RenderWindow& window_;

  // Distance between the side of the window and the graph
  const float margin_{80.f};

  // Dot radius
  const float dot_radius_{4.f};

  // Font uset to write on window
  sf::Font font_;

  // y coordinate of the key
  const float y_location_;

  // x coordinate of the left end of the S segment
  const float susceptible_x_{200.f};

  // x coordinate of the left end of the I segment
  const float infectious_x_{400.f};

  // x coordinate of the left end of the R segment
  const float removed_x_{600.f};

  // Length of the segments
  const float length_{50.f};

  // Distance of the dot from the x coordinate of the left end of the segment
  const float dot_delta_{23.f};

  // y coordinate of the dots
  const float dot_y_;

  // Font sizes
  const int font_size_{20};

  // Distance from the right end of the segment to the beginning of the
  // desctription text
  const float text_delta_{70.f};

  // y coordinate of the text
  const float text_y_;

  // Function that generates the segments
  sf::VertexArray create_line(const float, const sf::Color&) const;

  // Function that generates the dots
  sf::CircleShape create_dot(const float, const sf::Color&) const;

  // Function that generates texts
  sf::Text create_text(const std::string&, const float) const;

 public:
  // Constructor
  Key(sf::RenderWindow&);

  // KEy elements
  std::vector<sf::VertexArray> key_lines() const;
  std::vector<sf::CircleShape> key_dots() const;
  std::vector<sf::Text> key_description() const;
};
}  // namespace ep
#endif