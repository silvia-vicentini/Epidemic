#ifndef TEXT_HPP
#define TEXT_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../epidemic/epidemic.hpp"

namespace ep {

class Text {
 private:
  Epidemic epidemic_;

  // Window on which to draw the texts
  sf::RenderWindow& window_;

  const int T_;
  const int N_;

  // Margins between the side of the window and the graph
  const float margin_{80.f};

  // Division of the x and y axis
  const int x_partition_{8};
  const int y_partition_{6};

  // Font size for characters on axis
  const int axis_font_{20};

  // Title font size
  const int title_font_{30};

  // x and y coordinate of the title
  const float center_;
  const float title_y_{30.f};

  // x and y coordinates of the x axis
  const float x_axis_title_x_;
  const float x_axis_title_y_;

  // x and y coordinates of the y axis
  const float y_axis_title_x_{15.f};
  const float y_axis_title_y_{230.f};

  // y coordinate of all numbers on the x axis
  const float x_number_y_;

  // x coordinate of all numbers on the y axis
  const float y_number_x_{50.f};

  // y coordinate of the fors number on the y axis
  const float y_number_y_;

  // Distance between numbers on the y or x axis
  const float delta_y_;
  const float delta_x_;

  // Biggest numbers on the x and y axis
  const int max_x_val_;
  const int max_y_val_;

  // Font uset to write on window
  sf::Font font_;

  // Function to create texts
  sf::Text createText(const std::string&, const float, const float,
                      const int) const;

  // Function to converts number into texts
  std::vector<sf::Text> generateNumbers(const int, bool) const;

 public:
  // Constructor
  Text(const Epidemic&, sf::RenderWindow&);

  // Function to set the scale on x and y axis
  int nearest_multiple(const int, const int) const;

  // Graph title
  sf::Text set_Title() const;

  // x axis title
  sf::Text x_axis_name() const;

  // y axis title
  sf::Text y_axis_name() const;

  // Numbers on the x axis
  std::vector<sf::Text> x_numbers() const;

  // Numbers on the y axis
  std::vector<sf::Text> y_numbers() const;
};
}  // namespace ep
#endif
